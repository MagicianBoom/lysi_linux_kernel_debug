#include "lysi_debugfs.h"

static struct lysi_debugfs lysi_debugfs_dev;

static struct register_info xxxx_reg[] = {
    {"reg_name1", NULL, 0x12345678, 32},
    {"reg_name2", NULL, 0x23456789, 32},
};

// LY_TEST
static unsigned int xxxx_test_data1 = 999;

static int register_reg(struct register_info reg_info[], struct dentry *dir, int nums)
{
    int i = 0;
    int ret = LYSI_OK;
    struct register_info *reg_tmp;

    for (i = 0; i < nums; i++) {
        reg_tmp = &reg_info[i];

        // LY_TEST
        // reg_tmp->vir_addr = ioremap(reg_tmp->phy_addr, reg_tmp->reg_width/8);
        reg_tmp->vir_addr = &xxxx_test_data1;

        switch (reg_tmp->reg_width) {
        case 8:
            debugfs_create_x8(reg_tmp->name, 0666, dir, reg_tmp->vir_addr);
            break;

        case 16:
            debugfs_create_x16(reg_tmp->name, 0666, dir, reg_tmp->vir_addr);
            break;

        case 32:
            debugfs_create_x32(reg_tmp->name, 0666, dir, reg_tmp->vir_addr);
            break;

        case 64:
            debugfs_create_x64(reg_tmp->name, 0666, dir, reg_tmp->vir_addr);
            break;

        default:
            printk("ERROR\r\n");
            return -EINVAL;
        }
    }

    return ret;
}

int ioctl_xxxx(struct lysi_debugfs *lysi_debugfs_dev, unsigned long arg)
{
    struct xxxx_struct xxxx;
    int ret = LYSI_OK;

    if(copy_from_user(&xxxx, (void __user *)arg, sizeof(struct xxxx_struct))) {
        return -EFAULT;
    }

    printk("LY_DEBUG===> %s: xxx.data1: 0x%X\r\n", __func__, xxxx.data1);
    printk("LY_DEBUG===> %s: xxx.data2: 0x%X\r\n", __func__, xxxx.data2);

    return ret;
}

static int lysi_debugfs_open(struct inode *inode, struct file *file)
{
    if (inode->i_private) {
        file->private_data = inode->i_private;
    }

    return LYSI_OK;
}

static long lysi_debugfs_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int ret = LYSI_OK;

    switch(cmd) {
    case LYSI_IOCTL_CMD0:
        printk("LY_DEBUG===> %s: ioctl cmd0\r\n", __func__);
        ret = ioctl_xxxx(&lysi_debugfs_dev, arg);
        return ret;
    case LYSI_IOCTL_CMD1:
        printk("LY_DEBUG===> %s: ioctl cmd1\r\n", __func__);
        return LYSI_OK;
    default:
        printk("LY_DEBUG===> %s: cmd error\r\n", __func__);
    }

    return ret;
}

static const struct file_operations lysi_debugfs_fops = {
    .owner = THIS_MODULE,
    .open = lysi_debugfs_open,
    .unlocked_ioctl = lysi_debugfs_ioctl,
};

int lysi_debugfs_init(void)
{
    printk(KERN_INFO "lysi_debugfs: initialing...\n");
    lysi_debugfs_dev.root_dir = debugfs_create_dir("lysi_debugfs", NULL);
    if (!lysi_debugfs_dev.root_dir) {
        printk(KERN_INFO "lysi_debugfs: error create root dir\n");
        return LYSI_ERROR;
    } else {
        debugfs_create_file("lysi_debugfs_ioctl", 0777, lysi_debugfs_dev.root_dir,
                            NULL, &lysi_debugfs_fops);
    }

    lysi_debugfs_dev.xxxx_dir = debugfs_create_dir("xxxx", lysi_debugfs_dev.root_dir);
    register_reg(xxxx_reg, lysi_debugfs_dev.xxxx_dir, sizeof(xxxx_reg)/sizeof(struct register_info));

    return LYSI_OK;
}

void lysi_debugfs_exit(void)
{
    debugfs_remove_recursive(lysi_debugfs_dev.root_dir);
    printk(KERN_INFO "lysi_debugfs: exiting successful\n");
}

module_init(lysi_debugfs_init);
module_exit(lysi_debugfs_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("liuyang");