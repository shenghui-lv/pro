#ifndef COMMUDEMO_DEVCOMMU_H
#define COMMUDEMO_DEVCOMMU_H

#define LIB_DEV_COMMU_VERSION	"devcommu_ver1.0.0"

#define DEV_INIT    66
#define DEV_CLOSE   88
#define TEMPERATUREFLAG 1001
#define HUMIDITYFLAG 1002
#define CO2FLAG 101
#define SPICH1  102
#define SPICH2  103

#define ERR_OPEN_I2C_DEV            -1
#define ERR_OPEN_SPI_DEV            -2
#define ERR_OPEN_SERIAL_DEV         -3

#endif //COMMUDEMO_DEVCOMMU_H
