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
	std::string lowercase(shadertype);
	std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), std::tolower);

	if( hasShaderType(lowercase.c_str()) ){
		return validConnectionMap.find(lowercase)->second;
	}else{
		liquidMessage2(messageError, "shader type \"%s\" is not supported.", lowercase);
		return validConnectionMap.find("null")->second;
	}
}

}//namespace liquidmaya