
#ifndef _SHADER_MGR_H_
#define _SHADER_MGR_H_

class ShaderMgr
{
public:
	static ShaderMgr* getSingletonPtr();
	~ShaderMgr();

	void exportShaderGraph();

private:
	ShaderMgr();

	static ShaderMgr* m_instance;

};


#endif//_SHADER_MGR_H_