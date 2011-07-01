
#include <ri_interface.h>

#ifdef RIBLIB_AQSIS

#pragma comment(lib,"E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/build/DebugLib/aqsis_ri2rib.lib")//
#pragma comment(lib,"E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/build/DebugLib/aqsis_core.lib")
#pragma comment(lib,"E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/build/DebugLib/aqsis_math.lib")

#pragma comment(lib,"E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/build/DebugLib/aqsis_ribparse.lib")
#pragma comment(lib,"E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/build/DebugLib/aqsis_riutil.lib")//
#pragma comment(lib,"E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/build/DebugLib/aqsis_shadervm.lib")
#pragma comment(lib,"E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/build/DebugLib/aqsis_tex.lib")
#pragma comment(lib,"E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/build/DebugLib/aqsis_util.lib")
#pragma comment(lib,"E:/dev/tools/libtiff/3.8.2/lib/libtiff.lib")
//#elif defined()
#else 
#	pragma comment(lib,"../../bin/win32lib/rilib_d.lib")
#endif