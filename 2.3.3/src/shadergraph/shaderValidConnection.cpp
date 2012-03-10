#include "shaderValidConnection.h"
#include <liqlog.h>

namespace liquidmaya
{
ShaderValidConnection::ShaderValidConnection()
{
	setValidConnection();
}
//
ShaderValidConnection::~ShaderValidConnection()
{

}
//
void ShaderValidConnection::setValidConnection()
{
	MStringArray validConnection;
	
	//null (dummy shader)
	validConnection.clear();
	validConnection.append("");
	validConnectionMap.insert(std::make_pair("null", validConnection));	

	// MATERIAL -----------------------------------
	/// surface ///
	//anisotropic

	//Hair Tube shader

	//lambert
	validConnection.clear();
	validConnection.append("color");
	validConnection.append("transparency");
	validConnection.append("ambientColor");
	validConnection.append("incandescence");
	validConnection.append("diffuse");
	validConnection.append("outColor");
	validConnection.append("outTransparency");
	validConnectionMap.insert(std::make_pair("lambert", validConnection));	

	//layered shader

	//blinn
	validConnection.clear();
	validConnection.append("color");
	validConnection.append("transparency");
	validConnection.append("ambientColor");
	validConnection.append("incandescence");
	validConnection.append("diffuse");
	validConnection.append("eccentricity");
	validConnection.append("specularRollOff");
	validConnection.append("specularColor");
	validConnection.append("reflectivity");
	validConnection.append("reflectedColor");
	validConnection.append("outColor");
	validConnectionMap.insert(std::make_pair("blinn", validConnection));	

	//ocean shader

	//phong
	validConnection.clear();
	validConnection.append("color");
	validConnection.append("transparency");
	validConnection.append("ambientColor");
	validConnection.append("incandescence");
	validConnection.append("normalCamera");
	validConnection.append("diffuse");
	validConnection.append("translucence");
	validConnection.append("translucenceDepth");
	validConnection.append("translucenceFocus");
	validConnection.append("cosinePower");
	validConnection.append("specularColor");
	validConnection.append("reflectivity");
	validConnection.append("reflectedColor");
	validConnection.append("outColor");
	validConnection.append("outTransparency");
	validConnectionMap.insert(std::make_pair("phong", validConnection));	

	//phongE

	//ramp shader

	//shading map

	//surface shader

	//use background

	/// Volumetric ///
	//EnvFog

	//Fluid Shape

	//LightFog

	//ParticleCloud

	//VolumeFog

	//VolumeShader

	/// DISPLACEMENT ///
	//c muscle shader

	//displacement

	/// 2D Texture (normal)///
	//bulge

	//checker
	validConnection.clear();
	validConnection.append("color1");
	validConnection.append("color1R");
	validConnection.append("color1G");
	validConnection.append("color1B");
	validConnection.append("color2");
	validConnection.append("color2R");
	validConnection.append("color2G");
	validConnection.append("color2B");
	validConnection.append("uvCoord");
	validConnection.append("uCoord");
	validConnection.append("vCoord");
	validConnection.append("outColor");
	validConnection.append("outColorR");
	validConnection.append("outColorG");
	validConnection.append("outColorB");
	validConnectionMap.insert(std::make_pair("checker", validConnection));	

	//cloth

	// file
	validConnection.clear();
	validConnection.append("uvCoord");
	validConnection.append("outColor");
	validConnection.append("outTransparency");
	validConnectionMap.insert(std::make_pair("file", validConnection));	

	//FluidTexture2D

	//Fractal

	//grid

	//mountain

	//movie

	//noise

	//ocean

	//psd file

	//ramp

	//water

	/// 3D Textures ///
	//Brownian

	//cloud

	//crater

	//Fluid Texture 3D

	//granite

	//leather

	//marble

	//rock

	//snow

	//solidFractal

	//stucco

	//volumeNoise

	//wood

	/// Env Textures ///
	//envBall

	//envChrome

	//envCube

	//envSky 

	//envSphere

	/// other textures ///
	//layeredTexture

	/// Lights ///
	//ambientLight

	//areaLight

	//directionalLight

	//pointLight

	//spotLight

	//volumeLight

	/// General utilities ///
	//arrayMapper

	//bump2d

	//bump3d

	//condition

	//distanceBetween

	//heightField

	//lightInfo

	//multiplyDivide

	//place2dTexture
	validConnection.clear();
	validConnection.append("repeatUV");
	validConnection.append("outUV");
	validConnectionMap.insert(std::make_pair("place2dTexture", validConnection));	

	//place3dTexture

	//plusMinusAverage

	//projection

	//reverse

	//samplerInfo

	//setRange

	//stencil

	//studioClearCoat

	//uvChooser

	//vectorProduct

	/// color utilities ///
	//blendColors

	//clamp

	//contrast

	//gammaCorrect

	//hsv to rgb

	//luminance

	//remapColor

	//remapHsv

	//remapValue

	//rgb to hsv

	//smear

	//surfaceLuminance

	/// switch utilities ///
	//double switch

	//quad switch

	//single switch

	//triple switch

	/// particle utilities ///
	//particle sampler

	/// image planes ///
	//image plane

	/// glow ///
	//optical FX




}
//
bool ShaderValidConnection::hasShaderType(const char* shadertype)const
{
	return (validConnectionMap.find(shadertype) != validConnectionMap.end());
}
//
const MStringArray& 
ShaderValidConnection::getValidConnectionRef(const char* shadertype) const
{
	if( hasShaderType(shadertype) ){
		return validConnectionMap.find(shadertype)->second;
	}else{
		liquidMessage2(messageError, "shader type \"%s\" is not supported.", shadertype);
		assert(0&&"shader type is not supported.");
		return validConnectionMap.find("null")->second;
	}
}

}//namespace liquidmaya