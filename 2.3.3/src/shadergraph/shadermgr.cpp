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
	CM_TRACE_FUNC("ShaderMgr::exportShaderGraph()");

	shadingnetwork.exportShaderGraph();
}
//
int ShaderMgr::convertibleConnection(const char*plugname)
{
	CM_TRACE_FUNC("ShaderMgr::convertibleConnection("<<plugname<<")");
	return shadingnetwork.convertibleConnection(plugname);
}
//
const MStringArray& ShaderMgr::getValidConnectionRef(const char* shadertype) const
{
	CM_TRACE_FUNC("ShaderMgr::getValidConnectionRef("<<shadertype<<")");
	return shaderValidConnection.getValidConnectionRef(shadertype);
}
bool ShaderMgr::hasShaderType(const char* shadertype)const
{
	CM_TRACE_FUNC("ShaderMgr::hasShaderType("<<shadertype<<")");
	return shaderValidConnection.hasShaderType(shadertype);
}

}//namespace liquidmaya