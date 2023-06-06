#!/bin/bash

# 路径、密码等定义
PASSWORD=orangepi
LYSI_DIR=$(cd $(dirname $0); pwd)
SCP_TARGET_DIR=root@192.168.0.104:/home/orangepi/workspace/lysi_kernel_debugfs
SCP_SOURCE_DIR=$LYSI_DIR/bin

# 清除生成的文件
clean_all()
{
    cd $LYSI_DIR/driver
    make clean

    cd $LYSI_DIR/app
    make clean
}

build_all()
{
    # 清屏
    clear & clear

    # 编译lysi驱动
    cd $LYSI_DIR/driver
    make || exit

    # 编译APP
    cd $LYSI_DIR/app
    make ARCH=arm64 || exit

    # 搬运生成的需要用的文件
    rm $SCP_SOURCE_DIR/*
    cp $LYSI_DIR/driver/build/*.ko $SCP_SOURCE_DIR
    cp $LYSI_DIR/app/build/lysi_app $SCP_SOURCE_DIR
    cp $LYSI_DIR/run.sh $SCP_SOURCE_DIR

    # scp文件传输
    sshpass -p ${PASSWORD} scp ${SCP_SOURCE_DIR}/* ${SCP_TARGET_DIR}
}

help()
{
    echo "help"
}

BUILD_TARGET=$1

case "$BUILD_TARGET" in
help)
    help
    ;;
clean_all)
    clean_all
    ;;
build_all)
    build_all
    ;;
*)
    help
    exit 255
    ;;
esac
