#ifndef liqRiInterface_H
#define liqRiInterface_H

#define RIBLIB_AQSIS

//-------------------------------------------------------
#ifdef RIBLIB_AQSIS

//typedef int RtLightHandle;
#define INVALID_LIGHT_INDEX 0

#	include "E:/dev/autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/include/aqsis/ri/ri.h"
//#	include "E:/dev/autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/libs/core/renderer.h"

//#elif defined()
#else 
#	include "../riblib/ri.h"
#endif
//-------------------------------------------------------



#endif//liqRiInterface_H