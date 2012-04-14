#include "rm_renderer.h"
#include <liqRibPfxHairData.h>
#include <liqGlobalVariable.h>
#include "rm_helper.h"

namespace renderman
{
	static void _write(liqRibPfxHairData* pData, const structJob &currentJob);
	//
	void Renderer::write(
		/*const*/ liqRibPfxHairData* pData,
		const MString &ribFileName,
		const structJob &currentJob,
		const bool bReference)
	{
		CM_TRACE_FUNC("Renderer::write("<<pData->getFullPathName()<<","<<ribFileName<<","<<currentJob.name<<",ref="<<bReference<<")");

		assert(liqglo.m_ribFileOpen&&"rm_writePfxHairData.cpp");

	 	if( !bReference ){//write data at first time
			if( !currentJob.isShadow ){
				assert(pData->getRibFileFullPath().length()==0&&"rm_writePfxHairData.cpp");
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
	static void _write(liqRibPfxHairData* pData, const structJob &currentJob)
	{
		CM_TRACE_FUNC("_write("<<pData->getFullPathName()<<","<<currentJob.name<<")");

		//
		if( pData->isEmpty() ) 
		{
			unsigned numTokens( pData->tokenPointerArray.size() );
			boost::scoped_array< RtToken > tokenArray( new RtToken[ numTokens ] );
			boost::scoped_array< RtPointer > pointerArray( new RtPointer[ numTokens ] );
			assignTokenArraysV( pData->tokenPointerArray, tokenArray.get(), pointerArray.get() );

			RiCurvesV( "cubic", pData->ncurves, pData->nverts.get(), "nonperiodic", numTokens, tokenArray.get(), pointerArray.get() );
		} 
		else{
			RiIdentity(); // In case we're in a motion block!
			liquidMessage2(messageWarning, "pfxHair is empty %s",  pData->getFullPathName());
		}
	}
}//namespace renderman
