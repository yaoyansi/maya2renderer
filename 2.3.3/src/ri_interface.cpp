
#include <ri_interface.h>

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