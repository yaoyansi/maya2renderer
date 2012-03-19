#include "shaderOutputERCall.h"
#include <liqlog.h>
#include "../common/mayacheck.h"
#include "../shadergraph/convertShadingNetwork.h"
#include "../shadergraph/shadermgr.h"

#include <eiAPI/ei.h>

namespace ERCall
{
/// 2D Texture ///
// @node	maya shader node name
void Visitor::visitBulge(const char* node)
{

}
void Visitor::visitChecker(const char* node)
{
	OutputHelper o;

	o.beginRSL(node);

	ei_shader_param_string("desc", "maya_checker");
	// Inputs:
	o.addRSLVariable("float",	"alphaGain",		"alphaGain",		node);
	o.addRSLVariable("bool",	"alphaIsLuminance",	"alphaIsLuminance",	node);
	o.addRSLVariable("float",	"alphaOffset",		"alphaOffset",		node);
	o.addRSLVariable("color",	"color1",			"color1",			node);
	o.addRSLVariable("color",	"color2",			"color2",			node);
	o.addRSLVariable("color",	"colorGain",		"colorGain",		node);
	o.addRSLVariable("color",	"colorOffset",		"colorOffset",		node);
	o.addRSLVariable("float",	"contrast",			"contrast",			node);
	o.addRSLVariable("color",	"defaultColor",		"defaultColor",		node);
	o.addRSLVariable("float",	"filter",			"filter",			node);
	o.addRSLVariable("float",	"filterOffset",		"filterOffset",		node);
	o.addRSLVariable("bool",	"invert",			"invert",			node);
	o.addRSLVariable("vector",	"uvCoord",			"uvCoord",			node);
	// Outputs:
	o.addRSLVariable("float",	"outAlpha",			"outAlpha",			node);
	o.addRSLVariable("color",	"outColor",			"outColor",			node);

	o.endRSL();
}
void Visitor::visitCloth(const char* node)
{

}
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
	//input
	o.addRSLVariable("float",  "alphaGain",	"alphaGain",	node);
	o.addRSLVariable("bool",  "alphaIsLuminance",	"alphaIsLuminance",	node);
	o.addRSLVariable("float",  "alphaOffset",	"alphaOffset",	node);
	o.addRSLVariable("color",  "colorGain",	"colorGain",	node);
	o.addRSLVariable("color",  "colorOffset",	"colorOffset",	node);
	o.addRSLVariable("color",  "defaultColor",	"defaultColor",	node);
	o.addRSLVariable("vector",  "uvCoord",	"uvCoord",	node);
	o.addRSLVariable("texture", "fileTextureName",	"fileTextureName",	node);
	o.addRSLVariable("index", "filterType",	"filterType",	node);
	o.addRSLVariable("float",  "filter",	"filter",	node);
	o.addRSLVariable("float",  "filterOffset",	"filterOffset",	node);
	o.addRSLVariable("bool",  "invert",	"invert",	node);
	o.addRSLVariable("bool",  "fileHasAlpha",	"fileHasAlpha",	node);
	//o.addRSLVariable("index", "num_channels",	"num_channels",	node);
	//output
	o.addRSLVariable("float", "outAlpha",	"outAlpha",	node);
	o.addRSLVariable("color", "outColor",	"outColor",	node);
	o.addRSLVariable("color", "outTransparency",	"outTransparency",	node);
	o.endRSL();
}
//
//
// @node	maya shader node name
void Visitor::visitFluidTexture2D(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitFractal(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitGrid(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitMountain(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitMovie(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitNoise(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitOcean(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitPSDFileTex(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitRamp(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitWater(const char* node)
{

}
/// 3D Textures ///
// @node	maya shader node name
void Visitor::visitBrownian(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitCloud(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitCrater(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitFluidTexture3D(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitGranite(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitLeather(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitMarbler(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitRock(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitSnow(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitSolidFractal(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitStucco(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitVolumeNoise(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitWood(const char* node)
{

}
/// Env Textures ///
// @node	maya shader node name
void Visitor::visitEnvBall(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitEnvChrome(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitEnvCube(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitEnvSky(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitEnvSphere(const char* node)
{

}
/// other textures ///
// @node	maya shader node name
void Visitor::visitLayeredTexture(const char* node)
{

}
}//namespace ERCall