#ifndef COMMUDEMO_DEVSPI_H
#define COMMUDEMO_DEVSPI_H

#define SPI_DEV_NAME    "/dev/spidev0.0"

#define SPI_DEV_NUM_1       1
#define SPI_DEV_NUM_2       2

#define SPI_SEND_MAX_LEN    (2*1024)

typedef struct __SPI_PARAM
{
    int bits;
    int delayUs;
    int speed;
} TSpiParam, *PSpiParam;

typedef struct __protoData {
	unsigned short header;
	unsigned short serialNo;
	unsigned short len;
	char *data;
	unsigned short crc;
} __attribute__((packed)) TProtoData, PProtoData;

typedef struct __sensorData {
	unsigned short type;
	unsigned short len;
	char *value;
} __attribute__((packed)) TSensorData, *PSensorData;

#endif //COMMUDEMO_DEVSPI_H
