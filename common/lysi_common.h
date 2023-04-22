/*
 * lysi_common.h文件主要用来搭建嵌入式软件开发基础设施，其实现不依赖于任何硬件平台（如
 * ARM、RISCV等），也不依赖于操作系统（如linux、FreeRTOS等），仅受到C语言标准实现的制
 * 约。其作为通用的模块提供给所有支持LYSI软件基础设施的平台。
 */

#ifndef __LYSI_COMMON_H
#define __LYSI_COMMON_H

#define LYSI_OK                             0
#define LYSI_ERROR                          -1

#define lysi_assert(x) \
            if (!x) { \
                return LYSI_ERROR; \
            }

#endif