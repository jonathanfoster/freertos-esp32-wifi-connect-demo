#include <fnmatch.h>
#ifndef DEMO_WIFI_H
#define DEMO_WIFI_H

#include "iot_wifi.h"

BaseType_t demo_wifi_connect(void);

_Noreturn void demo_wifi_reconnect_task(void *args);

BaseType_t demo_wifi_reconnect_task_init();

BaseType_t demo_wifi_init(void);

#endif  /* DEMO_WIFI_H */
