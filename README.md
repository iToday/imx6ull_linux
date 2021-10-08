# imx6ull_linux
学习linux系统移植

# FAQ

## 1.uboot编译spl异常

    /bin/sh: 1: arm-none-linux-gnueabihf-ld.bfd: not found
    scripts/Makefile.spl:512: recipe for target 'spl/u-boot-spl' failed
    make[1]: *** [spl/u-boot-spl] Error 127
    Makefile:2001: recipe for target 'spl/u-boot-spl' failed
    make: *** [spl/u-boot-spl] Error 2

## 原因分析
编译链接工具未找到，但编译工具如gcc无异常；
命令行下使用arm-none-linux-gnueabihf-ld.bfd正常如下

    u-boot-2021.10$ arm-none-linux-gnueabihf-ld.bfd -v
    GNU ld (GNU Toolchain for the A-profile Architecture 10.3-2021.07 (arm-10.29)) 2.36.1.20210621

编译环境设置使用source ./set_env.sh；
怀疑在编译spl时，编译工具设置参数丢失；
## 解决方案：
    在~/.bashrc中配置交叉编译器:
    PATH=$PATH:/home/tudou/work/code/imx6ull_linux/tools/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf/bin
