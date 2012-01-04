#ifndef _SHADER_OUTPUT_MGR_H_
#define _SHADER_OUTPUT_MGR_H_

#include "../common/prerequest_std.h"

namespace liquidmaya{

	class ShaderOutput;
	class RSL;
	//
	class ShaderOutputMgr
	{
	public:
		static ShaderOutputMgr* getSingletonPtr();

		~ShaderOutputMgr();

		void outputBegin(const char* shaderNodeName);
		void outputUpstreamShader(const char* shaderNodeName);
		void outputShaderMethod(const char* shaderName,const char* shaderMethodVariavles,const char* shaderMethodBody);
		void outputEnd();

	private:
		ShaderOutputMgr();


		static ShaderOutputMgr* m_instance;
		
		void createReceivers();
		void deleteReceivers();

		void notify_outputBegin(const char* shaderNodeName);
		void notify_outputUpstreamShader(const char* shaderNodeName);
		void notify_outputShaderMethod(const char* shaderName,const char* shaderMethodVariavles,const char* shaderMethodBody);
		void notify_outputEnd();

		std::vector<ShaderOutput*> receivers;
	private:
		ShaderOutputMgr(const ShaderOutputMgr&);
		ShaderOutputMgr& operator=(const ShaderOutputMgr&);
	};

}//namespace liquidmaya
#endif//_SHADER_OUTPUT_H_