#ifndef _SHADER_OUTPUT_RSL_H_
#define _SHADER_OUTPUT_RSL_H_

#include "../common/prerequest_maya.h"
#include "../shadergraph/shaderOutput.h"

namespace RSL{

class OutputHelper
{
public:
	OutputHelper(std::ofstream& RSLfile);
	~OutputHelper();

	//--------------------------------------------------------------------
	// Perform the necessary setup to allow a variable to be used in the
	// current block (function) of RSL code.
	//
	// If the associated Maya plug is connected to a node we can convert,
	// then the variable is added to the block's header as an input/output
	// parameter.
	//
	// If the plug is not connected, or is connected to a node we can not
	// convert, then the variable is added to the block's body, and the
	// current Maya value is pulled in.
	//--------------------------------------------------------------------
	void addRSLVariable(MString rslType, const MString& rslName,
		const MString& mayaName, const MString& mayaNode);
	
	//--------------------------------------------------------------------
	// Add a segment of code to the current RSL block (function).
	//--------------------------------------------------------------------
	void addToRSL(const MString& code);

	//--------------------------------------------------------------------
	// Begin a new block (function) of RSL code.
	//--------------------------------------------------------------------
	void beginRSL (const MString& $name);

	//--------------------------------------------------------------------
	// End the current block (function) of RSL code.
	//--------------------------------------------------------------------
	void endRSL ();

protected:
	MString rslShaderHeader;
	MString rslShaderBody;

	std::ofstream& RSLfileRef;

private:
	OutputHelper(const OutputHelper&);
	OutputHelper& operator=(const OutputHelper&);
};
//////////////////////////////////////////////////////////////////////////
class Visitor : public liquidmaya::ShaderOutputVisitor
{
public:
	Visitor();
	~Visitor();

	virtual void preOutput(const char* shaderNodeName);
	virtual void outputBegin(const char* shaderNodeName);
	virtual void outputUpstreamShader(const char* shaderNodeName);
	virtual void outputShaderMethod(const char* shaderName,const char* shaderMethodVariavles,const char* shaderMethodBody);
	virtual void outputEnd();
	virtual void postOutput();
	virtual void outputShadingGroup(const char* shadingGroupNode);
	//
	/// surface ///
	// @node	maya shader node name
	virtual void visitAnisotropic(const char* node);
	// @node	maya shader node name
	virtual void visitBlinn(const char* node);
	// @node	maya shader node name
	virtual void visitHairTubeShader(const char* node);
	// @node	maya shader node name
	virtual void visitLambert(const char* node);
	// @node	maya shader node name
	virtual void visitLayeredShader(const char* node);
	// @node	maya shader node name
	virtual void visitOceanShader(const char* node);
	// @node	maya shader node name
	virtual void visitPhong(const char* node);
	// @node	maya shader node name
	virtual void visitPhongE(const char* node);
	// @node	maya shader node name
	virtual void visitRampShader(const char* node);
	// @node	maya shader node name
	virtual void visitShadingMap(const char* node);
	// @node	maya shader node name
	virtual void visitSurfaceShader(const char* node);
	// @node	maya shader node name
	virtual void visitUseBackground(const char* node);
	/// Volumetric ///
	// @node	maya shader node name
	virtual void visitEnvFog(const char* node);
	// @node	maya shader node name
	virtual void visitFluidShape(const char* node);
	// @node	maya shader node name
	virtual void visitLightFog(const char* node);
	// @node	maya shader node name
	virtual void visitParticleCloud(const char* node);
	// @node	maya shader node name
	virtual void visitVolumeFog(const char* node);
	// @node	maya shader node name
	virtual void visitVolumeShader(const char* node);
	/// DISPLACEMENT ///
	// @node	maya shader node name
	virtual void visitCMuscleShader(const char* node);
	// @node	maya shader node name
	virtual void visitDisplacementShader(const char* node);
	/// 2D Texture ///
	// @node	maya shader node name
	virtual void visitBulge(const char* node);
	// @node	maya shader node name
	virtual void visitChecker(const char* node);
	// @node	maya shader node name
	virtual void visitCloth(const char* node);
	// @node	maya shader node name
	virtual void visitFile(const char* node);
	// @node	maya shader node name
	virtual void visitFluidTexture2D(const char* node);
	// @node	maya shader node name
	virtual void visitFractal(const char* node);
	// @node	maya shader node name
	virtual void visitGrid(const char* node);
	// @node	maya shader node name
	virtual void visitMountain(const char* node);
	// @node	maya shader node name
	virtual void visitMovie(const char* node);
	// @node	maya shader node name
	virtual void visitNoise(const char* node);
	// @node	maya shader node name
	virtual void visitOcean(const char* node);
	// @node	maya shader node name
	virtual void visitPSDFileTex(const char* node);
	// @node	maya shader node name
	virtual void visitRamp(const char* node);
	// @node	maya shader node name
	virtual void visitWater(const char* node);
	/// 3D Textures ///
	// @node	maya shader node name
	virtual void visitBrownian(const char* node);
	// @node	maya shader node name
	virtual void visitCloud(const char* node);
	// @node	maya shader node name
	virtual void visitCrater(const char* node);
	// @node	maya shader node name
	virtual void visitFluidTexture3D(const char* node);
	// @node	maya shader node name
	virtual void visitGranite(const char* node);
	// @node	maya shader node name
	virtual void visitLeather(const char* node);
	// @node	maya shader node name
	virtual void visitMarbler(const char* node);
	// @node	maya shader node name
	virtual void visitRock(const char* node);
	// @node	maya shader node name
	virtual void visitSnow(const char* node);
	// @node	maya shader node name
	virtual void visitSolidFractal(const char* node);
	// @node	maya shader node name
	virtual void visitStucco(const char* node);
	// @node	maya shader node name
	virtual void visitVolumeNoise(const char* node);
	// @node	maya shader node name
	virtual void visitWood(const char* node);
	/// Env Textures ///
	// @node	maya shader node name
	virtual void visitEnvBall(const char* node);
	// @node	maya shader node name
	virtual void visitEnvChrome(const char* node);
	// @node	maya shader node name
	virtual void visitEnvCube(const char* node);
	// @node	maya shader node name
	virtual void visitEnvSky(const char* node);
	// @node	maya shader node name
	virtual void visitEnvSphere(const char* node);
	/// other textures ///
	// @node	maya shader node name
	virtual void visitLayeredTexture(const char* node);
	/// Lights ///
	// @node	maya shader node name
	virtual void visitAmbientLight(const char* node);
	// @node	maya shader node name
	virtual void visitAreaLight(const char* node);
	// @node	maya shader node name
	virtual void visitDirectionalLight(const char* node);
	// @node	maya shader node name
	virtual void visitPointLight(const char* node);
	// @node	maya shader node name
	virtual void visitSpotLight(const char* node);
	// @node	maya shader node name
	virtual void visitVolumeLight(const char* node);
	/// General utilities ///
	// @node	maya shader node name
	virtual void visitArrayMapper(const char* node);
	// @node	maya shader node name
	virtual void visitBump2d(const char* node);
	// @node	maya shader node name
	virtual void visitBump3d(const char* node);
	// @node	maya shader node name
	virtual void visitCondition(const char* node);
	// @node	maya shader node name
	virtual void visitDistanceBetween(const char* node);
	// @node	maya shader node name
	virtual void visitHeightField(const char* node);
	// @node	maya shader node name
	virtual void visitLightInfo(const char* node);
	// @node	maya shader node name
	virtual void visitMultiplyDivide(const char* node);
	// @node	maya shader node name
	virtual void visitPlace2dTexture(const char* node);
	// @node	maya shader node name
	virtual void visitPlace3dTexture(const char* node);
	// @node	maya shader node name
	virtual void visitPlusMinusAverage(const char* node);
	// @node	maya shader node name
	virtual void visitProjection(const char* node);
	// @node	maya shader node name
	virtual void visitReverse(const char* node);
	// @node	maya shader node name
	virtual void visitSamplerInfo(const char* node);
	// @node	maya shader node name
	virtual void visitSetRange(const char* node);
	// @node	maya shader node name
	virtual void visitStencil(const char* node);
	// @node	maya shader node name
	virtual void visitStudioClearCoat(const char* node);
	// @node	maya shader node name
	virtual void visitUVChooser(const char* node);
	// @node	maya shader node name
	virtual void visitVectorProduct(const char* node);
	/// color utilities ///
	// @node	maya shader node name
	virtual void visitBlendColors(const char* node);
	// @node	maya shader node name
	virtual void visitClamp(const char* node);
	// @node	maya shader node name
	virtual void visitContrast(const char* node);
	// @node	maya shader node name
	virtual void visitGammaCorrect(const char* node);
	// @node	maya shader node name
	virtual void visitHsvToRgb(const char* node);
	// @node	maya shader node name
	virtual void visitLuminance(const char* node);
	// @node	maya shader node name
	virtual void visitRemapColor(const char* node);
	// @node	maya shader node name
	virtual void visitrRemapHsv(const char* node);
	// @node	maya shader node name
	virtual void visitRemapValue(const char* node);
	// @node	maya shader node name
	virtual void visitRgbToHsv(const char* node);
	// @node	maya shader node name
	virtual void visitSmear(const char* node);
	// @node	maya shader node name
	virtual void visitSurfaceLuminance(const char* node);
	/// switch utilities ///
	// @node	maya shader node name
	virtual void visitDoubleShadingSwitch(const char* node);
	// @node	maya shader node name
	virtual void visitQuadShadingSwitch(const char* node);
	// @node	maya shader node name
	virtual void visitSingleShadingSwitch(const char* node);
	// @node	maya shader node name
	virtual void visitTripleShadingSwitch(const char* node);
	/// particle utilities ///	
	// @node	maya shader node name
	virtual void visitParticleSamplerInfo(const char* node);
	/// image planes ///
	// @node	maya shader node name
	virtual void visitImagePlane(const char* node);
	/// glow ///
	// @node	maya shader node name
	virtual void visitOpticalFX(const char* node);

	///mentalray shaders
	/// mib_amb_occlusion ///
	virtual void visit_mib_amb_occlusion(const char* node);

protected:
	std::ofstream RSLfile;
private:
	Visitor(const Visitor&);
	Visitor& operator=(const Visitor&);

	std::string shaderNodeName;
};

}//namespace RSL
#endif//_SHADER_OUTPUT_RSL_H_