#include "lysi_debugfs.h"

static struct lysi_debugfs lysi_debugfs_dev;

static struct register_info smmu_reg[] = {
    {"test1", NULL, 0x12345678, 32},
    {"test2", NULL, 0x23456789, 32},
};

static int register_reg(struct register_info reg_info[], struct dentry *dir)
{
    int reg_nums = sizeof(reg_info)/sizeof(struct register_info);
    int i = 0;
    int ret = 0;
    struct register_info *reg_tmp;

    for (i = 0; i < reg_nums; i++) {
        reg_tmp = smmu_reg[i];
        reg_tmp.vir_addr = ioremap(reg_tmp.phy_addr, reg_tmp.reg_width/8);
        switch (reg_tmp.reg_width) {
        case 8:
            debugfs_create_x8(reg_tmp->name, 0666, dir, reg_tmp.vir_addr);
            break;

        case 16:
            debugfs_create_x16(reg_tmp->name, 0666, dir, reg_tmp.vir_addr);
            break;

        case 32:
            debugfs_create_x32(reg_tmp->name, 0666, dir, reg_tmp.vir_addr);
            break;

        case 64:
            debugfs_create_x64(reg_tmp->name, 0666, dir, reg_tmp.vir_addr);
            break;

        default:
            printk("ERROR\r\n");
            return -EINVAL;
        }
    }

    return ret;
}

static int lysi_debugfs_open(struct inode *inode, struct file *file)
{
    if (inode->i_private) {
        file->private_data = inode->i_private;
    }

    return 0;
}

static long lysi_debugfs_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int ret;

    switch(cmd) {
    case LYSI_IOCTL_CMD0:
        printk("LY_DEBUG===> %s: ioctl cmd0\r\n", __func__);
        return 0;
    case LYSI_IOCTL_CMD1:
        printk("LY_DEBUG===> %s: ioctl cmd1\r\n", __func__);
        return 0;
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
        return 1;
    } else {
        debugfs_create_file("lysi_debugfs_ioctl", 0666, lysi_debugfs_dev.root_dir,
                            NULL, &lysi_debugfs_fops);
    }

    register_reg(smmu_reg, lysi_debugfs_dev.root_dir);

    return 0;
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