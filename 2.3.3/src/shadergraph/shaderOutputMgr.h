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

		void output(const char* shaderNodeName);

	private:
		ShaderOutputMgr();


		static ShaderOutputMgr* m_instance;
		
		void createReceivers();
		void deleteReceivers();
		void notify_output(const char* shaderNodeName);
		std::vector<ShaderOutput*> receivers;

	};

}//namespace liquidmaya
#endif//_SHADER_OUTPUT_H_