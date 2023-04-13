export ARCH := arm64
export CROSS_COMPILE := /home/magician/opt/gcc-arm-11.2-2022.02-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-
obj-m += lysi_debugfs.o

KDIR := /home/magician/workspace/orangepi-build/orangepi-build/kernel/orange-pi-5.10-rk3588

PWD := $(shell pwd)
OBJ_DIR := $(PWD)/build

all:
	make -C $(KDIR) M=$(OBJ_DIR) modules

$(OBJ_DIR):
	mkdir -p "$@"

clean:
	rm -rf *.o *.ko *.order *.symvers *.mod *.mod.c .**.cmd .mod* .Mod*
