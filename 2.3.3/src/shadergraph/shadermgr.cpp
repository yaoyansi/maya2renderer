#include "shadermgr.h"
#include "../common/mayacheck.h"
#include <liqlog.h>
#include "mayashader_materials.h"

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

const liquidmaya::Shader* 
ShaderMgr::getShader(const std::string& tname)
{
	//tname --> tnamel(lowcase)
	std::string tnamel;
	tnamel.resize(tname.size());
	std::transform(tname.begin(), tname.end(), tnamel.begin(), std::tolower);

	ShaderTypeMap::iterator i = shadertype.find(tnamel);
	
	//find it,
	if( i != shadertype.end() )
		return i->second;
	
	//not exist, create it	
	if("lambert"==tnamel){
		shadertype[tnamel] = new liquidmaya::Lambert();
	}else if("blinn"==tnamel){
		shadertype[tnamel] = new liquidmaya::Blinn();
	}//else if(...){}
	else{
		liquidMessage2(messageError, ("shader type <"+tnamel+"> is not supported.").c_str() );
		assert( 0 && "shader type is not support.");
		return 0;
	}

	return shadertype[tnamel];
}
//
int ShaderMgr::convertibleConnection(const char*plugname)
{
	return shadingnetwork.convertibleConnection(plugname);
}

}//namespace liquidmaya