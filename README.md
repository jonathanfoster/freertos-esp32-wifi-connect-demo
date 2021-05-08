# FreeRTOS ESP32 Wi-Fi Connect Demo

This demo shows how to use [Amazon FreeRTOS](https://github.com/aws/amazon-freertos) to connect an ESP32 to Wi-Fi.

## Prerequisites

* [ESP32-DevKitC](https://www.espressif.com/en/products/devkits/esp32-devkitc/overview)
* [Python 3](https://www.python.org/downloads/)

## Getting Started

1. Change the Wi-Fi SSID and password in [src/config/demo_wifi_config.h](src/config/demo_wifi_config.h#L10).
2. Configure the CMake project and build the firmware

    ```shell
   ./scripts/configure.sh
   ./scripts/build.sh
   ```

3. Flash your device with the firmware

    ```shell
    ./scripts/flash.sh
    ```

## Cloning

This repo uses [Git Submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules) to bring in dependent components. To clone this repo, you must add the `--recurse-submodules` argument.

```shell
git clone git@github.com:jonathanfoster/freertos-esp32-wifi-connect-demo.git --recurse-submodules
```

If you have downloaded the repo without using `--recurse-submodules` argument, then you must run:

```shell
git submodule update --init --recursive
```

## Setting Up Your Development Environment

1. Setup ESP-IDF toolchain

    ```shell
    brew install cmake ninja dfu-util ccache
    ```

2. Install [USB to UART Bridge VCP Drivers](https://www.silabs.com/documents/public/software/Mac_OSX_VCP_Driver.zip)
3. Install ESP-IDF

    ```shell
    cd freertos/vendors/espressif/esp-idf
    ./install.sh
    source ./export.sh
    ```

4. Build app

    ```shell
    ./scripts/build.sh
    ```

