#ifndef liqLog_H
#define liqLog_H

#include <liqGlobalHelpers.h>

#define LOG_BUFFER_LEN 1024

#define liquidMessage2(msgtype, msg,...) \
{\
	sprintf_s(gLogBuffer, LOG_BUFFER_LEN, (msg),__VA_ARGS__ );\
	liquidMessage(gLogBuffer, msgtype );\
}

//output debug info to rib file
#define liqRIBMsg( msg,...) \
{\
	sprintf_s(gLogBuffer, LOG_BUFFER_LEN, (msg),__VA_ARGS__ );\
	RiArchiveRecord( RI_COMMENT, "\t\t\t\t[DEBUG] %s", gLogBuffer );\
}

extern char gLogBuffer[LOG_BUFFER_LEN];

#endif//liqLog_H