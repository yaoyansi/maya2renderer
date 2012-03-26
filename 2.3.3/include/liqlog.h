#ifndef liqLog_H
#define liqLog_H

#include <trace/trace.hpp>
#include <liqGlobalHelpers.h>


#define LOG_BUFFER_LEN 1024

#define liquidMessage2(msgtype, msg,...) \
{\
	sprintf_s(gLogBuffer, LOG_BUFFER_LEN, (msg),__VA_ARGS__ );\
	liquidMessage(gLogBuffer, msgtype );\
}

void _liqRIBMsg(const char* msg);
//output debug info to rib file
#define liqRIBMsg( msg,...) \
{\
	if(liqRibTranslator::getInstancePtr()->m_outputDebugMsgToRib){\
		sprintf_s(gLogBuffer, LOG_BUFFER_LEN, (msg),__VA_ARGS__ );\
		_liqRIBMsg(gLogBuffer);\
	}\
}

void _logFunctionCall(const char* log);

extern char gLogBuffer[LOG_BUFFER_LEN];

#endif//liqLog_H