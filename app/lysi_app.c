#include "lysi_app.h"

struct xxxx_struct* parse_xxx_struct(int argc, char *argv[])
{
    int arg_no = 3;
    char *stop_at = NULL;
    struct xxxx_struct* xxxx = malloc(sizeof(struct xxxx_struct));
    if (!xxxx) {
        return NULL;
    }

    xxxx->test_data1 = strtoul(argv[arg_no++], &stop_at, 0);
    xxxx->test_data2 = strtoul(argv[arg_no++], &stop_at, 0);

    return xxxx;
}

void printf_usage(void)
{
    printf("usage\r\n");
    return;
}

int lysi_debugfs_xxxx(int argc, char *argv[])
{
    int ret = LYSI_OK;
    int fd = 0;
    struct xxxx_struct *xxxx;

    if (argc != 2) {
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

    return ret;
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
    }

    return ret;
}