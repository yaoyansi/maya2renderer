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


#include <liqRibTranslator.h>

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

#ifdef _WIN32
#include <process.h>
#include <io.h>
#include <direct.h>
#else
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#endif
#include <time.h>
#include <algorithm>
#include <sstream>

#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/case_conv.hpp>

// Renderman Headers
//extern "C" {
#include "ri_interface.h"
//}

#ifdef _WIN32
#  define RM_CMD "cmd.exe /c del"
#else
#  define RM_CMD "/bin/rm"
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
#include <maya/MItDependencyNodes.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MDagPathArray.h>
// Liquid headers
#include <liquid.h>
#include <liqRibHT.h>
#include <liqRenderer.h>
#include <liqRibLightData.h>
#include <liqGlobalHelpers.h>
#include <liqProcessLauncher.h>
#include <liqCustomNode.h>
#include <liqShaderFactory.h>
#include <liqExpression.h>
#include <liqRenderScript.h>
#include <liqGlobalVariable.h>
#include <liqJobScriptMgr.h>
#include <liqFrameScriptMgr.h>
#include <liqLightMgr.h>
#include <liqLocatorMgr.h>
#include <liqShadowRibWriterMgr.h>
#include <liqHeroRibWriterMgr.h>

using namespace boost;
using namespace std;

typedef int RtError;



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

liqRibTranslator* liqRibTranslator::mInstance = NULL;

/**
* This method actually does the renderman output.
*/
MStatus liqRibTranslator::_doItNew( const MArgList& args , const MString& originalLayer )
{
	MStatus status;
#if (Refactoring == 0)
	MString lastRibName;
#endif
	//bool hashTableInited = false;

	if( !liqglo.liquidBin && !liqglo.m_deferredGen ) 
		liquidMessage( "Creating RIB <Press ESC To Cancel> ...", messageInfo );

	// Remember the frame the scene was at so we can restore it later.
	originalTime = MAnimControl::currentTime();

	// Set the frames-per-second global (we'll need this for
	// streak particles)
	//
	MTime oneSecond( 1, MTime::kSeconds );
	liqglo.liqglo_FPS = oneSecond.as( MTime::uiUnit() );

	// append the progress flag for render job feedback
	if( useRenderScript ) 
		if( ( m_renderCommand == MString( "render" ) ) || ( m_renderCommand == MString( "prman" ) ) || ( m_renderCommand == MString( "renderdl" ) ) ) 
			m_renderCommand = m_renderCommand + " -Progress";

	// check to see if the output camera, if specified, is available
	if( liqglo.liquidBin && ( renderCamera == "" ) ) 
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
	// 	MString alfredCleanUpCommand;// not used. [9/15/2010 yys]
	// 	if( remoteRender ) 
	// 		alfredCleanUpCommand = MString( "RemoteCmd" );
	// 	else 
	// 		alfredCleanUpCommand = MString( "Cmd" );

	// 	MString alfredRemoteTagsAndServices;// not used. [9/15/2010 yys]
	// 	if( remoteRender || useNetRman ) 
	// 	{
	// 		alfredRemoteTagsAndServices  = MString( "-service { " );
	// 		alfredRemoteTagsAndServices += m_alfredServices.asChar();
	// 		alfredRemoteTagsAndServices += MString( " } -tags { " );
	// 		alfredRemoteTagsAndServices += m_alfredTags.asChar();
	// 		alfredRemoteTagsAndServices += MString( " } " );
	// 	}
	// A seperate one for cleanup as it doesn't need a tag!
	// 	MString alfredCleanupRemoteTagsAndServices;// not used. [9/15/2010 yys]
	// 	if( remoteRender || useNetRman ) 
	// 	{
	// 		alfredCleanupRemoteTagsAndServices  = MString( "-service { " );
	// 		alfredCleanupRemoteTagsAndServices += m_alfredServices.asChar();
	// 		alfredCleanupRemoteTagsAndServices += MString( " } " );
	// 	}

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
		liqglo.tempDefname    = generateTempMayaSceneName();

		if( liqglo.m_deferredGen ) 
		{
			MString currentFileType = MFileIO::fileType();
			MFileIO::exportAll( liqglo.tempDefname, currentFileType.asChar() );
		}

		if( !liqglo.m_deferredGen && m_justRib ) 
			useRenderScript = false;

		liqRenderScript jobScript;
		// 		liqRenderScript::Job preJobInstance;
		// 		preJobInstance.title = "liquid pre-job";
		// 		preJobInstance.isInstance = true;
		tJobScriptMgr jobScriptMgr(jobScript);

		if( useRenderScript ) 
		{
			if( renderJobName == "" ) 
				renderJobName = liqglo.liqglo_sceneName;

			jobScriptMgr.setCommonParameters(
				renderJobName.asChar(), liqglo.useNetRman, m_minCPU, m_maxCPU, liqglo.m_dirmaps 
			);
			if( m_preJobCommand != MString( "" ) ) 
			{
				jobScriptMgr.addJob("liquid pre-job", 
					m_preJobCommand.asChar(), liqglo.remoteRender && !liqglo.useNetRman);
			}
		}
		// build the frame array
		//
		if( m_renderView ) 
		{
			// if we are in renderView mode,
			// just ignore the animation range
			// and render the current frame.
			liqglo.frameNumbers.clear();
			liqglo.frameNumbers.push_back( ( int ) originalTime.as( MTime::uiUnit() ) );
		}
		//
		// start looping through the frames  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		//
		liquidMessage( "Starting to loop through frames", messageInfo );


		unsigned frameIndex( 0 );
		for ( ; frameIndex < liqglo.frameNumbers.size(); frameIndex++ ) 
		{
			int currentBlock( 0 );
			const MString framePreCommand(parseString( liqglo.m_preCommand, false));
			const MString frameRibgenCommand(parseString( m_ribgenCommand, false ));
			const MString frameRenderCommand( parseString( liqglo.liquidRenderer.renderCommand + " " + liqglo.liquidRenderer.renderCmdFlags, false ));
			const MString framePreFrameCommand(parseString( m_preFrameCommand, false ));
			const MString framePostFrameCommand(parseString( m_postFrameCommand, false ));

			liqRenderScript::Job frameScriptJob;
			tFrameScriptJobMgr frameScriptJobMgr(frameScriptJob);

			stringstream titleStream;
			titleStream << liqglo.liqglo_sceneName.asChar() << "Frame" << liqglo.liqglo_lframe;
 			frameScriptJobMgr.setCommonParameters( titleStream.str() );

			if( useRenderScript ) 
			{
				if( liqglo.m_deferredGen ) 
				{
					if( ( frameIndex % liqglo.m_deferredBlockSize ) == 0 ) 
					{
						if( liqglo.m_deferredBlockSize == 1 ) 
							currentBlock = liqglo.liqglo_lframe;
						else 
							currentBlock++;

						jobScriptMgr.addDefferedJob(currentBlock, frameIndex,
							framePreCommand, frameRibgenCommand
						);
					}
				}//if( m_deferredGen )
				if( !m_justRib ) 
				{
					if( liqglo.m_deferredGen ) 
					{
						stringstream ss;
						ss << liqglo.liqglo_sceneName.asChar() << "FrameRIBGEN" << currentBlock;
						frameScriptJobMgr.addInstanceJob(true, ss.str() );
					}
				}
			}//if( useRenderScript ) 
			///////////////////////////////////////////////////
			TempControlBreak tcb = 
				processOneFrame(frameIndex, liqglo);
			PROCESS_TEMP_CONTROL_BREAK_CONTINUE_RETURN(tcb)
			///////////////////////////////////////////////////
			// now we re-iterate through the job list to write out the alfred file if we are using it
			if( useRenderScript && !m_justRib ) 
			{
				bool alf_textures = false;
				bool alf_shadows = false;
				bool alf_refmaps = false;

				// write out make texture pass
				LIQDEBUGPRINTF( "-> Generating job for MakeTexture pass\n");
				frameScriptJobMgr.makeTexture(txtList, 
					alf_textures, alf_shadows, alf_refmaps);

				// write out shadows
				if( liqglo.liqglo_doShadows ) 
				{
					LIQDEBUGPRINTF( "-> writing out shadow information to alfred file.\n" );
					frameScriptJobMgr.makeShadow(shadowList, 
						alf_textures, alf_shadows, alf_refmaps, currentBlock);

				}//if( liqglo__.liqglo_doShadows ) 
				LIQDEBUGPRINTF( "-> finished writing out shadow information to render script file.\n" );

				// write out make reflection pass
				frameScriptJobMgr.makeReflection(refList,
					alf_textures, alf_shadows, alf_refmaps
				);

				LIQDEBUGPRINTF( "-> initiating hero pass information.\n" );
				structJob *frameJob = NULL;
				structJob *shadowPassJob = NULL;
				LIQDEBUGPRINTF( "-> setting hero pass.\n" );
				if( m_outputHeroPass && !m_outputShadowPass ){
					frameJob = &jobList[jobList.size() - 1];
				}
				else if( m_outputShadowPass && m_outputHeroPass ) 
				{
					frameJob = &jobList[jobList.size() - 1];
					shadowPassJob = &jobList[jobList.size() - 2];
				} 
				else if( m_outputShadowPass && !m_outputHeroPass ){
					shadowPassJob = &jobList[jobList.size() - 1];
				}

				LIQDEBUGPRINTF( "-> hero pass set.\n" );
				LIQDEBUGPRINTF( "-> writing out pre frame command information to render script file.\n" );
				frameScriptJobMgr.try_addPreFrameCommand(framePreFrameCommand.asChar());


				if( m_outputHeroPass ) 
				{
					frameScriptJobMgr.addHeroPass(frameJob->ribFileName, framePreCommand, frameRenderCommand);
				}//if( m_outputHeroPass ) 
				LIQDEBUGPRINTF( "-> finished writing out hero information to alfred file.\n" );
				if( m_outputShadowPass ) 
				{
					frameScriptJobMgr.addShadowPass(shadowPassJob->ribFileName, framePreCommand, frameRenderCommand);
				}//if( m_outputShadowPass )

//				if( liqglo.cleanRib || ( framePostFrameCommand != MString( "" ) ) ) 
//				{
				if( liqglo.cleanRib ) 
				{
					if( m_outputHeroPass  ) 
					{
						frameScriptJobMgr.cleanHeroPass(framePreCommand, frameJob->ribFileName);
					}
					if( m_outputShadowPass) 
					{
						frameScriptJobMgr.cleanShadowPass(framePreCommand, shadowPassJob->ribFileName);
					}
					if( liqglo.m_alfShadowRibGen ) 
					{
						MString     baseShadowName(getBaseShadowName(liqglo.liqglo_currentJob));
						frameScriptJobMgr.cleanShadowRibGen(framePreCommand, baseShadowName);
					}
				}
				// try to add post frame command
				frameScriptJobMgr.try_addPostFrameCommand(framePostFrameCommand);

				//}//if( cleanRib || ( framePostFrameCommand != MString( "" ) ) ) 
				if( m_outputHeroPass ){
					frameScriptJobMgr.viewHeroPassImage(frameJob->imageName);
				}
				if( m_outputShadowPass ){
					frameScriptJobMgr.viewShadowPassImage(shadowPassJob->imageName);
				}
#if (Refactoring == 0)
				if( m_outputShadowPass && !m_outputHeroPass ) 
					lastRibName = liquidGetRelativePath( liqglo__.liqglo_relativeFileNames, shadowPassJob->ribFileName, liqglo__.liqglo_projectDir );
				else 
					lastRibName = liquidGetRelativePath( liqglo__.liqglo_relativeFileNames, frameJob->ribFileName, liqglo__.liqglo_projectDir );
#endif		
			}//if( useRenderScript && !m_justRib ) 

			jobScript.addJob( frameScriptJob );


			if( ( ribStatus != kRibOK ) && !liqglo.m_deferredGen ) 
				break;

		} // frame for-loop

		if( useRenderScript ) 
		{
			if( m_preJobCommand != MString( "" ) ) 
			{
				liqRenderScript::Job preJobInstance;
				preJobInstance.title = "liquid pre-job";
				preJobInstance.isInstance = true;
				jobScript.addLeafDependency( preJobInstance );
			}
			// clean up the alfred file in the future
			if( !m_justRib ) 
			{
				if( liqglo.m_deferredGen ) 
				{
					jobScriptMgr.cleanupDefferedJob();
				}
				if( cleanRenderScript ) 
				{
					jobScriptMgr.cleanupRenderScript(renderScriptName);
				}
				if( m_postJobCommand != MString("") )
				{
					jobScriptMgr.cleanupPostJob(m_postJobCommand);
				}
			}
			jobScriptMgr.writeRenderScript(m_renderScriptFormat, renderScriptName);

		}
		LIQDEBUGPRINTF( "-> ending escape handler.\n" );
		m_escHandler.endComputation();

		if( !liqglo.m_deferredGen ) 
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
#if (Refactoring == 0)
		nPlug = rGlobalNode.findPlug( "lastRibFile" );
		nPlug.setValue( lastRibName );
#endif
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
				liqProcessLauncher::execute( m_renderScriptCommand, "\"" + renderScriptName + "\"", liqglo.liqglo_projectDir, false );
#else
				liqProcessLauncher::execute( m_renderScriptCommand, renderScriptName, liqglo.liqglo_projectDir, false );
#endif
				if( m_renderView ) 
				{
					doRenderView();
				}
			} 
			else 
			{
				// launch renders directly
				liquidMessage( string(), messageInfo ); // emit a '\n'
				//int exitstat = 0;

				// write out make texture pass
				doTextures();

				if( liqglo.liqglo_doShadows ) 
				{
					doShadows();
				}

				//if( !exitstat ){
				liquidMessage( "Rendering hero pass... ", messageInfo );
				cout << "[!] Rendering hero pass..." << endl;
				if( liqglo.liqglo_currentJob.skip ) 
				{
					cout << "    - skipping '" << liqglo.liqglo_currentJob.ribFileName.asChar() << "'" << endl;
					liquidMessage( "    - skipping '" + string( liqglo.liqglo_currentJob.ribFileName.asChar() ) + "'", messageInfo );
				} 
				else 
				{
					cout << "    + '" << liqglo.liqglo_currentJob.ribFileName.asChar() << "'" << endl;
					liquidMessage( "    + '" + string( liqglo.liqglo_currentJob.ribFileName.asChar() ) + "'", messageInfo );

#ifdef _WIN32
					liqProcessLauncher::execute( liqglo.liquidRenderer.renderCommand, " "+liqglo.liqglo_rifParams+" "+ liqglo.liquidRenderer.renderCmdFlags + " \"" + liqglo.liqglo_currentJob.ribFileName + "\"", "\"" + liqglo.liqglo_projectDir + "\"", false );
#else
					liqProcessLauncher::execute( liqglo.liquidRenderer.renderCommand, " "+liqglo.liqglo_rifParams+" "+ liqglo.liquidRenderer.renderCmdFlags + " " + liqglo.liqglo_currentJob.ribFileName, liqglo.liqglo_projectDir, false );
#endif
					/*  philippe: here we launch the liquidRenderView command which will listen to the liqmaya display driver
					to display buckets in the renderview.
					*/
					if( m_renderView ) 
					{
						doRenderView();
					}
				}
				//}//if( !exitstat )
 
			}//if( useRenderScript ) else
		} // if( launchRender )

		postActions(originalLayer);

		return ( (ribStatus == kRibOK || liqglo.m_deferredGen) ? MS::kSuccess : MS::kFailure);

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
//
void liqRibTranslator::calaculateSamplingTime(const long scanTime__)
{
	float sampleinc( ( liqglo.liqglo_shutterTime * m_blurTime ) / ( liqglo.liqglo_motionSamples - 1 ) );
	for ( unsigned msampleOn( 0 ); msampleOn < liqglo.liqglo_motionSamples; msampleOn++ ) 
	{
		float subframe;
		switch( shutterConfig ) 
		{
		case OPEN_ON_FRAME:
		default:
			subframe = scanTime__ + ( msampleOn * sampleinc );
			break;
		case CENTER_ON_FRAME:
			subframe = ( scanTime__ - ( liqglo.liqglo_shutterTime * m_blurTime * 0.5 ) ) + msampleOn * sampleinc;
			break;
		case CENTER_BETWEEN_FRAMES:
			subframe = scanTime__ + ( 0.5 * ( 1 - ( liqglo.liqglo_shutterTime * m_blurTime ) ) ) + ( msampleOn * sampleinc );
			break;
		case CLOSE_ON_NEXT_FRAME:
			subframe = scanTime__ + ( 1 - ( liqglo.liqglo_shutterTime * m_blurTime ) ) + ( msampleOn * sampleinc );
			break;
		}
		liqglo.liqglo_sampleTimes[ msampleOn ] = subframe;
		liqglo.liqglo_sampleTimesOffsets[ msampleOn ] = msampleOn * sampleinc;
	}
}

/**
* Set up data for the current job.
*/
MStatus liqRibTranslator::buildJobs__()
{
	LIQDEBUGPRINTF( "-> beginning to build job list\n" );
	MStatus returnStatus = MS::kSuccess;
	MStatus status;
	MObject cameraNode;
	//MDagPath lightPath;

	jobList.clear();
	shadowList.clear();
	txtList.clear();

//	structJob thisJob;

	MItDependencyNodes dependencyNodesIter(MFn::kDependencyNode, &returnStatus);
	if(returnStatus==MS::kSuccess)
	{
		//char *currentName = NULL;
		for(; !dependencyNodesIter.isDone(); dependencyNodesIter.next())
		{
			MFnDependencyNode dependencyNodeFn(dependencyNodesIter.thisNode());
			if( dependencyNodeFn.typeName()=="liquidSurface"
				|| dependencyNodeFn.typeName()=="liquidDisplacement"
				|| dependencyNodeFn.typeName()=="liquidVolume"
				|| dependencyNodeFn.typeName()=="liquidLight"
				)
			{
				MString name(dependencyNodeFn.name());
				liqShader currentShader(dependencyNodesIter.thisNode());
				scanExpressions(currentShader);
			}
		}
	}
	// what we do here is make all of the lights with depth shadows turned on into
	// cameras and add them to the renderable camera list *before* the main camera
	// so all the automatic depth map shadows are complete before the main pass

	if( liqglo.liqglo_doShadows ) 
	{
		returnStatus = buildShadowJobs__();
	} // liqglo_doShadows

	// Determine which cameras to render
	// it will either traverse the dag and find all the renderable cameras or
	// grab the current view and render that as a camera - both get added to the
	// end of the renderable camera array
	MDagPath cameraPath;
	if( renderCamera != "" ) 
	{
		MSelectionList camList;
		camList.add( renderCamera );
		camList.getDagPath( 0, cameraPath );
		MFnCamera fnCameraNode( cameraPath );
	} 
	else 
	{
		LIQDEBUGPRINTF( "-> getting current view\n" );
		m_activeView.getCamera( cameraPath );
	}

	structJob thisJob;
	MFnCamera fnCameraNode( cameraPath );
	thisJob.renderFrame   = liqglo.liqglo_lframe;
	thisJob.everyFrame    = true;
	thisJob.isPoint       = false;
	thisJob.path          = cameraPath;
	thisJob.name          = fnCameraNode.name();
	thisJob.isShadow      = false;
	thisJob.skip          = false;
	//for shadow pass
	thisJob.name         += "SHADOWPASS";
	thisJob.isShadowPass  = true;
	if( m_outputShadowPass ) 
		jobList.push_back( thisJob );
	//for hero pass
	thisJob.name          = fnCameraNode.name();
	thisJob.isShadowPass  = false;
	if( m_outputHeroPass ) 
		jobList.push_back( thisJob );

	liqglo.liqglo_shutterTime    = fnCameraNode.shutterAngle() * 0.5 / M_PI;


	// If we didn't find a renderable camera then give up
	if( jobList.size() == 0 ) 
	{
		MString cError("No Renderable Camera Found!\n");
		throw( cError );
		return MS::kFailure;
	}

	// step through the jobs and setup their names
	vector<structJob>::iterator iter = jobList.begin();
	while ( iter != jobList.end() )
	{
		LIQ_CHECK_CANCEL_REQUEST;
		thisJob = *iter;

		MString frameFileName;
		if( thisJob.isShadow )
			frameFileName = generateFileName( ( fileGenMode )fgm_shadow_rib, thisJob );
		else
			frameFileName = generateFileName( ( fileGenMode )fgm_beauty_rib, thisJob );
		iter->ribFileName = frameFileName;

		// set the skip flag for the job
		iter->skip   = false;
		thisJob.skip = false;

		if( thisJob.isShadow )
		{
			if( !liqglo.liqglo_doShadows )
			{
				// shadow generation disabled
				iter->skip   = true;
				thisJob.skip = true;
			}
			else if( !thisJob.everyFrame && ( liqglo.liqglo_noSingleFrameShadows || liqglo.liqglo_lframe > liqglo.frameNumbers[ 0 ] && thisJob.renderFrame != liqglo.liqglo_lframe ) )
			{
				// noSingleFrameShadows or rendering past the first frame of the sequence
				iter->skip   = true;
				thisJob.skip = true;
			}
			else if( thisJob.everyFrame && liqglo.liqglo_singleFrameShadowsOnly )
			{
				// singleFrameShadowsOnly on regular shadows
				iter->skip   = true;
				thisJob.skip = true;
			}
		}
		else if( liqglo.liqglo_singleFrameShadowsOnly )
		{
			// singleFrameShadowsOnly on hero pass
			iter->skip   = true;
			thisJob.skip = true;
		}

		MString outFileFmtString;

		if( thisJob.isShadow ) 
		{
			MString varVal;
			MString userShadowName;
			MFnDagNode lightNode( thisJob.path );

			if( liquidGetPlugValue( lightNode, "liquidShadowName", varVal, status ) == MS::kSuccess ) 
				userShadowName = parseString( varVal, false );
			//outFileFmtString = liqglo_textureDir;

			MString outName;
			if( userShadowName.length() ) 
				outName = userShadowName;
			else 
				outName = generateFileName( ( fileGenMode )fgm_shadow_tex, thisJob );

			iter->imageName = outName;
			thisJob = *iter;
			if( thisJob.isShadow ) 
				shadowList.push_back( thisJob );
		} 
		else 
		{
			MString outName;
			outName = generateFileName( ( fileGenMode )fgm_image, thisJob );
			iter->imageName = outName;
		}
		++iter;
	}//while ( iter != jobList.end() )

	// sort the shadow jobs to put the reference frames first
#ifndef _WIN32
	sort( jobList.begin(), jobList.end(), renderFrameSort );
	sort( shadowList.begin(), shadowList.end(), renderFrameSort );
	sort( txtList.begin(), txtList.end(), renderFrameSort );
#else
	sort( jobList.begin(), jobList.end(), renderFrameSort );
	sort( shadowList.begin(), shadowList.end(), renderFrameSort );
	sort( txtList.begin(), txtList.end(), renderFrameSort );
#endif
	ribStatus = kRibBegin;
	return MS::kSuccess;
}



//
TempControlBreak liqRibTranslator::processOneFrame(
	const unsigned int frameIndex,
	struct liqGlobalVariable &liqglo__
	)
{	

	liqShaderFactory::instance().clearShaders();

	liqglo__.liqglo_lframe = liqglo.frameNumbers[ frameIndex ];

	if( m_showProgress ) 
		printProgress( 1, liqglo.frameNumbers.size(), frameIndex );



	liqglo__.m_alfShadowRibGen = false;
	liqglo__.liqglo_preReadArchive.clear();
	liqglo__.liqglo_preRibBox.clear();
	liqglo__.liqglo_preReadArchiveShadow.clear();
	liqglo__.liqglo_preRibBoxShadow.clear();

	// make sure all the global strings are parsed for this frame
	const MString framePreCommand(parseString( liqglo.m_preCommand, false));
	const MString frameRibgenCommand(parseString( m_ribgenCommand, false ));
	const MString frameRenderCommand( parseString( liqglo__.liquidRenderer.renderCommand + " " + liqglo__.liquidRenderer.renderCmdFlags, false ));
	const MString framePreFrameCommand(parseString( m_preFrameCommand, false ));
	const MString framePostFrameCommand(parseString( m_postFrameCommand, false ));


	//***************************************************************
	LIQDEBUGPRINTF( "-> building jobs\n" );
	// Hmmmmmm not really clean ....
	if( buildJobs__() != MS::kSuccess ) 
		return TCB_Break;//break;
	//***************************************************************

	if( !liqglo.m_deferredGen ) 
	{
		if( m_showProgress ) 
			printProgress( 2, liqglo.frameNumbers.size(), frameIndex );

		long lastScannedFrame = -100000;
		long scanTime = liqglo__.liqglo_lframe;
		//hashTableInited = false;
		//
		// start iterating through the job list   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
		//
		if( jobList.size() == 0 ) 
		{
			liquidMessage( "Nothing to render!", messageWarning );
			return TCB_MS_Success;//return MS::kSuccess;
		}
		//cout <<"Job iteration start -------------------------------------"<<endl;
		//cout <<"    nsfs:"<<liqglo_noSingleFrameShadows<<"  sfso:"<<liqglo_singleFrameShadowsOnly<<endl;
		vector< structJob >::iterator iter( jobList.begin() );
		for (; iter != jobList.end(); ++iter ) 
		{
			m_currentMatteMode = false;
			liqglo__.liqglo_currentJob = *iter;

			if( liqglo__.liqglo_currentJob.skip ) 
				continue;

			//cout <<">> outputing job ["<<liqglo_lframe<<"] ->"<<liqglo_currentJob.name.asChar()<<" -> "<<liqglo_currentJob.imageName.asChar()<<endl;
			// set the scan time based on the job's render frame
			//
			scanTime = liqglo__.liqglo_currentJob.renderFrame;
			// if we changed the frame to calculate a shadow at a different time,
			// we need to rescan the scene, otherwise not.
			//
			if( lastScannedFrame != scanTime ) 
			{
				LIQDEBUGPRINTF( "Scanning at time: %u \n", scanTime );

				htable = shared_ptr< liqRibHT >( new liqRibHT() );
				//hashTableInited = true;
				LIQDEBUGPRINTF( "Created hash table...\n" );

				//  calculate sampling time
				//
				calaculateSamplingTime(scanTime);

				//cout <<"about to scan... "<<endl;
				// scan the scene
				//
				if( doCameraMotion || liqglo__.liqglo_doMotion || liqglo__.liqglo_doDef ) 
				{
					for ( int msampleOn = 0; msampleOn < liqglo__.liqglo_motionSamples; msampleOn++ ) 
						scanScene__( liqglo__.liqglo_sampleTimes[ msampleOn ] , msampleOn );
				} else {
					liqglo__.liqglo_sampleTimes[ 0 ] = scanTime;
					liqglo__.liqglo_sampleTimesOffsets[ 0 ] = 0;
					scanScene__( scanTime, 0 );
				}
				//cout <<"    + scene scan done !"<<endl;

				// mark the frame as already scanned
				lastScannedFrame = scanTime;
				liqglo__.liqglo_currentJob = *iter;
			}
			//
			// start scene parsing ------------------------------------------------------------------
			//
			if( liqglo__.liqglo_currentJob.isShadowPass ) 
				liqglo__.liqglo_isShadowPass = true;
			else 
				liqglo__.liqglo_isShadowPass = false;



			{//export geometry objects to rib files.
				//  						MMatrix matrix;
				//  						MDagPath path;
				//  						MObject transform;
				//  						MFnDagNode dagFn;
				//
				//  						for ( RNMAP::iterator rniter( htable->RibNodeMap.begin() ); rniter != htable->RibNodeMap.end(); rniter++ ) 
				//  						{
				//  							LIQ_CHECK_CANCEL_REQUEST;
				//  
				//  							liqRibNodePtr ribNode( rniter->second );
				//  							path = ribNode->path();
				//  							transform = path.transform();
				//  							
				//  							if( ( !ribNode ) || ( ribNode->object(0)->type == MRT_Light ) ) 
				//  								continue;
				//  							if( ribNode->object(0)->type == MRT_Coord || ribNode->object(0)->type == MRT_ClipPlane ) 
				//  								continue;
				//  
				//  							_writeObject(false, ribNode);
				//  
				//  						}
			}
			//************************************************************************************
			LIQDEBUGPRINTF( "-> setting RiOptions\n" );
			//************************************************************************************

			// Rib client file creation options MUST be set before RiBegin
#if defined(PRMAN) || defined(DELIGHT)
			/* THERE IS A RIBLIB BUG WHICH PREVENTS THIS WORKING */
			_RiOption_format_compress(liqglo__.liqglo_doBinary, liqglo__.liqglo_doCompression);
#endif // PRMAN || DELIGHT

			// world RiReadArchives and Rib Boxes ************************************************
			//
			if( liqglo__.liqglo_currentJob.isShadow && !liqglo.fullShadowRib )
			{
				tShadowRibWriterMgr shadowRibWriterMgr;
				TempControlBreak tcb = 
					shadowRibWriterMgr.write(
					liqglo__, 
					liqglo__.liqglo_currentJob, 
					scanTime,
					m_outputLightsInDeepShadows,
					jobList);
				PROCESS_TEMP_CONTROL_BREAK_CONTINUE(tcb)
			}//if( liqglo_currentJob.isShadow && !fullShadowRib ) 
			else 
			{
				tHeroRibWriterMgr heroRibWriterMgr;
				TempControlBreak tcb = 
					heroRibWriterMgr.write(
					liqglo__, 
					liqglo__.liqglo_currentJob, 
					scanTime,
					m_outputLightsInDeepShadows
					//,jobList
					);
				PROCESS_TEMP_CONTROL_BREAK_CONTINUE(tcb)
			}

#ifdef RENDER_PIPE
			fclose( liqglo_ribFP );
#endif
			liqglo__.liqglo_ribFP = NULL;
			if( m_showProgress ) 
				printProgress( 3, liqglo.frameNumbers.size(), frameIndex );
		}//for (; iter != jobList.end(); ++iter ) 
	}//if( !m_deferredGen ) 

	// set the rib file for the 'view last rib' menu command
	// NOTE: this may be overridden later on in certain code paths
#if (Refactoring == 0)
	if( !m_deferredGen )
		lastRibName = liqglo__.liqglo_currentJob.ribFileName;
#endif
	return TCB_OK;
}
//
void liqRibTranslator::doRenderView()
{
	MString local = (m_renderViewLocal)? "1":"0";
	stringstream tmp;
	tmp << m_renderViewTimeOut;
	//=============
	cout << ">> m_renderView: m_renderViewTimeOut = " << tmp.str().c_str() << endl;
	MString timeout( tmp.str().c_str() );
	MString displayCmd = "liquidRenderView "+( (renderCamera=="")?"":("-c "+renderCamera) ) + " -l " + local + " -port " + m_renderViewPort + " -timeout " + timeout ;
	if( m_renderViewCrop ) 
		displayCmd = displayCmd + " -doRegion";
	displayCmd = displayCmd + ";liquidSaveRenderViewImage();";
	//============= 
	cout << ">> m_renderView: m_displayCmd = " <<  displayCmd.asChar() << endl;
	MGlobal::executeCommand( displayCmd );
}
//
void liqRibTranslator::doTextures()
{
	vector<structJob>::iterator iter = txtList.begin();
	while ( iter != txtList.end() ) 
	{
		if(iter->skip)
		{
			cout << "    - skipping '"<< iter->ribFileName <<"'"<<endl;
			liquidMessage("     - skipping '"+string(iter->ribFileName.asChar())+"'", messageInfo);
			++iter;
			continue;
		}
		liquidMessage( "Making textures '" + string( iter->imageName.asChar() ) + "'", messageInfo );
		cout << "[!] Making textures '" << iter->imageName.asChar() << "'" << endl;
#ifdef _WIN32
		liqProcessLauncher::execute( iter->renderName, iter->ribFileName, liqglo.liqglo_projectDir, true );
#else
		liqProcessLauncher::execute( iter->renderName, iter->ribFileName, liqglo.liqglo_projectDir, true );
#endif
		++iter;
	}
}
//
void liqRibTranslator::doShadows()
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
		if( !liqProcessLauncher::execute( liqglo.liquidRenderer.renderCommand, liqglo.liquidRenderer.renderCmdFlags + " \"" + iter->ribFileName + "\"", liqglo.liqglo_projectDir, true ) )
#else
		if( !liqProcessLauncher::execute( liqglo.liquidRenderer.renderCommand, liqglo.liquidRenderer.renderCmdFlags + " " + iter->ribFileName, liqglo.liqglo_projectDir, true ) )
#endif
			break;
		++iter;
	} // while ( iter != shadowList.end() )
}
//
void liqRibTranslator::postActions(const MString& originalLayer__)
{
	// return to the frame we were at before we ran the animation
	LIQDEBUGPRINTF( "-> setting frame to current frame.\n" );
	MGlobal::viewFrame (originalTime);

	if( originalLayer__ != "" ) 
	{
		MString cmd;
		cmd = "if( `editRenderLayerGlobals -q -currentRenderLayer` != \"" + originalLayer__ + "\" ) editRenderLayerGlobals -currentRenderLayer \"" + originalLayer__ + "\";";
		if(  MGlobal::executeCommand( cmd, false, false ) == MS::kFailure ) 
		{
			MString err;
			err = "Liquid : could not switch back to render layer \"" + originalLayer__ + "\" !";
			throw err;
		}
	}
}
//
MStatus liqRibTranslator::buildShadowJobs__()
{
	structJob thisJob__;

	MStatus returnStatus__ = MS::kSuccess;
	MStatus status__;
	MDagPath lightPath__;

	MItDag dagIterator( MItDag::kDepthFirst, MFn::kLight, &returnStatus__ );
	for (; !dagIterator.isDone(); dagIterator.next()) 
	{
		if( !dagIterator.getPath( lightPath__ ) ) 
			continue;
		bool usesDepthMap = false;
		MFnLight fnLightNode( lightPath__ );
		liquidGetPlugValue( fnLightNode, "useDepthMapShadows", usesDepthMap, status__ );
		if( usesDepthMap && areObjectAndParentsVisible( lightPath__ ) ) 
		{
			// philippe : this is the default and can be overriden
			// by the everyFrame/renderAtFrame attributes.
			//
			thisJob__.renderFrame           = liqglo.liqglo_lframe;
			thisJob__.everyFrame            = true;
			thisJob__.shadowObjectSet       = "";
			thisJob__.shadowArchiveRibDone  = false;
			thisJob__.skip                  = false;
			//
			// We have a shadow job, so find out if we need to use deep shadows,
			// and the pixel sample__ count
			//
			thisJob__.deepShadows                 = false;
			thisJob__.shadowPixelSamples          = 1;
			thisJob__.shadowVolumeInterpretation  = 1;
			thisJob__.shadingRateFactor           = 1.0;
			thisJob__.shadowAggregation			= 0;

			// philippe : we grab the job's resolution now instead of in the output phase
			// that way , we can make sure one light can generate many shadow maps
			// with different resolutions
			thisJob__.aspectRatio = 1.0;
			liquidGetPlugValue( fnLightNode, "dmapResolution", thisJob__.width, status__ );
			thisJob__.height = thisJob__.width;

			// Get to our shader node.
			//
			MPlug liquidLightShaderNodeConnection;
			MStatus liquidLightShaderStatus;
			liquidLightShaderNodeConnection = fnLightNode.findPlug( "liquidLightShaderNode", &liquidLightShaderStatus );
			if( liquidLightShaderStatus == MS::kSuccess && liquidLightShaderNodeConnection.isConnected() )
			{
				MPlugArray liquidLightShaderNodePlugArray;
				liquidLightShaderNodeConnection.connectedTo( liquidLightShaderNodePlugArray, true, true );
				MFnDependencyNode fnLightShaderNode( liquidLightShaderNodePlugArray[0].node() );

				// Now grab the parameters.
				//
				liquidGetPlugValue( fnLightShaderNode, "deepShadows", thisJob__.deepShadows, status__ );

				// Only use the pixel samples and volume interpretation with deep shadows.
				//
				if( thisJob__.deepShadows )
				{
					liquidGetPlugValue( fnLightShaderNode, "pixelSamples", thisJob__.shadowPixelSamples, status__ );
					liquidGetPlugValue( fnLightShaderNode, "volumeInterpretation", thisJob__.shadowVolumeInterpretation, status__ );
				}

				// philippe : check the shadow rendering frequency
				//
				liquidGetPlugValue( fnLightShaderNode, "everyFrame", thisJob__.everyFrame, status__ );

				// philippe : this is crucial, as we rely on the renderFrame to check
				// which frame the scene should be scanned for that job.
				// If the job is a shadow rendering once only at a given frame, we take the
				// renderAtFrame attribute, otherwise, the current time.
				//
				if( !thisJob__.everyFrame ) 
					liquidGetPlugValue( fnLightShaderNode, "renderAtFrame", thisJob__.renderFrame, status__ );  

				// Check if the shadow aggregation option is used
				liquidGetPlugValue( fnLightShaderNode, "aggregateShadowMaps", thisJob__.shadowAggregation, status__ );  

				// philippe : check the shadow geometry set
				//
				liquidGetPlugValue( fnLightShaderNode, "geometrySet", thisJob__.shadowObjectSet, status__ );
				liquidGetPlugValue( fnLightShaderNode, "shadingRateFactor", thisJob__.shadingRateFactor, status__ );
			} 
			else 
			{
				/* Here we support the same options as those found on light shader nodes
				but we look for dynamic attributes, so we need a bit more error checking.
				*/
				//MPlug paramPlug = fnLightNode.findPlug( "deepShadows", &status );
				liquidGetPlugValue( fnLightNode, "deepShadows", thisJob__.deepShadows, status__ );
				if( thisJob__.deepShadows ) 
				{
					liquidGetPlugValue( fnLightNode, "pixelSamples", thisJob__.shadowPixelSamples, status__ );
					liquidGetPlugValue( fnLightNode, "volumeInterpretation", thisJob__.shadowVolumeInterpretation, status__ );
				}
				liquidGetPlugValue( fnLightNode, "everyFrame", thisJob__.everyFrame, status__ );
				if( !thisJob__.everyFrame ) 
					liquidGetPlugValue( fnLightNode, "renderAtFrame", thisJob__.renderFrame, status__ );  

				liquidGetPlugValue( fnLightNode, "geometrySet", thisJob__.shadowObjectSet, status__ );  
				liquidGetPlugValue( fnLightNode, "shadingRateFactor", thisJob__.shadingRateFactor, status__ ); 
			}
			// this will store the shadow camera path and the test's result
			bool lightHasShadowCam = false;
			MDagPathArray shadowCamPath;

			if( lightPath__.hasFn( MFn::kSpotLight ) || lightPath__.hasFn( MFn::kDirectionalLight ) ) 
			{
				bool computeShadow = true;
				thisJob__.hasShadowCam = false;
				MPlug liquidLightShaderNodeConnection;
				MStatus liquidLightShaderStatus;
				liquidLightShaderNodeConnection = fnLightNode.findPlug( "liquidLightShaderNode", &liquidLightShaderStatus );

				if( liquidLightShaderStatus == MS::kSuccess && liquidLightShaderNodeConnection.isConnected() ) 
				{
					// a shader is connected to the light !
					MPlugArray liquidLightShaderNodePlugArray;
					liquidLightShaderNodeConnection.connectedTo( liquidLightShaderNodePlugArray, true, true );
					MFnDependencyNode fnLightShaderNode( liquidLightShaderNodePlugArray[0].node() );

					// has the main shadow been disabled ?
					liquidGetPlugValue( fnLightShaderNode, "generateMainShadow", computeShadow, status__ ); 

					// look for shadow cameras...
					MStatus stat;
					MPlug shadowCamPlug = fnLightShaderNode.findPlug( "shadowCameras", &stat );
					// find the multi message attribute...
					if( stat == MS::kSuccess ) 
					{
						int numShadowCams = shadowCamPlug.numElements();
						//cout <<">> got "<<numShadowCams<<" shadow cameras"<<endl;
						// iterate through existing array elements
						for ( unsigned int i=0; i<numShadowCams; i++ ) 
						{
							stat.clear();
							MPlug camPlug = shadowCamPlug.elementByPhysicalIndex( i, &stat );
							if( stat != MS::kSuccess ) 
								continue;
							MPlugArray shadowCamPlugArray;

							// if the element is connected, keep going...
							if( camPlug.connectedTo( shadowCamPlugArray, true, false ) ) 
							{
								MFnDependencyNode shadowCamDepNode = shadowCamPlugArray[0].node();
								//cout <<"shadow camera plug "<<i<<" is connected to "<<shadowCamDepNode.name()<<endl;

								MDagPath cameraPath;
								cameraPath.getAPathTo( shadowCamPlugArray[0].node(), cameraPath);
								//cout <<"cameraPath : "<<cameraPath.fullPathName()<<endl;
								shadowCamPath.append( cameraPath );
								lightHasShadowCam = true;
							}
						}
					}
				}
				thisJob__.path = lightPath__;
				thisJob__.name = fnLightNode.name();
				thisJob__.texName = "";
				thisJob__.isShadow = true;
				thisJob__.isPoint = false;
				thisJob__.isShadowPass = false;

				// check to see if the minmax shadow option is used
				thisJob__.isMinMaxShadow = false;
				liquidGetPlugValue( fnLightNode, "liquidMinMaxShadow", thisJob__.isMinMaxShadow, status__ ); 
				// check to see if the midpoint shadow option is used
				thisJob__.isMidPointShadow = false;
				liquidGetPlugValue( fnLightNode, "useMidDistDmap", thisJob__.isMidPointShadow, status__ ); 
				// in lazy compute mode, we check if the map is already on disk first.
				if( m_lazyCompute && computeShadow ) 
				{
					MString fileName( generateFileName( (fileGenMode) fgm_shadow_tex, thisJob__ ) );
					if( fileExists( fileName ) ) 
						computeShadow = false;
				}
				//
				// store the main shadow map    *****************************
				//
				if( computeShadow )
					jobList.push_back( thisJob__ );
				// We have to handle point lights differently as they need 6 shadow maps!
			} 
			else if( lightPath__.hasFn(MFn::kPointLight) ) 
			{
				for ( unsigned dirOn( 0 ); dirOn < 6; dirOn++ ) 
				{
					thisJob__.hasShadowCam = false;
					thisJob__.path = lightPath__;
					thisJob__.name = fnLightNode.name();
					thisJob__.isShadow = true;
					thisJob__.isShadowPass = false;
					thisJob__.isPoint = true;
					thisJob__.pointDir = ( PointLightDirection )dirOn;

					// check to see if the midpoint shadow option is used
					thisJob__.isMidPointShadow = false;
					liquidGetPlugValue( fnLightNode, "useMidDistDmap", thisJob__.isMidPointShadow, status__ );

					bool computeShadow = true;
					MStatus liquidLightShaderStatus;
					MPlug liquidLightShaderNodeConnection( fnLightNode.findPlug( "liquidLightShaderNode", &liquidLightShaderStatus ) );

					if( liquidLightShaderStatus == MS::kSuccess && liquidLightShaderNodeConnection.isConnected() ) 
					{
						// a shader is connected to the light !
						MPlugArray liquidLightShaderNodePlugArray;
						liquidLightShaderNodeConnection.connectedTo( liquidLightShaderNodePlugArray, true, true );
						MFnDependencyNode fnLightShaderNode( liquidLightShaderNodePlugArray[0].node() );

						// has the main shadow been disabled ?
						liquidGetPlugValue( fnLightShaderNode, "generateMainShadow", computeShadow, status__ );

						// look for shadow cameras...
						MStatus stat;
						MPlug shadowCamPlug( fnLightShaderNode.findPlug( "shadowCameras", &stat ) );

						// find the multi message attribute...
						if( stat == MS::kSuccess ) 
						{
							int numShadowCams = shadowCamPlug.numElements();
							//cout <<">> got "<<numShadowCams<<" shadow cameras"<<endl;
							// iterate through existing array elements
							for ( unsigned i( 0 ); i < numShadowCams; i++ ) 
							{
								stat.clear();
								MPlug camPlug = shadowCamPlug.elementByPhysicalIndex( i, &stat );
								if( stat != MS::kSuccess ) 
									continue;
								MPlugArray shadowCamPlugArray;

								// if the element is connected, keep going...
								if( camPlug.connectedTo( shadowCamPlugArray, true, false ) ) 
								{
									MFnDependencyNode shadowCamDepNode = shadowCamPlugArray[0].node();
									//cout <<"shadow camera plug "<<i<<" is connected to "<<shadowCamDepNode.name()<<endl;

									MDagPath cameraPath;
									cameraPath.getAPathTo( shadowCamPlugArray[0].node(), cameraPath);
									//cout <<"cameraPath : "<<cameraPath.fullPathName()<<endl;
									shadowCamPath.append( cameraPath );
									lightHasShadowCam = true;
								}
							}
						}
					}
					MString fileName( generateFileName( ( fileGenMode )fgm_shadow_tex, thisJob__ ) );
					if( m_lazyCompute ) 
						if( fileExists( fileName ) ) 
							computeShadow = false;
					if( computeShadow ) 
						jobList.push_back( thisJob__ );
				}
			}
			// if the job has shadow cameras, we will store them here
			//
			if( lightHasShadowCam )
			{
				int isAggregate = thisJob__.shadowAggregation;
				for( unsigned i( 0 ); i < shadowCamPath.length(); i++ )
				{
					if( !i && isAggregate )
						thisJob__.shadowAggregation = 0;
					else if ( isAggregate )
						thisJob__.shadowAggregation = 1;
					else
						thisJob__.shadowAggregation = 0;
					thisJob__.shadowCamPath = shadowCamPath[ i ];
					thisJob__.hasShadowCam = true;

					MFnDependencyNode shadowCamDepNode( shadowCamPath[ i ].node() );
					thisJob__.name = shadowCamDepNode.name();
					if( isAggregate )
						thisJob__.texName = fnLightNode.name(); //MFnDependencyNode( shadowCamPath[ i ].node() ).name();
					//					else
					//						thisJob.texName = "";
					//						thisJob.name = shadowCamDepNode.name();
					if( liquidGetPlugValue( shadowCamDepNode, "liqShadowResolution", thisJob__.width, status__ ) == MS::kSuccess )
						thisJob__.height = thisJob__.width;
					liquidGetPlugValue( shadowCamDepNode, "liqMidPointShadow", thisJob__.isMidPointShadow, status__ );
					thisJob__.midPointRatio = 0;
					liquidGetPlugValue( shadowCamDepNode, "liqMidPointRatio", thisJob__.midPointRatio, status__ );
					liquidGetPlugValue( shadowCamDepNode, "liqDeepShadows", thisJob__.deepShadows, status__ );
					liquidGetPlugValue( shadowCamDepNode, "liqPixelSamples", thisJob__.shadowPixelSamples, status__ );
					liquidGetPlugValue( shadowCamDepNode, "liqVolumeInterpretation", thisJob__.shadowVolumeInterpretation, status__ );
					liquidGetPlugValue( shadowCamDepNode, "liqEveryFrame", thisJob__.everyFrame, status__ );
					// as previously : this is important as thisJob.renderFrame corresponds to the
					// scene scanning time.
					if( thisJob__.everyFrame )
						thisJob__.renderFrame = liqglo.liqglo_lframe;
					else
						liquidGetPlugValue( shadowCamDepNode, "liqRenderAtFrame", thisJob__.renderFrame, status__ );
					liquidGetPlugValue( shadowCamDepNode, "liqGeometrySet", thisJob__.shadowObjectSet, status__ );
					liquidGetPlugValue( shadowCamDepNode, "liqShadingRateFactor", thisJob__.shadingRateFactor, status__ );
					// test if the file is already on disk...
					if( m_lazyCompute )
					{
						MString fileName( generateFileName( ( fileGenMode )fgm_shadow_tex, thisJob__ ) );
						if( fileExists( fileName ) )
							continue;
					}
					jobList.push_back( thisJob__ );
				}
			}
		} // useDepthMap
		//cout <<thisJob.name.asChar()<<" -> shd:"<<thisJob.isShadow<<" ef:"<<thisJob.everyFrame<<" raf:"<<thisJob.renderFrame<<" set:"<<thisJob.shadowObjectSet.asChar()<<endl;
	} // light dagIterator

	MDagPath cameraPath;
	MItDag dagCameraIterator( MItDag::kDepthFirst, MFn::kCamera, &returnStatus__ );
	for ( ; !dagCameraIterator.isDone(); dagCameraIterator.next() ) 
	{
		if( !dagCameraIterator.getPath(cameraPath) ) 
			continue;
		bool usesDepthMap( false );
		MFnCamera fnCameraNode( cameraPath );
		liquidGetPlugValue( fnCameraNode, "useDepthMapShadows", usesDepthMap, status__ );
		if( usesDepthMap && areObjectAndParentsVisible( cameraPath ) ) 
		{
			//
			// We have a shadow job, so find out if we need to use deep shadows,
			// and the pixel sample count
			//
			thisJob__.deepShadows = false;
			thisJob__.shadowPixelSamples = 1;
			thisJob__.shadowVolumeInterpretation = 1;
			fnCameraNode.findPlug( "deepShadows" ).getValue( thisJob__.deepShadows );
			// Only use the pixel samples and volume interpretation with deep shadows.
			//
			if( thisJob__.deepShadows )
			{
				fnCameraNode.findPlug( "pixelSamples" ).getValue( thisJob__.shadowPixelSamples );
				fnCameraNode.findPlug( "volumeInterpretation" ).getValue( thisJob__.shadowVolumeInterpretation );
			}

			thisJob__.hasShadowCam = true;
			thisJob__.shadowCamPath = cameraPath;
			thisJob__.path = cameraPath;
			thisJob__.name = fnCameraNode.name();
			thisJob__.isShadow = true;
			thisJob__.isPoint = false;
			thisJob__.isShadowPass = false;

			// check to see if the minmax shadow option is used
			thisJob__.isMinMaxShadow = false;
			status__.clear();
			MPlug liquidMinMaxShadow = fnCameraNode.findPlug( "liquidMinMaxShadow", &status__ );
			if( status__ == MS::kSuccess ) 
				liquidMinMaxShadow.getValue( thisJob__.isMinMaxShadow );

			// check to see if the midpoint shadow option is used
			thisJob__.isMidPointShadow = false;
			status__.clear();
			MPlug liquidMidPointShadow = fnCameraNode.findPlug( "useMidDistDmap", &status__ );
			if( status__ == MS::kSuccess ) 
				liquidMidPointShadow.getValue( thisJob__.isMidPointShadow );

			bool computeShadow( true );
			if( m_lazyCompute ) 
			{
				MString fileName( generateFileName( ( fileGenMode )fgm_shadow_tex, thisJob__ ) );
				if( fileExists( fileName ) ) continue;
			}

			if( computeShadow ) 
				jobList.push_back( thisJob__ );
		}
	} // camera dagIterator

	return returnStatus__;
}
//
MStatus liqRibTranslator::scanScene__(float lframe, int sample )
{
	int count =0;

	MTime mt( ( double )lframe, MTime::uiUnit() );
	if( MGlobal::viewFrame(mt) == MS::kSuccess ) 
	{
		// scanScene: execute pre-frame command
		if( m_preFrameMel != "" ) 
		{
			MString preFrameMel( parseString( m_preFrameMel, false ) );
			if( fileExists( preFrameMel  ) ) 
				MGlobal::sourceFile( preFrameMel );
			else 
			{
				if( MS::kSuccess == MGlobal::executeCommand( preFrameMel, false, false ) ) 
					cout <<"Liquid -> pre-frame script executed successfully."<<endl<<flush;
				else 
					cout <<"Liquid -> ERROR :pre-frame script failed."<<endl<<flush;
			}
		}

		MStatus returnStatus;
		// scanScene: Scan the scene for lights
		{
			tLightMgr lightMgr;
			lightMgr.scanScene(lframe, sample,htable, count, returnStatus);
		}
		{
			tLocatorMgr locatorMgr;
			locatorMgr.scanScene(lframe, sample,htable, count, returnStatus);
		}

		if( !m_renderSelected )
		{
			MItDag dagIterator( MItDag::kDepthFirst, MFn::kInvalid, &returnStatus);
			for (; !dagIterator.isDone(); dagIterator.next())
			{
				MDagPath path;
				dagIterator.getPath( path );
				MObject currentNode = dagIterator.item();
				if(!currentNode.hasFn(MFn::kDagNode))
					continue;
				returnStatus = scanSceneNodes( currentNode, path, lframe, sample, count, returnStatus );
				if( MS::kSuccess != returnStatus )
					continue;
			}
		}
		else
		{
			// scanScene: find out the current selection for possible selected object output
			MSelectionList currentSelection;
			MGlobal::getActiveSelectionList( currentSelection );
			MItSelectionList selIterator( currentSelection );
			for( ; !selIterator.isDone(); selIterator.next() )
			{
				MDagPath objectPath;
				selIterator.getDagPath( objectPath );
				
				MItDag dagIterator( MItDag::kDepthFirst, MFn::kInvalid, &returnStatus);			
				dagIterator.reset (objectPath.node(), MItDag::kDepthFirst, MFn::kInvalid );
				for (; !dagIterator.isDone(); dagIterator.next())
				{
					MDagPath path;
					dagIterator.getPath( path );
					MObject currentNode = dagIterator.item();
					if(!currentNode.hasFn(MFn::kDagNode))
						continue;
					returnStatus = scanSceneNodes( currentNode, path, lframe, sample, count, returnStatus );
					if( MS::kSuccess != returnStatus )
						continue;
				}
			}
		}

		// scanScene: Now deal with all the particle-instanced objects (where a
		// particle is replaced by an object or group of objects).
		//
		dealwithParticleInstancedObjects(sample, lframe, count);


		vector<structJob>::iterator iter = jobList.begin();
		while ( iter != jobList.end() ) 
		{
			LIQ_CHECK_CANCEL_REQUEST;
			// scanScene: Get the camera/light info for this job at this frame
			/*MStatus status;*/

			if( !iter->isShadow ) 
			{
				getCameraData( iter , sample);
			} //if( !iter->isShadow )  
			else 
			{
				getLightData( iter , sample);
			}//if( !iter->isShadow ) else
			++iter;
		}//while ( iter != jobList.end() )

		// post-frame script execution
		if( m_postFrameMel != "" ) 
		{
			MString postFrameMel( parseString( m_postFrameMel, false ) );
			if( fileExists( postFrameMel  ) ) 
				MGlobal::sourceFile( postFrameMel );
			else 
				if( MS::kSuccess == MGlobal::executeCommand( postFrameMel, false, false ) ) 
					cout <<"Liquid -> post-frame script executed successfully."<<endl<<flush;
				else 
					cout <<"Liquid -> ERROR :post-frame script failed."<<endl<<flush;
		}
		return MS::kSuccess;
	}
	return MS::kFailure;
}
//
void liqRibTranslator::dealwithParticleInstancedObjects(
	const float lframe__, const int sample__,
	int &count__ 
	)
{
	MItInstancer instancerIter;
	while( !instancerIter.isDone() )
	{
		MDagPath path( instancerIter.path() );
		MString instanceStr( ( MString )"|INSTANCE_" +
			instancerIter.instancerId() + (MString)"_" +
			instancerIter.particleId() + (MString)"_" +
			instancerIter.pathId() );

		MMatrix instanceMatrix( instancerIter.matrix() );

		if( ( sample__ > 0 ) && isObjectMotionBlur( path ))
			htable->insert( path, lframe__, sample__, MRT_Unknown,count__++, &instanceMatrix, instanceStr, instancerIter.particleId() );
		else
			htable->insert( path, lframe__, 0, MRT_Unknown,count__++, &instanceMatrix, instanceStr, instancerIter.particleId() );
		instancerIter.next();
	}
}
//
void liqRibTranslator::getCameraData( vector<structJob>::iterator &iter__ , const int sample__)
{
	MStatus status;
				MDagPath path;
				MFnCamera   fnCamera( iter__->path );
				iter__->gotJobOptions = false;
				status.clear();
				MPlug cPlug = fnCamera.findPlug( MString( "ribOptions" ), &status );
				if( status == MS::kSuccess ) 
				{
					cPlug.getValue( iter__->jobOptions );
					iter__->gotJobOptions = true;
				}
				getCameraInfo( fnCamera );
				iter__->width = cam_width;
				iter__->height = cam_height;
				// scanScene: Renderman specifies shutter by time open
				// so we need to convert shutterAngle to time.
				// To do this convert shutterAngle to degrees and
				// divide by 360.
				//
				iter__->camera[sample__].shutter = fnCamera.shutterAngle() * 0.5 / M_PI;
				liqglo.liqglo_shutterTime = iter__->camera[sample__].shutter;
				iter__->camera[sample__].orthoWidth     = fnCamera.orthoWidth();
				iter__->camera[sample__].orthoHeight    = fnCamera.orthoWidth() * ((float)cam_height / (float)cam_width);
				iter__->camera[sample__].motionBlur     = fnCamera.isMotionBlur();
				iter__->camera[sample__].focalLength    = fnCamera.focalLength();
				iter__->camera[sample__].focalDistance  = fnCamera.focusDistance();
				iter__->camera[sample__].fStop          = fnCamera.fStop();

				// film back offsets
				double hSize, vSize, hOffset, vOffset;
				fnCamera.getFilmFrustum( fnCamera.focalLength(), hSize, vSize, hOffset, vOffset );

				double imr = ((float)cam_width / (float)cam_height);
				double fbr = hSize / vSize;
				double ho, vo;

				if( imr >= 1 ) 
				{
					switch ( fnCamera.filmFit() ) 
					{
					case MFnCamera::kVerticalFilmFit:
					case MFnCamera::kOverscanFilmFit:
						ho = hOffset / vSize * 2.0;
						vo = vOffset / vSize * 2.0;
						break;

					case MFnCamera::kHorizontalFilmFit:
					case MFnCamera::kFillFilmFit:
						ho = hOffset / ( vSize * fbr / imr ) * 2.0;
						vo = vOffset / ( vSize * fbr / imr ) * 2.0;
						break;

					default:
						ho = 0;
						vo = 0;
						break;
					}
				} 
				else 
				{
					switch ( fnCamera.filmFit() ) 
					{
					case MFnCamera::kFillFilmFit:
					case MFnCamera::kVerticalFilmFit:
						ho = hOffset / vSize * 2.0;
						vo = vOffset / vSize * 2.0;
						break;

					case MFnCamera::kHorizontalFilmFit:
					case MFnCamera::kOverscanFilmFit:
						ho = hOffset / ( vSize * fbr / imr ) * 2.0;
						vo = vOffset / ( vSize * fbr / imr ) * 2.0;
						break;

					default:
						ho = 0;
						vo = 0;
						break;
					}
				}
				iter__->camera[sample__].horizontalFilmOffset = ho;
				iter__->camera[sample__].verticalFilmOffset   = vo;

				// convert focal length to scene units
				MDistance flenDist(iter__->camera[sample__].focalLength,MDistance::kMillimeters);
				iter__->camera[sample__].focalLength = flenDist.as(MDistance::uiUnit());

				fnCamera.getPath(path);
				MTransformationMatrix xform( path.inclusiveMatrix() );

				// the camera is pointing toward negative Z
				double scale[] = { 1, 1, -1 };
				xform.setScale( scale, MSpace::kTransform );

				// scanScene:
				// philippe : rotate the main camera 90 degrees around Z-axis if necessary
				// ( only in main camera )
				MMatrix camRotMatrix;
				if( liqglo_rotateCamera == true ) 
				{
					float crm[4][4] = {  {  0.0,  1.0,  0.0,  0.0 },
					{ -1.0,  0.0,  0.0,  0.0 },
					{  0.0,  0.0,  1.0,  0.0 },
					{  0.0,  0.0,  0.0,  1.0 }};
					camRotMatrix = crm;
				}
				iter__->camera[sample__].mat = xform.asMatrixInverse() * camRotMatrix;

				if( fnCamera.isClippingPlanes() ) 
				{
					iter__->camera[sample__].neardb    = fnCamera.nearClippingPlane();
					iter__->camera[sample__].fardb    = fnCamera.farClippingPlane();
				} 
				else 
				{
					iter__->camera[sample__].neardb    = 0.001;    // TODO: these values are duplicated elsewhere in this file
					iter__->camera[sample__].fardb    = 250000.0; // TODO: these values are duplicated elsewhere in this file
				}
				iter__->camera[sample__].isOrtho = fnCamera.isOrtho();

				// scanScene: The camera's fov may not match the rendered image in Maya
				// if a film-fit is used. 'fov_ratio' is used to account for
				// this.
				//
				iter__->camera[sample__].hFOV = fnCamera.horizontalFieldOfView()/fov_ratio;
				iter__->aspectRatio = aspectRatio;

				// scanScene: Determine what information to write out (RGB, alpha, zbuffer)
				//
				iter__->imageMode.clear();

				bool isOn;
				MPlug boolPlug;
				boolPlug = fnCamera.findPlug( "image" );

				boolPlug.getValue( isOn );
				if( isOn ) 
				{
					// We are writing RGB info
					//
					iter__->imageMode = "rgb";
					iter__->format = outFormat;
				}
				boolPlug = fnCamera.findPlug( "mask" );
				boolPlug.getValue( isOn );
				if( isOn ) 
				{
					// We are writing alpha channel info
					//
					iter__->imageMode += "a";
					iter__->format = outFormat;
				}
				boolPlug = fnCamera.findPlug( "depth" );
				boolPlug.getValue( isOn );
				if( isOn ) {
					// We are writing z-buffer info
					//
					iter__->imageMode = "z";
					iter__->format = "zfile";
				}
}
//
void liqRibTranslator::getLightData( vector<structJob>::iterator &iter__ , const int sample__)
{
	MStatus status;

	// scanScene: doing shadow render
	//
	MDagPath path;
	MFnLight   fnLight( iter__->path );
	status.clear();

	iter__->gotJobOptions = false;
	MPlug cPlug = fnLight.findPlug( MString( "ribOptions" ), &status );
	if( status == MS::kSuccess ) {
		cPlug.getValue( iter__->jobOptions );
		iter__->gotJobOptions = true;
	}

	// philippe: this block is obsolete as we now get the resolution when building the job list
	//
	/* MPlug lightPlug = fnLight.findPlug( "dmapResolution" );
	float dmapSize;
	lightPlug.getValue( dmapSize );
	iter__->height = iter__->width = (int)dmapSize; */

	if( iter__->hasShadowCam ) 
	{
		// scanScene: the light uses a shadow cam
		//
		MFnCamera fnCamera( iter__->shadowCamPath );
		fnCamera.getPath(path);
		MTransformationMatrix xform( path.inclusiveMatrix() );

		// the camera is pointing toward negative Z
		double scale[] = { 1, 1, -1 };
		xform.setScale( scale, MSpace::kTransform );

		iter__->camera[sample__].mat         = xform.asMatrixInverse();
		iter__->camera[sample__].neardb      = fnCamera.nearClippingPlane();
		iter__->camera[sample__].fardb       = fnCamera.farClippingPlane();
		iter__->camera[sample__].isOrtho     = fnCamera.isOrtho();
		iter__->camera[sample__].orthoWidth  = fnCamera.orthoWidth();
		iter__->camera[sample__].orthoHeight = fnCamera.orthoWidth();
	} 
	else 
	{
		// scanScene: the light does not use a shadow cam
		//

		// get the camera world matrix
		fnLight.getPath(path);
		MTransformationMatrix xform( path.inclusiveMatrix() );

		// the camera is pointing toward negative Z
		double scale[] = { 1, 1, -1 };
		xform.setScale( scale, MSpace::kTransform );

		if( iter__->isPoint ) 
		{
			double ninty = M_PI/2;
			if( iter__->pointDir == pPX ) { double rotation[] = { 0, -ninty, 0 }; xform.setRotation( rotation, MTransformationMatrix::kXYZ ); }
			if( iter__->pointDir == pNX ) { double rotation[] = { 0, ninty, 0 }; xform.setRotation( rotation, MTransformationMatrix::kXYZ ); }
			if( iter__->pointDir == pPY ) { double rotation[] = { ninty, 0, 0 }; xform.setRotation( rotation, MTransformationMatrix::kXYZ ); }
			if( iter__->pointDir == pNY ) { double rotation[] = { -ninty, 0, 0 }; xform.setRotation( rotation, MTransformationMatrix::kXYZ ); }
			if( iter__->pointDir == pPZ ) { double rotation[] = { 0, M_PI, 0 }; xform.setRotation( rotation, MTransformationMatrix::kXYZ ); }
			if( iter__->pointDir == pNZ ) { double rotation[] = { 0, 0, 0 }; xform.setRotation( rotation, MTransformationMatrix::kXYZ ); }
		}
		iter__->camera[sample__].mat = xform.asMatrixInverse();

		MPlug shaderConnection( fnLight.findPlug( "liquidLightShaderNode", &status ) );
		if( status == MS::kSuccess && shaderConnection.isConnected() ) 
		{
			MPlugArray LightShaderPlugArray;
			shaderConnection.connectedTo( LightShaderPlugArray, true, true );
			MFnDependencyNode fnLightShaderNode( LightShaderPlugArray[0].node() );
			fnLightShaderNode.findPlug( "nearClipPlane" ).getValue( iter__->camera[sample__].neardb );
			fnLightShaderNode.findPlug( "farClipPlane" ).getValue( iter__->camera[sample__].fardb );
		} 
		else 
		{
			iter__->camera[sample__].neardb   = 0.001;    // TODO: these values are duplicated elsewhere in this file
			iter__->camera[sample__].fardb    = 250000.0; // TODO: these values are duplicated elsewhere in this file
			MPlug nearPlug = fnLight.findPlug( "nearClipPlane", &status );
			if( status == MS::kSuccess ) 
				nearPlug.getValue( iter__->camera[sample__].neardb );
			MPlug farPlug = fnLight.findPlug( "farClipPlane", &status );
			if( status == MS::kSuccess ) 
				farPlug.getValue( iter__->camera[sample__].fardb );
		}

		if( fnLight.dagPath().hasFn( MFn::kDirectionalLight ) ) 
		{
			iter__->camera[sample__].isOrtho = true;
			fnLight.findPlug( "dmapWidthFocus" ).getValue( iter__->camera[sample__].orthoWidth );
			fnLight.findPlug( "dmapWidthFocus" ).getValue( iter__->camera[sample__].orthoHeight );
		} 
		else 
		{
			iter__->camera[sample__].isOrtho = false;
			iter__->camera[sample__].orthoWidth = 0.0;
		}
	}

	if( iter__->deepShadows )
	{
		iter__->camera[sample__].shutter = liqglo.liqglo_shutterTime;
		iter__->camera[sample__].motionBlur = true;
	}
	else
	{
		iter__->camera[sample__].shutter = 0;
		iter__->camera[sample__].motionBlur = false;
	}
	iter__->camera[sample__].focalLength = 0;
	iter__->camera[sample__].focalDistance = 0;
	iter__->camera[sample__].fStop = 0;
	//doCameraMotion = 0;

	iter__->aspectRatio = 1.0;

	// The camera's fov may not match the rendered image in Maya
	// if a film-fit is used. 'fov_ratio' is used to account for
	// this.
	//
	if( iter__->hasShadowCam ) 
	{
		MFnCamera fnCamera( iter__->shadowCamPath );
		float camFov = fnCamera.horizontalFieldOfView();
		iter__->camera[sample__].hFOV = camFov;
	} 
	else 
	{
		MStatus coneStatus;
		MPlug lightPlug = fnLight.findPlug( "coneAngle", &coneStatus );
		if( coneStatus == MS::kSuccess ) 
		{
			// philippe : if we have a penumbra > 0, we must add it to the coneangle
			// to cover correctly the penumbra area.
			float angle = 0, penumbra = 0;
			lightPlug.getValue( angle );
			lightPlug = fnLight.findPlug( "penumbraAngle", &coneStatus );
			if( coneStatus == MS::kSuccess ) lightPlug.getValue( penumbra );
			if( penumbra > 0 ) angle += penumbra * 2;
			iter__->camera[sample__].hFOV = angle;
		} 
		else 
			iter__->camera[sample__].hFOV = 95;
	}

	// Determine what information to write out ( depth map or deep shadow )
	//
	iter__->imageMode.clear();
	if( iter__->deepShadows )
	{
		iter__->imageMode    += liqglo.liquidRenderer.dshImageMode;        //"deepopacity";
		iter__->format        =  liqglo.liquidRenderer.dshDisplayName;    //"deepshad";
	}
	else
	{
		iter__->imageMode += "z";
		iter__->format = "shadow";
	}
}
//
// MString liqRibTranslator::getBaseShadowName(const structJob &job__)
// {
// 	MString     baseShadowName___;
// 	// build the shadow archive name for the job
// 	bool renderAllFrames( job__.everyFrame );
// 	long refFrame( job__.renderFrame );
// 	MString geoSet( job__.shadowObjectSet );
// 	baseShadowName___ = generateShadowArchiveName( renderAllFrames, refFrame, geoSet );
// 	baseShadowName___ = liquidGetRelativePath( liqglo.liqglo_relativeFileNames, baseShadowName___, liqglo.liqglo_ribDir );
// 
// 	return baseShadowName___;
// }
//
liqRibTranslator* liqRibTranslator::getInstancePtr()
{
	assert(mInstance);
	return mInstance;
}
//
MStatus liqRibTranslator::ribPrologue__()
{
	return ribPrologue();
}
//
MStatus liqRibTranslator::ribEpilogue__()
{
	return ribEpilogue();
}
//
MStatus liqRibTranslator::framePrologue__( long lframe)
{
	LIQDEBUGPRINTF( "-> Beginning Frame Prologue__\n" );
	ribStatus = kRibFrame;

	if( !m_exportReadArchive )
	{
		RiFrameBegin( lframe );

		if( liqglo.liqglo_currentJob.isShadow )
		{
			if( !liqglo.liqglo_currentJob.deepShadows || liqglo.liqglo_currentJob.shadowPixelSamples == 1)
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
			if( liqglo.liqglo_currentJob.isMidPointShadow && !liqglo.liqglo_currentJob.deepShadows )
			{
				RtString midPoint = "midpoint";
				RtFloat midRatio = liqglo.liqglo_currentJob.midPointRatio;

				RiHider( "hidden", "depthfilter", &midPoint, RI_NULL );

				if ( liqglo.liqglo_currentJob.midPointRatio != 0 )
					RiHider( "hidden", "midpointratio", &midRatio, RI_NULL ); // Output to rib jami
			}
			//-----------------------------------------------------
			LIQDEBUGPRINTF( "-> Setting Display Options\n" );
			//MString relativeShadowName( liquidSanitizePath( liquidGetRelativePath( liqglo_relativeFileNames, liqglo_currentJob.imageName, liqglo_projectDir ) ) );
			if( !liqglo.liqglo_currentJob.isMinMaxShadow )
			{
				if( liqglo.liqglo_currentJob.deepShadows )
				{
					// RiDeclare( "volumeinterpretation", "string" );
					RtString viContinuous = "continuous";
					RtString viDiscrete   = "discrete";

					if( liqglo.liquidRenderer.renderName == MString("3Delight") )
					{
						liqRIBMsg("Display 1");
						RiDisplay( const_cast< char* >( liqglo.liqglo_currentJob.imageName.asChar()),
							const_cast< char* >( liqglo.liqglo_currentJob.format.asChar() ),
							(RtToken)liqglo.liqglo_currentJob.imageMode.asChar(),
							"string volumeinterpretation",
							( liqglo.liqglo_currentJob.shadowVolumeInterpretation == 1 ? &viContinuous : &viDiscrete ),
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

						MString deepFileImageName = "+" + liqglo.liqglo_currentJob.imageName;

						liqRIBMsg("Display 3");
						RiDisplay( const_cast< char* >( deepFileImageName.asChar() ),
							const_cast< char* >( liqglo.liqglo_currentJob.format.asChar() ),
							(RtToken)liqglo.liqglo_currentJob.imageMode.asChar(),
							"string volumeinterpretation",
							( liqglo.liqglo_currentJob.shadowVolumeInterpretation == 1 ? &viContinuous : &viDiscrete ),
							RI_NULL );
					}
				}//if( liqglo.liqglo_currentJob.deepShadows )
				else
				{
					liqRIBMsg("Display 4");
					RtInt aggregate( liqglo.liqglo_currentJob.shadowAggregation );
					RiDisplay( const_cast< char* >( liqglo.liqglo_currentJob.imageName.asChar() ),
						const_cast< char* >( liqglo.liqglo_currentJob.format.asChar() ),
						(RtToken)liqglo.liqglo_currentJob.imageMode.asChar(),
						"int aggregate", &aggregate,
						RI_NULL );
				}
			}//if( !liqglo.liqglo_currentJob.isMinMaxShadow )
			else
			{
				liqRIBMsg("Display 5");
				RiArchiveRecord( RI_COMMENT, "Display Driver:" );
				RtInt minmax = 1;
				RiDisplay( const_cast< char* >( (liqglo.liqglo_currentJob.imageName+(int)liqglo.liqglo_lframe).asChar() ),//const_cast< char* >( parseString(liqglo_currentJob.imageName).asChar() ),
					const_cast< char* >(liqglo.liqglo_currentJob.format.asChar()),
					(RtToken)liqglo.liqglo_currentJob.imageMode.asChar(),
					"minmax", &minmax,
					RI_NULL );
			}
		}//if( liqglo.liqglo_currentJob.isShadow )
		else
		{
			// Smooth Shading
			RiShadingInterpolation( "smooth" );
			// Quantization
			// overriden to floats when in rendering to Maya's renderView
			if( !m_renderView && quantValue != 0 )
			{
				int whiteValue = (int) pow( 2.0, quantValue ) - 1;
				RiQuantize( RI_RGBA, whiteValue, 0, whiteValue, 0.5 );
			}
			else
			{
				RiQuantize( RI_RGBA, 0, 0, 0, 0 );
			}
			if( m_rgain != 1.0 || m_rgamma != 1.0 )
			{
				RiExposure( m_rgain, m_rgamma );
			}

			LIQDEBUGPRINTF( "-> Setting Display Options\n" );
			if( ( m_cropX1 != 0.0 ) || ( m_cropY1 != 0.0 ) || ( m_cropX2 != 1.0 ) || ( m_cropY2 != 1.0 ) ) 
			{
				// philippe : handle the rotated camera case
				if( liqglo_rotateCamera == true ) 
					RiCropWindow( m_cropY2, m_cropY1, 1 - m_cropX1, 1 - m_cropX2 );
				else 
					RiCropWindow( m_cropX1, m_cropX2, m_cropY1, m_cropY2 );
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

				vector<structChannel>::iterator m_channels_iterator;
				m_channels_iterator = m_channels.begin();

				while ( m_channels_iterator != m_channels.end() ) 
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

			vector<structDisplay>::iterator m_displays_iterator;
			m_displays_iterator = m_displays.begin();

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

			while ( m_displays_iterator != m_displays.end() ) 
			{
				// check if additionnal displays are enabled
				// if not, call it off after the 1st iteration.
				if( m_ignoreAOVDisplays && m_displays_iterator > m_displays.begin() ) 
					break;

				// This is the override for the primary DD
				// when you render to maya's renderview.
				if( m_displays_iterator == m_displays.begin() && m_renderView ) 
				{
					MString imageName( m_pixDir );
					imageName += parseString( liqglo.liqglo_DDimageName[ 0 ], false );
					//imageName = liquidGetRelativePath( liqglo_relativeFileNames, imageName, liqglo_projectDir );

					MString formatType = "liqmaya";
					MString imageMode = "rgba";

					// char tmp[20];
					// sprintf( tmp, "%i", m_renderViewPort);
					// MString port = ( char* )tmp;
					MString port;
					port.set( m_renderViewPort );

					MString host = "localhost";
					if( !m_renderViewLocal ) 
						MGlobal::executeCommand( "strip(system(\"echo $HOST\"));", host );

					liqRIBMsg("Display 7");
					RiArchiveRecord( RI_COMMENT, "Render To Maya renderView :" );
					RiArchiveRecord( RI_VERBATIM, "Display \"%s\" \"%s\" \"%s\" \"int merge\" [0] \"int mayaDisplayPort\" [%s] \"string host\" [\"%s\"]\n", const_cast< char* >( imageName.asChar() ), formatType.asChar(), imageMode.asChar(), port.asChar(), host.asChar() );

					// in this case, override the launch render settings
					if( launchRender == false ) 
						launchRender = true;
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
						imageName = liqglo.liqglo_sceneName + ".#." + outExt;
					imageName = m_pixDir + parseString( imageName, false );
					// we test for an absolute path before converting from rel to abs path in case the picture dir was overriden through the command line.
					//if( m_pixDir.index( '/' ) != 0 ) imageName = liquidGetRelativePath( liqglo_relativeFileNames, imageName, liqglo_projectDir );
					if( m_displays_iterator > m_displays.begin() ) 
						imageName = "+" + imageName;
					// get display type ( tiff, openexr, etc )
					imageType = (*m_displays_iterator).type;
					if( imageType == "" ) 
						imageType = "framebuffer";
					// get display mode ( rgb, z or defined display channel )
					imageMode = (*m_displays_iterator).mode;
					if( imageMode == "" ) 
						imageMode = "rgba";
					// get quantization params
					if( (*m_displays_iterator).doQuantize && m_displays_iterator > m_displays.begin() ) 
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
					if( (*m_displays_iterator).doFilter && m_displays_iterator > m_displays.begin() )
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
					RiArchiveRecord( RI_VERBATIM, "Display \"%s\" \"%s\" \"%s\" %s %s %s %s\n", const_cast< char* >( imageName.asChar() ), 
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

		LIQDEBUGPRINTF( "-> Setting Resolution\n" );
		// philippe : Rotated Camera Case
		if( liqglo.liqglo_currentJob.isShadow == false && liqglo_rotateCamera  == true ) 
			RiFormat( liqglo.liqglo_currentJob.height, liqglo.liqglo_currentJob.width, liqglo.liqglo_currentJob.aspectRatio );
		else 
			RiFormat( liqglo.liqglo_currentJob.width, liqglo.liqglo_currentJob.height, liqglo.liqglo_currentJob.aspectRatio );

		if( liqglo.liqglo_currentJob.camera[0].isOrtho )
		{
			RtFloat frameWidth, frameHeight;
			// the whole frame width has to be scaled according to the UI Unit
			frameWidth  = liqglo.liqglo_currentJob.camera[0].orthoWidth  * 0.5 ;
			frameHeight = liqglo.liqglo_currentJob.camera[0].orthoHeight * 0.5 ;
			RiProjection( "orthographic", RI_NULL );

			// if we are describing a shadow map camera,
			// we need to set the screenwindow to the default,
			// as shadow maps are always square.
			if( liqglo.liqglo_currentJob.isShadow == true )
				RiScreenWindow( -frameWidth, frameWidth, -frameHeight, frameHeight );
			else
				RiScreenWindow( -frameWidth, frameWidth, -frameHeight, frameHeight );
		} 
		else 
		{
			RtFloat fieldOfView = liqglo.liqglo_currentJob.camera[0].hFOV * 180.0 / M_PI ;
			if( liqglo.liqglo_currentJob.isShadow && liqglo.liqglo_currentJob.isPoint ) 
				fieldOfView = liqglo.liqglo_currentJob.camera[0].hFOV;

			RiProjection( "perspective", RI_FOV, &fieldOfView, RI_NULL );

			// if we are describing a shadow map camera,
			// we need to set the screenwindow to the default,
			// as shadow maps are always square.
			if( liqglo.liqglo_currentJob.isShadow == false )
			{
				double ratio = (double)liqglo.liqglo_currentJob.width / (double)liqglo.liqglo_currentJob.height;
				double left, right, bottom, top;
				if( ratio <= 0 ) 
				{
					left    = -1 + liqglo.liqglo_currentJob.camera[0].horizontalFilmOffset;
					right   =  1 + liqglo.liqglo_currentJob.camera[0].horizontalFilmOffset;
					bottom  = -1 / ratio + liqglo.liqglo_currentJob.camera[0].verticalFilmOffset;
					top     =  1 / ratio + liqglo.liqglo_currentJob.camera[0].verticalFilmOffset;
				} 
				else 
				{
					left    = -ratio + liqglo.liqglo_currentJob.camera[0].horizontalFilmOffset;
					right   =  ratio + liqglo.liqglo_currentJob.camera[0].horizontalFilmOffset;
					bottom  = -1 + liqglo.liqglo_currentJob.camera[0].verticalFilmOffset;
					top     =  1 + liqglo.liqglo_currentJob.camera[0].verticalFilmOffset;
				}
				RiScreenWindow( left, right, bottom, top );
			} else 
				RiScreenWindow( -1.0, 1.0, -1.0, 1.0 );
		}

		RiClipping( liqglo.liqglo_currentJob.camera[0].neardb, liqglo.liqglo_currentJob.camera[0].fardb );
		if( doDof && !liqglo.liqglo_currentJob.isShadow ) 
			RiDepthOfField( liqglo.liqglo_currentJob.camera[0].fStop, liqglo.liqglo_currentJob.camera[0].focalLength, liqglo.liqglo_currentJob.camera[0].focalDistance );

		// Set up for camera motion blur
		/* doCameraMotion = liqglo_currentJob.camera[0].motionBlur && liqglo_doMotion; */
		float frameOffset = 0;
		if( doCameraMotion || liqglo.liqglo_doMotion || liqglo.liqglo_doDef ) 
		{
			switch( shutterConfig ) 
			{
			case OPEN_ON_FRAME:
			default:
				if(liqglo.liqglo_relativeMotion)
					RiShutter( 0, liqglo.liqglo_currentJob.camera[0].shutter );
				else
					RiShutter( lframe, lframe + liqglo.liqglo_currentJob.camera[0].shutter );
				frameOffset = lframe;
				break;
			case CENTER_ON_FRAME:
				if(liqglo.liqglo_relativeMotion)
					RiShutter(  - ( liqglo.liqglo_currentJob.camera[0].shutter * 0.5 ),  ( liqglo.liqglo_currentJob.camera[0].shutter * 0.5 ) );
				else
					RiShutter( ( lframe - ( liqglo.liqglo_currentJob.camera[0].shutter * 0.5 ) ), ( lframe + ( liqglo.liqglo_currentJob.camera[0].shutter * 0.5 ) ) );
				frameOffset = lframe - ( liqglo.liqglo_currentJob.camera[0].shutter * 0.5 );
				break;
			case CENTER_BETWEEN_FRAMES:
				if(liqglo.liqglo_relativeMotion)
					RiShutter( + ( 0.5 * ( 1 - liqglo.liqglo_currentJob.camera[0].shutter ) ), + liqglo.liqglo_currentJob.camera[0].shutter + ( 0.5 * ( 1 - liqglo.liqglo_currentJob.camera[0].shutter ) ) );
				else
					RiShutter( lframe + ( 0.5 * ( 1 - liqglo.liqglo_currentJob.camera[0].shutter ) ), lframe + liqglo.liqglo_currentJob.camera[0].shutter + ( 0.5 * ( 1 -liqglo.liqglo_currentJob.camera[0].shutter ) ) );
				frameOffset = lframe + ( 0.5 * ( 1 - liqglo.liqglo_currentJob.camera[0].shutter ) );
				break;
			case CLOSE_ON_NEXT_FRAME:
				if(liqglo.liqglo_relativeMotion)
					RiShutter( + ( 1 - liqglo.liqglo_currentJob.camera[0].shutter ),  1 );
				else
					RiShutter( lframe + ( 1 - liqglo.liqglo_currentJob.camera[0].shutter ), lframe + 1 );
				frameOffset = lframe + ( 1 - liqglo.liqglo_currentJob.camera[0].shutter );
				break;
			}
		} 
		else 
		{
			if(liqglo.liqglo_relativeMotion)
				RiShutter( 0, 0);
			else
				RiShutter( lframe, lframe );
			frameOffset = lframe;
		}
		// relative motion
		if(liqglo.liqglo_relativeMotion)    
			RiOption( "shutter", "offset", &frameOffset, RI_NULL);

#ifdef DELIGHT
		RiOption( "shutter", "efficiency", &liqglo.liqglo_shutterEfficiency, RI_NULL );
#endif
		if( liqglo.liqglo_currentJob.gotJobOptions ) 
			RiArchiveRecord( RI_COMMENT, "jobOptions: \n%s", liqglo.liqglo_currentJob.jobOptions.asChar() );

		if( ( liqglo.liqglo_preRibBox.length() > 0 ) && !liqglo.liqglo_currentJob.isShadow ) 
			for ( unsigned ii(0); ii < liqglo.liqglo_preRibBox.length(); ii++ ) 
				RiArchiveRecord( RI_COMMENT, "Additional Rib:\n%s", liqglo.liqglo_preRibBox[ii].asChar() );

		if( ( liqglo.liqglo_preReadArchive.length() > 0 ) && !liqglo.liqglo_currentJob.isShadow ) 
			for ( unsigned ii(0); ii < liqglo.liqglo_preReadArchive.length(); ii++ ) 
				RiArchiveRecord( RI_COMMENT, "Read Archive Data: \nReadArchive \"%s\"", liqglo.liqglo_preReadArchive[ii].asChar() );

		if( ( liqglo.liqglo_preRibBoxShadow.length() > 0 ) && !liqglo.liqglo_currentJob.isShadow ) 
			for ( unsigned ii(0); ii < liqglo.liqglo_preRibBoxShadow.length(); ii++ ) 
				RiArchiveRecord( RI_COMMENT, "Additional Rib:\n%s", liqglo.liqglo_preRibBoxShadow[ii].asChar() );

		if( ( liqglo.liqglo_preReadArchiveShadow.length() > 0 ) && liqglo.liqglo_currentJob.isShadow ) 
			for ( unsigned ii(0); ii < liqglo.liqglo_preReadArchiveShadow.length(); ii++ ) 
				RiArchiveRecord( RI_COMMENT, "Read Archive Data: \nReadArchive \"%s\"", liqglo.liqglo_preReadArchiveShadow[ii].asChar() );

		// if we motion-blur the cam, open the motion block
		//
		if( doCameraMotion && ( !liqglo.liqglo_currentJob.isShadow || liqglo.liqglo_currentJob.deepShadows) ) 
			if(liqglo.liqglo_relativeMotion)
				RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimesOffsets );
			else
				RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimes );

		// write the camera transform
		//
		RtMatrix cameraMatrix;
		liqglo.liqglo_currentJob.camera[0].mat.get( cameraMatrix );
		RiTransform( cameraMatrix );

		// if we motion-blur the cam, write the subsequent motion samples and close the motion block
		//
		if( doCameraMotion && ( !liqglo.liqglo_currentJob.isShadow || liqglo.liqglo_currentJob.deepShadows ) ) 
		{
			int mm = 1;
			while ( mm < liqglo.liqglo_motionSamples ) 
			{
				liqglo.liqglo_currentJob.camera[mm].mat.get( cameraMatrix );
				RiTransform( cameraMatrix );
				++mm;
			}
			RiMotionEnd();
		}

	}
	return MS::kSuccess;
}
//
MStatus liqRibTranslator::worldPrologue__()
{
	return worldPrologue();
}
//
MStatus liqRibTranslator::lightBlock__()
{
	return lightBlock();
}
//
MStatus liqRibTranslator::coordSysBlock__()
{
	return coordSysBlock();
}
//
MStatus liqRibTranslator::objectBlock__()
{
	return objectBlock();
}
//
MStatus liqRibTranslator::worldEpilogue__()
{
	return worldEpilogue();
}
//
MStatus liqRibTranslator::frameEpilogue__( long scanTime)
{
	return frameEpilogue(scanTime);
}