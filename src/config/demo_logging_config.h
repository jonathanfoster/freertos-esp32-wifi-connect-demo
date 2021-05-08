#ifndef DEMO_LOGGING_CONFIG_H
#define DEMO_LOGGING_CONFIG_H

#define LOGGING_QUEUE_LENGTH 32
#define LOGGING_TASK_PRIORITY (tskIDLE_PRIORITY + 5)
#define LOGGING_TASK_STACK_SIZE (configMINIMAL_STACK_SIZE * 4)

#define LIBRARY_LOG_NAME "demo"
#define LIBRARY_LOG_LEVEL IOT_LOG_DEBUG

#include "iot_logging_setup.h"

#define log_error(...) IotLogError(__VA_ARGS__)
#define log_warn(...) IotLogWarn(__VA_ARGS__)
#define log_info(...) IotLogInfo(__VA_ARGS__)
#define log_debug(...) IotLogDebug(__VA_ARGS__)

#include "logging_stack.h"

#endif /* DEMO_LOGGING_CONFIG_H */
