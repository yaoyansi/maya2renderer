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
		static void writeRSL(const char* node);

	protected:
		virtual void setValidConnection();

	};
	//
	class Blinn : public liquidmaya::Shader
	{
	public:
		Blinn();
		virtual ~Blinn();
		static void writeRSL(const char* node);

	protected:
		virtual void setValidConnection();

	};
	//
	//
	//////////////////////////////////////////////////////////////////////////
	liquidmaya::Shader* getShader();
}

#endif//_MAYA_SHADER_MATERIAL_H_