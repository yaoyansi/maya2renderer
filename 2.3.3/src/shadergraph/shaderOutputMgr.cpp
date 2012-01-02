#include "shaderOutputMgr.h"
#include "shaderOutputRSL.h"

namespace liquidmaya{


ShaderOutputMgr* ShaderOutputMgr::m_instance = 0;
//
ShaderOutputMgr::ShaderOutputMgr()
{
	rsl = new liquidmaya::RSL();
}
//
ShaderOutputMgr::~ShaderOutputMgr()
{
	delete rsl;
	rsl = 0;
}
//
ShaderOutputMgr* ShaderOutputMgr::getSingletonPtr()
{
	if( !m_instance){
		m_instance = new ShaderOutputMgr();
	}
	return m_instance;
}

}//namespace liquidmaya