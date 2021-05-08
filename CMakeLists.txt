cmake_minimum_required(VERSION 3.13)

set(IDF_PROJECT_EXECUTABLE demo)
set(AFR_BOARD espressif.esp32_devkitc CACHE INTERNAL "")

project(demo)

add_executable(
    demo
    src/config/demo_config.h
    src/config/demo_logging_config.h
    src/config/demo_wifi_config.h
    src/main.c
    src/wifi/demo_wifi.c
    src/wifi/demo_wifi.h)

include_directories(BEFORE freertos_config)
add_subdirectory(freertos)

target_link_libraries(
    demo
    PRIVATE
    AFR::backoff_algorithm
    AFR::common
    AFR::common_io
    AFR::dev_mode_key_provisioning
    AFR::logging
    AFR::pkcs11
    AFR::pkcs11_helpers
    AFR::platform
    AFR::secure_sockets
    AFR::tls
    AFR::transport_interface_secure_sockets
    AFR::utils
    AFR::wifi)
