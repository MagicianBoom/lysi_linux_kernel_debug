# lysi_linux_kernel_debugfs
lysi_linux_kernel_debugfs是Linux内核设备驱动开发调试、Linux内核开发调试的工具，以debugfs为核心，支持寄存器组直接映射至用户态进行读写，支持ioctl来调用内核函数进行调试。
## 工程目录
- app：用户态应用程序，实现ioctl的调用功能
- bin：中间文件输出目录
- common：lysi嵌入式软件基础设施通用模块，其实现不依赖于任何硬件平台（如ARM、RISCV等），也不依赖于操作系统（如linux、FreeRTOS等），仅受到C语言标准实现的制约。其作为通用的模块提供给所有支持LYSI软件基础设施的平台。
- driver：内核态驱动程序，lysi的debugfs驱动核心程序，提供了ioctl的实现、寄存器组呈现于文件系统的实现。
- build.sh：编译脚本，必要时依据平台、工程特性自行更改
- README.md：说明手册
- run.sh：linux下的命令执行脚本，请按需自行更改
## ./build.sh命令自动补全功能
- 执行 source shell_complete 命令后即可使用
- 如果要增加命令，build.sh和shell_complete要同时增加命令