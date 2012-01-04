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
		static void writeRSL(const char* node, std::ofstream& RSLfile);

	protected:
		virtual void setValidConnection();
	private:
		Lambert(const Lambert&);
		Lambert& operator=(const Lambert&);
	};
	//
	class Blinn : public liquidmaya::Shader
	{
	public:
		Blinn();
		virtual ~Blinn();
		static void writeRSL(const char* node, std::ofstream& RSLfile);

	protected:
		virtual void setValidConnection();
	private:
		Blinn(const Blinn&);
		Blinn& operator=(const Blinn&);
	};
	//
	//
	//////////////////////////////////////////////////////////////////////////
	liquidmaya::Shader* getShader();
}

#endif//_MAYA_SHADER_MATERIAL_H_