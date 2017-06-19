#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/i2c-dev.h>
#include <android/log.h>

#include "utils.h"
#include "devi2c.h"

static int gI2cFd = -1;

static int SetHighRepetMeasure(int fd)
{
    int ret = 0;
    char config[] = { 0x2C, 0x06 };
	ret = write(fd, config, sizeof(config));
	usleep(10000);
	return ret;
}

int OpenI2cDev()
{
    int fd = -1;
    fd = open(I2C_DEV_NAME, O_RDWR);
    if(fd < 0)
    {
        return fd;
    }
    gI2cFd = fd;
    ioctl(fd, I2C_SLAVE, 0x44);
    return fd;
}

int ReadI2cDev(char *buf, int len)
{
    int i = 0;
    int ret = 0;
    if(gI2cFd <= 0)
    {
        return gI2cFd;
    }
    SetHighRepetMeasure(gI2cFd);
    ret = read(gI2cFd, buf, len);
    return ret;
}

int WriteI2cDev(char *buf, int len)
{
    int ret = 0;
    if(gI2cFd <= 0)
    {
        return gI2cFd;
    }
    ret = write(gI2cFd, buf, len);
    return ret;
}

int CloseI2cDev()
{
    if(gI2cFd <= 0)
    {
        return gI2cFd;
    }
    close(gI2cFd);
    gI2cFd = -1;

    return TRUE;
}
