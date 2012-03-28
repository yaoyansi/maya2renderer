#include "rm_renderer.h"
#include <liqRibLocatorData.h>
#include "rm_helper.h"
#include <liqGlobalVariable.h>

namespace renderman
{
	static void _write(liqRibLocatorData* pData, const structJob &currentJob);
	//
	void Renderer::write(
		/*const*/ liqRibLocatorData* pData,
		const MString &ribFileName,
		const structJob &currentJob,
		const bool bReference)
	{
		CM_TRACE_FUNC("Renderer::write("<<pData->getName()<<","<<ribFileName<<","<<currentJob.name<<",ref="<<bReference<<")");

		assert(liqglo.m_ribFileOpen &&"rm_writeLocatorData.cpp");

	 	if( !bReference ){//write data at first time
			if( !currentJob.isShadow ){
				assert(pData->getRibFileFullPath().length()==0&&"rm_writeLocatorData.cpp");
			}
			pData->setRibFileFullPath(ribFileName);

	 		renderman::Helper o;
	 		o.RiBeginRef(pData->getRibFileFullPath().asChar());
	 		_write(pData, currentJob);
	 		o.RiEndRef();
	 
	 	}else{
	 		//write the reference
	 		assert(pData->getRibFileFullPath() == ribFileName);
	 		RiReadArchive( const_cast< RtToken >( pData->getRibFileFullPath().asChar() ), NULL, RI_NULL );
	 	}
	}
	//
	static void _write(liqRibLocatorData* pData, const structJob &currentJob__)
	{
		CM_TRACE_FUNC("write("<<pData->getName()<<","<<currentJob__.name<<",...)");

		RiTranslate( 0., 0., 0. );
		LIQDEBUGPRINTF( "-> writing locator" );
	}
}//namespace renderman
