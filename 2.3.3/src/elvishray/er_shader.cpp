
#include "er_renderer.h"
// Maya headers
#include "../log/prerequest_maya.h"
// Liquid headers
#include <liqShader.h>

#include "../log/mayacheck.h"
#include "ercall.h"
#include "log_helper.h"

namespace elvishray
{
	//////////////////////////////////////////////////////////////////////////
	void getDagPathByName(MDagPath &dagPath, const char *name);
	void getDependNodeByName(MObject &depNode, const char *name);
	void getShaderType(MString &type, const MString &name);
	void shader_surface_lambert(const MString &mayaShaderName);
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
		const std::string &liquidShaderName=shader.getName();
		const std::string &rmSloFilePath=shader.getShaderFileName();
		const std::string &mayaShaderName=rmSloFilePath.substr(rmSloFilePath.find_last_of('/')+1);
		_s( "// shader_surface("<<mayaShaderName<<","<<", ...)" );//Renderman slo file name, e.g."your_shader_dir/test_type2"
		//_s( "// shader_surface("<<liquidShaderName<<","<<", ...)" );//e.g."lambert1", or "liquidSurface1", NOTE: it is liquidShader, not maya shader.

		MObject shaderNode;
		getDependNodeByName(shaderNode, mayaShaderName.c_str());
		if(shaderNode.hasFn(MFn::kLambert)){
			shader_surface_lambert(mayaShaderName.c_str());
		}
// 		MString shaderType;
// 		getShaderType(shaderType, mayaShaderName.c_str());
// 		if(shaderType=="lambert"){
// 			shader_surface_lambert(mayaShaderName);
// 		}
		
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
// 		const std::string shaderobject(shader.getName()+"_object");
// 		_S( ei_shader( shaderobject.c_str() ));
// 		_S( ei_shader_param_string("desc", "plastic") );
// 		//_S( ei_shader_param_vector("Ka", 1.0f, 1.0f, 1.0f) ); 
// 		_S( ei_shader_param_vector("Kd", 0.7f, 1.0f, 1.0f) ); 
// 		_S( ei_shader_param_scalar("Ks", 1.0f) );
// 		_S( ei_shader_param_scalar("roughness", 0.2f ) );
// 		_S( ei_end_shader() );
// 
// 		_S( ei_shader("opaque_shadow"));
// 		_S( ei_shader_param_string("desc", "opaque"));
// 		_S( ei_end_shader());
// 
// 		_S( ei_material( shader.getName().c_str() ) );
// 		_S( ei_add_surface(	shaderobject.c_str() ) );
// 		//_S( ei_shadow( "opaque_shadow" ) );
// 		_S( ei_end_material() );
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
	void getDagPathByName(MDagPath &dagPath, const char *name)
	{
		MSelectionList      selList;
		IfMErrorWarn(MGlobal::getSelectionListByName( name, selList ));
		IfMErrorWarn(selList.getDagPath( 0, dagPath ));
	}
	void getDependNodeByName(MObject &depNode, const char *name)
	{
		MSelectionList      selList;
		IfMErrorWarn(MGlobal::getSelectionListByName( name, selList ));
		IfMErrorWarn(selList.getDependNode( 0, depNode ));
	}
	void getShaderType(MString &type, const MString &name)
	{
		IfMErrorWarn( MGlobal::executeCommand( ("nodeType \""+name+"\""), type) );
	}
	void shader_surface_lambert(const MString &mayaShaderName)
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