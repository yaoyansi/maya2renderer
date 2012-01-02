#ifndef _MAYA_SHADER_MATERIAL_H_
#define _MAYA_SHADER_MATERIAL_H_

#include "mayashader.h"

namespace liquidmaya
{

	class Lambert : public liquidmaya::Shader
	{
	public:
		Lambert();
		virtual ~Lambert();
		virtual void writeRSL(const char* node) const;

	protected:
		virtual void setValidConnection();

	};
	//
	class Blinn : public liquidmaya::Shader
	{
	public:
		Blinn();
		virtual ~Blinn();
		virtual void writeRSL(const char* node) const;

	protected:
		virtual void setValidConnection();

	};
	//
	//
	//////////////////////////////////////////////////////////////////////////
	liquidmaya::Shader* getShader();
}

#endif//_MAYA_SHADER_MATERIAL_H_