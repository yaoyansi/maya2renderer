#include "shaderOutputMgr.h"
#include "shaderOutputRSL.h"
#include "shaderOutputER.h"
#include "shaderOutputERCall.h"


namespace liquidmaya{


ShaderOutputMgr* ShaderOutputMgr::m_instance = 0;
//
ShaderOutputMgr::ShaderOutputMgr()
{
	createReceivers();
}
//
ShaderOutputMgr::~ShaderOutputMgr()
{
	deleteReceivers();
}
//
ShaderOutputMgr* ShaderOutputMgr::getSingletonPtr()
{
	if( !m_instance){
		m_instance = new ShaderOutputMgr();
	}
	return m_instance;
}
//
void ShaderOutputMgr::createReceivers()
{
	receivers.push_back( new RSL::Visitor());
	receivers.push_back( new ER::Visitor());
	receivers.push_back( new ERCall::Visitor());
}
//
void ShaderOutputMgr::deleteReceivers()
{
	std::vector<ShaderOutputVisitor*>::iterator i = receivers.begin();
	std::vector<ShaderOutputVisitor*>::iterator e = receivers.end();
	for( ; i != e; ++i )
	{
		delete (*i);
	}
	receivers.clear();
}
//
//
void ShaderOutputMgr::notify_outputBegin(const char* shaderNodeName)
{
	std::vector<ShaderOutputVisitor*>::iterator i = receivers.begin();
	std::vector<ShaderOutputVisitor*>::iterator e = receivers.end();
	for( ; i != e; ++i )
	{
		(*i)->outputBegin(shaderNodeName);
	}
}
void ShaderOutputMgr::notify_outputUpstreamShader(const char* shaderNodeName)
{
	std::vector<ShaderOutputVisitor*>::iterator i = receivers.begin();
	std::vector<ShaderOutputVisitor*>::iterator e = receivers.end();
	for( ; i != e; ++i )
	{
		(*i)->outputUpstreamShader(shaderNodeName);
	}
}
void ShaderOutputMgr::notify_outputShaderMethod(const char* shaderName,const char* shaderMethodVariavles,const char* shaderMethodBody)
{
	std::vector<ShaderOutputVisitor*>::iterator i = receivers.begin();
	std::vector<ShaderOutputVisitor*>::iterator e = receivers.end();
	for( ; i != e; ++i )
	{
		(*i)->outputShaderMethod(shaderName, shaderMethodVariavles, shaderMethodBody);
	}
}
void ShaderOutputMgr::notify_outputEnd()
{
	std::vector<ShaderOutputVisitor*>::iterator i = receivers.begin();
	std::vector<ShaderOutputVisitor*>::iterator e = receivers.end();
	for( ; i != e; ++i )
	{
		(*i)->outputEnd();
	}
}
void ShaderOutputMgr::notify_outputShadingGroup(const char* shadingGroupNode)
{
	std::vector<ShaderOutputVisitor*>::iterator i = receivers.begin();
	std::vector<ShaderOutputVisitor*>::iterator e = receivers.end();
	for( ; i != e; ++i )
	{
		(*i)->outputShadingGroup(shadingGroupNode);
	}
}
//
void ShaderOutputMgr::outputBegin(const char* shaderNodeName)
{
	notify_outputBegin(shaderNodeName);
}
void ShaderOutputMgr::outputUpstreamShader(const char* shaderNodeName)
{
	notify_outputUpstreamShader(shaderNodeName);
}
void ShaderOutputMgr::outputShaderMethod(const char* shaderName,const char* shaderMethodVariavles,const char* shaderMethodBody)
{
	notify_outputShaderMethod(shaderName, shaderMethodVariavles, shaderMethodBody);
}
void ShaderOutputMgr::outputEnd()
{
	notify_outputEnd();
}
void ShaderOutputMgr::outputShadingGroup(const char* shadingGroupNode)
{
	notify_outputShadingGroup(shadingGroupNode);
}
//

}//namespace liquidmaya