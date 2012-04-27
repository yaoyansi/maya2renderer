#include "shaderOutputRSL.h"
#include "../common/mayacheck.h"
#include "../shadergraph/shadermgr.h"
#include "ri_interface.h"
#include <trace/trace.hpp>
#include <liqGlobalHelpers.h>

namespace RSL
{
/// 2D Texture ///
// @node	maya shader node name
void Visitor::visitBulge(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitBulge("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitChecker(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitChecker("<<node<<")");

	OutputHelper o(RSLfile);

	o.addInclude("checker.h");

	o.beginRSL(node);
	//input
	o.addRSLVariable(       "", "float",  "alphaGain",		"alphaGain",	node);
	o.addRSLVariable("uniform", "float",  "alphaIsLuminance","alphaIsLuminance",node);
	o.addRSLVariable(       "", "float",  "alphaOffset",	"alphaOffset",	node);
	o.addRSLVariable(       "", "color",  "color1",			"color1",		node);
	o.addRSLVariable(       "", "color",  "color2",			"color2",		node);
	o.addRSLVariable(       "", "color",  "colorGain",		"colorGain",	node);
	o.addRSLVariable(       "", "color",  "colorOffset",	"colorOffset",	node);
	o.addRSLVariable("uniform", "float",  "contrast",		"contrast",		node);
	o.addRSLVariable(       "", "color",  "defaultColor",	"defaultColor",	node);
	o.addRSLVariable(       "", "float",  "filter",			"filter",		node);
	o.addRSLVariable(       "", "float",  "filterOffset",	"filterOffset",	node);
	o.addRSLVariable("uniform", "float",  "invert",			"invert",		node);
	o.addRSLVariable(       "", "float2", "uvCoord",		"uvCoord",		node);
	//Output
	o.addRSLVariable(       "", "float",  "outAlpha",		"outAlpha",		node);
	o.addRSLVariable(       "", "vector",  "outColor",		"outColor",		node);

	o.addToRSL("{");
	o.addToRSL("  color _outColor;");
	o.addToRSL("  maya_checker("
					//Inputs
					"alphaGain,         \n\t"
					"alphaIsLuminance,  \n\t"
					"alphaOffset,       \n\t"
					"color1,            \n\t"
					"color2,            \n\t"
					"colorGain,         \n\t"
					"colorOffset,       \n\t"
					"contrast,          \n\t"
					"defaultColor,      \n\t"
					"filter,            \n\t"
					"filterOffset,      \n\t"
					"invert,            \n\t"
					"uvCoord,           \n\t"
					//Outputs
					"outAlpha,          \n\t"
					"_outColor          \n"
			"   );");
	o.addToRSL("  outColor        = vector _outColor;");
	o.addToRSL("}");

	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitCloth(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitCloth("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitFile(const char* node)
{	
	CM_TRACE_FUNC("Visitor::visitFile("<<node<<")");

	OutputHelper o(RSLfile);

	o.addInclude("file.h");

	o.beginRSL( node );

	MString mayaTexName(getFileNodeImageName(node));
	MString texName = mayaTexName + ".tex";
	//system("txmake mayaTexName texName");
	IfMErrorWarn(MGlobal::executeCommand("system(\"txmake "+mayaTexName+" "+texName+"\")", true));

	//input
	o.addRSLVariable(       "", "float",  "alphaGain",		"alphaGain",	node);
	o.addRSLVariable("uniform", "float",  "alphaIsLuminance",	"alphaIsLuminance",	node);
	o.addRSLVariable(       "", "float",  "alphaOffset",	"alphaOffset",	node);
	o.addRSLVariable(       "", "color",  "colorGain",		"colorGain",	node);
	o.addRSLVariable(       "", "color",  "colorOffset",	"colorOffset",	node);
	o.addRSLVariable(       "", "color",  "defaultColor",	"defaultColor",	node);
	o.addRSLVariable(       "", "float2", "uvCoord",		"uvCoord",node);
	//texName
	o.addRSLVariable("uniform", "float", "filterType",		"filterType",	node);
	o.addRSLVariable("uniform", "float", "filter",			"filter",		node);
	o.addRSLVariable(       "", "float", "filterOffset",	"filterOffset",	node);
	o.addRSLVariable("uniform", "float", "invert",			"invert",		node);
	o.addRSLVariable("uniform", "float", "fileHasAlpha",	"fileHasAlpha",	node);
	//o.addRSLVariable("index", "num_channels",	"num_channels",	node);
	//output
	o.addRSLVariable(       "", "float", "outAlpha",		"outAlpha",		node);
	o.addRSLVariable(       "", "vector", "outColor",		"outColor",		node);
	o.addRSLVariable(       "", "vector", "outTransparency",	"outTransparency",	node);


	o.addToRSL("{");
	o.addToRSL("  color _outColor;");
	o.addToRSL("  color _outTransparency;");
	o.addToRSL("  maya_file("
						//Inputs
						"alphaGain,         \n\t"
						"alphaIsLuminance,  \n\t"
						"alphaOffset,       \n\t"
						"colorGain,         \n\t"
						"colorOffset,       \n\t"
						"defaultColor,      \n\t"
						"\""+texName+"\",   \n\t"
						"filterType,        \n\t"
						"filter,            \n\t"
						"filterOffset,      \n\t"
						"invert,            \n\t"
						"uvCoord,           \n\t"
						//Outputs
						"outAlpha,          \n\t"
						"_outColor,         \n\t"
						"_outTransparency   \n"
			   "   );");

	o.addToRSL("  outColor        = vector _outColor;");
	o.addToRSL("  outTransparency = vector _outTransparency;");

	o.addToRSL("}");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitFluidTexture2D(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitFluidTexture2D("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitFractal(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitFractal("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitGrid(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitGrid("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitMountain(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitMountain("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitMovie(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitMovie("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitNoise(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitNoise("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitOcean(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitOcean("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitPSDFileTex(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitPSDFileTex("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitRamp(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitRamp("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitWater(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitWater("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// 3D Textures ///
// @node	maya shader node name
void Visitor::visitBrownian(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitBrownian("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitCloud(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitCloud("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitCrater(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitCrater("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitFluidTexture3D(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitFluidTexture3D("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitGranite(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitGranite("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitLeather(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitLeather("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitMarbler(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitMarbler("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitRock(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitRock("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSnow(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitSnow("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSolidFractal(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitSolidFractal("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitStucco(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitStucco("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitVolumeNoise(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitVolumeNoise("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitWood(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitWood("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// Env Textures ///
// @node	maya shader node name
void Visitor::visitEnvBall(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitEnvBall("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitEnvChrome(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitEnvChrome("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitEnvCube(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitEnvCube("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitEnvSky(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitEnvSky("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitEnvSphere(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitEnvSphere("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// other textures ///
// @node	maya shader node name
void Visitor::visitLayeredTexture(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitLayeredTexture("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}

}//namespace RSL