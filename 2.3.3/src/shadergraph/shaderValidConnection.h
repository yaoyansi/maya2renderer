#ifndef _SHADER_VALID_CONNRCTION_H_
#define _SHADER_VALID_CONNRCTION_H_

#include "../common/prerequest_std.h"
#include "../common/prerequest_maya.h"

namespace liquidmaya
{

class ShaderValidConnection
{
public:
	ShaderValidConnection();
	~ShaderValidConnection();


	// @shadertype	e.g. "lambert","blinn",.... lowercase is prefered.
	const MStringArray& getValidConnectionRef(const char* shadertype)const;
	bool hasShaderType(const char* shadertype)const;

protected:
	void setValidConnection();


	std::map<const std::string, MStringArray> validConnectionMap;

private:
	ShaderValidConnection(const ShaderValidConnection&);
	ShaderValidConnection& operator=(const ShaderValidConnection&);
};
}//namespace liquidmaya


#endif//_SHADER_VALID_CONNRCTION_H_