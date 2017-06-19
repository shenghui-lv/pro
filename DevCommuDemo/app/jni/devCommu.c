#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <android/log.h>

#include "utils.h"
#include "devCommu.h"
#include "commu_beyond_commudemo_DevCommuJni.h"

static int GetDevCommuVersion(char *inOutBuf, int dataLen, int inOutBufLen)
{
	int len = 0;

	len = snprintf(inOutBuf, inOutBufLen, "%s", LIB_DEV_COMMU_VERSION);

	return len;
}

static int DevCommuInit(char *inOutBuf, int dataLen, int inOutBufLen)
{
    int tmp = 0;
    int ret = 0;

    tmp = OpenI2cDev();
    if(tmp < 0)
    {
        ret = ERR_OPEN_I2C_DEV;
    }

    tmp = OpenSpiDev();
    if(tmp < 0)
    {
        ret = ERR_OPEN_SPI_DEV;
    }

    tmp = OpenSerialDev();
    if(tmp < 0)
    {
        ret = ERR_OPEN_SERIAL_DEV;
    }

    return ret;
}

static int DevCommuDeInit(char *inOutBuf, int dataLen, int inOutBufLen)
{
    int ret = 0;

    CloseI2cDev();
    CloseSpiDev();
    CloseSerialDev();

    return ret;
}

static int SendCmdMessage(int cmd, char *inOutBuf, int dataLen, int inOutBufLen)
{
	int ret = 0;

	switch(cmd)
    {
        case TEMPERATUREFLAG:   //获取温度值
            ret = ReadI2cDev(inOutBuf, dataLen);
            break;
        case HUMIDITYFLAG:   //获取湿度值
            ret = ReadI2cDev(inOutBuf, dataLen);
            break;
        case CO2FLAG:
            ret = GetCO2Value(inOutBuf, dataLen);
            break;
        case SPICH1:
            ret = ReadI2cDev(inOutBuf, dataLen);
            break;
        case SPICH2:
            ret = ReadI2cDev(inOutBuf, dataLen);
            break;
        default:
            LOGD("Error, Not support this cmd.");
            break;
    }
    return ret;
}

JNIEXPORT jint JNICALL Java_commu_beyond_devcommudemo_DevCommuJni_SendCmdMessage
  (JNIEnv *env, jobject thiz, jint cmd, jbyteArray inOutBuf, jint dataLen, jint inOutBufLen)
{
	int ret = 0;
	char *pInOutBuf = NULL;

    if(inOutBufLen > 0)
	{
		pInOutBuf = (*env)->GetByteArrayElements(env, inOutBuf, NULL);
	}

    ret = SendCmdMessage(cmd, pInOutBuf, dataLen, inOutBufLen);

	if(inOutBufLen > 0)
    {
        if(ret > 0)
        {
            (*env)->SetByteArrayRegion(env, inOutBuf, 0, ret, pInOutBuf);
        }
    }
    return ret;
}

