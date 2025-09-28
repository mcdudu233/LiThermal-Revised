#!/bin/bash

export ROOTPATH=`pwd`
export STAGING_DIR=$ROOTPATH/target

mkdir build
cd build

# 编译 LiThermal
cmake $ROOTPATH/.. -DROOTPATH=$ROOTPATH -DCMAKE_TOOLCHAIN_FILE=$ROOTPATH/../toolchain.cmake
make -j`nproc`

# 编译 BSOD
$ROOTPATH/toolchain-sunxi-musl/toolchain/bin/arm-openwrt-linux-gcc -o $ROOTPATH/build/BSOD $ROOTPATH/../tools/BSOD.c

# 将所有编译好的文件复制到 UDISK 目录下
if [ ! -d $ROOTPATH/UDISK ]; then
    mkdir $ROOTPATH/UDISK
fi
cp $ROOTPATH/build/LiThermal $ROOTPATH/UDISK
cp $ROOTPATH/build/BSOD $ROOTPATH/UDISK
cp $ROOTPATH/thermalcamera.sh $ROOTPATH/UDISK
