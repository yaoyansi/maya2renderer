#include "shaderOutputRSL.h"
//#include <liqlog.h>
//#include <liqShader.h>
//#include <liqShaderFactory.h>
#include "../common/mayacheck.h"
//#include "../shadergraph/convertShadingNetwork.h"
//#include "../shadergraph/shadermgr.h"
#include "ri_interface.h"

namespace RSL
{
	void Visitor::visitPlace2dTexture(const char* node)
	{
		OutputHelper o(RSLfile);

		o.beginRSL(node);

		o.addRSLVariable("float2", "repeatUV", "repeatUV", node);
		o.addRSLVariable("float2", "outUV", "outUV", node);

		o.addToRSL("extern float s, t;");
		o.addToRSL("outUV[ 0 ] = mod( t * repeatUV[ 0 ], 1 );");
		o.addToRSL("outUV[ 1 ] = mod( s * repeatUV[ 1 ], 1 );");

		o.endRSL();
	}
}//namespace RSL