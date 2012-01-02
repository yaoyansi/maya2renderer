#include "logmgr.h"

namespace liquid
{
	//LogMgr* LogMgr::m_instance = 0;

	LogMgr::LogMgr()
	{

	}
	//
	LogMgr::~LogMgr()
	{

	}
	void LogMgr::open(const char* logfile)
	{
		m_logfile.open(logfile);
	}
	void LogMgr::close()
	{
		m_logfile.close();
	}
	//
	// LogMgr* LogMgr::getInstancePtr()
	// {
	// 	if (m_instance==0)
	// 	{
	// 		m_instance = new LogMgr();
	// 	}
	// 	return m_instance;
	// }
	//
}