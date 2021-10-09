#!/bin/bash

source ./set_env.sh

make distclean

make mx6ull_14x14_evk_defconfig

make

#原git仓库https://github.com/Gateworks/u-boot-imx6.git