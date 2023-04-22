#include "lysi_app.h"

//===== demo for use START =====
struct xxxx_struct* parse_xxx_struct(int argc, char *argv[])
{
    int arg_no = 2;
    char *stop_at = NULL;
    struct xxxx_struct* xxxx = malloc(sizeof(struct xxxx_struct));
    lysi_assert(xxxx != NULL);

    xxxx->data1 = strtoul(argv[arg_no++], &stop_at, 0);
    xxxx->data2 = strtoul(argv[arg_no++], &stop_at, 0);

    return xxxx;
}

int lysi_debugfs_xxxx(int argc, char *argv[])
{
    int ret = LYSI_OK;
    int fd = 0;
    struct xxxx_struct *xxxx;
    int struct_member_nums = 2;

    if (argc != 2+struct_member_nums) {
        printf("Invalid argument count %d\r\n", argc);
        printf_usage();
        return LYSI_ERROR;
    }

    xxxx = parse_xxx_struct(argc, argv);

    fd = open(LYSI_DEBUGFS_IOCTL_DEV_NAME, O_RDWR, 0);
    if (fd < 0) {
        printf("open failed\r\n");
        return LYSI_ERROR;
    }

    ret = ioctl(fd, LYSI_IOCTL_CMD0, xxxx);
    if (ret) {
        printf("lysi_debugfs_xxxx failed, ret:%d\r\n", ret);
    }

    close(fd);
    free(xxxx);
    return ret;
}
//===== demo for use END =====

void printf_usage(void)
{
    printf("usage\r\n");
    return;
}

int main(int argc, char *argv[])
{
    int fd, ret;
    char *dev_file_path;
    int cmd;

    if (argc < 2) {
        printf_usage();
        return LYSI_ERROR;
    }

    if (memcmp(argv[1], "lysi_debugfs_xxxx", strlen(argv[1])) == 0) {
        ret = lysi_debugfs_xxxx(argc, argv);
    } else {
        printf_usage();
        return LYSI_ERROR;
    }

    return ret;
}