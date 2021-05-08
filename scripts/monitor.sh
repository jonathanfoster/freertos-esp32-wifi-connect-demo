#!/usr/bin/env bash

set -euo pipefail

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"

python "$DIR/../freertos/vendors/espressif/esp-idf/tools/idf.py" monitor -p /dev/cu.SLAB_USBtoUART
