#!/usr/bin/env bash

set -euo pipefail

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"
BUILD_DIR="$DIR/../build"

cmake --build "$BUILD_DIR"
