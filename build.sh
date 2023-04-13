#!/bin/bash

# 路径、密码等定义
PASSWORD=orangepi
LYSI_DIR=$(cd $(dirname $0); pwd)
BUILD_DIR=$LYSI_DIR/build
SCP_TARGET_DIR=orangepi@192.168.0.104:/home/orangepi/workspace
SCP_SOURCE_DIR=$BUILD_DIR/bin

# 清除生成的文件
clean_all()
{
    cd $LYSI_DIR/driver
    make clean

    cd $LYSI_DIR/app
    make clean
}

# 清屏
clear & clear

# 编译lysi驱动
cd $LYSI_DIR/driver
make

# 编译APP
cd $LYSI_DIR/app
make ARCH=arm64

# 搬运生成的需要用的文件
rm $SCP_SOURCE_DIR/*
cp $LYSI_DIR/*.ko $SCP_SOURCE_DIR
cp $LYSI_DIR/run.sh $SCP_SOURCE_DIR
cp $LYSI_DIR/app/build/lysi_app $SCP_SOURCE_DIR
cp $LYSI_DIR/driver/dev/lysi_dev.ko $SCP_SOURCE_DIR

# scp文件传输
sshpass -p ${PASSWORD} scp ${SCP_SOURCE_DIR}/* ${SCP_TARGET_DIR}

clean_all
