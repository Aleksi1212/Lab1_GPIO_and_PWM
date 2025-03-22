#!/usr/bin/env bash
set -eEuo pipefail

if [ $# -eq 0 ]; then
    echo "No arguments provided. Enter build, run or clean."
    exit 1
fi

BUILD_DIR="build"

if [ "$1" == "build" ]; then
    if [ ! -d "$BUILD_DIR" ]; then
        mkdir -p "$BUILD_DIR"
    fi

    cd "$BUILD_DIR"
    cmake ..
    make -j$(nproc)

    exit 0
fi

if [ "$1" == "run" ]; then
    if [ ! -d "$BUILD_DIR" ]; then
        echo "Project not built."
        exit 1
    fi

    PROJECT_NAME=$(<project_name.txt)
    cd "$BUILD_DIR"
    openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 8000; program $PROJECT_NAME.elf verify reset exit"

    exit 0
fi

if [ "$1" == "clean" ]; then
    rm -rf "$BUILD_DIR"
    exit 0
fi