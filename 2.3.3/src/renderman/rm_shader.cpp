
#include "rm_renderer.h"
#include <liqShader.h>
#include <liqShaderFactory.h>
namespace renderman
{
	void Renderer::shader_transformBegin(const liqString  shaderSpace)
	{
		RiTransformBegin();
		RiCoordSysTransform( /*( RtString )*/shaderSpace );
	}
	void Renderer::shader_transformEnd(const liqString  shaderSpace)
	{
		RiTransformEnd();
	}
	void Renderer::shader_surface(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
		)
	{
		int shaderParamCount = tokenPointerArray.size() - 1;
		boost::scoped_array< RtToken > tokenArray( new RtToken[ tokenPointerArray.size() ] );
		boost::scoped_array< RtPointer > pointerArray( new RtPointer[ tokenPointerArray.size() ] );
		assignTokenArrays( tokenPointerArray.size(), &tokenPointerArray[ 0 ], tokenArray.get(), pointerArray.get() );

		RiSurfaceV ( const_cast<char *>(shader.getShaderFileName().c_str()), shaderParamCount, tokenArray.get() , pointerArray.get() );

	}
	liqLightHandle Renderer::shader_light(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
		)
	{
		int shaderParamCount = tokenPointerArray.size() - 1;
		boost::scoped_array< RtToken > tokenArray( new RtToken[ tokenPointerArray.size() ] );
		boost::scoped_array< RtPointer > pointerArray( new RtPointer[ tokenPointerArray.size() ] );
		assignTokenArrays( tokenPointerArray.size(), &tokenPointerArray[ 0 ], tokenArray.get(), pointerArray.get() );

		return RiLightSourceV( const_cast<char *>(shader.getShaderFileName().c_str()), shaderParamCount, tokenArray.get(), pointerArray.get() );
	}
	void Renderer::shader_displacement(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
		)
	{
		int shaderParamCount = tokenPointerArray.size() - 1;
		boost::scoped_array< RtToken > tokenArray( new RtToken[ tokenPointerArray.size() ] );
		boost::scoped_array< RtPointer > pointerArray( new RtPointer[ tokenPointerArray.size() ] );
		assignTokenArrays( tokenPointerArray.size(), &tokenPointerArray[ 0 ], tokenArray.get(), pointerArray.get() );

		RiDisplacementV( const_cast<char *>(shader.getShaderFileName().c_str()), shaderParamCount, tokenArray.get(), pointerArray.get());

	}
	void Renderer::shader_volume(
		const liqShader &shader, 
		const std::vector<liqTokenPointer> &tokenPointerArray
		)
	{
		int shaderParamCount = tokenPointerArray.size() - 1;
		boost::scoped_array< RtToken > tokenArray( new RtToken[ tokenPointerArray.size() ] );
		boost::scoped_array< RtPointer > pointerArray( new RtPointer[ tokenPointerArray.size() ] );
		assignTokenArrays( tokenPointerArray.size(), &tokenPointerArray[ 0 ], tokenArray.get(), pointerArray.get() );

		RiAtmosphereV ( const_cast<char *>(shader.getShaderFileName().c_str()), shaderParamCount,  tokenArray.get(), pointerArray.get() );

	}
	void Renderer::shader_UserDefinedShader(const liqShader* liqshader)
	{

		// write co-shaders before
		unsigned int i; 
		for(i=0; i<liqshader->m_coShaderArray.size(); i++)
		{
			liqShader &coShader = liqShaderFactory::instance().getShader(liqshader->m_coShaderArray[i]);
			if( coShader.hasErrors )
			{
				char errorMsg[512];
				sprintf(errorMsg, "[liqShader::write] While initializing coShader for '%s', node couldn't be exported", coShader.getName().c_str());
				liquidMessage( errorMsg, messageError );
			}
			else
			{
				this->writeAsCoShader(&coShader/*shortShaderNames, indentLevel*/);
			}
		}

		// write shader
		char* shaderFileName = const_cast<char*>(liqshader->getShaderFileName().c_str());
		if( liqshader->shaderSpace != "" )
		{
			this->shader_transformBegin((const liqString)liqshader->shaderSpace.asChar());
		}
		// output shader
		// its one less as the tokenPointerArray has a preset size of 1 not 0

		if( liqshader->shader_type_ex == "light" )
		{
				//outputIndentation(indentLevel);
				RtLightHandle ret = this->shader_light( *liqshader,  liqshader->tokenPointerArray );
#ifdef RIBLIB_AQSIS
				(const_cast<liqShader*>(liqshader))->shaderHandler.set( reinterpret_cast<ptrdiff_t>(static_cast<RtLightHandle>(ret)) );
#else
				liqshader->shaderHandler.set( ret );
#endif
		}else if(liqshader->shader_type_ex == "surface"){
				//outputIndentation(indentLevel);
				this->shader_surface( *liqshader,  liqshader->tokenPointerArray );
		}else if(liqshader->shader_type_ex == "displacement"){
				//outputIndentation(indentLevel);
				this->shader_displacement( *liqshader,  liqshader->tokenPointerArray );
		}else if(liqshader->shader_type_ex == "volume"){
				//outputIndentation(indentLevel);
				this->shader_volume( *liqshader,   liqshader->tokenPointerArray );
		}else{
			char errorMsg[512];
			sprintf(errorMsg, "[liqShader::write] Unknown shader type for %s shader_type=%s", liqshader->getName().c_str(), liqshader->shader_type_ex.asChar());
			liquidMessage( errorMsg, messageError );
		}
		//
		if( liqshader->shaderSpace != "" )
		{
			this->shader_transformEnd((const liqString)liqshader->shaderSpace.asChar());
		}
	}
	//
	void Renderer::writeAsCoShader(const liqShader* liqshader)
	{

		//	unsigned int indentLevel = 0;

		MFnDependencyNode node(liqshader->m_mObject);
		if( liqshader->hasErrors )
		{
			liquidMessage2(messageError, "[liqShader::write] Erros occured while initializing shader '%s', won't export shader", node.name().asChar());
			return;
		}
		// write up co-shaders before
		unsigned int i; 
		for(i=0; i<liqshader->m_coShaderArray.size(); i++)
		{
			//liqShader coShader(m_coShaderArray[i]);
			liqShader &coShader = liqShaderFactory::instance().getShader(liqshader->m_coShaderArray[i]);
			this->writeAsCoShader(&coShader);
		}
		// write co-shader
		boost::scoped_array< RtToken > tokenArray( new RtToken[ liqshader->tokenPointerArray.size() ] );
		boost::scoped_array< RtPointer > pointerArray( new RtPointer[ liqshader->tokenPointerArray.size() ] );
		assignTokenArrays( liqshader->tokenPointerArray.size(), &liqshader->tokenPointerArray[ 0 ], tokenArray.get(), pointerArray.get() );


		char* shaderFileName = const_cast<char*>(liqshader->getShaderFileName().c_str());
		if( liqshader->shaderSpace != "" )
		{
			this->shader_transformBegin((const liqString)liqshader->shaderSpace.asChar());

		}
		// output shader
		// its one less as the tokenPointerArray has a preset size of 1 not 0
		int shaderParamCount = liqshader->tokenPointerArray.size() - 1;
		char *shaderHandlerPtr = const_cast<char*>(liqshader->shaderHandler.asChar());

		// 	switch( shader_type )
		// 	{
		// 	case SHADER_TYPE_SHADER:case SHADER_TYPE_SURFACE:case SHADER_TYPE_DISPLACEMENT:case SHADER_TYPE_VOLUME:
		// 		//outputIndentation(indentLevel);
		// 		RiShaderV(shaderFileName, shaderHandlerPtr, shaderParamCount, tokenArray.get(), pointerArray.get());
		// 		break;
		// 	default :
		// 		char errorMsg[512];
		// 		sprintf(errorMsg, "[liqShader::writeAsCoShader] Unknown shader type for %s shader_type=%d (%s)", name.c_str(), shader_type, liqGetSloInfo::getTypeStr(shader_type).asChar());
		// 		liquidMessage( errorMsg, messageError );
		// 		break;
		// 	}
		if( liqshader->shader_type_ex=="shader"       ||
			liqshader->shader_type_ex=="surface"      ||
			liqshader->shader_type_ex=="displacement" ||
			liqshader->shader_type_ex=="volume"         )
		{
			//outputIndentation(indentLevel);
			RiShaderV(shaderFileName, shaderHandlerPtr, shaderParamCount, tokenArray.get(), pointerArray.get());
		}else{
			char errorMsg[512];
			sprintf(errorMsg, "[liqShader::writeAsCoShader] Unknown shader type for %s shader_type=%s", liqshader->getName().c_str(), liqshader->shader_type_ex.asChar());
			liquidMessage( errorMsg, messageError );
		}


		if( liqshader->shaderSpace != "" )
		{
			this->shader_transformEnd((const liqString)liqshader->shaderSpace.asChar());

		}
	}
}//namespace renderman