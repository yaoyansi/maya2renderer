#include <liqShadowRibWriterMgr.h>

#include <string>

#include <liqGlobalVariable.h>
#include <liqRibTranslator.h>
#include <liqProcessLauncher.h>

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
	CM_TRACE_FUNC("tShadowRibWriterMgr::write(liqglo___,"<<currentJob___.name<<","<<scanTime__<<","<<m_outputLightsInDeepShadows__<<",jobList__.size="<<jobList__.size()<<")");

	MString     baseShadowName__(getBaseShadowName(currentJob___));

	if( !currentJob___.shadowArchiveRibDone ) 
	{
		//
		//  create the read-archive shadow files
		//
#ifndef RENDER_PIPE
		liquidMessage( "Beginning RIB output to '" + std::string( baseShadowName__.asChar() ) + "'", messageInfo );
		RiBegin( const_cast< RtToken >( baseShadowName__.asChar() ) );
		liqglo.m_ribFileOpen = true;
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
		liqglo.m_ribFileOpen = false;
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
	liqglo.m_ribFileOpen = true;
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
	liqglo.m_ribFileOpen = false;
	//------------------------------------------------------------
	//rendering
#ifdef _WIN32
	printf("shadow.liqProcessLauncher::execute(%s, %s %s \"%s\", \"%s\", %d)\n",
		liqglo.liquidRenderer.renderCommand.asChar(), liqglo___.liqglo_rifParams.asChar(), liqglo___.liquidRenderer.renderCmdFlags.asChar(), currentJob___.ribFileName.asChar(), liqglo___.liqglo_projectDir.asChar(), false);
	liqProcessLauncher::execute( liqglo___.liquidRenderer.renderCommand, " "+liqglo___.liqglo_rifParams+" "+ liqglo___.liquidRenderer.renderCmdFlags + " \"" + currentJob___.ribFileName + "\"", "\"" + liqglo___.liqglo_projectDir + "\"", false );
#else
	liqProcessLauncher::execute( liqglo___.liquidRenderer.renderCommand, " "+liqglo___.liqglo_rifParams+" "+ liqglo___.liquidRenderer.renderCmdFlags + " " + currentJob___.ribFileName, liqglo___.liqglo_projectDir, false );
#endif
	//------------------------------------------------------------
	return TCB_OK;
}


//
void tShadowRibWriterMgr::ribPrologue_samples(RtFloat xsamples, RtFloat ysamples)
{
	CM_TRACE_FUNC("tShadowRibWriterMgr::ribPrologue_samples("<<xsamples<<","<<ysamples<<")");

	RiPixelSamples( xsamples, ysamples );
}
//
void tShadowRibWriterMgr::ribPrologue_shadingrate(RtFloat size)
{
	CM_TRACE_FUNC("tShadowRibWriterMgr::ribPrologue_shadingrate("<<size<<")");

	RiShadingRate( size );
}
//
void tShadowRibWriterMgr::ribPrologue_filter(
	liquidlong m_rFilter,
	RtFloat m_rFilterX, RtFloat m_rFilterY)
{
	CM_TRACE_FUNC("tShadowRibWriterMgr::ribPrologue_filter("<<m_rFilter<<","<<m_rFilterX<<","<<m_rFilterY<<")");

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
	CM_TRACE_FUNC("tShadowRibWriterMgr::ribPrologue_pass("<<pass<<")");

	RiOption( "user", "string pass", ( RtPointer )&pass, RI_NULL );	
}
//
void tShadowRibWriterMgr::framePrologue_display(const structJob &currentJob)
{
	CM_TRACE_FUNC("tShadowRibWriterMgr::framePrologue_display(job="<<currentJob.name<<")");

			if( !/*liqglo.liqglo_*/currentJob.deepShadows || /*liqglo.liqglo_*/currentJob.shadowPixelSamples == 1)
			{
				if( liqglo.liquidRenderer.renderName == MString("Pixie") )
				{
					RtFloat zero = 0;
					RiHider( "hidden", "jitter", &zero, RI_NULL );
				}
				else
				{
					RtInt zero = 0;
					RiHider( "hidden", "int jitter", &zero, RI_NULL );
				}
			}
			if( /*liqglo.liqglo_*/currentJob.isMidPointShadow && !/*liqglo.liqglo_*/currentJob.deepShadows )
			{
				RtString midPoint = "midpoint";
				RtFloat midRatio = /*liqglo.liqglo_*/currentJob.midPointRatio;

				RiHider( "hidden", "depthfilter", &midPoint, RI_NULL );

				if ( /*liqglo.liqglo_*/currentJob.midPointRatio != 0 )
					RiHider( "hidden", "midpointratio", &midRatio, RI_NULL ); // Output to rib jami
			}
			//-----------------------------------------------------
			LIQDEBUGPRINTF( "-> Setting Display Options\n" );
			//MString relativeShadowName( liquidSanitizePath( liquidGetRelativePath( liqglo_relativeFileNames, liqglo_currentJob.imageName, liqglo_projectDir ) ) );
			if( !/*liqglo.liqglo_*/currentJob.isMinMaxShadow )
			{
				if( /*liqglo.liqglo_*/currentJob.deepShadows )
				{
					// RiDeclare( "volumeinterpretation", "string" );
					RtString viContinuous = "continuous";
					RtString viDiscrete   = "discrete";

					if( liqglo.liquidRenderer.renderName == MString("3Delight") )
					{
						liqRIBMsg("Display 1");
						RiDisplay( const_cast< char* >( /*liqglo.liqglo_*/currentJob.imageName.asChar()),
							const_cast< char* >( /*liqglo.liqglo_*/currentJob.format.asChar() ),
							(RtToken)/*liqglo.liqglo_*/currentJob.imageMode.asChar(),
							"string volumeinterpretation",
							( /*liqglo.liqglo_*/currentJob.shadowVolumeInterpretation == 1 ? &viContinuous : &viDiscrete ),
							RI_NULL );
					}
					else
					{
						// Deep shadows cannot be the primary output driver in PRMan & co.
						// We need to create a null output zfile first, and use the deep
						// shadows as a secondary output.
						//
						if( liqglo.liquidRenderer.renderName != MString("Pixie") )
						{
							liqRIBMsg("Display 2");
							RiDisplay( "null", "null", "z", RI_NULL );
						}

						MString deepFileImageName = "+" + /*liqglo.liqglo_*/currentJob.imageName;

						liqRIBMsg("Display 3");
						RiDisplay( const_cast< char* >( deepFileImageName.asChar() ),
							const_cast< char* >( /*liqglo.liqglo_*/currentJob.format.asChar() ),
							(RtToken)/*liqglo.liqglo_*/currentJob.imageMode.asChar(),
							"string volumeinterpretation",
							( /*liqglo.liqglo_*/currentJob.shadowVolumeInterpretation == 1 ? &viContinuous : &viDiscrete ),
							RI_NULL );
					}
				}//if( liqglo.liqglo_currentJob.deepShadows )
				else
				{
					liqRIBMsg("Display 4");
					RtInt aggregate( /*liqglo.liqglo_*/currentJob.shadowAggregation );
					RiDisplay( const_cast< char* >( /*liqglo.liqglo_*/currentJob.imageName.asChar() ),
						const_cast< char* >( /*liqglo.liqglo_*/currentJob.format.asChar() ),
						(RtToken)/*liqglo.liqglo_*/currentJob.imageMode.asChar(),
						"int aggregate", &aggregate,
						RI_NULL );
				}
			}//if( !liqglo.liqglo_currentJob.isMinMaxShadow )
			else
			{
				liqRIBMsg("Display 5");
				RiArchiveRecord( RI_COMMENT, "Display Driver:" );
				RtInt minmax = 1;
				RiDisplay( const_cast< char* >( (/*liqglo.liqglo_*/currentJob.imageName+(int)liqglo.liqglo_lframe).asChar() ),//const_cast< char* >( parseString(liqglo_currentJob.imageName).asChar() ),
					const_cast< char* >(/*liqglo.liqglo_*/currentJob.format.asChar()),
					(RtToken)/*liqglo.liqglo_*/currentJob.imageMode.asChar(),
					"minmax", &minmax,
					RI_NULL );
			}
}
//