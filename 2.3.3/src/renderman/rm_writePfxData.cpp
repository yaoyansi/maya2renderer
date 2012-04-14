#include "rm_renderer.h"
#include <liqRibPfxHairData.h>
#include <liqGlobalVariable.h>
#include "rm_helper.h"

namespace renderman
{
	static void _write(liqRibPfxData* pData, const structJob &currentJob);
	//
	void Renderer::write(
		/*const*/ liqRibPfxData* pData,
		const MString &ribFileName,
		const structJob &currentJob,
		const bool bReference)
	{
		CM_TRACE_FUNC("Renderer::write("<<pData->getFullPathName()<<","<<ribFileName<<","<<currentJob.name<<",ref="<<bReference<<")");

	 	assert(liqglo.m_ribFileOpen&&"liqRibPfxData.cpp");
	 
	 	if( !bReference ){//write data at first time
			if( !currentJob.isShadow ){
				assert(pData->getRibFileFullPath().length()==0&&"rm_writePfxData.cpp");
			}
			pData->setRibFileFullPath(ribFileName);
	 
	 		renderman::Helper o;
	 		o.RiBeginRef(pData->getRibFileFullPath().asChar());
	 		_write(pData,currentJob);
	 		o.RiEndRef();
	 
	 	}else{
	 		//write the reference
	 		assert(pData->getRibFileFullPath() == ribFileName);
	 		RiReadArchive( const_cast< RtToken >( pData->getRibFileFullPath().asChar() ), NULL, RI_NULL );
	 	}
	}
	//
	static void _write(liqRibPfxData* pData, const structJob &currentJob)
	{
		CM_TRACE_FUNC("_write("<<pData->getFullPathName()<<","<<currentJob.name<<")");

		LIQDEBUGPRINTF( "-> writing painteffects curves\n" );

		unsigned setOn( 0 );
		if( pData->pfxtype == MRT_PfxLeaf )
			setOn = 1;
		if( pData->pfxtype == MRT_PfxPetal )
			setOn = 2;

		if( pData->hasFeature[ setOn ] )
		{
			unsigned numTokens( pData->pfxTokenPointerArrays[ setOn ].size() );
			boost::scoped_array< RtToken > tokenArray( new RtToken[ numTokens ] );
			boost::scoped_array< RtPointer > pointerArray( new RtPointer[ numTokens ] );
			assignTokenArraysV( pData->pfxTokenPointerArrays[ setOn ], tokenArray.get(), pointerArray.get() );

			RiCurvesV( "cubic", pData->nverts[ setOn ].size(), const_cast< RtInt* >( &pData->nverts[ setOn ][ 0 ] ), "nonperiodic", numTokens, tokenArray.get(), pointerArray.get() );
		}

	}
}//namespace renderman
