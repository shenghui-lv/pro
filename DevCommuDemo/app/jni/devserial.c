#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <android/log.h>

#include "utils.h"
#include "devserial.h"

static int gSerialFd = -1;
static char co2SetCommand[8] = {0xFE, 0x04, 0x00, 0x03, 0x00, 0x01, 0xD5, 0xC5};

int SetSerialParam(char *param)
{
    struct termios tio;
    int baud = atoi(param);
    if(gSerialFd <= 0)
    {
        return gSerialFd;
    }
    switch(baud)
    {
        case 2400:  baud = B2400;   break;
        case 4800:  baud = B4800;   break;
        case 9600:  baud = B9600;   break;
        case 19200: baud = B19200;  break;
        case 38400: baud = B38400;  break;
        case 57600: baud = B57600;  break;
        case 115200:    baud = B115200; break;
        default:    baud = B9600;   break;
    }
    tcgetattr(gSerialFd, &tio);
    tio.c_cflag = baud | CS8 | CLOCAL | CREAD;
    tio.c_oflag &= ~OPOST;
    tio.c_oflag = IGNPAR;
    tio.c_lflag = 0;
    tio.c_cc[VTIME] = 0;
    tio.c_cc[VMIN] = 1;
    tcsetattr(gSerialFd, TCSANOW, &tio);
    tcflush(gSerialFd, TCIFLUSH);
    return TRUE;
}

int OpenSerialDev()
{
    int fd = -1;

    fd = open(SERIAL_DEV_NAME, O_RDWR | O_NDELAY | O_NOCTTY);
    if(fd < 0)
    {
        return fd;
    }
    gSerialFd = fd;
    return fd;
}

int ReadSerialDev(char *buf, int len)
{
    int ret = 0;

    if(gSerialFd <= 0)
    {
        return gSerialFd;
    }
    ret = read(gSerialFd, buf, len);
    return ret;
}

int WriteSerialDev(char *buf, int len)
{
    int ret = 0;

    if(gSerialFd <= 0)
    {
        return gSerialFd;
    }
    ret = write(gSerialFd, buf, len);
    return ret;
}

int CloseSerialDev()
{
    if(gSerialFd <= 0)
    {
        return gSerialFd;
    }
    close(gSerialFd);
    gSerialFd = -1;

    return TRUE;
}

int GetCO2Value(char *buf, int len)
{
    int ret = 0;
    if(gSerialFd < 0)
        SetSerialParam("9600");
        OpenSerialDev();
    if(gSerialFd > 0) {
        WriteSerialDev(co2SetCommand, sizeof(co2SetCommand));
        ret = ReadSerialDev(buf, len);
        buf[0] = buf[3];
        buf[1] = buf[4];
    }
    return ret;
}