#ifndef _RI_INTERFACE_H_
#define _RI_INTERFACE_H_

//#define RIBLIB_AQSIS

#ifdef RIBLIB_AQSIS
	
//#elif  defined()
#else 
#	include "../riblib/ri.h"
#	pragma comment(lib,"../../bin/win32lib/rilib_d.lib")
#endif


#endif