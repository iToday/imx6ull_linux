#!/bin/bash

export ARCH=arm

export CROSS_COMPILE=arm-none-linux-gnueabihf-
export PATH=$PATH:../tools/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf/bin


make imx_v7_defconfig

make
