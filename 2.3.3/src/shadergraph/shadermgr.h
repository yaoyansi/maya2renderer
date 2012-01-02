
#ifndef _SHADER_MGR_H_
#define _SHADER_MGR_H_

#include "../common/prerequest_maya.h"
#include "../common/prerequest_std.h"
#include "mayashader.h"
#include "convertShadingNetwork.h"

namespace liquidmaya
{

	//
	class ShaderMgr
	{
	public:
		static ShaderMgr* getSingletonPtr();
		~ShaderMgr();

		void exportShaderGraph();
		const liquidmaya::Shader* getShader(const std::string& shadertype);
		int convertibleConnection(const char*plugname);

	private:
		ShaderMgr();
		static ShaderMgr* m_instance;

		typedef std::map<const std::string, const liquidmaya::Shader*> ShaderTypeMap;
		ShaderTypeMap shadertype; 

		ConvertShadingNetwork shadingnetwork;

	};
}


#endif//_SHADER_MGR_H_