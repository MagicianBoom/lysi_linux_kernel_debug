#ifndef LYSI_DEBUGFS_H
#define LYSI_DEBUGFS_H

#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/fs.h>
#include <linux/io.h>
#include <linux/slab.h>

#define LYSI_TYPE               '!'
#define LYSI_MAGIC              117
#define LYSI_IOCTL_CMD0         (_IO(LYSI_TYPE, LYSI_MAGIC+0))
#define LYSI_IOCTL_CMD1         (_IO(LYSI_TYPE, LYSI_MAGIC+1))
#define LYSI_IOCTL_CMD2         (_IO(LYSI_TYPE, LYSI_MAGIC+2))
#define LYSI_IOCTL_CMD3         (_IO(LYSI_TYPE, LYSI_MAGIC+3))
#define LYSI_IOCTL_CMD4         (_IO(LYSI_TYPE, LYSI_MAGIC+4))
#define LYSI_IOCTL_CMD5         (_IO(LYSI_TYPE, LYSI_MAGIC+5))
#define LYSI_IOCTL_CMD6         (_IO(LYSI_TYPE, LYSI_MAGIC+6))
#define LYSI_IOCTL_CMD7         (_IO(LYSI_TYPE, LYSI_MAGIC+7))

#define LYSI_OK                 0
#define LYSI_ERROR              -1

struct lysi_debugfs{
    struct dentry *root_dir;
    struct dentry *xxxx_dir;
};

struct register_info{
    char *name;
    void __iomem *vir_addr;
    unsigned long long phy_addr;
    unsigned char reg_width;
};

struct xxxx_struct{
    unsigned int data1;
    unsigned int data2;
};

#endif