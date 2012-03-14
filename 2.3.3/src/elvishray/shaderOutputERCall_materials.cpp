#include "shaderOutputERCall.h"
#include <liqlog.h>
#include "../common/mayacheck.h"
#include "../shadergraph/convertShadingNetwork.h"
#include "../shadergraph/shadermgr.h"

#include <eiAPI/ei.h>

namespace ERCall
{
// @node	maya shader node name
void Visitor::visitAnisotropic(const char* node)
{

}
void Visitor::visitBlinn(const char* node)
{
	OutputHelper o;

	o.beginRSL(node);

	ei_shader_param_string("desc", "plastic");

	o.addRSLVariable("vector", "inColor",		"color",		node);
	o.addRSLVariable("vector", "transparency", "transparency", node);
	o.addRSLVariable("vector", "ambColor",		"ambientColor", node);
	o.addRSLVariable("vector", "incandescence","incandescence",node);
	o.addRSLVariable("float",  "diffusion",	"diffuse",		node);
	o.addRSLVariable("float",  "eccentricity", "eccentricity", node);
	o.addRSLVariable("float",  "specRollOff",	"specularRollOff",node);
	o.addRSLVariable("vector", "specColor",	"specularColor",node);
	o.addRSLVariable("vector", "outColor",		"outColor",		node);

//	MStringArray con;
//	IfMErrorWarn(MGlobal::executeCommand( ("listConnections(\""+MString(node)+"\" + \".reflectedColor\")"), con));
//	if( con.length() != 0 )
//	{
//		o.addRSLVariable( "float", "reflectivity", "reflectivity", node);
//		o.addRSLVariable( "vector", "refColor", "reflectedColor", node);
//		o.addToRSL( "Cspecular += ( reflectivity * refColor );");
//	}

	o.endRSL();
}
void Visitor::visitHairTubeShader(const char* node)
{

}
void Visitor::visitLambert(const char* node)
{
	OutputHelper o;

	o.beginRSL(node);

	ei_shader_param_string("desc", "maya_lambert_transparent");

	o.addRSLVariable("vector", "Cs",		"color",		node);
	o.addRSLVariable("vector", "transparency", "transparency", node);
	o.addRSLVariable("vector", "ambientColor",	"ambientColor", node);
	o.addRSLVariable("vector", "incandescence","incandescence",node);
	o.addRSLVariable("float",  "diffusion",	"diffuse",		node);
	o.addRSLVariable("vector", "outColor",		"outColor",		node);
	o.addRSLVariable("vector", "outTransparency","outTransparency",node);

	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitLayeredShader(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitOceanShader(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitPhong(const char* node)
{
	OutputHelper o;
	o.beginRSL(node);

	ei_shader_param_string("desc", "maya_phong");
	//Common Material Attributes
	o.addRSLVariable("vector", "color_",		"color",		node);
	o.addRSLVariable("vector", "transparency",	"transparency", node);
	o.addRSLVariable("vector", "ambientColor",	"ambientColor", node);
	o.addRSLVariable("vector", "incandescence",	"incandescence",node);
	o.addRSLVariable("normal", "normalCamera",	"normalCamera",	node);
	o.addRSLVariable("float",  "diffuse",		"diffuse",		node);
	o.addRSLVariable("float",  "translucence",			"translucence",		node);
	o.addRSLVariable("float",  "translucenceDepth",		"translucenceDepth",node);
	o.addRSLVariable("float",  "translucenceFocus",		"translucenceFocus",node);
	//Specular Shading
	o.addRSLVariable("float",	"cosinePower",			"cosinePower",		node);
	o.addRSLVariable("vector",	"specularColor",		"specularColor",	node);
	o.addRSLVariable("float",	"reflectivity",			"reflectivity",		node);
	o.addRSLVariable("vector",	"reflectedColor",		"reflectedColor",	node);
	//Matte Opacity
	o.addRSLVariable("index",	"matteOpacityMode",		"matteOpacityMode",	node);
	o.addRSLVariable("float",	"matteOpacity",			"matteOpacity",		node);
	//Raytrace Options
	o.addRSLVariable("index",	"reflectionLimit",		"reflectionLimit",	node);
	//output
	o.addRSLVariable("vector", "outColor",		"outColor",		node);
	o.addRSLVariable("vector", "outTransparency","outTransparency",node);

	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitPhongE(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitRampShader(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitShadingMap(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitSurfaceShader(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitUseBackground(const char* node)
{

}
/// Volumetric ///
// @node	maya shader node name
void Visitor::visitEnvFog(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitFluidShape(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitLightFog(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitParticleCloud(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitVolumeFog(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitVolumeShader(const char* node)
{

}
/// DISPLACEMENT ///
// @node	maya shader node name
void Visitor::visitCMuscleShader(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitDisplacementShader(const char* node)
{

}

/// Lights ///
// @node	maya shader node name
void Visitor::visitAmbientLight(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitAreaLight(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitDirectionalLight(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitPointLight(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitSpotLight(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitVolumeLight(const char* node)
{

}
}//namespace ERCall