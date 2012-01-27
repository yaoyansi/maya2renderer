#include "shaderOutputERCall.h"
#include <liqlog.h>
#include "../common/mayacheck.h"
#include "../shadergraph/convertShadingNetwork.h"
#include "../shadergraph/shadermgr.h"

#include <eiAPI/ei.h>

namespace ERCall
{
/// General utilities ///
// @node	maya shader node name
void Visitor::visitArrayMapper(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitBump2d(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitBump3d(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitCondition(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitDistanceBetween(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitHeightField(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitLightInfo(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitMultiplyDivide(const char* node)
{

}
	void Visitor::visitPlace2dTexture(const char* node)
	{
		OutputHelper o;

		o.beginRSL(node);

		ei_shader_param_string("desc", "maya_place2dTexture");
		o.addRSLVariable("vector",  "repeatUV",	"repeatUV",	node);
		o.addRSLVariable("vector",  "outUV",	"outUV",	node);

		o.endRSL();
	}
// @node	maya shader node name
void Visitor::visitPlace3dTexture(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitPlusMinusAverage(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitProjection(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitReverse(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitSamplerInfo(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitSetRange(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitStencil(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitStudioClearCoat(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitUVChooser(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitVectorProduct(const char* node)
{

}
/// color utilities ///
// @node	maya shader node name
void Visitor::visitBlendColors(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitClamp(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitContrast(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitGammaCorrect(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitHsvToRgb(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitLuminance(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitRemapColor(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitrRemapHsv(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitRemapValue(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitRgbToHsv(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitSmear(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitSurfaceLuminance(const char* node)
{

}
/// switch utilities ///
// @node	maya shader node name
void Visitor::visitDoubleShadingSwitch(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitQuadShadingSwitch(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitSingleShadingSwitch(const char* node)
{

}
// @node	maya shader node name
void Visitor::visitTripleShadingSwitch(const char* node)
{

}
/// particle utilities ///	
// @node	maya shader node name
void Visitor::visitParticleSamplerInfo(const char* node)
{

}
/// image planes ///
// @node	maya shader node name
void Visitor::visitImagePlane(const char* node)
{

}
/// glow ///
// @node	maya shader node name
void Visitor::visitOpticalFX(const char* node)
{

}
}//namespace ERCall