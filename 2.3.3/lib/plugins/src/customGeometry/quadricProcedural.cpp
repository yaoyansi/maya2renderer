#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ri.h"

#if defined(USE_LIQUID_RIB)
#	pragma comment(lib, "E:/dev/Autodesk/maya/myplugin/project/liquid_/2.3.3/bin/win32lib/RILIB_d.lib")
const char *token="use liquid rib";
#elif defined(USE_AQSIS_RIB)
 #	pragma comment(lib, "E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/prebuild/lib/aqsis_core.lib")
// #	pragma comment(lib, "E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/prebuild/lib/aqsis_math.lib")
 #	pragma comment(lib, "E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/prebuild/lib/aqsis_ri2rib.lib")
// #	pragma comment(lib, "E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/prebuild/lib/aqsis_ribparse.lib")
// #	pragma comment(lib, "E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/prebuild/lib/aqsis_riutil.lib")
// #	pragma comment(lib, "E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/prebuild/lib/aqsis_shadervm.lib")
// #	pragma comment(lib, "E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/prebuild/lib/aqsis_slcomp.lib")
// #	pragma comment(lib, "E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/prebuild/lib/aqsis_slxargs.lib")
// #	pragma comment(lib, "E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/prebuild/lib/aqsis_tex.lib")
// #	pragma comment(lib, "E:/dev/render/renderer/renderman.compliant/aqsis/1.6.0/prebuild/lib/aqsis_util.lib")


const char *token="use aqsis rib";
#else
#	pragma comment(lib, "E:/dev/tools/pixar/renderman/13.5/lib/prman.lib")
const char *token="use prman rib";
#endif

#ifdef USE_LIQUID_RIB

#else

#endif


#ifdef _WIN32
#define export __declspec(dllexport)
#define strtok_r(str,delim,saveptr) strtok((str),(delim))
#else
#define export
#endif

extern "C" {
    export RtPointer ConvertParameters(RtString paramstr);
    export RtVoid Subdivide(RtPointer data, RtFloat detail);
    export RtVoid Free(RtPointer data);
}

enum QuadricsType {
    kCylinder,
    kDisk,
    kPartialDisk,
    kSphere    
};

struct quadricsData {
    QuadricsType shapeType;
    RtFloat radius1;
    RtFloat radius2;
    RtFloat height;
    RtFloat startAngle;
    RtFloat sweepAngle;
};

export RtPointer ConvertParameters(RtString paramstr) 
{
	printf("\n+++%s\n", token);
    struct quadricsData* data;
    char* parameters;
    char* token, *tokenstate;
    int i, j;

    parameters = strdup(paramstr);

    data = reinterpret_cast<struct quadricsData*>(malloc(sizeof(struct quadricsData)));

    token = strtok_r(parameters, " ", &tokenstate);
    data->shapeType = static_cast<QuadricsType>(atoi(token));

    token = strtok_r(0, " ", &tokenstate);
    data->radius1 = atof(token);

    token = strtok_r(0, " ", &tokenstate);
    data->radius2 = atof(token);

    token = strtok_r(0, " ", &tokenstate);
    data->height = atof(token);

    token = strtok_r(0, " ", &tokenstate);
    data->startAngle = atof(token);

    token = strtok_r(0, " ", &tokenstate);
    data->sweepAngle = atof(token);    
    
    free(parameters);
    return (RtPointer)(data);
}

export RtVoid Subdivide(RtPointer datap, RtFloat detail) 
{
    struct quadricsData* data = reinterpret_cast<struct quadricsData*>(datap);
    int i, j;

	RiTransformBegin();
	//RiRotate(50.0, 0, 0, 1);
	RiSphere(data->radius1, 0.0, data->radius1, 360.0, RI_NULL);
	RiTransformEnd();
}

export RtVoid Free(RtPointer datap) 
{

    struct quadricsData* data = reinterpret_cast<struct quadricsData*>(datap);
    free(data);
}
