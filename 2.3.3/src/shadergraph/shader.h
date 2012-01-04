#ifndef _SHADER_H_
#define _SHADER_H_

namespace liquid
{
	class ShaderInterface
	{
	public:
		ShaderInterface(){}
		virtual ~ShaderInterface() = 0{}
	private:
		ShaderInterface(const ShaderInterface&);
		ShaderInterface& operator=(const ShaderInterface&);
	};
}


#endif//_SHADER_H_