#include "lysi_app.h"

static int cmd[] = {3, 3, 3, 3, 3, 3, 3, 3};

int verify_argc(int index, int argc)
{
    if (argc != cmd[index]){
        printf("Error Usage!\r\n");
        return -1;
    }

    return 0;
}

int ioctl_cmd0(int argc, char *argv[])
{
    int ret = 0;
    if (argc != 3) {
        printf("Error Usage!\r\n");
        return -1;
    }



}

// argv[0]: app_name
// argv[1]: dev_file_path
// argv[2]: cmd_code
// argv[3]...: args
int main(int argc, char *argv[])
{
    int fd, ret;
    char *dev_file_path;
    int cmd;

    if (argc < 3) {
        printf("usage: lysi_app dev_file_path cmd_code [args...]\r\n");
        return -1;
    }

    verify_argc(atoi(argv[2]), argc);

    dev_file_path = argv[1];
    cmd = atoi(argv[2]);

    /* 打开驱动文件 */
    fd = open(dev_file_path, O_RDWR);
    if(fd < 0){
        printf("Can't open file %s\r\n", dev_file_path);
        return -1;
    }

    switch(cmd) {
    case 0:
        return ioctl(fd, LYSI_IOCTL_CMD0, 0);
    case 1:
        return ioctl(fd, LYSI_IOCTL_CMD1, 0);
    case 2:
        return ioctl(fd, LYSI_IOCTL_CMD2, 0);
    case 3:
        return ioctl(fd, LYSI_IOCTL_CMD3, 0);
    case 4:
        return ioctl(fd, LYSI_IOCTL_CMD4, 0);
    case 5:
        return ioctl(fd, LYSI_IOCTL_CMD5, 0);
    case 6:
        return ioctl(fd, LYSI_IOCTL_CMD6, 0);
    case 7:
        return ioctl(fd, LYSI_IOCTL_CMD7, 0);
    default:
        printf("cmd error\r\n");
        return -1;
    }

    /* 关闭设备 */
    ret = close(fd);
    if(ret < 0){
        printf("Can't close file %s\r\n", dev_file_path);
        return -1;
    }
    return 0;
}