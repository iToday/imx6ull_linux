#!/bin/sh

export ARCH=arm
#export CROSS_COMPILE=aarch64-none-linux-gnu-
#export PATH=$PATH:/home/xu/work/code/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin 

#export CROSS_COMPILE=arm-linux-gnueabihf-
#export PATH=$PATH:/home/xu/work/code/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin

#export CROSS_COMPILE=armeb-linux-gnueabihf-
#export PATH=$PATH:/home/xu/work/code/gcc-linaro-7.5.0-2019.12-x86_64_armeb-linux-gnueabihf/bin

export CROSS_COMPILE=arm-none-linux-gnueabihf-
export PATH=$PATH:./compilation_tool/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf/bin
