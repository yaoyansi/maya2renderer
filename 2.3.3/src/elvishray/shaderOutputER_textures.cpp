#include "shaderOutputER.h"
#include <liqlog.h>
#include "../common/mayacheck.h"
//#include "../shadergraph/convertShadingNetwork.h"
//#include "../shadergraph/shadermgr.h"

namespace ER
{

void Visitor::visitFile(const char* node)
{
	OutputHelper o(file);

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
			o.addToRSL( "ei_make_texture(\""+fileImageName+"\",\""+fileTextureName+"\","+
				"EI_TEX_WRAP_CLAMP, EI_TEX_WRAP_CLAMP, EI_FILTER_BOX, 1.0f, 1.0f)" );
		}
		//construct texture node
		//if (ei_file_exists(fileTextureName))
		{
			o.addToRSL( "ei_texture(\""+fileImageName+"\");" );
			o.addToRSL( "ei_file_texture(\""+fileTextureName+"\", eiFALSE);" );
			o.addToRSL( "ei_end_texture();" );
		}
	}


	o.beginRSL(node);

	o.addToRSL("ei_shader_param_string(\"desc\", \"maya_file\");");
	o.addRSLVariable("vector",  "uvCoord",	"uvCoord",	node);
	o.addRSLVariable("texture", "fileTextureName",	"fileTextureName",	node);
//	o.addRSLVariable("vector", "outColor",	"outColor",	node);
//	o.addToRSL("ei_shader_param_texture(\"fileTextureName\", texturename1)");
	o.endRSL();
}
//
void Visitor::visitChecker(const char* node)
{
	OutputHelper o(file);

	o.beginRSL(node);

	o.addToRSL("ei_shader_param_string(\"desc\", \"maya_checker_uv\");");
	o.addRSLVariable("color",  "color1",	"color1",	node);
	o.addRSLVariable("color",  "color2",	"color2",	node);
	o.addRSLVariable("vector", "uvCoord",	"uvCoord",	node);
	o.addRSLVariable("color",  "outColor",	"outColor",	node);

	o.endRSL();
}

}//namespace ER