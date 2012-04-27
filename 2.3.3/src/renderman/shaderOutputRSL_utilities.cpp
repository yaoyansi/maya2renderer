#include "shaderOutputRSL.h"
//#include <liqlog.h>
//#include <liqShader.h>
//#include <liqShaderFactory.h>
#include "../common/mayacheck.h"
//#include "../shadergraph/convertShadingNetwork.h"
//#include "../shadergraph/shadermgr.h"
#include "ri_interface.h"
#include <liqGlobalHelpers.h>

namespace RSL
{
/// General utilities ///
// @node	maya shader node name
void Visitor::visitArrayMapper(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitArrayMapper("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitBump2d(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitBump2d("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitBump3d(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitBump3d("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitCondition(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitCondition("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitDistanceBetween(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitDistanceBetween("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitHeightField(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitHeightField("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitLightInfo(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitLightInfo("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitMultiplyDivide(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitMultiplyDivide("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitPlace2dTexture(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitPlace2dTexture("<<node<<")");

	MString coverageU, coverageV;
	MString noiseU, noiseV;
	MString offsetU, offsetV;
	MString repeatU, repeatV;
	MString mirrorU, mirrorV;
	MString rotateFrame;
	MString rotateUV;
	MString stagger;
	MString translateFrameU,translateFrameV;
	MString wrapU, wrapV;
	{
		MObject m_node;
		MStatus status;
		float fvalue;

		getDependNodeByName(m_node, node);
		liquidGetPlugValue(m_node, "coverageU", fvalue, status);  coverageU.set(fvalue);
		liquidGetPlugValue(m_node, "coverageV", fvalue, status);  coverageV.set(fvalue);
		liquidGetPlugValue(m_node, "noiseU", fvalue, status);  noiseU.set(fvalue);
		liquidGetPlugValue(m_node, "noiseV", fvalue, status);  noiseV.set(fvalue);
		liquidGetPlugValue(m_node, "offsetU", fvalue, status);  offsetU.set(fvalue);
		liquidGetPlugValue(m_node, "offsetV", fvalue, status);  offsetV.set(fvalue);
		liquidGetPlugValue(m_node, "repeatU", fvalue, status);  repeatU.set(fvalue);
		liquidGetPlugValue(m_node, "repeatV", fvalue, status);  repeatV.set(fvalue);
		liquidGetPlugValue(m_node, "mirrorU", fvalue, status);  mirrorU.set(fvalue);
		liquidGetPlugValue(m_node, "mirrorV", fvalue, status);  mirrorV.set(fvalue);
		liquidGetPlugValue(m_node, "rotateFrame", fvalue, status);  rotateFrame.set(fvalue);
		liquidGetPlugValue(m_node, "rotateUV", fvalue, status);		rotateUV.set(fvalue);
		liquidGetPlugValue(m_node, "stagger", fvalue, status);		stagger.set(fvalue);
		liquidGetPlugValue(m_node, "translateFrameU", fvalue, status);	translateFrameU.set(fvalue);
		liquidGetPlugValue(m_node, "translateFrameV", fvalue, status);	translateFrameV.set(fvalue);
		liquidGetPlugValue(m_node, "wrapU", fvalue, status);		wrapU.set(fvalue);
		liquidGetPlugValue(m_node, "wrapV", fvalue, status);		wrapV.set(fvalue);
	}

	OutputHelper o(RSLfile);

	o.addInclude("place2dTexture.h");

	o.beginRSL(node);
	// Inputs
	o.addToRSL("extern float s, t;");
	o.addToRSL("float uvCoord[2];");
	o.addToRSL("uvCoord[0] = s;");
	o.addToRSL("uvCoord[1] = 1 - t;");//adjust for Renderman
	o.addRSLVariable("uniform", "float2", "coverage",		"coverage",		node);
	o.addRSLVariable("uniform", "float",  "mirrorU",		"mirrorU",		node);
	o.addRSLVariable("uniform", "float",  "mirrorV",		"mirrorV",		node);
	o.addRSLVariable("uniform", "float2", "noiseUV",		"noiseUV",		node);
	o.addRSLVariable(		"", "float2", "offset",			"offset",		node);
	o.addRSLVariable("uniform", "float2", "repeatUV",		"repeatUV",		node);
	o.addRSLVariable("uniform", "float",  "rotateFrame",	"rotateFrame",	node);
	o.addRSLVariable("uniform", "float",  "rotateUV",		"rotateUV",		node);
	o.addRSLVariable("uniform", "float",  "stagger",		"stagger",		node);
	o.addRSLVariable("uniform", "float2", "translateFrame",	"translateFrame",node);
	o.addRSLVariable("uniform", "float",  "wrapU",			"wrapU",		node);
	o.addRSLVariable("uniform", "float",  "wrapV",			"wrapV",		node);
	// Outputs
	o.addRSLVariable(       "", "float2", "outUV",		"outUV",	node);

	o.addToRSL("{");
	o.addToRSL("uniform float i_coverageU="+coverageU+";");
	o.addToRSL("uniform float i_coverageV="+coverageV+";");
	o.addToRSL("uniform float i_mirrorU="+mirrorU+";");
	o.addToRSL("uniform float i_mirrorV="+mirrorV+";");
	o.addToRSL("uniform float i_noiseU="+noiseU+";");
	o.addToRSL("uniform float i_noiseV="+noiseV+";");
	o.addToRSL("uniform float i_repeatU="+repeatU+";");
	o.addToRSL("uniform float i_repeatV="+repeatV+";");
	o.addToRSL("uniform float i_rotateFrame="+rotateFrame+";");
	o.addToRSL("uniform float i_rotateUV="+rotateUV+";");
	o.addToRSL("uniform float i_stagger="+stagger+";");
	o.addToRSL("uniform float i_translateFrameU="+translateFrameU+";");
	o.addToRSL("uniform float i_translateFrameV="+translateFrameV+";");
	o.addToRSL("uniform float i_wrapU="+wrapU+";");
	o.addToRSL("uniform float i_wrapV="+wrapV+";");
	o.addToRSL("  maya_place2dTexture("
					//Inputs
					"uvCoord,			\n\t"
					"i_coverageU,       \n\t"
					"i_coverageV,		\n\t"
					"i_mirrorU,			\n\t"
					"i_mirrorV,			\n\t"
					"i_noiseU,			\n\t"
					"i_noiseV,			\n\t"
					+offsetU+",			\n\t"
					+offsetV+",			\n\t"
					"i_repeatU,			\n\t"
					"i_repeatV,			\n\t"
					"i_rotateFrame,		\n\t"
					"i_rotateUV,		\n\t"
					"i_stagger,			\n\t"
					"i_translateFrameU,	\n\t"
					"i_translateFrameV,	\n\t"
					"i_wrapU,			\n\t"
					"i_wrapV,			\n\t"
					//Outputs
					"outUV   \n"
			"   );");
	o.addToRSL("}");
	o.addToRSL("coverage[0]="+coverageU+";");
	o.addToRSL("coverage[1]="+coverageV+";");
	o.addToRSL("mirrorU="+mirrorU+";");
	o.addToRSL("mirrorV="+mirrorV+";");
	o.addToRSL("noiseUV[0]="+noiseU+";");
	o.addToRSL("noiseUV[1]="+noiseV+";");
	o.addToRSL("offset[0]="+offsetU+";");
	o.addToRSL("offset[1]="+offsetV+";");
	o.addToRSL("repeatUV[0]="+repeatU+";");
	o.addToRSL("repeatUV[1]="+repeatV+";");
	o.addToRSL("rotateFrame="+rotateFrame+";");
	o.addToRSL("rotateUV="+rotateUV+";");
	o.addToRSL("stagger="+stagger+";");
	o.addToRSL("translateFrame[0]="+translateFrameU+";");
	o.addToRSL("translateFrame[1]="+translateFrameV+";");
	o.addToRSL("wrapU="+wrapU+";");
	o.addToRSL("wrapV="+wrapV+";");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitPlace3dTexture(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitPlace3dTexture("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitPlusMinusAverage(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitPlusMinusAverage("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitProjection(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitProjection("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitReverse(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitReverse("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSamplerInfo(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitSamplerInfo("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSetRange(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitSetRange("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitStencil(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitStencil("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitStudioClearCoat(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitStudioClearCoat("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitUVChooser(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitUVChooser("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitVectorProduct(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitVectorProduct("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// color utilities ///
// @node	maya shader node name
void Visitor::visitBlendColors(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitBlendColors("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitClamp(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitClamp("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitContrast(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitContrast("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitGammaCorrect(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitGammaCorrect("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitHsvToRgb(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitHsvToRgb("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitLuminance(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitLuminance("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitRemapColor(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitRemapColor("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitrRemapHsv(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitrRemapHsv("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitRemapValue(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitRemapValue("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitRgbToHsv(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitRgbToHsv("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSmear(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitSmear("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSurfaceLuminance(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitSurfaceLuminance("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// switch utilities ///
// @node	maya shader node name
void Visitor::visitDoubleShadingSwitch(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitDoubleShadingSwitch("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitQuadShadingSwitch(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitQuadShadingSwitch("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSingleShadingSwitch(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitSingleShadingSwitch("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitTripleShadingSwitch(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitTripleShadingSwitch("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// particle utilities ///	
// @node	maya shader node name
void Visitor::visitParticleSamplerInfo(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitParticleSamplerInfo("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// image planes ///
// @node	maya shader node name
void Visitor::visitImagePlane(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitImagePlane("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// glow ///
// @node	maya shader node name
void Visitor::visitOpticalFX(const char* node)
{
	CM_TRACE_FUNC("Visitor::visitOpticalFX("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}


}//namespace RSL