#include <liqShadowRibWriterMgr.h>

#include <string>

#include <liqGlobalVariable.h>
#include <liqRibTranslator.h>

tShadowRibWriterMgr::tShadowRibWriterMgr()
{

}
//
tShadowRibWriterMgr::~tShadowRibWriterMgr()
{

}
//
TempControlBreak tShadowRibWriterMgr::write(
	struct liqGlobalVariable &liqglo___, 
	const structJob &currentJob___ ,
	const long scanTime__,
	const bool m_outputLightsInDeepShadows__,
	std::vector<structJob>  jobList__
	)
{
	MString     baseShadowName__(getBaseShadowName(currentJob___));

	if( !currentJob___.shadowArchiveRibDone ) 
	{
		//
		//  create the read-archive shadow files
		//
#ifndef RENDER_PIPE
		liquidMessage( "Beginning RIB output to '" + std::string( baseShadowName__.asChar() ) + "'", messageInfo );
		RiBegin( const_cast< RtToken >( baseShadowName__.asChar() ) );
#else
		liqglo__.liqglo_ribFP = fopen( baseShadowName.asChar(), "w" );
		if( liqglo__.liqglo_ribFP ) {
			LIQDEBUGPRINTF( "-> setting pipe option\n" );
			RtInt ribFD( fileno( liqglo__.liqglo_ribFP ) );
			RiOption( "rib", "pipe", &ribFD, RI_NULL );
		}
		else
		{
			liquidMessage( "Error opening RIB -- writing to stdout.\n", messageError );
		}
		liquidMessage( "Beginning RI output directly to renderer", messageInfo );
		RiBegin( RI_NULL );
#endif
		if( liqRibTranslator::getInstancePtr()->worldPrologue__() != MS::kSuccess )
			return TCB_Break;//break;
		if( currentJob___.isShadow && currentJob___.deepShadows && m_outputLightsInDeepShadows__ ) 
			if( liqRibTranslator::getInstancePtr()->lightBlock__() != MS::kSuccess ) 
				return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->coordSysBlock__() != MS::kSuccess ) 
			return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->objectBlock__() != MS::kSuccess ) 
			return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->worldEpilogue__() != MS::kSuccess ) 
			return TCB_Break;//break;
		RiEnd();
#ifdef RENDER_PIPE  
		fclose( liqglo___.liqglo_ribFP );
#endif
		liqglo___.liqglo_ribFP = NULL;

		// mark all other jobs with the same set as done
		std::vector<structJob>::iterator iterCheck = jobList__.begin();
		while ( iterCheck != jobList__.end() ) 
		{
			if( iterCheck->shadowObjectSet == currentJob___.shadowObjectSet &&
				iterCheck->everyFrame == currentJob___.everyFrame &&
				iterCheck->renderFrame == currentJob___.renderFrame
				)
				iterCheck->shadowArchiveRibDone = true;
			++iterCheck;
		}

		liqglo___.m_alfShadowRibGen = true;
	}//  !liqglo_currentJob.shadowArchiveRibDone  
	else{
		//todo....
	}
	//----------------------------------------------------------------
#ifndef RENDER_PIPE
	liquidMessage( "Beginning RIB output to '" + std::string( currentJob___.ribFileName.asChar() ) + "'", messageInfo );
	RiBegin( const_cast< RtToken >( currentJob___.ribFileName.asChar() ) );
#else//RENDER_PIPE
	liqglo___.liqglo_ribFP = fopen( currentJob___.ribFileName.asChar(), "w" );
	if( liqglo___.liqglo_ribFP ) 
	{
		RtInt ribFD = fileno( liqglo___.liqglo_ribFP );
		RiOption( ( RtToken )"rib", ( RtToken )"pipe", &ribFD, RI_NULL );
	} 
	else
	{
		liquidMessage( "Error opening RIB -- writing to stdout.\n", messageError );
	}

	liquidMessage( "Beginning RI output directly to renderer", messageInfo );
	RiBegin( RI_NULL );
#endif//RENDER_PIPE
	// reference the correct shadow archive
	//
	/* cout <<"  * referencing shadow archive "<<baseShadowName.asChar()<<endl; */
	if( liqRibTranslator::getInstancePtr()->ribPrologue__() == MS::kSuccess ) 
	{
		if( liqRibTranslator::getInstancePtr()->framePrologue__( scanTime__ ) != MS::kSuccess ) 
			return TCB_Break;//break;
		//MString realShadowName( liquidSanitizePath( liquidGetRelativePath( liqglo_relativeFileNames, baseShadowName, liqglo_projectDir ) ) );
		RiArchiveRecord( RI_COMMENT, "Read Archive Data:\n" );
		RiReadArchive( const_cast< RtToken >( baseShadowName__.asChar() ), NULL, RI_NULL );
		if( liqRibTranslator::getInstancePtr()->frameEpilogue__( scanTime__ ) != MS::kSuccess ) 
			return TCB_Break;//break;
		liqRibTranslator::getInstancePtr()->ribEpilogue__();
	}
	RiEnd();
	//------------------------------------------------------------

	return TCB_OK;
}
