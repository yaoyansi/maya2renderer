
#include "er_renderer.h"
// Maya headers
#include "../common/prerequest_maya.h"
// Liquid headers
#include <liqShader.h>
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
	void Renderer::shader_surface(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
	)
	{
		std::string const& liquidShaderName=shader.getName();
		std::string const& rmSloFilePath=shader.getShaderFileName();
		std::string const& mayaShaderName=rmSloFilePath.substr(rmSloFilePath.find_last_of('/')+1);
		_s( "// shader_surface("<<mayaShaderName<<","<<", ...)" );//Renderman slo file name, e.g."your_shader_dir/test_type2"
		//_s( "// shader_surface("<<liquidShaderName<<","<<", ...)" );//e.g."lambert1", or "liquidSurface1", NOTE: it is liquidShader, not maya shader.

		MObject shaderNode;
		getDependNodeByName(shaderNode, mayaShaderName.c_str());
		if(shaderNode.hasFn(MFn::kLambert)){
			shader_surface_lambert(mayaShaderName.c_str());
		}
#if 0 //tokenPointerArray only store parameters of user-defined shader
		size_t parameterNum =  tokenPointerArray.size() - 1;
		for(size_t i=0; i<parameterNum; ++i)
		{
// 			_s("//- "
// 				<<const_cast<liqTokenPointer*>(&tokenPointerArray[i])->getDetailedTokenName()<<","//uniform float intensity
// 				<<tokenPointerArray[i].getDetailType()<<","
// 				<<"//tokenPointerArray[i].getTokenFloatArray()"<<","
// 				<<"//[error]tokenPointerArray[i].getTokenString()"<<","
// 				<<tokenPointerArray[i].getTokenName()<<","//intensity,
// 				<<tokenPointerArray[i].getParameterType()<<","//rFloat,
// 				<<tokenPointerArray[i].getRiDeclare()<<","//uniform float,
// 				);
// 			_s("// "<<tokenPointerArray[i].getTokenName());
			liqTokenPointer* vp = const_cast< liqTokenPointer* >( &tokenPointerArray[i] );
			switch( tokenPointerArray[i].getParameterType() )
			{
			case rFloat:
				{
					const liqFloat *v = vp->getTokenFloatArray();
					_s("//     "<<v[0]);
				}
				break;
			case rPoint: case rVector: case rNormal: case rColor:
				{
					const liqFloat *v = vp->getTokenFloatArray();
					_s("//     "<<v[0]<<","<<v[1]<<","<<v[2]);
				}
				break;
			case rString: case rShader:
				{
					const std::string &v = vp->getTokenString();
					_s("//     "<<v);
				}
				break; 
			case rHpoint:
				{
					const liqFloat *v = vp->getTokenFloatArray();
					_s("//     "<<v[0]<<","<<v[1]<<","<<v[2]<<","<<v[3]);
				}
				break;
			case rMatrix:
				{
					const liqFloat *v = vp->getTokenFloatArray();
					_s("//     "
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
#endif

	}
	liqLightHandle Renderer::shader_light(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
	)
	{
		_s( "// shader_light("<<shader.getName()<<","<<", ...)" );

		return (liqLightHandle)0;	
	}
	void Renderer::shader_displacement(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
	)
	{
		_s( "// shader_displacement("<<shader.getName()<<","<<", ...)" );	 
	}
	void Renderer::shader_volume(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
	)
	{
		_s( "// shader_volume("<<shader.getName()<<","<<", ...)" );	
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
		MDoubleArray color;
		IfMErrorWarn( MGlobal::executeCommand( ("getAttr \""+mayaShaderName+".color\""), color) );
		
		MDoubleArray transparency;
		IfMErrorWarn( MGlobal::executeCommand( ("getAttr \""+mayaShaderName+".transparency\""), transparency) );

		const MString shaderObjectName(mayaShaderName+"_object");
		const MString opaqueShadowObjectName(mayaShaderName+"_opaque_shadow_object");
		_s("//----------------shader begin---");
		_S( ei_shader( shaderObjectName.asChar()) );
		_S( ei_shader_param_string("desc", "plastic") );
		_S( ei_shader_param_vector("Cs", color[0], color[1], color[2]) );
		_S( ei_shader_param_vector("Kd", 0.7f, 1.0f, 1.0f) );
		_S( ei_shader_param_scalar("Ks", 1.0f) );
		_S( ei_shader_param_scalar("roughness", 0.2f) );
		_S( ei_end_shader() );

		_S( ei_shader(opaqueShadowObjectName.asChar()) );
		_S( ei_shader_param_string("desc", "opaque") );
		_S( ei_end_shader() );

		_S( ei_material(mayaShaderName.asChar()) );
		_S( ei_add_surface(shaderObjectName.asChar()) );
		_S( ei_add_shadow(opaqueShadowObjectName.asChar()) );
		_S( ei_end_material() );
		_s("//----------------shader end ---");
	}
	//
}//namespace elvishray