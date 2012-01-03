#ifndef _MAYA_SHADER_H_
#define _MAYA_SHADER_H_

#include "shader.h"
#include "../common/prerequest_std.h"
#include "../common/prerequest_maya.h"

namespace liquidmaya
{
	class Shader : public liquid::ShaderInterface
	{
	public:
		//typedef std::vector<std::string> ConnectionList;
	public:
		Shader();
		virtual ~Shader();

		const MStringArray& getValidConnectionRef() const;

		//virtual void writeRSL(const char* nodename) const = 0;

	protected:
		virtual void setValidConnection() = 0;

		MStringArray validConnection;
	};
}



#endif//_MAYA_SHADER_H_