#include "demo_wifi.h"

#include <string.h>

#include "../config/demo_config.h"
#include "esp_wifi.h"
#include "iot_logging_setup.h"
#include "nvs_flash.h"

static SemaphoreHandle_t wifi_reconnect_lock = NULL;
static TaskHandle_t wifi_reconnect_task = NULL;

BaseType_t demo_wifi_connect(void) {
    BaseType_t result = pdFAIL;
    WIFINetworkParams_t network_params;

    log_debug("configuring network parameters");
    const char *ssid = WIFI_SSID;
    size_t ssid_length = strlen(ssid);
    memcpy(network_params.ucSSID, ssid, ssid_length);
    network_params.ucSSIDLength = ssid_length;

    const char *password = WIFI_PASSWORD;
    size_t password_length = strlen(password);
    memcpy(network_params.xPassword.xWPA.cPassphrase, password, password_length);
    network_params.xPassword.xWPA.ucLength = password_length;
    network_params.xSecurity = eWiFiSecurityWPA2;

    log_debug("connecting to SSID %s.", ssid);
    result = WIFI_ConnectAP(&network_params);
    if (result != eWiFiSuccess) {
        log_error("error connecting to SSID %s: error code %d", ssid, result);
        return result;
    }

    return pdPASS;
}

BaseType_t demo_wifi_reconnect_task_init() {
    BaseType_t result = pdFAIL;

    wifi_reconnect_lock = xSemaphoreCreateBinary();
    result = xSemaphoreGive(wifi_reconnect_lock);
    if (result != pdPASS) {
        log_error("error releasing Wi-Fi reconnect lock: error code %d", result);
        return result;
    }

    log_debug("creating Wi-Fi reconnect task");
    result = xTaskCreate(demo_wifi_reconnect_task, WIFI_RECONNECT_TASK_NAME, WIFI_RECONNECT_TASK_STACK_SIZE, NULL,
                         WIFI_RECONNECT_TASK_PRIORITY, &wifi_reconnect_task);
    if (result != pdPASS) {
        log_error("error creating Wi-Fi connect task: error code %d", result);
        return result;
    }

    return result;
}

_Noreturn void demo_wifi_reconnect_task(void *args) {
    BaseType_t result = pdFAIL;
    TickType_t delay_ticks = pdMS_TO_TICKS(WIFI_RECONNECT_DELAY_MS);

    for (;;) {
        result = WIFI_IsConnected(NULL);
        if (result == pdTRUE) {
            vTaskDelay(delay_ticks);
            continue;
        }

        result = xSemaphoreTake(wifi_reconnect_lock, portMAX_DELAY);
        if (result != pdPASS) {
            log_error("error obtaining Wi-Fi reconnect lock");
            continue;
        }

        log_debug("reconnecting to Wi-Fi access point");
        result = demo_wifi_connect();
        if (result != pdPASS) {
            log_error("error reconnecting to Wi-Fi access point: error code %d", result);
        }

        result = xSemaphoreGive(wifi_reconnect_lock);
        if (result != pdPASS) {
            log_error("error releasing Wi-Fi reconnect lock");
        }

        vTaskDelay(delay_ticks);
    }
}

BaseType_t demo_wifi_init(void) {
    BaseType_t result = pdFAIL;

    log_debug("initializing default NVS partition");
    esp_err_t nvs_result = nvs_flash_init();
    if (nvs_result == ESP_ERR_NVS_NO_FREE_PAGES || nvs_result == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        log_error("error initializing default NVS partition: error code %d", nvs_result);
        return nvs_result;
    }

    log_debug("turning on Wi-Fi module");
    result = WIFI_On();
    if (result != eWiFiSuccess) {
        log_error("error turning on Wi-Fi module: error code %d", result);
        return result;
    }

    // FIXME: Wi-Fi must be started before calling WIFI_ConnectAP to avoid hanging
//    log_debug("starting Wi-Fi");
//    result = esp_wifi_start();
//    if (result != ESP_OK) {
//        log_error("error starting Wi-Fi: error code %d", result);
//        return result;
//    }

    return pdPASS;
}
