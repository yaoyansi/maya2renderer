
#include <ri_interface.h>

#define _POSIX_
#include <limits.h>
#include <string>

#include <liqlog.h>

#ifdef RIBLIB_AQSIS

//set the aqsis_libs, e.g. $(AQSIS_LIB_X32)=E:/dev/autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/DebugLib/
// #pragma comment(lib,"aqsis_ri2rib.lib")
// #pragma comment(lib,"aqsis_core.lib")
//#pragma comment(lib,"aqsis_math.lib")
//#pragma comment(lib,"aqsis_ribparse.lib")
// #pragma comment(lib,"aqsis_riutil.lib")
//#pragma comment(lib,"aqsis_shadervm.lib")
// #pragma comment(lib,"aqsis_tex.lib")
// #pragma comment(lib,"aqsis_util.lib")

//pre-build libtiff.lib
//#pragma comment(lib,"E:/dev/tools/libtiff/3.8.2/lib/libtiff.lib")
//we build libtiff.lib from source code
//set the libtiff libs, e.g.$(LIBTIFF)=E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/libtiff/3.8.2/src/tiff/3.8.2/tiff-3.8.2-src/libtiff/
//#pragma comment(lib,"libtiff.lib")

//#elif defined()
#else 
#	pragma comment(lib,"../../bin/win32lib/rilib_d.lib")
#endif
//--------------------------------------------------------
RtVoid RiBegin_liq(RtToken name)
{
	CM_TRACE_FUNC("RiBegin_liq("<<name<<")");
	std::string newname(name);

	if( strlen(name)>=_POSIX_PATH_MAX )//file name is too long
	{
		liquidMessage2( messageError, "file name is too long(>=%d(_POSIX_PATH_MAX)):%s", _POSIX_PATH_MAX, name );
		assert(0&&"FATAL ERROE: file name is too long!");
#ifdef _WIN32
		newname = "\\\\?\\";//see MAX_PATH: http://msdn.microsoft.com/en-us/library/aa365247.aspx#maxpath
		newname+= name;
#else
#error "If the file path name is too long, how to handle this case on linux?"
		exit(0);
#endif
	}
	
	RiBegin( const_cast<RtToken>(newname.c_str()) );
}
//--------------------------------------------------------