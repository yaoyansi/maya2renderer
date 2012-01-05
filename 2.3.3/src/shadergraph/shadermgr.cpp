#include "shadermgr.h"
#include "../common/mayacheck.h"
#include <liqlog.h>

namespace liquidmaya{

ShaderMgr* ShaderMgr::m_instance = 0;

ShaderMgr::ShaderMgr()
{

}
//
ShaderMgr::~ShaderMgr()
{

}
//
ShaderMgr* ShaderMgr::getSingletonPtr()
{
	if(!m_instance){
		m_instance = new ShaderMgr();
	}
	return m_instance;
}
//
void ShaderMgr::exportShaderGraph()
{
	shadingnetwork.exportShaderGraph();
}
//
int ShaderMgr::convertibleConnection(const char*plugname)
{
	return shadingnetwork.convertibleConnection(plugname);
}
//
const MStringArray& ShaderMgr::getValidConnectionRef(const char* shadertype) const
{
	return shaderValidConnection.getValidConnectionRef(shadertype);
}

}//namespace liquidmaya