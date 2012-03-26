#include "trace.hpp"

namespace	cm
{
	std::string Trace::trace_file_  = "";
	int         Trace::depth_       = 0;

	// arbitrarily support nesting 34 deep for no particular reason
	const char* Trace::nest_        = 
		"| | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | ";
	time_t      Trace::last_invoke_time_ = 0;
}