#根据ARCH变量的值，选择合适的编译器
ARCH?=x86
ifeq ($(ARCH),x86)
	CC=gcc
else
	CC=/home/magician/opt/gcc-arm-11.2-2022.02-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-gcc
endif

#目标文件
TARGET=lysi_app
#生成中间文件夹
BUILD_DIR=/home/magician/workspace/lysi/app/build
#源文件文件夹列表
SRC_DIR=/home/magician/workspace/lysi/app

#所有源文件的路径名列表
SOURCES=$(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
#所有依赖文件的路径名列表
OBJS=$(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(SOURCES)))

#编译目标
$(BUILD_DIR)/$(TARGET) : $(OBJS)
	$(CC) $^ -o $@

#创建生成文件夹和中间文件
$(BUILD_DIR)/%.o : %.c | create_build
	$(CC) -c $< -o $@

#伪目标（清除生成文件、创建生成文件夹）
.PHONY:clean create_build
clean:
	rm -r $(BUILD_DIR)

create_build:
	mkdir -p $(BUILD_DIR)
