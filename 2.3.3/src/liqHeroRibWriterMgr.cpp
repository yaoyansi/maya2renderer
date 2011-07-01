#include <liqHeroRibWriterMgr.h>

#include <string>

#include <liqGlobalVariable.h>
#include <liqRibTranslator.h>

tHeroRibWriterMgr::tHeroRibWriterMgr()
{

}
//
tHeroRibWriterMgr::~tHeroRibWriterMgr()
{

}
//
TempControlBreak tHeroRibWriterMgr::write(
struct liqGlobalVariable &liqglo___, 
	const structJob &currentJob___ ,
	const long scanTime__,
	const bool m_outputLightsInDeepShadows__
	//,std::vector<structJob>  jobList__
	)
{
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
	// full beauty/shadow rib generation
	//
	/* cout <<"  * build full rib"<<endl; */
	if( liqRibTranslator::getInstancePtr()->ribPrologue__(currentJob___) == MS::kSuccess ) 
	{
		if( liqRibTranslator::getInstancePtr()->framePrologue__( scanTime__, currentJob___ ) != MS::kSuccess ) 
			return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->worldPrologue__(currentJob___) != MS::kSuccess ) 
			return TCB_Break;//break;
		if( !currentJob___.isShadow || ( currentJob___.isShadow && currentJob___.deepShadows && m_outputLightsInDeepShadows__) ) 
			if( liqRibTranslator::getInstancePtr()->lightBlock__(currentJob___) != MS::kSuccess ) 
				return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->coordSysBlock__(currentJob___) != MS::kSuccess ) 
			return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->objectBlock__(currentJob___) != MS::kSuccess ) 
			return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->worldEpilogue__() != MS::kSuccess ) 
			return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->frameEpilogue__( scanTime__ ) != MS::kSuccess ) 
			return TCB_Break;//break;
		liqRibTranslator::getInstancePtr()->ribEpilogue__();
		// output info when done with the rib - Alf
		cout <<"Finished RIB generation "<<currentJob___.ribFileName.asChar()<<endl;
	}
	RiEnd();

	return TCB_OK;
}
//
//
void tHeroRibWriterMgr::ribPrologue_samples(RtFloat xsamples, RtFloat ysamples)
{
	RiPixelSamples( xsamples, ysamples );
}
//
void tHeroRibWriterMgr::ribPrologue_shadingrate(RtFloat size)
{
	RiShadingRate( size );
}
//
void tHeroRibWriterMgr::ribPrologue_filter(
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
		//RiPixelFilter( filterfunc, xwidth, ywidth );
}
//
void tHeroRibWriterMgr::ribPrologue_hider(HiderType hidertype)
{
	RtString hiderName;
	switch( hidertype ) 
	{
	case htPhoton:
		hiderName = "photon";
		break;
	case htRaytrace:
		hiderName = "raytrace";
		break;
	case htOpenGL:
		hiderName = "OpenGL";
		break;
	case htZbuffer:
		hiderName = "zbuffer";
		break;
	case htDepthMask:
		hiderName = "depthmask";
		break;
	case htHidden:
	default:
		hiderName = "hidden";
	}
	MString hiderOptions = getHiderOptions( liqglo.liquidRenderer.renderName, hiderName );
	RiArchiveRecord( RI_VERBATIM, "Hider \"%s\" %s\n", hiderName, ( char* )hiderOptions.asChar() );

}
//
void tHeroRibWriterMgr::ribPrologue_pass(RtString pass)
{
	RiOption( "user", "string pass", ( RtPointer )&pass, RI_NULL );	
}