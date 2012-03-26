#include "trace.hpp"

namespace	cm
{
	std::string Trace::trace_file_  = "";
	int         Trace::depth_       = 0;
	std::ofstream Trace::m_logfile;

	// arbitrarily support nesting 34 deep for no particular reason
	const char* Trace::nest_        = 
		"| | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | ";
	time_t      Trace::last_invoke_time_ = 0;
	//////////////////////////////////////////////////////////////////////////

	Trace::Trace(std::string msg)
	{
		LogMsg(depth_, depth_ * 2, msg.c_str());
		++depth_;
	}
	Trace::~Trace()
	{
		--depth_;
	}
	void Trace::openFile(const char *trace_file)
	{
		trace_file_ = trace_file;

		m_logfile.open(trace_file_.c_str());
		if( !m_logfile.is_open() )
		{
			assert(0&&"[cm::Trace] can't open file.");
			printf("[cm::Trace] can't open file: %s.\n", trace_file_.c_str() );
		}
	}
	void Trace::closeFile()
	{
		m_logfile.flush();
		m_logfile.close();
		trace_file_ = "";
	}
	void Trace::LogMsg(int depth, int align, const char *msg)
	{
		assert(m_logfile.is_open());
		std::string indent(4*depth, ' ');
		// only log the timestamp when the time changes
		//unsigned int len = fprintf( fp, "%s>(%d)%s\n", indent.c_str(), depth, msg);
		m_logfile<<indent<<">"<<"("<<depth<<")"<<msg<<std::endl;
	}
}