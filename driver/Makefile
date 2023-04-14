# 编译目标名称
OBJ := lysi_kernel_debugfs

# 自定义目录与属性
export ARCH := arm64
export CROSS_COMPILE := /home/magician/opt/gcc-arm-11.2-2022.02-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-
KDIR := /home/magician/workspace/orangepi-build/orangepi-build/kernel/orange-pi-5.10-rk3588

# 文件与文件路径
BUILD_DIR = $(PWD)/build
SRC = $(PWD)
BUILD_DIR_MAKEFILE = $(PWD)/build/Makefile
obj-m += $(OBJ).o

# 源文件
$(OBJ)-objs += lysi_debugfs.o

# 编译
default: $(BUILD_DIR_MAKEFILE)
	make -C $(KDIR) M=$(BUILD_DIR) src=$(SRC) modules

$(BUILD_DIR_MAKEFILE): $(BUILD_DIR)
	touch "$@"

$(BUILD_DIR):
	mkdir -p "$@"

clean:
	make -C $(KDIR) M=$(BUILD_DIR) src=$(SRC) clean
	rm -r $(BUILD_DIR)

