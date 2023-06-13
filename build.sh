#!/bin/bash

# 路径、密码等定义
PASSWORD=orangepi
LYSI_DIR=$(cd $(dirname $0); pwd)
SCP_TARGET_DIR=root@192.168.0.104:/lib/modules/5.10.110-rockchip-rk3588/kernel/drivers/lysi
SCP_SOURCE_DIR=$LYSI_DIR/bin

# 清除生成的文件
clean_all()
{
    cd $LYSI_DIR/driver/lysi_debugfs
    make clean

    cd $LYSI_DIR/driver/lysi_kprobe
    make clean

    cd $LYSI_DIR/app
    make clean
}

build_app()
{
    # 编译APP
    cd $LYSI_DIR/app
    make ARCH=arm64 || exit

    rm $SCP_SOURCE_DIR/*
    cp $LYSI_DIR/app/build/lysi_app $SCP_SOURCE_DIR

    # scp文件传输
    sshpass -p ${PASSWORD} scp ${SCP_SOURCE_DIR}/* ${SCP_TARGET_DIR}

    make clean
}

build_debugfs()
{
    # 清屏
    clear & clear

    DRV_DIR=$LYSI_DIR/driver/lysi_debugfs

    # 编译lysi驱动
    cd $DRV_DIR
    make || exit

    # 搬运生成的需要用的文件
    rm $SCP_SOURCE_DIR/*
    cp $DRV_DIR/build/*.ko $SCP_SOURCE_DIR
    cp $LYSI_DIR/run.sh $SCP_SOURCE_DIR

    # scp文件传输
    sshpass -p ${PASSWORD} scp ${SCP_SOURCE_DIR}/* ${SCP_TARGET_DIR}

    make clean
}

build_kprobe()
{
    # 清屏
    clear & clear

    DRV_DIR=$LYSI_DIR/driver/lysi_kprobe

    # 编译lysi驱动
    cd $DRV_DIR
    make || exit

    # 搬运生成的需要用的文件
    rm $SCP_SOURCE_DIR/*
    cp $DRV_DIR/build/*.ko $SCP_SOURCE_DIR
    cp $LYSI_DIR/run.sh $SCP_SOURCE_DIR

    # scp文件传输
    sshpass -p ${PASSWORD} scp ${SCP_SOURCE_DIR}/* ${SCP_TARGET_DIR}

    make clean
}

build_all()
{
    build_app
    build_debugfs
    build_kprobe
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
app)
    build_app
    ;;
debugfs)
    build_debugfs
    ;;
kprobe)
    build_kprobe
    ;;
all)
    build_all
    ;;
*)
    help
    exit 255
    ;;
esac
