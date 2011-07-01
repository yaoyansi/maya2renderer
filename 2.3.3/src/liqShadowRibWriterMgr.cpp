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
		if( liqRibTranslator::getInstancePtr()->worldPrologue__(currentJob___) != MS::kSuccess )
			return TCB_Break;//break;
		if( currentJob___.isShadow && currentJob___.deepShadows && m_outputLightsInDeepShadows__ ) 
			if( liqRibTranslator::getInstancePtr()->lightBlock__(currentJob___) != MS::kSuccess ) 
				return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->coordSysBlock__(currentJob___) != MS::kSuccess ) 
			return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->objectBlock__(currentJob___) != MS::kSuccess ) 
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
	if( liqRibTranslator::getInstancePtr()->ribPrologue__(currentJob___) == MS::kSuccess ) 
	{
		if( liqRibTranslator::getInstancePtr()->framePrologue__( scanTime__, currentJob___) != MS::kSuccess ) 
			return TCB_Break;//break;
		//MString realShadowName( liquidSanitizePath( liquidGetRelativePath( liqglo_relativeFileNames, baseShadowName, liqglo_projectDir ) ) );
		RiArchiveRecord( RI_COMMENT, "Read Archive Data:\n" );
		RiReadArchive( const_cast< RtToken >( baseShadowName__.asChar() ), NULL, RI_NULL );
		if( liqRibTranslator::getInstancePtr()->frameEpilogue__( scanTime__ ) != MS::kSuccess ) 
			return TCB_Break;//break;
		liqRibTranslator::getInstancePtr()->ribEpilogue__(currentJob___);
	}
	RiEnd();
	//------------------------------------------------------------

	return TCB_OK;
}


//
void tShadowRibWriterMgr::ribPrologue_samples(RtFloat xsamples, RtFloat ysamples)
{
	RiPixelSamples( xsamples, ysamples );
}
//
void tShadowRibWriterMgr::ribPrologue_shadingrate(RtFloat size)
{
	RiShadingRate( size );
}
//
void tShadowRibWriterMgr::ribPrologue_filter(
	liquidlong m_rFilter,
	RtFloat m_rFilterX, RtFloat m_rFilterY)
{
	switch (m_rFilter) 
	{
	case pfBoxFilter:
		RiPixelFilter( RiBoxFilter, m_rFilterX, m_rFilterY );
		break;
	case pfTriangleFilter:
		RiPixelFilter( RiTriangleFilter, m_rFilterX, m_rFilterY );
		break;
	case pfCatmullRomFilter:
		RiPixelFilter( RiCatmullRomFilter, m_rFilterX, m_rFilterY );
		break;
	case pfGaussianFilter:
		RiPixelFilter( RiGaussianFilter, m_rFilterX, m_rFilterY );
		break;
	case pfSincFilter:
		RiPixelFilter( RiSincFilter, m_rFilterX, m_rFilterY );
		break;
#if defined ( DELIGHT ) || defined ( PRMAN ) || defined ( GENERIC_RIBLIB )
	case pfBlackmanHarrisFilter:
		RiArchiveRecord( RI_VERBATIM, "PixelFilter \"blackman-harris\" %g %g\n", m_rFilterX, m_rFilterY);
		break;
	case pfMitchellFilter:
		RiArchiveRecord( RI_VERBATIM, "PixelFilter \"mitchell\" %g %g\n", m_rFilterX, m_rFilterY);
		break;
	case pfSepCatmullRomFilter:
		RiArchiveRecord( RI_VERBATIM, "PixelFilter \"separable-catmull-rom\" %g %g\n", m_rFilterX, m_rFilterY);
		break;
	case pfBesselFilter:
		RiArchiveRecord( RI_VERBATIM, "PixelFilter \"bessel\" %g %g\n", m_rFilterX, m_rFilterY);
		break;
#endif
#if defined ( PRMAN ) || defined ( GENERIC_RIBLIB )
	case pfLanczosFilter:
		RiArchiveRecord( RI_VERBATIM, "PixelFilter \"lanczos\" %g %g\n", m_rFilterX, m_rFilterY);
		break;
	case pfDiskFilter:
		RiArchiveRecord( RI_VERBATIM, "PixelFilter \"disk\" %g %g\n", m_rFilterX, m_rFilterY);
		break;
#endif
	default:
		RiArchiveRecord( RI_COMMENT, "Unknown Pixel Filter selected" );
		break;
	}
}
//
void tShadowRibWriterMgr::ribPrologue_pass(RtString pass)
{
	RiOption( "user", "string pass", ( RtPointer )&pass, RI_NULL );	
}