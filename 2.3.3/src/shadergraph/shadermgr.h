
#ifndef _SHADER_MGR_H_
#define _SHADER_MGR_H_

#include "../common/prerequest_maya.h"
#include "../common/prerequest_std.h"
#include "convertShadingNetwork.h"
#include "shaderValidConnection.h"

namespace liquidmaya
{

	class OutputAgentInterface;
	//
	class ShaderMgr
	{
	public:
		static ShaderMgr* getSingletonPtr();
		~ShaderMgr();

		//
		void exportShaderGraph();

		//
		int convertibleConnection(const char*plugname);

		// @shadertype	e.g. "lambert","blinn",.... lowercase is prefered.
		const MStringArray& getValidConnectionRef(const char* shadertype) const;

	private:
		ShaderMgr();
		static ShaderMgr* m_instance;

		//
		ConvertShadingNetwork shadingnetwork;

		//
		ShaderValidConnection shaderValidConnection;

	private:
		ShaderMgr(const ShaderMgr&);
		ShaderMgr& operator=(const ShaderMgr&);
	};
}


#endif//_SHADER_MGR_H_