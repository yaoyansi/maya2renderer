#ifndef _SHADER_OUTPUT_H_
#define _SHADER_OUTPUT_H_

namespace liquidmaya{

// Visitor Pattern
class ShaderOutputVisitor
{
public:
	ShaderOutputVisitor();
	virtual ~ShaderOutputVisitor();

	virtual void preOutput(const char* shaderNodeName) = 0;
	virtual void outputBegin(const char* shaderNodeName) = 0;
	virtual void outputUpstreamShader(const char* shaderNodeName) = 0;
	virtual void outputShaderMethod(
		const char* shaderName,
		const char* shaderMethodVariavles,
		const char* shaderMethodBody
		) = 0;
	virtual void outputEnd() = 0;
	virtual void postOutput() = 0;
	virtual void outputShadingGroup(const char* shadingGroupNode) = 0;
	//
	/// surface ///
	// @node	maya shader node name
	virtual void visitAnisotropic(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitBlinn(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitHairTubeShader(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitLambert(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitLayeredShader(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitOceanShader(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitPhong(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitPhongE(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitRampShader(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitShadingMap(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitSurfaceShader(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitUseBackground(const char* node) = 0;
	/// Volumetric ///
	// @node	maya shader node name
	virtual void visitEnvFog(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitFluidShape(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitLightFog(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitParticleCloud(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitVolumeFog(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitVolumeShader(const char* node) = 0;
	/// DISPLACEMENT ///
	// @node	maya shader node name
	virtual void visitCMuscleShader(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitDisplacementShader(const char* node) = 0;
	/// 2D Texture ///
	// @node	maya shader node name
	virtual void visitBulge(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitChecker(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitCloth(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitFile(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitFluidTexture2D(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitFractal(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitGrid(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitMountain(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitMovie(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitNoise(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitOcean(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitPSDFileTex(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitRamp(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitWater(const char* node) = 0;
	/// 3D Textures ///
	// @node	maya shader node name
	virtual void visitBrownian(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitCloud(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitCrater(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitFluidTexture3D(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitGranite(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitLeather(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitMarbler(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitRock(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitSnow(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitSolidFractal(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitStucco(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitVolumeNoise(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitWood(const char* node) = 0;
	/// Env Textures ///
	// @node	maya shader node name
	virtual void visitEnvBall(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitEnvChrome(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitEnvCube(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitEnvSky(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitEnvSphere(const char* node) = 0;
	/// other textures ///
	// @node	maya shader node name
	virtual void visitLayeredTexture(const char* node) = 0;
	/// Lights ///
	// @node	maya shader node name
	virtual void visitAmbientLight(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitAreaLight(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitDirectionalLight(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitPointLight(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitSpotLight(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitVolumeLight(const char* node) = 0;
	/// General utilities ///
	// @node	maya shader node name
	virtual void visitArrayMapper(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitBump2d(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitBump3d(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitCondition(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitDistanceBetween(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitHeightField(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitLightInfo(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitMultiplyDivide(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitPlace2dTexture(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitPlace3dTexture(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitPlusMinusAverage(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitProjection(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitReverse(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitSamplerInfo(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitSetRange(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitStencil(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitStudioClearCoat(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitUVChooser(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitVectorProduct(const char* node) = 0;
	/// color utilities ///
	// @node	maya shader node name
	virtual void visitBlendColors(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitClamp(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitContrast(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitGammaCorrect(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitHsvToRgb(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitLuminance(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitRemapColor(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitrRemapHsv(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitRemapValue(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitRgbToHsv(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitSmear(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitSurfaceLuminance(const char* node) = 0;
	/// switch utilities ///
	// @node	maya shader node name
	virtual void visitDoubleShadingSwitch(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitQuadShadingSwitch(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitSingleShadingSwitch(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitTripleShadingSwitch(const char* node) = 0;
	/// particle utilities ///	
	// @node	maya shader node name
	virtual void visitParticleSamplerInfo(const char* node) = 0;
	/// image planes ///
	// @node	maya shader node name
	virtual void visitImagePlane(const char* node) = 0;
	/// glow ///
	// @node	maya shader node name
	virtual void visitOpticalFX(const char* node) = 0;

	///mentalray shaders
	/// mib_amb_occlusion ///
	virtual void visit_mib_amb_occlusion(const char* node) = 0;

protected:
	void _outputUpstreamShader(const char* shaderNodeName, const char* nodetype);

private:
	ShaderOutputVisitor(const ShaderOutputVisitor&);
	ShaderOutputVisitor& operator=(const ShaderOutputVisitor&);
};
//

}//namespace liquidmaya
#endif//_SHADER_OUTPUT_H_