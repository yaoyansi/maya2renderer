
#include <liqlog.h>

char gLogBuffer[LOG_BUFFER_LEN];

void _logFunctionCall(const char* log)
{
	printf("CALL:%s\n", log );
	_flushall();
}
void _liqRIBMsg(const char* msg)
{
	RiArchiveRecord( RI_COMMENT, "\t\t\t\t[DEBUG] %s", msg );
}