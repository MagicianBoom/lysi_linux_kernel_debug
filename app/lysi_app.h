#ifndef __LYSI_APP_H
#define __LYSI_APP_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "linux/ioctl.h"

#define LYSI_TYPE               '?'
#define LYSI_MAGIC              100
#define LYSI_IOCTL_CMD0         (_IO(LYSI_TYPE, LYSI_MAGIC+0))
#define LYSI_IOCTL_CMD1         (_IO(LYSI_TYPE, LYSI_MAGIC+1))
#define LYSI_IOCTL_CMD2         (_IO(LYSI_TYPE, LYSI_MAGIC+2))
#define LYSI_IOCTL_CMD3         (_IO(LYSI_TYPE, LYSI_MAGIC+3))
#define LYSI_IOCTL_CMD4         (_IO(LYSI_TYPE, LYSI_MAGIC+4))
#define LYSI_IOCTL_CMD5         (_IO(LYSI_TYPE, LYSI_MAGIC+5))
#define LYSI_IOCTL_CMD6         (_IO(LYSI_TYPE, LYSI_MAGIC+6))
#define LYSI_IOCTL_CMD7         (_IO(LYSI_TYPE, LYSI_MAGIC+7))

#endif