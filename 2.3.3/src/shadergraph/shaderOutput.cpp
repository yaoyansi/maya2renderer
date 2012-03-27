#include "shaderOutput.h"
#include <liqlog.h>
#include "../common/mayacheck.h"

namespace liquidmaya{

	ShaderOutputVisitor::ShaderOutputVisitor()
	{

	}
	ShaderOutputVisitor::~ShaderOutputVisitor()
	{

	}
	void ShaderOutputVisitor::_outputUpstreamShader(const char* shaderNodeName, const char* nodetype)
	{	
		CM_TRACE_FUNC("ShaderOutputVisitor::_outputUpstreamShader("<<shaderNodeName<<","<<nodetype<<")");
		// MATERIAL -----------------------------------
		/// surface ///
		if( strcmp("anisotropic", nodetype) == 0 ){
			visitAnisotropic(shaderNodeName);
		}
		else if( strcmp("blinn", nodetype) == 0 ){
			visitBlinn(shaderNodeName);
		}
		else if( strcmp("hairTubeShader", nodetype) == 0 ){
			visitHairTubeShader(shaderNodeName);
		}
		else if( strcmp("lambert", nodetype) == 0 )
		{
			visitLambert(shaderNodeName);
		}
		else if( strcmp("layeredShader", nodetype) == 0 )
		{
			visitLayeredShader(shaderNodeName);
		}
		else if( strcmp("oceanShader", nodetype) == 0 )
		{
			visitOceanShader(shaderNodeName);
		}
		else if( strcmp("phong", nodetype) == 0 )
		{
			visitPhong(shaderNodeName);
		}
		else if( strcmp("phongE", nodetype) == 0 )
		{
			visitPhongE(shaderNodeName);
		}
		else if( strcmp("rampShader", nodetype) == 0 )
		{
			visitRampShader(shaderNodeName);
		}
		else if( strcmp("shadingMap", nodetype) == 0 )
		{
			visitShadingMap(shaderNodeName);
		}
		else if( strcmp("surfaceShader", nodetype) == 0 )
		{
			visitSurfaceShader(shaderNodeName);
		}
		else if( strcmp("useBackground", nodetype) == 0 )
		{
			visitUseBackground(shaderNodeName);
		}
		/// Volumetric ///
		else if( strcmp("envFog", nodetype) == 0 )
		{
			visitEnvFog(shaderNodeName);
		}
		else if( strcmp("fluidShape", nodetype) == 0 )
		{
			visitFluidShape(shaderNodeName);
		}
		else if( strcmp("lightFog", nodetype) == 0 )
		{
			visitLightFog(shaderNodeName);
		}
		else if( strcmp("particleCloud", nodetype) == 0 )
		{
			visitParticleCloud(shaderNodeName);
		}
		else if( strcmp("volumeFog", nodetype) == 0 )
		{
			visitVolumeFog(shaderNodeName);
		}
		else if( strcmp("volumeShader", nodetype) == 0 )
		{
			visitVolumeShader(shaderNodeName);
		}
		/// DISPLACEMENT ///
		else if( strcmp("cMuscleShader", nodetype) == 0 )
		{
			visitCMuscleShader(shaderNodeName);
		}
		else if( strcmp("displacementShader", nodetype) == 0 )
		{
			visitDisplacementShader(shaderNodeName);
		}
		/// 2D Texture ///
		else if( strcmp("bulge", nodetype) == 0 ){
			visitBulge(shaderNodeName);
		}
		else if( strcmp("checker", nodetype) == 0 ){
			visitChecker(shaderNodeName);
		}
		else if( strcmp("cloth", nodetype) == 0 ){
			visitCloth(shaderNodeName);
		}
		else if( strcmp("file", nodetype) == 0 ){
			visitFile(shaderNodeName);
		}
		else if( strcmp("fluidTexture2D", nodetype) == 0 ){
			visitFluidTexture2D(shaderNodeName);
		}
		else if( strcmp("fractal", nodetype) == 0 ){
			visitFractal(shaderNodeName);
		}
		else if( strcmp("grid", nodetype) == 0 ){
			visitGrid(shaderNodeName);
		}
		else if( strcmp("mountain", nodetype) == 0 ){
			visitMountain(shaderNodeName);
		}
		else if( strcmp("movie", nodetype) == 0 ){
			visitMovie(shaderNodeName);
		}
		else if( strcmp("noise", nodetype) == 0 ){
			visitNoise(shaderNodeName);
		}
		else if( strcmp("ocean", nodetype) == 0 ){
			visitOcean(shaderNodeName);
		}
		else if( strcmp("psdFileTex", nodetype) == 0 ){
			visitPSDFileTex(shaderNodeName);
		}
		else if( strcmp("ramp", nodetype) == 0 ){
			visitRamp(shaderNodeName);
		}
		else if( strcmp("water", nodetype) == 0 ){
			visitWater(shaderNodeName);
		}
		/// 3D Textures ///
		else if( strcmp("brownian", nodetype) == 0 ){
			visitBrownian(shaderNodeName);
		}
		else if( strcmp("cloud", nodetype) == 0 ){
			visitCloud(shaderNodeName);
		}
		else if( strcmp("crater", nodetype) == 0 ){
			visitCrater(shaderNodeName);
		}
		else if( strcmp("fluidTexture3D", nodetype) == 0 ){
			visitFluidTexture3D(shaderNodeName);
		}
		else if( strcmp("granite", nodetype) == 0 ){
			visitGranite(shaderNodeName);
		}
		else if( strcmp("leather", nodetype) == 0 ){
			visitLeather(shaderNodeName);
		}
		else if( strcmp("marble", nodetype) == 0 ){
			visitMarbler(shaderNodeName);
		}
		else if( strcmp("rock", nodetype) == 0 ){
			visitRock(shaderNodeName);
		}
		else if( strcmp("snow", nodetype) == 0 ){
			visitSnow(shaderNodeName);
		}
		else if( strcmp("solidFractal", nodetype) == 0 ){
			visitSolidFractal(shaderNodeName);
		}
		else if( strcmp("stucco", nodetype) == 0 ){
			visitStucco(shaderNodeName);
		}
		else if( strcmp("volumeNoise", nodetype) == 0 ){
			visitVolumeNoise(shaderNodeName);
		}
		else if( strcmp("wood", nodetype) == 0 ){
			visitWood(shaderNodeName);
		}
		/// Env Textures ///
		else if( strcmp("envBall", nodetype) == 0 ){
			visitEnvBall(shaderNodeName);
		}
		else if( strcmp("envChrome", nodetype) == 0 ){
			visitEnvChrome(shaderNodeName);
		}
		else if( strcmp("envCube", nodetype) == 0 ){
			visitEnvCube(shaderNodeName);
		}
		else if( strcmp("envSky", nodetype) == 0 ){
			visitEnvSky(shaderNodeName);
		}
		else if( strcmp("envSphere", nodetype) == 0 ){
			visitEnvSphere(shaderNodeName);
		}
		/// other textures ///
		else if( strcmp("layeredTexture", nodetype) == 0 ){
			visitLayeredTexture(shaderNodeName);
		}
		/// Lights ///
		else if( strcmp("ambientLight", nodetype) == 0 ){
			visitAmbientLight(shaderNodeName);
		}
		else if( strcmp("areaLight", nodetype) == 0 ){
			visitAreaLight(shaderNodeName);
		}
		else if( strcmp("directionalLight", nodetype) == 0 ){
			visitDirectionalLight(shaderNodeName);
		}
		else if( strcmp("pointLight", nodetype) == 0 ){
			visitPointLight(shaderNodeName);
		}
		else if( strcmp("spotLight", nodetype) == 0 ){
			visitSpotLight(shaderNodeName);
		}
		else if( strcmp("volumeLight", nodetype) == 0 ){
			visitVolumeLight(shaderNodeName);
		}
		/// General utilities ///
		else if( strcmp("arrayMapper", nodetype) == 0 ){
			visitArrayMapper(shaderNodeName);
		}
		else if( strcmp("bump2d", nodetype) == 0 ){
			visitBump2d(shaderNodeName);
		}
		else if( strcmp("bump3d", nodetype) == 0 ){
			visitBump3d(shaderNodeName);
		}
		else if( strcmp("condition", nodetype) == 0 ){
			visitCondition(shaderNodeName);
		}
		else if( strcmp("distanceBetween", nodetype) == 0 ){
			visitDistanceBetween(shaderNodeName);
		}
		else if( strcmp("heightField", nodetype) == 0 ){
			visitHeightField(shaderNodeName);
		}
		else if( strcmp("lightInfo", nodetype) == 0 ){
			visitLightInfo(shaderNodeName);
		}
		else if( strcmp("multiplyDivide", nodetype) == 0 ){
			visitMultiplyDivide(shaderNodeName);
		}
		else if( strcmp("place2dTexture", nodetype) == 0 ){
			visitPlace2dTexture(shaderNodeName);
		}
		else if( strcmp("place3dTexture", nodetype) == 0 ){
			visitPlace3dTexture(shaderNodeName);
		}
		else if( strcmp("plusMinusAverage", nodetype) == 0 ){
			visitPlusMinusAverage(shaderNodeName);
		}
		else if( strcmp("projection", nodetype) == 0 ){
			visitProjection(shaderNodeName);
		}
		else if( strcmp("reverse", nodetype) == 0 ){
			visitReverse(shaderNodeName);
		}
		else if( strcmp("samplerInfo", nodetype) == 0 ){
			visitSamplerInfo(shaderNodeName);
		}
		else if( strcmp("setRange", nodetype) == 0 ){
			visitSetRange(shaderNodeName);
		}
		else if( strcmp("stencil", nodetype) == 0 ){
			visitStencil(shaderNodeName);
		}
		else if( strcmp("studioClearCoat", nodetype) == 0 ){
			visitStudioClearCoat(shaderNodeName);
		}
		else if( strcmp("uvChooser", nodetype) == 0 ){
			visitUVChooser(shaderNodeName);
		}
		else if( strcmp("vectorProduct", nodetype) == 0 ){
			visitVectorProduct(shaderNodeName);
		}
		/// color utilities ///
		else if( strcmp("blendColors", nodetype) == 0 ){
			visitBlendColors(shaderNodeName);
		}
		else if( strcmp("clamp", nodetype) == 0 ){
			visitClamp(shaderNodeName);
		}
		else if( strcmp("contrast", nodetype) == 0 ){
			visitContrast(shaderNodeName);
		}
		else if( strcmp("gammaCorrect", nodetype) == 0 ){
			visitGammaCorrect(shaderNodeName);
		}
		else if( strcmp("hsvToRgb", nodetype) == 0 ){
			visitHsvToRgb(shaderNodeName);
		}
		else if( strcmp("luminance", nodetype) == 0 ){
			visitLuminance(shaderNodeName);
		}
		else if( strcmp("remapColor", nodetype) == 0 ){
			visitRemapColor(shaderNodeName);
		}
		else if( strcmp("remapHsv", nodetype) == 0 ){
			visitrRemapHsv(shaderNodeName);
		}
		else if( strcmp("remapValue", nodetype) == 0 ){
			visitRemapValue(shaderNodeName);
		}
		else if( strcmp("rgbToHsv", nodetype) == 0 ){
			visitRgbToHsv(shaderNodeName);
		}
		else if( strcmp("smear", nodetype) == 0 ){
			visitSmear(shaderNodeName);
		}
		else if( strcmp("surfaceLuminance", nodetype) == 0 ){
			visitSurfaceLuminance(shaderNodeName);
		}
		/// switch utilities ///
		else if( strcmp("doubleShadingSwitch", nodetype) == 0 ){
			visitDoubleShadingSwitch(shaderNodeName);
		}
		else if( strcmp("quadShadingSwitch", nodetype) == 0 ){
			visitQuadShadingSwitch(shaderNodeName);
		}
		else if( strcmp("singleShadingSwitch", nodetype) == 0 ){
			visitSingleShadingSwitch(shaderNodeName);
		}
		else if( strcmp("tripleShadingSwitch", nodetype) == 0 ){
			visitTripleShadingSwitch(shaderNodeName);
		}
		/// particle utilities ///		
		else if( strcmp("particleSamplerInfo", nodetype) == 0 ){
			visitParticleSamplerInfo(shaderNodeName);
		}
		/// image planes ///
		else if( strcmp("imagePlane", nodetype) == 0 ){
			visitImagePlane(shaderNodeName);
		}
		/// glow ///
		else if( strcmp("opticalFX", nodetype) == 0 ){
			visitOpticalFX(shaderNodeName);
		}
		else{
			liquidMessage2(messageError, ("shader type <"+std::string(nodetype)+"> is not supported.").c_str() );
			assert( 0 && "shader type is not support.");
		}
	}
}//namespace liquidmaya