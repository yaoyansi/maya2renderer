#include "shaderOutputERCall.h"
#include <liqlog.h>
#include "../common/mayacheck.h"
#include "../shadergraph/convertShadingNetwork.h"
#include "../shadergraph/shadermgr.h"

#include <eiAPI/ei.h>

namespace ERCall
{
	void Visitor::visitPlace2dTexture(const char* node)
	{
		OutputHelper o;

		o.beginRSL(node);

		ei_shader_param_string("desc", "maya_place2dTexture");
		o.addRSLVariable("vector",  "repeatUV",	"repeatUV",	node);
		o.addRSLVariable("vector",  "outUV",	"outUV",	node);

		o.endRSL();
	}
}//namespace ERCall