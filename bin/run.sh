#!/bin/bash

insmod lysi_dev.ko
insmod lysi.ko

./lysi_app /dev/lysi_dev 0
./lysi_app /dev/lysi_dev 1
./lysi_app /dev/lysi_dev 2
./lysi_app /dev/lysi_dev 3
./lysi_app /dev/lysi_dev 4
./lysi_app /dev/lysi_dev 5
./lysi_app /dev/lysi_dev 6
./lysi_app /dev/lysi_dev 7

rmmod lysi_dev
rmmod lysi