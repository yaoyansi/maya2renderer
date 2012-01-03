#include "shaderOutputMgr.h"
#include "shaderOutputRSL.h"

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
	receivers.push_back( new RSL());
}
//
void ShaderOutputMgr::deleteReceivers()
{
	std::vector<ShaderOutput*>::iterator i = receivers.begin();
	std::vector<ShaderOutput*>::iterator e = receivers.end();
	for( ; i != e; ++i )
	{
		delete (*i);
	}
	receivers.clear();
}
//
void ShaderOutputMgr::notify_output(const char* shaderNodeName)
{
	std::vector<ShaderOutput*>::iterator i = receivers.begin();
	std::vector<ShaderOutput*>::iterator e = receivers.end();
	for( ; i != e; ++i )
	{
		(*i)->output(shaderNodeName);
	}
}
//
void ShaderOutputMgr::output(const char* shaderNodeName)
{
	notify_output(shaderNodeName);
}
}//namespace liquidmaya