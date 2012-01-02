#include "mayashader.h"

namespace liquidmaya
{

	Shader::Shader()
	{

	}
	//
	Shader::~Shader()
	{

	}
	//
	const MStringArray&
	Shader::getValidConnectionRef() const
	{
		assert(validConnection.length()!=0);
		return validConnection;
	}
	//
}