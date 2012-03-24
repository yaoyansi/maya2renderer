#include <liqHeroRibWriterMgr.h>

#include <string>
#include "./common/prerequest_maya.h"

#include <liqGlobalVariable.h>
#include <liqRibTranslator.h>
#include "shadergraph/shadermgr.h"

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
	//RiBegin() is moved to RM::Renderer::HeroPassBegin()
	// full beauty/shadow rib generation
	//
	/* cout <<"  * build full rib"<<endl; */
	if( liqRibTranslator::getInstancePtr()->ribPrologue__(currentJob___) == MS::kSuccess ) 
	{
		if( liqRibTranslator::getInstancePtr()->framePrologue__( scanTime__, currentJob___ ) != MS::kSuccess ) 
			return TCB_Break;//break;

		if (liqRibTranslator::getInstancePtr()->m_OutputShaderGraph){
			liquidmaya::ShaderMgr::getSingletonPtr()->exportShaderGraph();
		}
		
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
		liqRibTranslator::getInstancePtr()->ribEpilogue__(currentJob___);
		// output info when done with the rib - Alf
		printf("Finished RIB generation %s\n", currentJob___.ribFileName.asChar());
	}
	//RiEnd() is moved to RM::Renderer::HeroPassEnd()

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
//
void tHeroRibWriterMgr::framePrologue_display(const structJob &currentJob)
{
			// Smooth Shading
			RiShadingInterpolation( "smooth" );
			// Quantization
			// overriden to floats when in rendering to Maya's renderView
			if( !liqglo.m_renderView && liqglo.quantValue != 0 )
			{
				int whiteValue = (int) pow( 2.0, liqglo.quantValue ) - 1;
				RiQuantize( RI_RGBA, whiteValue, 0, whiteValue, 0.5 );
			}
			else
			{
				RiQuantize( RI_RGBA, 0, 0, 0, 0 );
			}
			if( liqglo.m_rgain != 1.0 || liqglo.m_rgamma != 1.0 )
			{
				RiExposure( liqglo.m_rgain, liqglo.m_rgamma );
			}

			LIQDEBUGPRINTF( "-> Setting Display Options\n" );
			if( ( liqglo.m_cropX1 != 0.0 ) || ( liqglo.m_cropY1 != 0.0 ) || ( liqglo.m_cropX2 != 1.0 ) || ( liqglo.m_cropY2 != 1.0 ) ) 
			{
				// philippe : handle the rotated camera case
				if( liqglo.liqglo_rotateCamera == true ) 
					RiCropWindow( liqglo.m_cropY2, liqglo.m_cropY1, 1 - liqglo.m_cropX1, 1 - liqglo.m_cropX2 );
				else 
					RiCropWindow( liqglo.m_cropX1, liqglo.m_cropX2, liqglo.m_cropY1, liqglo.m_cropY2 );
			}
			// display channels
			if( liqglo.liquidRenderer.supports_DISPLAY_CHANNELS ) 
			{
				RiArchiveRecord( RI_COMMENT, "Display Channels:" );
				// philippe -> to do : move this to higher scope ?
				MStringArray channeltype;
				channeltype.append( "float" );
				channeltype.append( "color" );
				channeltype.append( "point" );
				channeltype.append( "normal" );
				channeltype.append( "vector" );

				std::vector<StructChannel>::iterator m_channels_iterator;
				m_channels_iterator = liqglo.m_channels.begin();

				while ( m_channels_iterator != liqglo.m_channels.end() ) 
				{
					int       numTokens = 0;
					RtToken   tokens[5];
					RtPointer values[5];

					MString channel;
					char* filter;
					int quantize[4];
					float filterwidth[2];
					float dither;

					// #if defined( GENERIC_RIBLIB )          
					MString quantize_str;
					MString dither_str;
					MString filter_str;
					// #endif
					channel = channeltype[m_channels_iterator->type];
					char theArraySize[8];
					sprintf( theArraySize, "%d", m_channels_iterator->arraySize );
					if( m_channels_iterator->arraySize > 0 ) 
						channel += "[" + (MString)theArraySize + "]";
					channel += " " + m_channels_iterator->name ;

					if( m_channels_iterator->quantize ) 
					{
						int max = ( int )pow( 2., m_channels_iterator->bitDepth ) - 1;
						dither = m_channels_iterator->dither;
						quantize[0] = quantize[2] = 0;
						quantize[1] = quantize[3] = max;
						tokens[ numTokens ] = "int[4] quantize";
						values[ numTokens ] = (RtPointer)quantize;
						numTokens++;
#if !defined( GENERIC_RIBLIB )               
					}
#else
						MString maxStr, dStr;
						maxStr.set( max );
						quantize_str = "\"int[4] quantize\" [ 0 " + maxStr + " 0 " + maxStr + " ]";

						dStr.set( dither, 4 );
						dither_str = "\"float dither\" ["+ dStr +"]";
					}
					else
					{
						quantize_str = "\"int[4] quantize\" [ 0 0 0 0 ]"; 
						dither_str.clear();
					}
#endif

					if( m_channels_iterator->filter ) 
					{
						MString pixFilter( liqglo.liquidRenderer.pixelFilterNames[ m_channels_iterator->pixelFilter ] );
						filter = ( char* )pixFilter.asChar();

						liquidMessage2(messageInfo, ">>  m_channels_iterator->pixelFilter = %s\n", liqglo.liquidRenderer.pixelFilterNames[ m_channels_iterator->pixelFilter ].asChar() );
						liquidMessage2(messageInfo, ">>  pixFilter.asChar() = %s\n", pixFilter.asChar() );

						tokens[ numTokens ] = "string filter";
						values[ numTokens ] = ( RtPointer )&filter;
						numTokens++;

						filterwidth[0] = m_channels_iterator->pixelFilterX;
						filterwidth[1] = m_channels_iterator->pixelFilterY;
						tokens[ numTokens ] = "float filterwidth[2]";
						values[ numTokens ] = ( RtPointer )filterwidth;
						numTokens++;
#if !defined( GENERIC_RIBLIB )               
					}
#else
						MString pixFilterX, pixFilterY;
						pixFilterX.set( filterwidth[0], 4 );
						pixFilterY.set( filterwidth[1], 4 );
						filter_str = "\"string filter\" [\"" + pixFilter +"\"] \"float filterwidth[2]\" [" + pixFilterX + " " + pixFilterY +"]";
					} 
					else
						filter_str.clear();
#endif

#if defined( DELIGHT )  || defined( PRMAN ) || defined( PIXIE )
					//if( liquidRenderer.renderName == MString("PRMan") )
					RiDisplayChannelV( ( RtToken )channel.asChar(), numTokens, tokens, values );
#else
					// || defined( GENERIC_RIBLIB )

					RiArchiveRecord( RI_VERBATIM, "DisplayChannel \"%s\" %s %s %s", const_cast< char* >( channel.asChar() ),  quantize_str.asChar(), dither_str.asChar(), filter_str.asChar() );

#endif
					m_channels_iterator++;
				}//while ( m_channels_iterator != m_channels.end() ) 
			}//if( liqglo.liquidRenderer.supports_DISPLAY_CHANNELS ) 
			
			
			// output display drivers
			RiArchiveRecord( RI_COMMENT, "Display Drivers:" );
			liqRIBMsg("Display 6");

			std::vector<StructDisplay>::iterator m_displays_iterator;
			m_displays_iterator = liqglo.m_displays.begin();

			MString parameterString;
			MString imageName;
			MString imageType;
			MString imageMode;
			MString quantizer;
			MString dither;
			MString filter;
			MStringArray paramType;
			paramType.append( "string " );
			paramType.append( "float " );
			paramType.append( "int " );

			while ( m_displays_iterator != liqglo.m_displays.end() ) 
			{
				// check if additionnal displays are enabled
				// if not, call it off after the 1st iteration.
				if( liqglo.m_ignoreAOVDisplays && m_displays_iterator > liqglo.m_displays.begin() ) 
					break;

				// This is the override for the primary DD
				// when you render to maya's renderview.
				if( m_displays_iterator == liqglo.m_displays.begin() && liqglo.m_renderView ) 
				{
					MString imageName( liqglo.m_pixDir );
					imageName += parseString( liqglo.m_displays[ 0 ].name, false );
					//imageName = liquidGetRelativePath( liqglo_relativeFileNames, imageName, liqglo_projectDir );

					MString formatType = "liqmaya";
					MString imageMode = "rgba";

					// char tmp[20];
					// sprintf( tmp, "%i", m_renderViewPort);
					// MString port = ( char* )tmp;
					MString port;
					port.set( liqglo.m_renderViewPort );

					MString host = "localhost";
					if( !liqglo.m_renderViewLocal ) 
						MGlobal::executeCommand( "strip(system(\"echo $HOST\"));", host );

					liqRIBMsg("Display 7");
					RiArchiveRecord( RI_COMMENT, "Render To Maya renderView :" );
					RiArchiveRecord( RI_VERBATIM, "Display \"%s\" \"%s\" \"%s\" \"int merge\" [0] \"int mayaDisplayPort\" [%s] \"string host\" [\"%s\"]\n", 
						const_cast< char* >( imageName.asChar() ), 
						formatType.asChar(), imageMode.asChar(), port.asChar(), host.asChar() );

					// in this case, override the launch render settings
					if( liqglo.launchRender == false ) 
						liqglo.launchRender = true;
				} 
				else 
				{
					// check if display is enabled
					if( !(*m_displays_iterator).enabled ) 
					{
						m_displays_iterator++;
						continue;
					}
					// get display name
					// defaults to scenename.0001.tif if left empty
					imageName = (*m_displays_iterator).name;
					if( imageName == "" ) 
						imageName = liquidTransGetSceneName() + ".#." + liqglo.outExt;
					imageName = liqglo.m_pixDir + parseString( imageName, false );
					// we test for an absolute path before converting from rel to abs path in case the picture dir was overriden through the command line.
					//if( liqglo.m_pixDir.index( '/' ) != 0 ) imageName = liquidGetRelativePath( liqglo_relativeFileNames, imageName, liqglo_projectDir );
					if( m_displays_iterator > liqglo.m_displays.begin() ) 
						imageName = "+" + imageName;
					// get display type ( tiff, openexr, etc )
					imageType = (*m_displays_iterator).type;
					if( !isBatchMode() ){
						if( imageType == "" )
							imageType = "framebuffer";
					}else {// if in batch mode, we always use "file"
						imageType = "file";
					}
					// get display mode ( rgb, z or defined display channel )
					imageMode = (*m_displays_iterator).mode;
					if( imageMode == "" ) 
						imageMode = "rgba";
					// get quantization params
					if( (*m_displays_iterator).doQuantize && m_displays_iterator > liqglo.m_displays.begin() ) 
					{
						if( (*m_displays_iterator).bitDepth != 0 ) 
						{
							MString maxStr;
							int max = (int) pow( 2.0, (*m_displays_iterator).bitDepth ) - 1;

							maxStr.set( (double)max );
							quantizer = "\"float quantize[4]\" [ 0 " + maxStr + " 0 " + maxStr + " ]";

						} 
						else 
							quantizer = "\"float quantize[4]\" [ 0 0 0 0 ]";
						// char tmp[20];
						//sprintf( tmp, "%.1f", (*m_displays_iterator).dither );
						//  MString dStr = ( char* )tmp;
						MString dStr; 
						dStr.set( (*m_displays_iterator).dither, 3 );
						dither = "\"float dither\" ["+ dStr +"]";

					} 
					else 
					{
						quantizer.clear();
						dither.clear();
					}

					// get filter params
					if( (*m_displays_iterator).doFilter && m_displays_iterator > liqglo.m_displays.begin() )
					{

						MString pixFilter( liqglo.liquidRenderer.pixelFilterNames[(*m_displays_iterator).filter] );

						MString pixFilterX;  
						MString pixFilterY;
						pixFilterX.set( (*m_displays_iterator).filterX, 4 );
						pixFilterY.set( (*m_displays_iterator).filterY, 4 );

						filter = "\"string filter\" [\"" + pixFilter +"\"] \"float filterwidth[2]\" [" + pixFilterX + " " + pixFilterY +"]";
					} 
					else 
						filter.clear();

					// display driver specific arguments
					parameterString.clear();
					for ( int p = 0; p < (*m_displays_iterator).xtraParams.num; p++ ) 
					{
						parameterString += "\"";
						parameterString += paramType[ (*m_displays_iterator).xtraParams.type[p] ];
						parameterString += (*m_displays_iterator).xtraParams.names[p].asChar();
						parameterString += "\" [";
						parameterString += ((*m_displays_iterator).xtraParams.type[p] > 0)? "":"\"";
						parameterString += (*m_displays_iterator).xtraParams.data[p].asChar();
						parameterString += ((*m_displays_iterator).xtraParams.type[p] > 0)? "] ":"\"] ";
					}

					liqRIBMsg("Display 8");
					// output call
					RiArchiveRecord( RI_VERBATIM, "Display \"%s\" \"%s\" \"%s\" %s %s %s %s\n", 
						const_cast< char* >( imageName.asChar() ), 
						imageType.asChar(), 
						imageMode.asChar(), 
						( quantizer.length() )? quantizer.asChar() : "", 
						( dither.length() )? dither.asChar() : "", 
						( filter.length() )? filter.asChar() : "", 
						( parameterString.length() )? parameterString.asChar() : "" );
				}
				m_displays_iterator++;
			}//while ( m_displays_iterator != m_displays.end() )
}