#include "shaderOutput.h"
#include <liqlog.h>
#include "../common/mayacheck.h"

namespace liquidmaya{

	ShaderOutputVisitor::ShaderOutputVisitor()
	{

	}
	ShaderOutputVisitor::~ShaderOutputVisitor()
	{

	}
	void ShaderOutputVisitor::_outputUpstreamShader(const char* shaderNodeName, const char* nodetype)
	{
		if( strcmp("lambert", nodetype) == 0 )
		{
			visitLambert(shaderNodeName);
		}
		else if( strcmp("blinn", nodetype) == 0 ){
			visitBlinn(shaderNodeName);
		}
		else if( strcmp("file", nodetype) == 0 ){
			visitFile(shaderNodeName);
		}
		else if( strcmp("place2dTexture", nodetype) == 0 ){
			visitPlace2dTexture(shaderNodeName);
		}
		//else if(...){}
		else{
			liquidMessage2(messageError, ("shader type <"+std::string(nodetype)+"> is not supported.").c_str() );
			assert( 0 && "shader type is not support.");
		}
	}
}//namespace liquidmaya