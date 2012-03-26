// A Simple C++ Function Call Stack Trace Utility
// By Mockey Chen
// email:mockey.chen@gmail.com
// http://www.codeproject.com/Articles/12949/A-Simple-C-Function-Call-Stack-Trace-Utility

/************************************************************************

Introduction
Under UNIX/Linux platform, program coredump generates a core file, we can analyze the core file and 
determine what's wrong in our program. The core file records the function call stack (e.g. under gdb
you can use bt command to see backtrace), that is mostly information for us to troubleshooting.

When I debug my program, I try to record the function call stack in program debug log to help me
diagnose the program's defect. Fortunately, C++ gives us a simple way to implement this.

Rational
Just use C++ constructor/destructor semantic, we can make our own trace class. At the function entrance,
we declare a local variable, it will invoke the constructor immediately, when leaving the function,
the local variable will be destroyed and call destructor. That's all. what we need to do is implement a
class's constructor and destructor. This rational is simple enough, but this way sometimes can help us a lot. 

***********************************************************************/

#ifndef CM_TRACE_20060209_HPP
#define CM_TRACE_20060209_HPP

// trace.hpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string>

#define CM_TRACE_FILE(trace_file)	cm::Trace::LogToFile(trace_file)

#define CM_TRACE_FUNC(func_name)    std::stringstream __CM_TRACE_SSTR; __CM_TRACE_SSTR<<func_name; cm::Trace __CM_TRACE__(__CM_TRACE_SSTR.str())
#define CM_TRACE_FUNC_ARG1(func_name, argfmt, arg)   \
	cm::Trace __CM_TRACE__(func_name, argfmt, arg)
#define CM_TRACE_FUNC_ARG2(func_name, argfmt, arg1, arg2)   \
	cm::Trace __CM_TRACE__(func_name, argfmt, arg1, arg2)
// more macros define....

namespace	cm
{
	class	Trace
	{
	public:
		explicit Trace(std::string msg)
		{
			LogMsg(depth_, depth_ * 2, msg.c_str());
			++depth_;
		}

		~Trace()
		{
			--depth_;
		}

		/// special the global log file.
		void static LogToFile(const char *trace_file)
		{
			trace_file_ = trace_file;
		}

	private:
		void LogMsg(int depth, int align, const char *msg)
		{
			FILE	*fp = fopen(trace_file_.c_str(), "a+");
			if (fp == NULL)
			{
				printf("[cm::Trace] can't open file: %s.\n", trace_file_.c_str() );
				return;
			}

			std::string indent(4*depth, ' ');
			// only log the timestamp when the time changes
			unsigned int len = fprintf( fp, "%s>(%d)%s\n", indent.c_str(), depth, msg);
			fflush(fp);
			fclose(fp);
		}
	private:
		// the debug trace filename
		static std::string	trace_file_;

		// function call stack depth
		static int			depth_;
		static const char*  nest_;
		static time_t       last_invoke_time_;
	};

}	// end namespace cm
#endif // CM_TRACE_20060209_HPP

/************************************************************************

Using the Code
First you need to call CM_TRACE_FILE() to special debug log filename, then at function entrance,
call CM_TRACE(). Here is an example. 

#include "cm/trace.hpp"

void foo()
{
	CM_TRACE_FUNC("foo");
}

void bar(int x)
{
	CM_TRACE_FUNC_ARG1("bar", "(%d)", x);
	foo();
}

void foobar(int x, const char* s)
{
	CM_TRACE_FUNC_ARG2("foobar", "(%d, %s)", x, s);
	bar(789);
}

void foobar3(int x, int y, double z)
{
	CM_TRACE_FUNC_ARG3("foobar3", "(%d, %d, %f)", x, y, z);
	foobar(123, "4546");
}

int main()
{
	CM_TRACE_FILE("./trace.log");
	CM_TRACE_FUNC("main");
	foo();
	bar(23);
	foobar(33, "char");
	foobar3(12, 23, 34.45);
	return 0;
}

Then open `trace.log', use your favourite editor. At the end of file, you will see the following: 
20060211.132431 > (0)main()
				| > (1)foo()
				| > (1)bar(23)
				| | > (2)foo()
				| > (1)foobar(33, char)
				| | > (2)bar(789)
				| | | > (3)foo()
				| > (1)foobar3(12, 23, 34.450000)
				| | > (2)foobar(123, 4546)
				| | | > (3)bar(789)
				| | | | > (4)foo()


Conclusion
The rational in this article is simple, but we can write simple code do useful things.

Revision History
v1.00 Feb 4, 2005. Mockey
Original article
v1.01 Feb 11 2005. Mockey
Change fstream to FILE*
Change string to sprintf for more efficiency. Thanks Jon Wold's comment
Rename CM_TRACE to CM_TRACE_FUN and add CM_TRACE_FUN_ARGx macros.
Add feature to log the function call arguments.

License
This article, along with any associated source code and files, is licensed under The Code Project Open License (CPOL)

About the Author
Mockey Chen

China China
Member
Mockey is a C++ programmer, experienced with C/C++ program under UNIX platform, his primarily research field is communication program for telecom. He works for one of china's biggest telecom equipment supplier until Dec 2006.
He's current interest is Linux kernel programming, especial in networking hack.
Mockey lives in Chengdu, China. To contact Mockey, email at mockey.chen@gmail.com
************************************************************************/