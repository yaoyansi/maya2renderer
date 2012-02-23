
#include "er_renderer.h"
// Maya headers
#include "../common/prerequest_maya.h"
// Liquid headers
#include <liqShader.h>
#include <liqShaderFactory.h>
#include <liqGlobalHelpers.h>
#include "../common/mayacheck.h"
#include "ercall.h"
#include "log_helper.h"


namespace elvishray
{
	//////////////////////////////////////////////////////////////////////////

	void shader_surface_lambert(MString const& mayaShaderName);
	//////////////////////////////////////////////////////////////////////////
	void Renderer::shader_transformBegin(const liqString  shaderSpace)
	{

	}
	void Renderer::shader_transformEnd(const liqString  shaderSpace)
	{

	}
	void Renderer::_UserDefinedShader(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
	)
	{
		std::string const& liquidShaderName=shader.getName();
		std::string const& rmSloFilePath=shader.getShaderFileName();
		std::string const& mayaShaderName=rmSloFilePath.substr(rmSloFilePath.find_last_of('/')+1);
		_s( "// shader("<<mayaShaderName<<","<<", ...)" );//Renderman slo file name, e.g."your_shader_dir/test_type2"
		//_s( "// shader("<<liquidShaderName<<","<<", ...)" );//e.g."lambert1", or "liquidSurface1", NOTE: it is liquidShader, not maya shader.

		_S( ei_shader(liquidShaderName.c_str()) );

		_s("ei_shader_param_string( \"desc\",\""<<mayaShaderName<<"\");");
		ei_shader_param_string("desc", mayaShaderName.c_str()); // //"opaque"

		//tokenPointerArray only store parameters of user-defined shader
		size_t parameterNum =  tokenPointerArray.size() - 1;
		for(size_t i=0; i<parameterNum; ++i)
		{
 			//_s("//- "
 			//	<<const_cast<liqTokenPointer*>(&tokenPointerArray[i])->getDetailedTokenName()<<","//uniform float intensity
 			//	<<tokenPointerArray[i].getDetailType()<<","
 			//	<<"//tokenPointerArray[i].getTokenFloatArray()"<<","
 			//	<<"//[error]tokenPointerArray[i].getTokenString()"<<","
 			//	<<tokenPointerArray[i].getTokenName()<<","//intensity,
 			//	<<tokenPointerArray[i].getParameterType()<<","//rFloat,
 			//	<<tokenPointerArray[i].getRiDeclare()<<","//uniform float,
 			//	);
// 			_s("// "<<tokenPointerArray[i].getTokenName());

			liqTokenPointer* vp = const_cast< liqTokenPointer* >( &tokenPointerArray[i] );
			switch( tokenPointerArray[i].getParameterType() )
			{
			case rFloat:
				{
					const liqFloat *v = vp->getTokenFloatArray();
					_s("ei_shader_param_scalar(\""<<vp->getTokenName()<<"\"," <<v[0]<<");");
					ei_shader_param_scalar( vp->getTokenName().c_str(), v[0] );
				}
				break;
			case rPoint: case rVector: case rNormal: case rColor:
				{
					const liqFloat *v = vp->getTokenFloatArray();
					_s("ei_shader_param_vector(\""<<vp->getTokenName()<<"\"," <<v[0]<<","<<v[1]<<","<<v[2]<<");");
					ei_shader_param_vector( vp->getTokenName().c_str(), v[0] ,v[1], v[2] );
				}
				break;
			case rString: case rShader:
				{
					const std::string &v = vp->getTokenString();
					_s("ei_shader_param_string(\""<<vp->getTokenName()<<"\"," <<v<<");");
					ei_shader_param_string( vp->getTokenName().c_str(), v.c_str() );
				}
				break; 
			case rHpoint:
				{
					const liqFloat *v = vp->getTokenFloatArray();
					_s("ei_shader_param_vector4(\""<<vp->getTokenName()<<"\"," <<v[0]<<","<<v[1]<<","<<v[2]<<","<<v[3]<<");");
					ei_shader_param_vector4( vp->getTokenName().c_str(), v[0] ,v[1], v[2], v[3] );
				}
				break;
			case rMatrix:
				{
					const liqFloat *v = vp->getTokenFloatArray();
					_s("//matrix:"
						<<v[0]<<","<<v[1]<<","<<v[2]<<","<<v[3]
						<<v[4]<<","<<v[5]<<","<<v[6]<<","<<v[7]
						<<v[8]<<","<<v[9]<<","<<v[10]<<","<<v[11]
						<<v[12]<<","<<v[13]<<","<<v[14]<<","<<v[15]
					);
				}
				;break;
			default :
				assert(0);
			}

		}//for
		_S( ei_end_shader() );


	}
	void Renderer::shader_surface(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
		)
	{
		_UserDefinedShader(shader, tokenPointerArray);
	}
	liqLightHandle Renderer::shader_light(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
	)
	{
		_UserDefinedShader(shader, tokenPointerArray);

		return (liqLightHandle)0;//dummy value
	}
	void Renderer::shader_displacement(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
	)
	{
		_UserDefinedShader(shader, tokenPointerArray);
	}
	void Renderer::shader_volume(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
	)
	{
		_UserDefinedShader(shader, tokenPointerArray);
	}

	void Renderer::dummyPhongShader()
	{
		_s("//----------------phong_shader_for_test begin---");
		_S( ei_shader("phong_shader_for_test") );
		_S( ei_shader_param_string("desc", "plastic") );
		_S( ei_shader_param_vector("Cs", 1.0f, 0.2f, 0.3f) );
		_S( ei_shader_param_vector("Kd", 0.7f, 1.0f, 1.0f) );
		_S( ei_shader_param_scalar("Ks", 1.0f) );
		_S( ei_shader_param_scalar("roughness", 0.2f) );
		_S( ei_end_shader() );

		_S( ei_shader("opaque_shadow_for_test") );
		_S( ei_shader_param_string("desc", "opaque") );
		_S( ei_end_shader() );

		_S( ei_material("phong_mtl_for_test") );
		_S( ei_add_surface("phong_shader_for_test") );
		_S( ei_add_shadow("opaque_shadow_for_test") );
		_S( ei_end_material() );
		_s("//----------------phong_shader_for_test end ---");
	}
	//////////////////////////////////////////////////////////////////////////

	void shader_surface_lambert(MString const& mayaShaderName)
	{
// 		MDoubleArray color;
// 		IfMErrorWarn( MGlobal::executeCommand( ("getAttr \""+mayaShaderName+".color\""), color) );
// 		
// 		MDoubleArray transparency;
// 		IfMErrorWarn( MGlobal::executeCommand( ("getAttr \""+mayaShaderName+".transparency\""), transparency) );
// 
// 		const MString shaderObjectName(mayaShaderName+"_object");
// 		const MString opaqueShadowObjectName(mayaShaderName+"_opaque_shadow_object");
// 		_s("//----------------shader begin---");
// 		_S( ei_shader( shaderObjectName.asChar()) );
// 		_S( ei_shader_param_string("desc", "plastic") );
// 		_S( ei_shader_param_vector("Cs", color[0], color[1], color[2]) );
// 		_S( ei_shader_param_vector("Kd", 0.7f, 1.0f, 1.0f) );
// 		_S( ei_shader_param_scalar("Ks", 1.0f) );
// 		_S( ei_shader_param_scalar("roughness", 0.2f) );
// 		_S( ei_end_shader() );
// 
// 		_S( ei_shader(opaqueShadowObjectName.asChar()) );
// 		_S( ei_shader_param_string("desc", "opaque") );
// 		_S( ei_end_shader() );
// 
// 		_S( ei_material(mayaShaderName.asChar()) );
// 		_S( ei_add_surface(shaderObjectName.asChar()) );
// 		_S( ei_add_shadow(opaqueShadowObjectName.asChar()) );
// 		_S( ei_end_material() );
// 		_s("//----------------shader end ---");
	}
	//
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
				assert(0&&"er has not coShader.");
				//coShader.writeAsCoShader(/*shortShaderNames, indentLevel*/);
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
		}else if(liqshader->shader_type_ex == "displace"){
			//outputIndentation(indentLevel);
			this->shader_displacement( *liqshader,  liqshader->tokenPointerArray );
		}else if(liqshader->shader_type_ex == "volume"){
			//outputIndentation(indentLevel);
			this->shader_volume( *liqshader,   liqshader->tokenPointerArray );
		}else if(liqshader->shader_type_ex == "shadow"){
			//outputIndentation(indentLevel);
			this->shader_shadow( *liqshader,   liqshader->tokenPointerArray );
		}else if(liqshader->shader_type_ex == "environment"){
			//outputIndentation(indentLevel);
			this->shader_environment( *liqshader,   liqshader->tokenPointerArray );
		}else if(liqshader->shader_type_ex == "photon"){
			//outputIndentation(indentLevel);
			this->shader_photon( *liqshader,   liqshader->tokenPointerArray );
		}else{
			char errorMsg[512];
			sprintf(errorMsg, "[liqShader::write] Unknown shader type for %s shader_type=%s", liqshader->getName().c_str(), liqshader->shader_type_ex.asChar());
			liquidMessage( errorMsg, messageError );
		}

		if( liqshader->shaderSpace != "" )
		{
			this->shader_transformEnd((const liqString)liqshader->shaderSpace.asChar());
		}
	}
	void Renderer::shader_shadow(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
		)
	{
		_UserDefinedShader(shader, tokenPointerArray);
	}
	void Renderer::shader_environment(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
		)
	{
		_UserDefinedShader(shader, tokenPointerArray);
	}
	void Renderer::shader_photon(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
		)
	{
		_UserDefinedShader(shader, tokenPointerArray);
	}
	void Renderer::getValidShaderPlugsInShadingGroup(std::vector<std::string>& plugs)const
	{
		plugs.clear();
		plugs.push_back("surfaceShader");
		plugs.push_back("displacementShader");
		plugs.push_back("volumeShader");
		plugs.push_back("liqShadowShader");
		plugs.push_back("liqEnvironmentShader");
		plugs.push_back("liqPhotonShader");
	}

}//namespace elvishray