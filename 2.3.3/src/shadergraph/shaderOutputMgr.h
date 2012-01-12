#ifndef _SHADER_OUTPUT_MGR_H_
#define _SHADER_OUTPUT_MGR_H_

#include "../common/prerequest_std.h"

namespace liquidmaya{

	class ShaderOutputVisitor;
	//
	class ShaderOutputMgr
	{
	public:
		static ShaderOutputMgr* getSingletonPtr();

		~ShaderOutputMgr();

		void preOutput(const char* shaderNodeName);
		void outputBegin(const char* shaderNodeName);
		void outputUpstreamShader(const char* shaderNodeName);
		void outputShaderMethod(const char* shaderName,const char* shaderMethodVariavles,const char* shaderMethodBody);
		void outputEnd();
		void postOutput();

		void outputShadingGroup(const char* shadingGroupNode);

		void addReceiver(ShaderOutputVisitor* visitor);
		void deleteReceivers();

	private:
		ShaderOutputMgr();

		static ShaderOutputMgr* m_instance;
		
		void notify_preOutput(const char* shaderNodeName);
		void notify_outputBegin(const char* shaderNodeName);
		void notify_outputUpstreamShader(const char* shaderNodeName);
		void notify_outputShaderMethod(const char* shaderName,const char* shaderMethodVariavles,const char* shaderMethodBody);
		void notify_outputEnd();
		void notify_postOutput();
		void notify_outputShadingGroup(const char* shadingGroupNode);

		std::vector<ShaderOutputVisitor*> receivers;
	private:
		ShaderOutputMgr(const ShaderOutputMgr&);
		ShaderOutputMgr& operator=(const ShaderOutputMgr&);
	};

}//namespace liquidmaya
#endif//_SHADER_OUTPUT_H_