
#include "er_renderer.h"

#include <liqShader.h>

#include "ercall.h"
#include "log_helper.h"

namespace elvishray
{
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
		//_s( "// shader_surface("<<shader.getShaderFileName()<<","<<", ...)" );//e.g."your_shader_dir/test_type2"
		_s( "// shader_surface("<<shader.getName()<<","<<", ...)" );//e.g."lambert1", or "liquidSurface1"

		
		size_t parameterNum =  tokenPointerArray.size() - 1;
		for(size_t i=0; i<parameterNum; ++i)
		{
// 			_s("//- "
// 				<<const_cast<liqTokenPointer*>(&tokenPointerArray[i])->
// 				getDetailedTokenName()<<","//uniform float intensity
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
		const std::string shaderobject(shader.getName()+"_object");
		_S( ei_shader( shaderobject.c_str() ));
		_S( ei_shader_param_string("desc", "plastic") );
		//_S( ei_shader_param_vector("Ka", 1.0f, 1.0f, 1.0f) ); 
		_S( ei_shader_param_vector("Kd", 0.7f, 1.0f, 1.0f) ); 
		_S( ei_shader_param_scalar("Ks", 1.0f) );
		_S( ei_shader_param_scalar("roughness", 0.2f ) );
		_S( ei_end_shader() );

		_S( ei_shader("opaque_shadow"));
		_S( ei_shader_param_string("desc", "opaque"));
		_S( ei_end_shader());

		_S( ei_material( shader.getName().c_str() ) );
		_S( ei_add_surface(	shaderobject.c_str() ) );
		//_S( ei_shadow( "opaque_shadow" ) );
		_S( ei_end_material() );
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
}//namespace elvishray