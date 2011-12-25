
#include "rm_renderer.h"
#include <liqShader.h>

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
}//namespace renderman