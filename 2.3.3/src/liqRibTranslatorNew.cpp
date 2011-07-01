/*
**
**
** The contents of this file are subject to the Mozilla Public License Version
** 1.1  (the "License"); you may not use this file except in compliance with
** the License. You may obtain a copy of the License at
** http://www.mozilla.org/MPL/
**
** Software distributed under the License is distributed on an "AS IS" basis,
** WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
** for the specific language governing rights and limitations under the
** License.
**
** The Original Code is the Liquid Rendering Toolkit.
**
** The Initial Developer of the Original Code is Colin Doncaster. Portions
** created by Colin Doncaster are Copyright (C) 2002. All Rights Reserved.
**
** Contributor(s): Berj Bannayan.
**
**
** The RenderMan (R) Interface Procedures and Protocol are:
** Copyright 1988, 1 989, Pixar
** All Rights Reserved
**
**
** RenderMan (R) is a registered trademark of Pixar
*/


#include <sys/types.h>

#ifndef _WIN32
#include <sys/time.h>
#include <sys/stat.h>
// Dynamic Object Headers
#include <dlfcn.h>
#endif

#ifdef _WIN32
#pragma warning(disable:4786)
#endif



// Renderman Headers
//extern "C" {
#include "ri_interface.h"
//}

#ifdef _WIN32
#include <process.h>
#include <io.h>
#include <direct.h>
#else
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#endif

#include <algorithm>
#include <time.h>

#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <strstream>

#if defined(_WIN32) && !defined(DEFINED_LIQUIDVERSION)
// unix build gets this from the Makefile
static const char *LIQUIDVERSION =
#include "../liquid.version"
;
#define DEFINED_LIQUIDVERSION
#endif

//#define USE_DELETE

#ifdef USE_DELETE
#	ifdef _WIN32
#		define RM_CMD "cmd.exe /c del"
#	else
#	  define RM_CMD "/bin/rm"
#	endif
#else
#  define RM_CMD ""
#endif

// Maya headers
#include <maya/MAnimControl.h>
#include <maya/MFileIO.h>
#include <maya/MFnLight.h>
#include <maya/MFnTransform.h>
#include <maya/MGlobal.h>
#include <maya/MItDag.h>
#include <maya/MItInstancer.h>
#include <maya/MItSelectionList.h>
#include <maya/MPlug.h>
#include <maya/MSelectionList.h>
#include <maya/MSyntax.h>
#include <maya/MDistance.h>
#include <maya/MFnSet.h>
#include <maya/MFnStringArrayData.h>
#include <maya/MFnIntArrayData.h>
#include <maya/MFnPfxGeometry.h>
#include <maya/MDistance.h>
#include <maya/MDagModifier.h>
#include <maya/MPxNode.h>
#include <maya/MRenderLineArray.h>

// Liquid headers
#include <liquid.h>
#include <liqRibHT.h>
#include <liqRenderer.h>
#include <liqRibTranslator.h>
#include <liqGlobalHelpers.h>
#include <liqProcessLauncher.h>
#include <liqCustomNode.h>
#include <liqShaderFactory.h>

using namespace boost;
using namespace std;

typedef int RtError;


// this get's set if we are running the commandline version of liquid
extern bool liquidBin;
extern int  debugMode;


extern liquidVerbosityType liqglo_verbosity;
// Kept global for liquidRigGenData and liquidRibParticleData
extern FILE        *liqglo_ribFP;
extern long         liqglo_lframe;
extern structJob    liqglo_currentJob;
extern bool         liqglo_doMotion;                         // Motion blur for transformations
extern bool         liqglo_doDef;                            // Motion blur for deforming objects
extern bool         liqglo_doCompression;                    // output compressed ribs
extern bool         liqglo_doBinary;                         // output binary ribs
extern bool         liqglo_relativeMotion;                   // Use relative motion blocks
extern RtFloat      liqglo_sampleTimes[LIQMAXMOTIONSAMPLES]; // current sample times
extern RtFloat      liqglo_sampleTimesOffsets[LIQMAXMOTIONSAMPLES]; // current sample times (as offsets from frame)
extern int          liqglo_motionSamples;                    // used to assign more than two motion blur samples!
extern float        liqglo_shutterTime;
extern float        liqglo_shutterEfficiency;
extern bool         liqglo_doShadows;                        // Kept global for liquidRigLightData
extern bool         liqglo_shapeOnlyInShadowNames;
extern MString      liqglo_sceneName;
extern bool         liqglo_beautyRibHasCameraName;           // if true, usual behaviour, otherwise, no camera name in beauty rib
extern bool         liqglo_isShadowPass;                     // true if we are rendering a shadow pass
extern bool         liqglo_expandShaderArrays;
extern bool         liqglo_shortShaderNames;                 // true if we don't want to output path names with shaders
extern bool         liqglo_relativeFileNames;                // true if we only want to output project relative names
extern MStringArray liqglo_DDimageName;
extern double       liqglo_FPS;                              // Frame-rate (for particle streak length)
extern bool         liqglo_outputMeshUVs;                    // true if we are writing uvs for subdivs/polys (in addition to "st")
extern bool         liqglo_noSingleFrameShadows;             // allows you to skip single-frame shadows when you chunk a render
extern bool         liqglo_singleFrameShadowsOnly;           // allows you to skip single-frame shadows when you chunk a render
extern MString      liqglo_renderCamera;                     // a global copy for liqRibPfxToonData
extern bool         liqglo_relativeTransforms;               // wether we do Transform or ConcatTransform (relative)

// Kept global for liquidGlobalHelper
extern MString      liqglo_projectDir;
extern MString      liqglo_ribDir;
extern MString      liqglo_textureDir;
extern MString      liqglo_shaderPath;               // Shader searchpath
extern MString      liqglo_texturePath;             // Texture searchpath
extern MString      liqglo_archivePath;
extern MString      liqglo_proceduralPath;

// Kept global for liqRibNode.cpp
extern MStringArray liqglo_preGenerateArchive;
extern MStringArray liqglo_preReadArchive;
extern MStringArray liqglo_preRibBox;
extern MStringArray liqglo_preReadArchiveShadow;
extern  MStringArray liqglo_preRibBoxShadow;
extern MString      liqglo_currentNodeName;
extern MString      liqglo_currentNodeShortName;

extern bool         liqglo_useMtorSubdiv;  // use mtor subdiv attributes
extern bool         liqglo_outputMayaPolyCreases;
extern bool         liqglo_renderAllCurves;
extern HiderType    liqglo_hider;

// Kept global for raytracing
extern bool         rt_useRayTracing;
extern RtFloat      rt_traceBreadthFactor;
extern RtFloat      rt_traceDepthFactor;
extern int          rt_traceMaxDepth;
extern RtFloat      rt_traceSpecularThreshold;
extern int         rt_traceRayContinuation;
extern int          rt_traceCacheMemory;
extern bool         rt_traceDisplacements;
extern bool         rt_traceSampleMotion;
extern RtFloat      rt_traceBias;
extern int          rt_traceMaxDiffuseDepth;
extern int          rt_traceMaxSpecularDepth;
extern RtFloat      rt_irradianceMaxError;
extern RtFloat      rt_irradianceMaxPixelDist;

// Additionnal globals for organized people
extern MString      liqglo_shotName;
extern MString      liqglo_shotVersion;
extern MString      liqglo_layer;
extern bool         liqglo_doExtensionPadding;
extern int          liqglo_outPadding;

// renderer properties
extern liqRenderer liquidRenderer;

#if 0
#ifdef _WIN32
// Hmmmmmmmm what's this ?
int RiNColorSamples;
#endif
// these are little storage variables to keep track of the current graphics state and will eventually be wrapped in
// a specific class
#endif


//void liqRibTranslator::freeShaders( void )
//{
//  LIQDEBUGPRINTF( "-> freeing shader data.\n" );
//  m_shaders.clear();
//  LIQDEBUGPRINTF( "-> finished freeing shader data.\n" );
//}

// Hmmmmm should change magic to Liquid


#if defined( DELIGHT ) || defined( ENTROPY ) ||  defined( PRMAN ) || defined( AIR ) || defined( PIXIE ) || defined( GENERIC_RIBLIB ) 
extern void liqRibTranslatorErrorHandler( RtInt code, RtInt severity, char* message );
#else
extern void liqRibTranslatorErrorHandler( RtInt code, RtInt severity, const char* message );
#endif

/**
* This method actually does the renderman output.
*/
MStatus liqRibTranslator::doItNew( const MArgList& args , const MString& originalLayer )
{
	MStatus status;
	MString lastRibName;
	bool hashTableInited = false;



	status = liquidDoArgs( args );
	if( !status ) 
		return MS::kFailure;

	if( !liquidBin && !m_deferredGen ) 
		liquidMessage( "Creating RIB <Press ESC To Cancel> ...", messageInfo );

	// Remember the frame the scene was at so we can restore it later.
	MTime originalTime = MAnimControl::currentTime();

	// Set the frames-per-second global (we'll need this for
	// streak particles)
	//
	MTime oneSecond( 1, MTime::kSeconds );
	liqglo_FPS = oneSecond.as( MTime::uiUnit() );

	// append the progress flag for render job feedback
	if( useRenderScript ) 
		if( ( m_renderCommand == MString( "render" ) ) || ( m_renderCommand == MString( "prman" ) ) || ( m_renderCommand == MString( "renderdl" ) ) ) 
			m_renderCommand = m_renderCommand + " -Progress";

	// check to see if the output camera, if specified, is available
	if( liquidBin && ( renderCamera == "" ) ) 
	{
		liquidMessage( "No render camera specified!", messageError );
		return MS::kFailure;
	}
	if( renderCamera != "" ) 
	{
		MStatus selectionStatus;
		MSelectionList camList;
		selectionStatus = camList.add( renderCamera );
		if( selectionStatus != MS::kSuccess ) 
		{
			liquidMessage( "Invalid render camera!", messageError );
			return MS::kFailure;
		}
	}

	// check to see if all the directories we are working with actually exist.
	/*if( verifyOutputDirectories() ) {
	MString err( "The output directories are not properly setup in the globals" );
	throw err;
	}*/
	// This is bollocks! Liquid defaults to system temp folders if it can't setup shit. It should always work, not breaks
	verifyOutputDirectories();

	// setup the error handler
#if( !defined (GENERIC_RIBLIB) ) && ( defined ( AQSIS ) || ( _WIN32 && DELIGHT ) )
#  ifdef _WIN32
	if( m_errorMode ) RiErrorHandler( (void(__cdecl*)(int,int,char*))liqRibTranslatorErrorHandler );
#  else
	if( m_errorMode ) RiErrorHandler( (void(*)(int,int,char*))liqRibTranslatorErrorHandler );
#  endif
#else
	if( m_errorMode ) RiErrorHandler( liqRibTranslatorErrorHandler );
#endif
	// Setup helper variables for alfred
	MString alfredCleanUpCommand;
	if( remoteRender ) 
		alfredCleanUpCommand = MString( "RemoteCmd" );
	else 
		alfredCleanUpCommand = MString( "Cmd" );

	MString alfredRemoteTagsAndServices;
	if( remoteRender || useNetRman ) 
	{
		alfredRemoteTagsAndServices  = MString( "-service { " );
		alfredRemoteTagsAndServices += m_alfredServices.asChar();
		alfredRemoteTagsAndServices += MString( " } -tags { " );
		alfredRemoteTagsAndServices += m_alfredTags.asChar();
		alfredRemoteTagsAndServices += MString( " } " );
	}
	// A seperate one for cleanup as it doesn't need a tag!
	MString alfredCleanupRemoteTagsAndServices;
	if( remoteRender || useNetRman ) 
	{
		alfredCleanupRemoteTagsAndServices  = MString( "-service { " );
		alfredCleanupRemoteTagsAndServices += m_alfredServices.asChar();
		alfredCleanupRemoteTagsAndServices += MString( " } " );
	}

	// exception handling block, this tracks liquid for any possible errors and tries to catch them
	// to avoid crashing
	try 
	{
		m_escHandler.beginComputation();

		MString preFrameMel = parseString( m_preFrameMel );
		MString postFrameMel = parseString( m_postFrameMel );

		if( ( preFrameMel  != "" ) && !fileExists( preFrameMel ) ) 
			liquidMessage( "Cannot find pre frame MEL script file! Assuming local.", messageWarning );

		if( ( m_postFrameMel != "" ) && !fileExists( postFrameMel ) ) 
			liquidMessage( "Cannot find post frame MEL script file! Assuming local.", messageWarning );

		// build temp file names
		MString renderScriptName = generateRenderScriptName();
		MString tempDefname    = generateTempMayaSceneName();

		if( m_deferredGen ) 
		{
			MString currentFileType = MFileIO::fileType();
			MFileIO::exportAll( tempDefname, currentFileType.asChar() );
		}

		if( !m_deferredGen && m_justRib ) 
			useRenderScript = false;

		liqRenderScript jobScript;
// 		liqRenderScript::Job preJobInstance;
// 		preJobInstance.title = "liquid pre-job";
// 		preJobInstance.isInstance = true;

		if( useRenderScript ) 
		{
			if( renderJobName == "" ) 
				renderJobName = liqglo_sceneName;
			jobScript.title = renderJobName.asChar();

			if( useNetRman ) 
			{
				jobScript.minServers = m_minCPU;
				jobScript.maxServers = m_maxCPU;
			} 
			else 
			{
				jobScript.minServers = 1;
				jobScript.maxServers = 1;
			}

			if ( m_dirmaps.length() )
				jobScript.dirmaps = m_dirmaps.asChar();

			if( m_preJobCommand != MString( "" ) ) 
			{
				liqRenderScript::Job preJob;
				preJob.title = "liquid pre-job";
				preJob.commands.push_back( liqRenderScript::Cmd( m_preJobCommand.asChar(), ( remoteRender && !useNetRman ) ) );
				jobScript.addJob( preJob );
			}
		}
		// build the frame array
		//
		if( m_renderView ) 
		{
			// if we are in renderView mode,
			// just ignore the animation range
			// and render the current frame.
			frameNumbers.clear();
			frameNumbers.push_back( ( int ) originalTime.as( MTime::uiUnit() ) );
		}
		//
		// start looping through the frames  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		//
		liquidMessage( "Starting to loop through frames", messageInfo );

		int currentBlock( 0 );
		unsigned frameIndex( 0 );
		for ( ; frameIndex < frameNumbers.size(); frameIndex++ ) 
		{
			liqShaderFactory::instance().clearShaders();

			liqglo_lframe = frameNumbers[ frameIndex ];

			if( m_showProgress ) 
				printProgress( 1, frameNumbers.size(), frameIndex );

			liqRenderScript::Job frameScriptJob;

			m_alfShadowRibGen = false;
			liqglo_preReadArchive.clear();
			liqglo_preRibBox.clear();
			liqglo_preReadArchiveShadow.clear();
			liqglo_preRibBoxShadow.clear();

			// make sure all the global strings are parsed for this frame
			MString frameRenderCommand    = parseString( liquidRenderer.renderCommand + " " + liquidRenderer.renderCmdFlags, false );
			MString frameRibgenCommand    = parseString( m_ribgenCommand, false );
			MString framePreCommand       = parseString( m_preCommand, false );
			MString framePreFrameCommand  = parseString( m_preFrameCommand, false );
			MString framePostFrameCommand = parseString( m_postFrameCommand, false );

			if( useRenderScript ) 
			{
				if( m_deferredGen ) 
				{
					liqRenderScript::Job deferredJob;
					if( ( frameIndex % m_deferredBlockSize ) == 0 ) 
					{
						if( m_deferredBlockSize == 1 ) 
							currentBlock = liqglo_lframe;
						else 
							currentBlock++;

						stringstream ribGenExtras;
						// ribGenExtras << " -progress -noDef -nop -noalfred -projectDir " << liqglo_projectDir.asChar() << " -ribName " << liqglo_sceneName.asChar() << " -mf " << tempDefname.asChar() << " -t ";
						ribGenExtras << " -progress -noDef -projectDir " << liqglo_projectDir.asChar() << " -ribName " << liqglo_sceneName.asChar() << " -fl ";

						unsigned lastGenFrame( ( frameIndex + m_deferredBlockSize ) < frameNumbers.size() ? frameIndex + m_deferredBlockSize : frameNumbers.size() );

						//liquidMessage2(messageInfo, ">>> frameIndex = %d m_deferredBlockSize = %d frameNumbers.size = %d lastGenFrame = %d\n",frameIndex,m_deferredBlockSize,frameNumbers.size(),lastGenFrame );

						for( unsigned outputFrame( frameIndex ); outputFrame < lastGenFrame; outputFrame++ )
						{  
							ribGenExtras << frameNumbers[ outputFrame ];
							ribGenExtras << (( outputFrame != ( lastGenFrame - 1 ) )? ", " : " ");
							//liquidMessage2(messageInfo, "\t outputFrame = %d\n", outputFrame );
						}
						stringstream titleStream;
						titleStream << liqglo_sceneName.asChar() << "FrameRIBGEN" << currentBlock;
						deferredJob.title = titleStream.str();

						stringstream ss;
						ss << framePreCommand.asChar() << " " << frameRibgenCommand.asChar() << ribGenExtras.str() << " " << tempDefname.asChar();
						liqRenderScript::Cmd cmd( ss.str(), remoteRender );
						cmd.alfredServices = m_defGenService.asChar();
						cmd.alfredTags     = m_defGenKey.asChar();
						if( m_alfredExpand ) 
							cmd.alfredExpand = true;

						deferredJob.commands.push_back(cmd);
						jobScript.addJob(deferredJob);
					}
				}
				if( !m_justRib ) 
				{
					stringstream titleStream;
					titleStream << liqglo_sceneName.asChar() << "Frame" << liqglo_lframe;
					frameScriptJob.title = titleStream.str();

					if( m_deferredGen ) 
					{
						stringstream ss;
						ss << liqglo_sceneName.asChar() << "FrameRIBGEN" << currentBlock;
						liqRenderScript::Job instanceJob;
						instanceJob.isInstance = true;
						instanceJob.title = ss.str();
						frameScriptJob.childJobs.push_back(instanceJob);
					}
				}
			}

			LIQDEBUGPRINTF( "-> building jobs\n" );
			// Hmmmmmm not really clean ....
			if( buildJobs() != MS::kSuccess ) 
				break;

			if( !m_deferredGen ) 
			{
				if( m_showProgress ) 
					printProgress( 2, frameNumbers.size(), frameIndex );

				long lastScannedFrame = -100000;
				long scanTime = liqglo_lframe;
				hashTableInited = false;
				//
				// start iterating through the job list   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
				//
				if( jobList.size() == 0 ) 
				{
					liquidMessage( "Nothing to render!", messageWarning );
					return MS::kSuccess;
				}
				//cout <<"Job iteration start -------------------------------------"<<endl;
				//cout <<"    nsfs:"<<liqglo_noSingleFrameShadows<<"  sfso:"<<liqglo_singleFrameShadowsOnly<<endl;
				vector< structJob >::iterator iter( jobList.begin() );
				for (; iter != jobList.end(); ++iter ) 
				{
					m_currentMatteMode = false;
					liqglo_currentJob = *iter;

					if( liqglo_currentJob.skip ) 
						continue;

					//cout <<">> outputing job ["<<liqglo_lframe<<"] ->"<<liqglo_currentJob.name.asChar()<<" -> "<<liqglo_currentJob.imageName.asChar()<<endl;
					// set the scan time based on the job's render frame
					//
					scanTime = liqglo_currentJob.renderFrame;
					// if we changed the frame to calculate a shadow at a different time,
					// we need to rescan the scene, otherwise not.
					//
					if( lastScannedFrame != scanTime ) 
					{
						LIQDEBUGPRINTF( "Scanning at time: %u \n", scanTime );
						// hash table handling
						//
						/*if( hashTableInited && htable ) {
						//cout <<"delete old table... "<<flush;
						//delete htable;
						htable.reset();
						//freeShaders();
						}*/

						htable = shared_ptr< liqRibHT >( new liqRibHT() );
						hashTableInited = true;
						LIQDEBUGPRINTF( "Created hash table...\n" );

						//  calculate sampling time
						//
						float sampleinc( ( liqglo_shutterTime * m_blurTime ) / ( liqglo_motionSamples - 1 ) );
						for ( unsigned msampleOn( 0 ); msampleOn < liqglo_motionSamples; msampleOn++ ) 
						{
							float subframe;
							switch( shutterConfig ) 
							{
							case OPEN_ON_FRAME:
							default:
								subframe = scanTime + ( msampleOn * sampleinc );
								break;
							case CENTER_ON_FRAME:
								subframe = ( scanTime - ( liqglo_shutterTime * m_blurTime * 0.5 ) ) + msampleOn * sampleinc;
								break;
							case CENTER_BETWEEN_FRAMES:
								subframe = scanTime + ( 0.5 * ( 1 - ( liqglo_shutterTime * m_blurTime ) ) ) + ( msampleOn * sampleinc );
								break;
							case CLOSE_ON_NEXT_FRAME:
								subframe = scanTime + ( 1 - ( liqglo_shutterTime * m_blurTime ) ) + ( msampleOn * sampleinc );
								break;
							}
							liqglo_sampleTimes[ msampleOn ] = subframe;
							liqglo_sampleTimesOffsets[ msampleOn ] = msampleOn * sampleinc;
						}
						//cout <<"about to scan... "<<endl;
						// scan the scene
						//
						if( doCameraMotion || liqglo_doMotion || liqglo_doDef ) 
						{
							for ( int msampleOn = 0; msampleOn < liqglo_motionSamples; msampleOn++ ) 
								scanScene( liqglo_sampleTimes[ msampleOn ] , msampleOn );
						} else {
							liqglo_sampleTimes[ 0 ] = scanTime;
							liqglo_sampleTimesOffsets[ 0 ] = 0;
							scanScene( scanTime, 0 );
						}
						//cout <<"    + scene scan done !"<<endl;

						// mark the frame as already scanned
						lastScannedFrame = scanTime;
						liqglo_currentJob = *iter;
					}
					//
					// start scene parsing ------------------------------------------------------------------
					//
					if( liqglo_currentJob.isShadowPass ) 
						liqglo_isShadowPass = true;
					else 
						liqglo_isShadowPass = false;

					// build the shadow archive name for the job
					{
						bool renderAllFrames( liqglo_currentJob.everyFrame );
						long refFrame( liqglo_currentJob.renderFrame );
						MString geoSet( liqglo_currentJob.shadowObjectSet );
						baseShadowName = generateShadowArchiveName( renderAllFrames, refFrame, geoSet );
						baseShadowName = liquidGetRelativePath( liqglo_relativeFileNames, baseShadowName, liqglo_ribDir );
					}

					{//export geometry objects to rib files.
						MMatrix matrix;
						MDagPath path;
						MObject transform;
						MFnDagNode dagFn;

						for ( RNMAP::iterator rniter( htable->RibNodeMap.begin() ); rniter != htable->RibNodeMap.end(); rniter++ ) 
						{
							LIQ_CHECK_CANCEL_REQUEST;

							liqRibNodePtr ribNode( rniter->second );
							path = ribNode->path();
							transform = path.transform();
							
							if( ( !ribNode ) || ( ribNode->object(0)->type == MRT_Light ) ) 
								continue;
							if( ribNode->object(0)->type == MRT_Coord || ribNode->object(0)->type == MRT_ClipPlane ) 
								continue;

							_writeObject( ribNode);

						}
					}

					LIQDEBUGPRINTF( "-> setting RiOptions\n" );

					// Rib client file creation options MUST be set before RiBegin
#if defined(PRMAN) || defined(DELIGHT)
					/* THERE IS A RIBLIB BUG WHICH PREVENTS THIS WORKING */
					LIQDEBUGPRINTF( "-> setting binary option\n" );
					if( liqglo_doBinary ) 
					{
						RtString format[ 1 ] = { "binary" };
						RiOption( "rib", "format", ( RtPointer )format, RI_NULL );
					}

					LIQDEBUGPRINTF( "-> setting compression option\n" );
					if( liqglo_doCompression ) 
					{
						RtString comp[ 1 ] = { "gzip" };
						RiOption( "rib", "compression", ( RtPointer )comp, RI_NULL );
					}
#endif // PRMAN || DELIGHT
#ifdef PRMAN
					RtString style = "indented";
					RiOption( "rib", "string asciistyle", &style, RI_NULL );
#endif
					// world RiReadArchives and Rib Boxes ************************************************
					//
					if( liqglo_currentJob.isShadow && !liqglo_currentJob.shadowArchiveRibDone && !fullShadowRib ) 
					{
						//
						//  create the read-archive shadow files
						//
#ifndef RENDER_PIPE
						liquidMessage( "Beginning RIB output to '" + string( baseShadowName.asChar() ) + "'", messageInfo );
						RiBegin( const_cast< RtToken >( baseShadowName.asChar() ) );
#else
						liqglo_ribFP = fopen( baseShadowName.asChar(), "w" );
						if( liqglo_ribFP ) {
							LIQDEBUGPRINTF( "-> setting pipe option\n" );
							RtInt ribFD( fileno( liqglo_ribFP ) );
							RiOption( "rib", "pipe", &ribFD, RI_NULL );
						}
						else
						{
							liquidMessage( "Error opening RIB -- writing to stdout.\n", messageError );
						}
						liquidMessage( "Beginning RI output directly to renderer", messageInfo );
						RiBegin( RI_NULL );
#endif
						if( worldPrologue() != MS::kSuccess ) 
							break;
						if( liqglo_currentJob.isShadow && liqglo_currentJob.deepShadows && m_outputLightsInDeepShadows ) 
							if( lightBlock() != MS::kSuccess ) 
								break;
						if( coordSysBlock() != MS::kSuccess ) 
							break;
						if( objectBlock() != MS::kSuccess ) 
							break;
						if( worldEpilogue() != MS::kSuccess ) 
							break;
						RiEnd();
#ifdef RENDER_PIPE  
						fclose( liqglo_ribFP );
#endif
						liqglo_ribFP = NULL;

						// mark all other jobs with the same set as done
						vector<structJob>::iterator iterCheck = jobList.begin();
						while ( iterCheck != jobList.end() ) 
						{
							if( iterCheck->shadowObjectSet == liqglo_currentJob.shadowObjectSet &&
								iterCheck->everyFrame == liqglo_currentJob.everyFrame &&
								iterCheck->renderFrame == liqglo_currentJob.renderFrame
								)
								iterCheck->shadowArchiveRibDone = true;
							++iterCheck;
						}

						m_alfShadowRibGen = true;
					}//if( liqglo_currentJob.isShadow && !liqglo_currentJob.shadowArchiveRibDone && !fullShadowRib ) 

#ifndef RENDER_PIPE
					liquidMessage( "Beginning RIB output to '" + string( liqglo_currentJob.ribFileName.asChar() ) + "'", messageInfo );
					RiBegin( const_cast< RtToken >( liqglo_currentJob.ribFileName.asChar() ) );

#ifdef DELIGHT
					LIQDEBUGPRINTF( "-> setting binary option\n" );
					{
						RtString format[1] = {"ascii"};
						if( liqglo_doBinary ) 
							format[0] = "binary";
						RiOption( "rib", "format", ( RtPointer )&format, RI_NULL);
					}
#endif
#else
					liqglo_ribFP = fopen( liqglo_currentJob.ribFileName.asChar(), "w" );
					if( liqglo_ribFP ) 
					{
						RtInt ribFD = fileno( liqglo_ribFP );
						RiOption( ( RtToken )"rib", ( RtToken )"pipe", &ribFD, RI_NULL );
					} 
					else
					{
						liquidMessage( "Error opening RIB -- writing to stdout.\n", messageError );
					}

					liquidMessage( "Beginning RI output directly to renderer", messageInfo );
					RiBegin( RI_NULL );
#endif
					if( liqglo_currentJob.isShadow && !fullShadowRib ) 
					{
						// reference the correct shadow archive
						//
						/* cout <<"  * referencing shadow archive "<<baseShadowName.asChar()<<endl; */
						if( ribPrologue() == MS::kSuccess ) 
						{
							if( framePrologue( scanTime ) != MS::kSuccess ) 
								break;
							//MString realShadowName( liquidSanitizePath( liquidGetRelativePath( liqglo_relativeFileNames, baseShadowName, liqglo_projectDir ) ) );
							RiArchiveRecord( RI_COMMENT, "Read Archive Data:\n" );
							RiReadArchive( const_cast< RtToken >( baseShadowName.asChar() ), NULL, RI_NULL );
							if( frameEpilogue( scanTime ) != MS::kSuccess ) 
								break;
							ribEpilogue();
						}
					} 
					else 
					{
						// full beauty/shadow rib generation
						//
						/* cout <<"  * build full rib"<<endl; */
						if( ribPrologue() == MS::kSuccess ) 
						{
							if( framePrologue( scanTime ) != MS::kSuccess ) 
								break;
							if( worldPrologue() != MS::kSuccess ) 
								break;
							if( !liqglo_currentJob.isShadow || ( liqglo_currentJob.isShadow && liqglo_currentJob.deepShadows && m_outputLightsInDeepShadows) ) 
								if( lightBlock() != MS::kSuccess ) 
									break;
							if( coordSysBlock() != MS::kSuccess ) 
								break;
							if( objectBlock() != MS::kSuccess ) 
								break;
							if( worldEpilogue() != MS::kSuccess ) 
								break;
							if( frameEpilogue( scanTime ) != MS::kSuccess ) 
								break;
							ribEpilogue();
							// output info when done with the rib - Alf
							cout <<"Finished RIB generation "<<liqglo_currentJob.ribFileName.asChar()<<endl;
						}
					}
					RiEnd();
#ifdef RENDER_PIPE
					fclose( liqglo_ribFP );
#endif
					liqglo_ribFP = NULL;
					if( m_showProgress ) 
						printProgress( 3, frameNumbers.size(), frameIndex );
				}//for (; iter != jobList.end(); ++iter ) 

				/*
				if( hashTableInited && htable ) {
				delete htable;
				freeShaders();
				htable = NULL;
				}*/
			}//if( !m_deferredGen ) 

			// set the rib file for the 'view last rib' menu command
			// NOTE: this may be overridden later on in certain code paths
			if( !m_deferredGen ) 
				lastRibName = liqglo_currentJob.ribFileName;
			// now we re-iterate through the job list to write out the alfred file if we are using it
			if( useRenderScript && !m_justRib ) 
			{
				bool alf_textures = false;
				bool alf_shadows = false;
				bool alf_refmaps = false;
				// write out make texture pass
				LIQDEBUGPRINTF( "-> Generating job for MakeTexture pass\n");
				vector<structJob>::iterator iter = txtList.begin();
				if( txtList.size() ) 
				{
					alf_textures = true;
					liqRenderScript::Job textureJob;
					stringstream ts;
					ts << "Textures." << liqglo_lframe;
					textureJob.title = ts.str();

					while ( iter != txtList.end() ) 
					{
						liqRenderScript::Job textureSubtask;
						stringstream ts;
						ts << textureJob.title << " " << iter->imageName.asChar();
						textureSubtask.title = ts.str();
						if( m_deferredGen ) {

						}
						stringstream ss;
						ss << iter->renderName.asChar() << " " << iter->ribFileName.asChar();
						liqRenderScript::Cmd cmd( ss.str(), ( remoteRender && !useNetRman ) );

						if( m_alfredExpand ) 
							cmd.alfredExpand = true;

						cmd.alfredServices = m_alfredServices.asChar();
						cmd.alfredTags     = m_alfredTags.asChar();
						textureSubtask.commands.push_back( cmd );
						textureSubtask.chaserCommand = ( string( "sho \"" ) + liqglo_textureDir.asChar() + " " + iter->imageName.asChar() + "\"" );
						++iter;
						textureJob.childJobs.push_back( textureSubtask );
					}
					frameScriptJob.childJobs.push_back( textureJob );
				}

				// write out shadows
				if( liqglo_doShadows ) 
				{
					LIQDEBUGPRINTF( "-> writing out shadow information to alfred file.\n" );
					vector< structJob >::iterator iter = shadowList.begin();
					if( shadowList.size() ) 
					{
						alf_shadows = true;
						liqRenderScript::Job shadowJob;
						stringstream ts;
						ts << "Shadows." << liqglo_lframe;
						shadowJob.title = ts.str();
						while ( iter != shadowList.end() ) 
						{
							alf_shadows = true;
							liqRenderScript::Job shadowSubtask;
							shadowSubtask.title = iter->name.asChar();
							if( alf_textures ) 
							{
								stringstream ss;
								ss << "Textures." << liqglo_lframe;
								liqRenderScript::Job instanceJob;
								instanceJob.isInstance = true;
								instanceJob.title = ss.str();
								shadowSubtask.childJobs.push_back(instanceJob);
							}
							if( m_deferredGen ) 
							{
								stringstream ss;
								ss << liqglo_sceneName.asChar() << "FrameRIBGEN" << currentBlock;
								liqRenderScript::Job instanceJob;
								instanceJob.isInstance = true;
								instanceJob.title = ss.str();
								shadowSubtask.childJobs.push_back(instanceJob);
							}
							stringstream ss;
							if( useNetRman ) 
							{
#ifdef _WIN32
								ss << framePreCommand.asChar() << " netrender %H -Progress \"" << iter->ribFileName.asChar() << "\"";
#else
								ss << framePreCommand.asChar() << " netrender %H -Progress " << iter->ribFileName.asChar();
#endif
							} else {
#ifdef _WIN32
								ss << framePreCommand.asChar() << " " << frameRenderCommand.asChar() << " \"" << iter->ribFileName.asChar() << "\"";
#else
								ss << framePreCommand.asChar() << " " << frameRenderCommand.asChar() << " " << iter->ribFileName.asChar();
#endif
							}
							liqRenderScript::Cmd cmd(ss.str(), (remoteRender && !useNetRman));
							if( m_alfredExpand ) 
								cmd.alfredExpand = true;

							cmd.alfredServices = m_alfredServices.asChar();
							cmd.alfredTags     = m_alfredTags.asChar();
							shadowSubtask.commands.push_back(cmd);

							if(cleanRib)  
							{
								stringstream ss;
#ifdef _WIN32
								ss << framePreCommand.asChar() << " " << RM_CMD << " \"" << iter->ribFileName.asChar() << "\"";
#else
								ss << framePreCommand.asChar() << " " << RM_CMD << " " << iter->ribFileName.asChar();
#endif

								shadowSubtask.cleanupCommands.push_back( liqRenderScript::Cmd( ss.str(), remoteRender ) );
							}
							shadowSubtask.chaserCommand = ( string( "sho \"" ) + iter->imageName.asChar() + "\"" );
							++iter;
							if( !m_alfShadowRibGen && !fullShadowRib ) 
								m_alfShadowRibGen = true;
							shadowJob.childJobs.push_back( shadowSubtask );
						}
						frameScriptJob.childJobs.push_back( shadowJob );
					}
				}
				LIQDEBUGPRINTF( "-> finished writing out shadow information to render script file.\n" );

				// write out make reflection pass
				if( refList.size() ) 
				{
					LIQDEBUGPRINTF( "-> Generating job for ReflectionMap pass\n" );
					vector<structJob>::iterator iter = refList.begin();

					alf_refmaps = true;
					liqRenderScript::Job reflectJob;
					stringstream ts;
					ts << "Reflections." << liqglo_lframe;
					reflectJob.title = ts.str();

					while ( iter != refList.end() ) 
					{
						liqRenderScript::Job reflectSubtask;
						stringstream ts;
						ts << reflectJob.title << " " << iter->imageName.asChar();
						reflectSubtask.title = ts.str();
						if( m_deferredGen ) {

						}
						if( alf_textures ) 
						{
							stringstream ss;
							ss << "Textures." << liqglo_lframe;
							liqRenderScript::Job instanceJob;
							instanceJob.isInstance = true;
							instanceJob.title = ss.str();
							reflectJob.childJobs.push_back( instanceJob );
						}
						if( alf_shadows ) 
						{
							stringstream ss;
							ss << "Shadows." << liqglo_lframe;
							liqRenderScript::Job instanceJob;
							instanceJob.isInstance = true;
							instanceJob.title = ss.str();
							reflectJob.childJobs.push_back( instanceJob );
						}

						stringstream ss;
						ss << iter->renderName.asChar() << " " << iter->ribFileName.asChar();
						liqRenderScript::Cmd cmd( ss.str(), (remoteRender && !useNetRman) );

						if( m_alfredExpand ) 
							cmd.alfredExpand = true;

						cmd.alfredServices = m_alfredServices.asChar();
						cmd.alfredTags     = m_alfredTags.asChar();
						reflectSubtask.commands.push_back( cmd );
						reflectSubtask.chaserCommand = ( string( "sho \"" ) + liqglo_textureDir.asChar() + " " + iter->imageName.asChar() + "\"" );
						++iter;
						reflectJob.childJobs.push_back( reflectSubtask );
					}
					frameScriptJob.childJobs.push_back( reflectJob );
				}

				LIQDEBUGPRINTF( "-> initiating hero pass information.\n" );
				structJob *frameJob = NULL;
				structJob *shadowPassJob = NULL;
				LIQDEBUGPRINTF( "-> setting hero pass.\n" );
				if( m_outputHeroPass && !m_outputShadowPass ) 
					frameJob = &jobList[jobList.size() - 1];
				else if( m_outputShadowPass && m_outputHeroPass ) 
				{
					frameJob = &jobList[jobList.size() - 1];
					shadowPassJob = &jobList[jobList.size() - 2];
				} 
				else if( m_outputShadowPass && !m_outputHeroPass ) 
					shadowPassJob = &jobList[jobList.size() - 1];

				LIQDEBUGPRINTF( "-> hero pass set.\n" );
				LIQDEBUGPRINTF( "-> writing out pre frame command information to render script file.\n" );
				if( framePreFrameCommand != MString("") ) 
				{
					liqRenderScript::Cmd cmd(framePreFrameCommand.asChar(), (remoteRender && !useNetRman));
					cmd.alfredServices = m_alfredServices.asChar();
					cmd.alfredTags     = m_alfredTags.asChar();
					frameScriptJob.commands.push_back(cmd);
				}

				if( m_outputHeroPass ) 
				{
					stringstream ss;
					MString ribFileName = frameJob->ribFileName;
					if ( m_dirmaps.length() )
					{  
						ribFileName = "\\\"%D(" + ribFileName + ")\\\"";      
						LIQDEBUGPRINTF( "==> Set DirMaps : %s.\n", m_dirmaps.asChar() );
					}
					if( useNetRman ) 
					{
#ifdef _WIN32
						ss << framePreCommand.asChar() << " netrender %H -Progress \"" << ribFileName.asChar() << "\"";
#else
						ss << framePreCommand.asChar() << " netrender %H -Progress " << ribFileName.asChar();
#endif
					} 
					else 
					{
#ifdef _WIN32
						ss << framePreCommand.asChar() << " " << frameRenderCommand.asChar() << " -Progress \"" << ribFileName.asChar() << "\"";
#else
						ss << framePreCommand.asChar() << " " << frameRenderCommand.asChar() << " -Progress " << ribFileName.asChar();
#endif
					}
					liqRenderScript::Cmd cmd(ss.str(), (remoteRender && !useNetRman));
					if( m_alfredExpand ) 
						cmd.alfredExpand = true;

					cmd.alfredServices = m_alfredServices.asChar();
					cmd.alfredTags     = m_alfredTags.asChar();
					frameScriptJob.commands.push_back(cmd);
				}
				LIQDEBUGPRINTF( "-> finished writing out hero information to alfred file.\n" );
				if( m_outputShadowPass ) 
				{
					stringstream ss;
					if( useNetRman ) 
					{
#ifdef _WIN32
						ss << framePreCommand.asChar() << " netrender %H -Progress \"" << shadowPassJob->ribFileName.asChar() << "\"";
#else
						ss << framePreCommand.asChar() << " netrender %H -Progress " << shadowPassJob->ribFileName.asChar();
#endif
					} else {
#ifdef _WIN32
						ss << framePreCommand.asChar() << " " << frameRenderCommand.asChar() << " \"" << shadowPassJob->ribFileName.asChar() << "\"";
#else
						ss << framePreCommand.asChar() << " " << frameRenderCommand.asChar() << " " << shadowPassJob->ribFileName.asChar();
#endif
					}
					liqRenderScript::Cmd cmd(ss.str(), (remoteRender && !useNetRman));
					if( m_alfredExpand ) 
						cmd.alfredExpand = true;

					cmd.alfredServices = m_alfredServices.asChar();
					cmd.alfredTags     = m_alfredTags.asChar();
					frameScriptJob.commands.push_back(cmd);
				}

				if( cleanRib || ( framePostFrameCommand != MString( "" ) ) ) 
				{
					if( cleanRib ) 
					{
						stringstream ss;
						if( m_outputHeroPass  ) 
						{
#ifdef _WIN32
							ss << framePreCommand.asChar() << " " << RM_CMD << " \"" << frameJob->ribFileName.asChar() << "\"";
#else
							ss << framePreCommand.asChar() << " " << RM_CMD << " " << frameJob->ribFileName.asChar();
#endif
						}
						if( m_outputShadowPass) 
						{
#ifdef _WIN32
							ss << framePreCommand.asChar() << " " << RM_CMD << " \"" << shadowPassJob->ribFileName.asChar() << "\"";
#else
							ss << framePreCommand.asChar() << " " << RM_CMD << " " << shadowPassJob->ribFileName.asChar();
#endif
						}
						if( m_alfShadowRibGen ) 
						{
#ifdef _WIN32
							ss << framePreCommand.asChar() << " " << RM_CMD << " \"" << baseShadowName.asChar() << "\"";
#else
							ss << framePreCommand.asChar() << " " << RM_CMD << " " << baseShadowName.asChar();
#endif
						}
						frameScriptJob.cleanupCommands.push_back(liqRenderScript::Cmd(ss.str(), remoteRender));
					}
					if( framePostFrameCommand != MString("") ) 
					{
						liqRenderScript::Cmd cmd(framePostFrameCommand.asChar(), (remoteRender && !useNetRman));
						frameScriptJob.cleanupCommands.push_back(cmd);
					}
				}
				if( m_outputHeroPass ) 
					frameScriptJob.chaserCommand = (string( "sho \"" ) + frameJob->imageName.asChar() + "\"" );
				if( m_outputShadowPass ) 
					frameScriptJob.chaserCommand = (string( "sho \"" ) + shadowPassJob->imageName.asChar() + "\"" );
				if( m_outputShadowPass && !m_outputHeroPass ) 
					lastRibName = liquidGetRelativePath( liqglo_relativeFileNames, shadowPassJob->ribFileName, liqglo_projectDir );
				else 
					lastRibName = liquidGetRelativePath( liqglo_relativeFileNames, frameJob->ribFileName, liqglo_projectDir );
			}
			jobScript.addJob( frameScriptJob );
			if( ( ribStatus != kRibOK ) && !m_deferredGen ) 
				break;
		} // frame for-loop

		if( useRenderScript ) 
		{
			if( m_preJobCommand != MString( "" ) ) {
				liqRenderScript::Job preJobInstance;
				preJobInstance.title = "liquid pre-job";
				preJobInstance.isInstance = true;
				jobScript.addLeafDependency( preJobInstance );
			}
			// clean up the alfred file in the future
			if( !m_justRib ) 
			{
				if( m_deferredGen ) 
				{
					stringstream ss;
					ss << RM_CMD << " " << tempDefname.asChar();
					jobScript.cleanupCommands.push_back( liqRenderScript::Cmd( ss.str(), remoteRender ) );
				}
				if( cleanRenderScript ) 
				{
					stringstream ss;
					ss << RM_CMD << " " << renderScriptName.asChar();
					jobScript.cleanupCommands.push_back( liqRenderScript::Cmd( ss.str(), remoteRender ) );
				}
				if( m_postJobCommand != MString("") ) 
					jobScript.cleanupCommands.push_back( liqRenderScript::Cmd(m_postJobCommand.asChar(), (remoteRender && !useNetRman) ) );
			}
			if( m_renderScriptFormat == ALFRED ) 
				jobScript.writeALF( liquidGetRelativePath( liqglo_relativeFileNames, renderScriptName, liqglo_projectDir ).asChar() );
			if( m_renderScriptFormat == XML ) 
				jobScript.writeXML( liquidGetRelativePath( liqglo_relativeFileNames, renderScriptName, liqglo_projectDir ).asChar() );
		}
		LIQDEBUGPRINTF( "-> ending escape handler.\n" );
		m_escHandler.endComputation();

		if( !m_deferredGen ) 
			liquidMessage( "Finished creating RIB", messageInfo );
		LIQDEBUGPRINTF( "-> clearing job list.\n" );
		jobList.clear();
		jobScript.clear();

		// set the attributes on the liquidGlobals for the last rib file and last alfred script name
		LIQDEBUGPRINTF( "-> setting lastAlfredScript and lastRibFile.\n" );
		MGlobal::executeCommand("if(!attributeExists(\"lastRenderScript\",\"liquidGlobals\")) { addAttr -ln \"lastRenderScript\" -dt \"string\" liquidGlobals; }");
		MFnDependencyNode rGlobalNode( rGlobalObj );
		MPlug nPlug;
		nPlug = rGlobalNode.findPlug( "lastRenderScript" );
		nPlug.setValue( renderScriptName );
		nPlug = rGlobalNode.findPlug( "lastRibFile" );
		nPlug.setValue( lastRibName );
		LIQDEBUGPRINTF( "-> spawning command.\n" );
		if( launchRender ) 
		{
			if( useRenderScript ) 
			{
				if( m_renderScriptCommand == "" ) 
					m_renderScriptCommand = "alfred";

				if( m_renderScriptFormat == NONE ) 
					liquidMessage( "No render script format specified to Liquid, and direct render execution not selected.", messageWarning );

#ifdef _WIN32
				// Moritz: Added quotes to render script name as it may contain spaces in bloody Windoze
				// Note: also adding quotes to the path (aka project dir) breaks ShellExecute() -- cost me one hour to trace this!!!
				// Bloody, damn, asinine Windoze!!!
				liqProcessLauncher::execute( m_renderScriptCommand, "\"" + renderScriptName + "\"", liqglo_projectDir, false );
#else
				liqProcessLauncher::execute( m_renderScriptCommand, renderScriptName, liqglo_projectDir, false );
#endif
				if( m_renderView ) 
				{
					MString local = (m_renderViewLocal)? "1":"0";
					stringstream tmp;
					tmp << m_renderViewTimeOut;
					//=============
					cout << ">> m_renderView: m_renderViewTimeOut = " << tmp.str().c_str() << endl;
					MString timeout( tmp.str().c_str() );
					MString displayCmd = "liquidRenderView -c " + renderCamera + " -l " + local + " -port " + m_renderViewPort + " -timeout " + timeout ;
					if( m_renderViewCrop ) 
						displayCmd = displayCmd + " -doRegion";
					displayCmd = displayCmd + ";liquidSaveRenderViewImage();";
					//============= 
					cout << ">> m_renderView: m_displayCmd = " <<  displayCmd.asChar() << endl;
					MGlobal::executeCommand( displayCmd );
				}
			} 
			else 
			{
				// launch renders directly
				liquidMessage( string(), messageInfo ); // emit a '\n'
				int exitstat = 0;

				// write out make texture pass
				vector<structJob>::iterator iter = txtList.begin();
				while ( iter != txtList.end() ) 
				{
					liquidMessage( "Making textures '" + string( iter->imageName.asChar() ) + "'", messageInfo );
					cout << "[!] Making textures '" << iter->imageName.asChar() << "'" << endl;
#ifdef _WIN32
					liqProcessLauncher::execute( iter->renderName, " -progress \"" + iter->ribFileName + "\"", liqglo_projectDir, true );
#else
					liqProcessLauncher::execute( iter->renderName, " -progress " + iter->ribFileName, liqglo_projectDir, true );
#endif
					++iter;
				}
				if( liqglo_doShadows ) 
				{
					liquidMessage( "Rendering shadow maps... ", messageInfo );
					cout << endl << "[!] Rendering shadow maps... " << endl;
					vector<structJob>::iterator iter = shadowList.begin();
					while ( iter != shadowList.end() ) 
					{
						if( iter->skip ) 
						{
							cout <<"    - skipping '" << iter->ribFileName.asChar() << "'" << endl;
							liquidMessage( "    - skipping '" + string( iter->ribFileName.asChar() ) + "'", messageInfo );
							++iter;
							continue;
						}
						cout << "    + '" << iter->ribFileName.asChar() << "'" << endl;
						liquidMessage( "    + '" + string( iter->ribFileName.asChar() ) + "'", messageInfo );
#ifdef _WIN32
						if( !liqProcessLauncher::execute( liquidRenderer.renderCommand, liquidRenderer.renderCmdFlags + " \"" + iter->ribFileName + "\"", liqglo_projectDir, true ) )
#else
						if( !liqProcessLauncher::execute( liquidRenderer.renderCommand, liquidRenderer.renderCmdFlags + " " + iter->ribFileName, liqglo_projectDir, true ) )
#endif
							break;
						++iter;
					} // while ( iter != shadowList.end() )
				}
				if( !exitstat ) 
				{
					liquidMessage( "Rendering hero pass... ", messageInfo );
					cout << "[!] Rendering hero pass..." << endl;
					if( liqglo_currentJob.skip ) 
					{
						cout << "    - skipping '" << liqglo_currentJob.ribFileName.asChar() << "'" << endl;
						liquidMessage( "    - skipping '" + string( liqglo_currentJob.ribFileName.asChar() ) + "'", messageInfo );
					} 
					else 
					{
						cout << "    + '" << liqglo_currentJob.ribFileName.asChar() << "'" << endl;
						liquidMessage( "    + '" + string( liqglo_currentJob.ribFileName.asChar() ) + "'", messageInfo );

#ifdef _WIN32
						liqProcessLauncher::execute( liquidRenderer.renderCommand, liquidRenderer.renderCmdFlags + " \"" + liqglo_currentJob.ribFileName + "\"", "\"" + liqglo_projectDir + "\"", false );
#else
						liqProcessLauncher::execute( liquidRenderer.renderCommand, liquidRenderer.renderCmdFlags + " " + liqglo_currentJob.ribFileName, liqglo_projectDir, false );
#endif
						/*  philippe: here we launch the liquidRenderView command which will listen to the liqmaya display driver
						to display buckets in the renderview.
						*/
						if( m_renderView ) 
						{
							MString local = (m_renderViewLocal)? "1":"0";
							stringstream tmp;
							tmp << m_renderViewTimeOut;
							//=============
							cout << ">> m_renderView: m_renderViewTimeOut = " << tmp.str().c_str() << endl;
							MString timeout( tmp.str().c_str() );
							MString displayCmd = "liquidRenderView -c " + renderCamera + " -l " + local + " -port " + m_renderViewPort + " -timeout " + timeout ;
							if( m_renderViewCrop ) 
								displayCmd = displayCmd + " -doRegion";
							displayCmd = displayCmd + ";liquidSaveRenderViewImage();";
							//============= 
							cout << ">> m_renderView: m_displayCmd = " <<  displayCmd.asChar() << endl;
							MGlobal::executeCommand( displayCmd );
						}
					}
				}//if( !exitstat ) 
			}//if( useRenderScript ) else
		} // if( launchRender )

		// return to the frame we were at before we ran the animation
		LIQDEBUGPRINTF( "-> setting frame to current frame.\n" );
		MGlobal::viewFrame (originalTime);

		if( originalLayer != "" ) 
		{
			MString cmd;
			cmd = "if( `editRenderLayerGlobals -q -currentRenderLayer` != \"" + originalLayer + "\" ) editRenderLayerGlobals -currentRenderLayer \"" + originalLayer + "\";";
			if(  MGlobal::executeCommand( cmd, false, false ) == MS::kFailure ) 
			{
				MString err;
				err = "Liquid : could not switch back to render layer \"" + originalLayer + "\" !";
				throw err;
			}
		}

		return ( (ribStatus == kRibOK || m_deferredGen) ? MS::kSuccess : MS::kFailure);

	} 
	catch ( MString errorMessage ) 
	{
		liquidMessage( errorMessage.asChar(), messageError );
		/*if( htable && hashTableInited ) delete htable;
		freeShaders();*/
		m_escHandler.endComputation();
		return MS::kFailure;
	} 
	catch ( ... ) 
	{
		liquidMessage( "Unknown exception thrown", messageError );
		/*if( htable && hashTableInited ) delete htable;
		freeShaders();*/
		m_escHandler.endComputation();
		return MS::kFailure;
	}
}

/**
* Calculate the port field of view for the camera.
*/
