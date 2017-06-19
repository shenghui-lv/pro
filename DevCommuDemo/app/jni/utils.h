#ifndef COMMUDEMO_UTILS_H
#define COMMUDEMO_UTILS_H

#ifndef TRUE
#define TRUE		1
#endif

#ifndef FALSE
#define FALSE		0
#endif

#define DEBUG TRUE
#define LOGD(...) if(DEBUG) __android_log_print(ANDROID_LOG_DEBUG, "[DEVCOMMU]", __VA_ARGS__)

#endif //COMMUDEMO_UTILS_H
