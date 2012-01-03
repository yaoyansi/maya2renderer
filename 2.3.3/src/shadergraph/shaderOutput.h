#ifndef _SHADER_OUTPUT_H_
#define _SHADER_OUTPUT_H_

namespace liquidmaya{

class ShaderOutput
{
public:
	ShaderOutput();
	virtual ~ShaderOutput();

	virtual void outputBegin(const char* shaderNodeName) = 0;

	virtual void outputUpstreamShader(const char* shaderNodeName) = 0;
	
	virtual void outputShaderMethod(
		const char* shaderName,
		const char* shaderMethodVariavles,
		const char* shaderMethodBody
		) = 0;
	
	virtual void outputEnd() = 0;

};

}//namespace liquidmaya
#endif//_SHADER_OUTPUT_H_