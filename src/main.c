#include <fnmatch.h>
#include <iot_init.h>
#include <stdlib.h>

#include "config/demo_config.h"
#include "aws_dev_mode_key_provisioning.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "iot_config.h"
#include "iot_logging_task.h"
#include "iot_system_init.h"
#include "iot_wifi.h"
#include "wifi/demo_wifi.h"

void app_main(void) {
    BaseType_t result = pdFAIL;

    xLoggingTaskInitialize(LOGGING_TASK_STACK_SIZE, LOGGING_TASK_PRIORITY, LOGGING_QUEUE_LENGTH);

    log_info("initializing system libraries");
    result = SYSTEM_Init();
    if (result != pdPASS) {
        log_error("error initializing system libraries: error code %d", result);
        return;
    }

    log_info("initializing TCP/IP stack");
    tcpip_adapter_init();

    log_info("initializing Wi-Fi");
    result = demo_wifi_init();
    if (result != pdPASS) {
        log_error("error initializing Wi-Fi: error code %d", result);
        return;
    }

    log_info("connecting to Wi-Fi access point");
    result = demo_wifi_connect();
    if (result != pdPASS) {
        log_error("error connecting to Wi-Fi access point: error code %d", result);
        return;
    }

    log_info("starting Wi-Fi reconnect task");
    result = demo_wifi_reconnect_task_init();
    if (result != pdPASS) {
        log_error("error starting Wi-Fi reconnect task: error code %d", result);
        return;
    }

    vTaskStartScheduler();
}

extern void esp_vApplicationIdleHook();
__unused void vApplicationIdleHook() { esp_vApplicationIdleHook(); }

__unused void vApplicationDaemonTaskStartupHook(void) {}

extern void esp_vApplicationTickHook();
void IRAM_ATTR vApplicationTickHook() { esp_vApplicationTickHook(); }

void vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer, StackType_t** ppxIdleTaskStackBuffer,
                                   uint32_t* pulIdleTaskStackSize) {
    static StaticTask_t idle_task_tcb;
    static StackType_t idle_task_stack[configMINIMAL_STACK_SIZE];

    *ppxIdleTaskTCBBuffer = &idle_task_tcb;
    *ppxIdleTaskStackBuffer = idle_task_stack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory(StaticTask_t** ppxTimerTaskTCBBuffer, StackType_t** ppxTimerTaskStackBuffer,
                                    uint32_t* pulTimerTaskStackSize) {
    static StaticTask_t timer_task_tcb;
    static StackType_t timer_task_stack[configTIMER_TASK_STACK_DEPTH];

    *ppxTimerTaskTCBBuffer = &timer_task_tcb;
    *ppxTimerTaskStackBuffer = timer_task_stack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
