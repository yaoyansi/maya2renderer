#ifndef _LIQUID_LOG_H_
#define _LIQUID_LOG_H_

#define LOG_BUFFER_LEN 1024

#define liquidMessage2(msgtype, msg,...) \
{\
	sprintf_s(gLogBuffer, LOG_BUFFER_LEN, (msg),__VA_ARGS__ );\
	liquidMessage(gLogBuffer, msgtype );\
}


extern char gLogBuffer[LOG_BUFFER_LEN];

#endif//_LIQUID_LOG_H_