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

	// material -----------------------------------
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

	//...

	// utility -----------------------------------
	// file
	validConnection.clear();
	validConnection.append("uvCoord");
	validConnection.append("outColor");
	validConnection.append("outTransparency");
	validConnectionMap.insert(std::make_pair("file", validConnection));	
	
	// place2dTexture
	validConnection.clear();
	validConnection.append("repeatUV");
	validConnection.append("outUV");
	validConnectionMap.insert(std::make_pair("place2dTexture", validConnection));	

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