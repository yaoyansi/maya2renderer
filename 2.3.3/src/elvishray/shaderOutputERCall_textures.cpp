#include "shaderOutputERCall.h"
#include <liqlog.h>
#include "../common/mayacheck.h"
#include "../shadergraph/convertShadingNetwork.h"
#include "../shadergraph/shadermgr.h"

#include <eiAPI/ei.h>

namespace ERCall
{
void Visitor::visitFile(const char* node)
{	
	OutputHelper o;

	//generate texture and construct texture node
	{
		MString fileImageName;
		IfMErrorWarn(MGlobal::executeCommand("getAttr \""+MString(node)+".fileTextureName\"", fileImageName));
		//test "fileImageName" exist or not.
		if( access(fileImageName.asChar(), 0) != 0){
			liquidMessage2(messageError,"%s not exist!", fileImageName.asChar());
			assert(0&&"image not exist.");
		}

		bool isERTex;//whether fileImageName is ER texture
		{
			std::string fileImageName_(fileImageName.asChar());
			std::size_t i_last_dot = fileImageName_.find_last_of('.');
			if( i_last_dot == std::string::npos ){
				liquidMessage2(messageWarning,"%s has no extention!", fileImageName_.c_str());
				assert(0&&"warrning: texture name has not extention.");
			}
			std::string imgext(fileImageName_.substr(i_last_dot+1));//imgext=tex
			std::transform(imgext.begin(),imgext.end(),imgext.begin(),tolower);
		
			isERTex = (imgext == "tex");
		}

		MString fileTextureName = (isERTex)? fileImageName : (fileImageName+".tex");

		//generate texture
		if ( access(fileTextureName.asChar(), 0) != 0 )//not exist
		{
			ei_make_texture(fileImageName.asChar(), fileTextureName.asChar(),
				EI_TEX_WRAP_CLAMP, EI_TEX_WRAP_CLAMP, EI_FILTER_BOX, 1.0f, 1.0f);
		}
		//construct texture node
		//if (ei_file_exists(fileTextureName))
		{
			ei_texture(fileImageName.asChar());
				ei_file_texture(fileTextureName.asChar(), eiFALSE);
			ei_end_texture();
		}
	}


	o.beginRSL(node);

	ei_shader_param_string("desc", "maya_file");
	o.addRSLVariable("vector",  "uvCoord",	"uvCoord",	node);
	o.addRSLVariable("texture", "fileTextureName",	"fileTextureName",	node);
//	o.addRSLVariable("vector", "outColor",	"outColor",	node);
//	o.addToRSL("ei_shader_param_texture(\"fileTextureName\", texturename1)");
	o.endRSL();
}
//
void Visitor::visitChecker(const char* node)
{
	OutputHelper o;

	o.beginRSL(node);

	ei_shader_param_string("desc", "maya_checker_uv");
	o.addRSLVariable("color",  "color1",	"color1",	node);
	o.addRSLVariable("color",  "color2",	"color2",	node);
	o.addRSLVariable("vector", "uvCoord",	"uvCoord",	node);
	o.addRSLVariable("color",  "outColor",	"outColor",	node);

	o.endRSL();
}
}//namespace ERCall