#include "rm_renderer.h"
#include <liqRibLocatorData.h>
#include "rm_helper.h"

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
	 	if( !bReference ){//write data at first time
	 		assert(pData->getRibFileFullPath().length()==0);
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
	static void _write(liqRibLocatorData* pData, const structJob &currentJob)
	{
		RiTranslate( 0., 0., 0. );
		LIQDEBUGPRINTF( "-> writing locator" );
	}
}//namespace renderman
