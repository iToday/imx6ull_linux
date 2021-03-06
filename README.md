# imx6ull_linux
学习linux系统移植

# FAQ

## 1.uboot编译spl异常

    /bin/sh: 1: arm-none-linux-gnueabihf-ld.bfd: not found
    scripts/Makefile.spl:512: recipe for target 'spl/u-boot-spl' failed
    make[1]: *** [spl/u-boot-spl] Error 127
    Makefile:2001: recipe for target 'spl/u-boot-spl' failed
    make: *** [spl/u-boot-spl] Error 2

### 原因分析
编译链接工具未找到，但编译工具如gcc无异常；
命令行下使用arm-none-linux-gnueabihf-ld.bfd正常如下

    u-boot-2021.10$ arm-none-linux-gnueabihf-ld.bfd -v
    GNU ld (GNU Toolchain for the A-profile Architecture 10.3-2021.07 (arm-10.29)) 2.36.1.20210621

编译环境设置使用source ./set_env.sh；
怀疑在编译spl时，编译工具设置参数丢失；

### 解决方案：
    在~/.bashrc中配置交叉编译器:
    PATH=$PATH:/home/tudou/work/code/imx6ull_linux/tools/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf/bin

## 2.tools/dumpimage failed

        tools/lib/ecdsa/ecdsa-libcrypto.o：在函数‘ecdsa_add_verify_data’中：
        ecdsa-libcrypto.c:(.text+0x6fd)：对‘EC_POINT_get_affine_coordinates’未定义的引用
        collect2: error: ld returned 1 exit status
        scripts/Makefile.host:104: recipe for target 'tools/dumpimage' failed
        make[1]: *** [tools/dumpimage] Error 1
        Makefile:1817: recipe for target 'tools' failed
        make: *** [tools] Error 2

### 原因分析
openssl version -a 查看openssl版本如下
        
        OpenSSL 1.1.0  25 Aug 2016
        built on: reproducible build, date unspecified
        platform: linux-x86_64
        compiler: gcc -DDSO_DLFCN -DHAVE_DLFCN_H -DNDEBUG -DOPENSSL_THREADS -DOPENSSL_NO_STATIC_ENGINE -DOPENSSL_PIC -DOPENSSL_IA32_SSE2 -DOPENSSL_BN_ASM_MONT -        DOPENSSL_BN_ASM_MONT5 -DOPENSSL_BN_ASM_GF2m -DSHA1_ASM -DSHA256_ASM -DSHA512_ASM -DMD5_ASM -DAES_ASM -DVPAES_ASM -DBSAES_ASM -DGHASH_ASM -DECP_NISTZ256_ASM -DPOLY1305_ASM -DOPENSSLDIR="\"/usr/local/ssl\"" -DENGINESDIR="\"/usr/local/lib/engines-1.1\""  -Wa,--noexecstack
        OPENSSLDIR: "/usr/local/ssl"
        ENGINESDIR: "/usr/local/lib/engines-1.1"

查找openssl文档发现[EC_POINT_get_affine_coordinates](https://www.openssl.org/docs/manmaster/man3/EC_POINT_get_affine_coordinates.html)在OpenSSL 1.1.1版本才引入

EC_POINT_set_affine_coordinates, EC_POINT_get_affine_coordinates, and EC_POINT_set_compressed_coordinates were added in **OpenSSL 1.1.1**.


### 解决方案
        EC_POINT_get_affine_coordinates(group, point, x, y, NULL);
        更改为
        EC_POINT_get_affine_coordinates_GFp(group, point, x, y, NULL);
