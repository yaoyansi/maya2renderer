#ifndef liqRiInterface_H
#define liqRiInterface_H

// use aqsis for rib exportion
#define RIBLIB_AQSIS

//-------------------------------------------------------
#ifdef RIBLIB_AQSIS

//typedef int RtLightHandle;
#define INVALID_LIGHT_INDEX 0

#	include <aqsis/ri/ri.h>

//#elif defined()
#else 
#	include "../riblib/ri.h"
#endif
//-------------------------------------------------------



#endif//liqRiInterface_H