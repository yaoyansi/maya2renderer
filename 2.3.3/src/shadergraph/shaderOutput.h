#ifndef _SHADER_OUTPUT_H_
#define _SHADER_OUTPUT_H_

namespace liquidmaya{

class ShaderOutput
{
public:
	ShaderOutput();
	virtual ~ShaderOutput();

	virtual void output(const char* shaderNodeName) = 0;


};

}//namespace liquidmaya
#endif//_SHADER_OUTPUT_H_