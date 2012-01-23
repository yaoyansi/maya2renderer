#include "shaderOutputER.h"
#include <liqlog.h>
#include "../common/mayacheck.h"
//#include "../shadergraph/convertShadingNetwork.h"
//#include "../shadergraph/shadermgr.h"

namespace ER
{
	void Visitor::visitPlace2dTexture(const char* node)
	{
		OutputHelper o(file);

		o.beginRSL(node);

		o.addToRSL("ei_shader_param_string(\"desc\", \"maya_place2dTexture\");");
		o.addRSLVariable("vector",  "repeatUV",	"repeatUV",	node);
		o.addRSLVariable("vector",  "outUV",	"outUV",	node);

		o.endRSL();
	}
}//namespace ER