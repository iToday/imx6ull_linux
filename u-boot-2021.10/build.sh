#!/bin/bash

source ./set_env.sh

make distclean

make mx6ull_14x14_evk_defconfig

make
