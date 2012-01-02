#ifndef _SHADER_OUTPUT_MGR_H_
#define _SHADER_OUTPUT_MGR_H_

namespace liquidmaya{

	class ShaderOutput;
	class RSL;
	//
	class ShaderOutputMgr
	{
	public:
		static ShaderOutputMgr* getSingletonPtr();

		~ShaderOutputMgr();

		RSL *rsl;

	private:
		ShaderOutputMgr();
		static ShaderOutputMgr* m_instance;


	};

}//namespace liquidmaya
#endif//_SHADER_OUTPUT_H_