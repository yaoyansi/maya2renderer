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

/**
* This method actually does the renderman output.
*/
MStatus liqRibTranslator::_doItNew( const MArgList& args , const MString& originalLayer )
{
	MStatus status;
	//- omitted temporarily
//	MString lastRibName;
	//bool hashTableInited = false;

	if( !liqglo.liquidBin && !m_deferredGen ) 
		liquidMessage( "Creating RIB <Press ESC To Cancel> ...", messageInfo );

	// Remember the frame the scene was at so we can restore it later.
	MTime originalTime = MAnimControl::currentTime();

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

		if( m_deferredGen ) 
		{
			MString currentFileType = MFileIO::fileType();
			MFileIO::exportAll( liqglo.tempDefname, currentFileType.asChar() );
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
				renderJobName = liqglo.liqglo_sceneName;
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


		unsigned frameIndex( 0 );
		for ( ; frameIndex < frameNumbers.size(); frameIndex++ ) 
		{
			TempControlBreak tcb = 
				processOneFrame(frameIndex, liqglo, jobScript);
			PROCESS_TEMP_CONTROL_BREAK(tcb)
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
				if( m_deferredGen ) 
				{
					stringstream ss;
					ss << RM_CMD << " " << liqglo.tempDefname.asChar();
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
				jobScript.writeALF( liquidGetRelativePath( liqglo.liqglo_relativeFileNames, renderScriptName, liqglo.liqglo_projectDir ).asChar() );
			if( m_renderScriptFormat == XML ) 
				jobScript.writeXML( liquidGetRelativePath( liqglo.liqglo_relativeFileNames, renderScriptName, liqglo.liqglo_projectDir ).asChar() );
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
		//- omitted temporarily
		//nPlug = rGlobalNode.findPlug( "lastRibFile" );
		//nPlug.setValue( lastRibName );
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
				if( liqglo.liqglo_doShadows ) 
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
				if( !exitstat ) 
				{
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
//
void liqRibTranslator::makeReflectionPass(
	std::vector<structJob> &refList__, 
	liqRenderScript::Job &reflectJob__,
	const bool alf_textures__,
	const bool alf_shadows__,
	bool &alf_refmaps__
	)
{
	LIQDEBUGPRINTF( "-> Generating job for ReflectionMap pass\n" );
	vector<structJob>::iterator iter = refList__.begin();

	alf_refmaps__ = true;

	stringstream ts;
	ts << "Reflections." << liqglo.liqglo_lframe;
	reflectJob__.title = ts.str();

	while ( iter != refList__.end() ) 
	{
		liqRenderScript::Job reflectSubtask;
		stringstream ts;
		ts << reflectJob__.title << " " << iter->imageName.asChar();
		reflectSubtask.title = ts.str();
		if( m_deferredGen ) {

		}
		if( alf_textures__ ) 
		{
			stringstream ss;
			ss << "Textures." << liqglo.liqglo_lframe;
			liqRenderScript::Job instanceJob;
			instanceJob.isInstance = true;
			instanceJob.title = ss.str();
			reflectJob__.childJobs.push_back( instanceJob );
		}
		if( alf_shadows__ ) 
		{
			stringstream ss;
			ss << "Shadows." << liqglo.liqglo_lframe;
			liqRenderScript::Job instanceJob;
			instanceJob.isInstance = true;
			instanceJob.title = ss.str();
			reflectJob__.childJobs.push_back( instanceJob );
		}

		stringstream ss;
		ss << iter->renderName.asChar() << " " << iter->ribFileName.asChar();
		liqRenderScript::Cmd cmd( ss.str(), (remoteRender && !useNetRman) );

		if( m_alfredExpand ) 
			cmd.alfredExpand = true;

		cmd.alfredServices = m_alfredServices.asChar();
		cmd.alfredTags     = m_alfredTags.asChar();
		reflectSubtask.commands.push_back( cmd );
		reflectSubtask.chaserCommand = ( string( "sho \"" ) + liqglo.liqglo_textureDir.asChar() + " " + iter->imageName.asChar() + "\"" );
		++iter;
		reflectJob__.childJobs.push_back( reflectSubtask );
	}

}

void liqRibTranslator::makeShadowPass(
									  std::vector<structJob> &shadowList__, 
									  liqRenderScript::Job &shadowJob__,
									  const bool alf_textures__,
									  bool &alf_shadows__,
									  const bool alf_refmaps__,
									  const MString &framePreCommand__,
									  const MString &frameRenderCommand__,
									  const int currentBlock__
									  )
{
	vector< structJob >::iterator iter = shadowList__.begin();

	alf_shadows__ = true;

	stringstream ts;
	ts << "Shadows." << liqglo.liqglo_lframe;
	shadowJob__.title = ts.str();
	while ( iter != shadowList__.end() ) 
	{
		alf_shadows__ = true;
		liqRenderScript::Job shadowSubtask;
		shadowSubtask.title = iter->name.asChar();
		if( alf_textures__ ) 
		{
			stringstream ss;
			ss << "Textures." << liqglo.liqglo_lframe;
			liqRenderScript::Job instanceJob;
			instanceJob.isInstance = true;
			instanceJob.title = ss.str();
			shadowSubtask.childJobs.push_back(instanceJob);
		}
		if( m_deferredGen ) 
		{
			stringstream ss;
			ss << liqglo.liqglo_sceneName.asChar() << "FrameRIBGEN" << currentBlock__;
			liqRenderScript::Job instanceJob;
			instanceJob.isInstance = true;
			instanceJob.title = ss.str();
			shadowSubtask.childJobs.push_back(instanceJob);
		}
		stringstream ss;
		if( useNetRman ) 
		{
#ifdef _WIN32
			ss << framePreCommand__.asChar() << " netrender %H -Progress \"" << iter->ribFileName.asChar() << "\"";
#else
			ss << framePreCommand__.asChar() << " netrender %H -Progress " << iter->ribFileName.asChar();
#endif
		} else {
#ifdef _WIN32
			ss << framePreCommand__.asChar() << " " << frameRenderCommand__.asChar() << " \"" << iter->ribFileName.asChar() << "\"";
#else
			ss << framePreCommand__.asChar() << " " << frameRenderCommand__.asChar() << " " << iter->ribFileName.asChar();
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
			ss << framePreCommand__.asChar() << " " << RM_CMD << " \"" << iter->ribFileName.asChar() << "\"";
#else
			ss << framePreCommand__.asChar() << " " << RM_CMD << " " << iter->ribFileName.asChar();
#endif

			shadowSubtask.cleanupCommands.push_back( liqRenderScript::Cmd( ss.str(), remoteRender ) );
		}
		shadowSubtask.chaserCommand = ( string( "sho \"" ) + iter->imageName.asChar() + "\"" );
		++iter;
		if( !m_alfShadowRibGen && !fullShadowRib ) 
			m_alfShadowRibGen = true;
		shadowJob__.childJobs.push_back( shadowSubtask );
	}
}
//
void liqRibTranslator::makeTexturePass(
									   std::vector<structJob> &txtList__, 
									   liqRenderScript::Job &textureJob__,
									   bool &alf_textures__,
									   const bool alf_shadows__,
									   const bool alf_refmaps__
									   )
{
	vector<structJob>::iterator iter = txtList__.begin();

	alf_textures__ = true;

	stringstream ts;
	ts << "Textures." << liqglo.liqglo_lframe;
	textureJob__.title = ts.str();

	while ( iter != txtList.end() ) 
	{
		liqRenderScript::Job textureSubtask;
		stringstream ts;
		ts << textureJob__.title << " " << iter->imageName.asChar();
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
		textureSubtask.chaserCommand = ( string( "sho \"" ) + liqglo.liqglo_textureDir.asChar() + " " + iter->imageName.asChar() + "\"" );
		++iter;
		textureJob__.childJobs.push_back( textureSubtask );
	}
}
//
void liqRibTranslator::addDefferedJob(
									  liqRenderScript::Job &deferredJob__,
									  const int currentBlock__,
									  const unsigned int frameIndex__,
									  const MString &framePreCommand__,
									  const MString &frameRibgenCommand__,
									  const MString &tempDefname__
									  )
{
	stringstream ribGenExtras;
	// ribGenExtras << " -progress -noDef -nop -noalfred -projectDir " << liqglo_projectDir.asChar() << " -ribName " << liqglo_sceneName.asChar() << " -mf " << liqglo.tempDefname.asChar() << " -t ";
	ribGenExtras << " -progress -noDef -projectDir " << liqglo.liqglo_projectDir.asChar() << " -ribName " << liqglo.liqglo_sceneName.asChar() << " -fl ";

	unsigned lastGenFrame( ( frameIndex__ + m_deferredBlockSize ) < frameNumbers.size() ? frameIndex__ + m_deferredBlockSize : frameNumbers.size() );

	//liquidMessage2(messageInfo, ">>> frameIndex = %d m_deferredBlockSize = %d frameNumbers.size = %d lastGenFrame = %d\n",frameIndex,m_deferredBlockSize,frameNumbers.size(),lastGenFrame );

	for( unsigned outputFrame( frameIndex__ ); outputFrame < lastGenFrame; outputFrame++ )
	{  
		ribGenExtras << frameNumbers[ outputFrame ];
		ribGenExtras << (( outputFrame != ( lastGenFrame - 1 ) )? ", " : " ");
		// liquidMessage2(messageInfo, "\t outputFrame = %d\n", outputFrame );
	}
	stringstream titleStream;
	titleStream << liqglo.liqglo_sceneName.asChar() << "FrameRIBGEN" << currentBlock__;
	deferredJob__.title = titleStream.str();

	stringstream ss;
	ss << framePreCommand__.asChar() << " " << frameRibgenCommand__.asChar() << ribGenExtras.str() << " " << tempDefname__.asChar();
	liqRenderScript::Cmd cmd( ss.str(), remoteRender );
	cmd.alfredServices = m_defGenService.asChar();
	cmd.alfredTags     = m_defGenKey.asChar();
	if( m_alfredExpand ) 
		cmd.alfredExpand = true;

	deferredJob__.commands.push_back(cmd);

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
	MDagPath lightPath;

	jobList.clear();
	shadowList.clear();
	txtList.clear();

	structJob thisJob;

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
		MItDag dagIterator( MItDag::kDepthFirst, MFn::kLight, &returnStatus );
		for (; !dagIterator.isDone(); dagIterator.next()) 
		{
			if( !dagIterator.getPath( lightPath ) ) 
				continue;
			bool usesDepthMap = false;
			MFnLight fnLightNode( lightPath );
			liquidGetPlugValue( fnLightNode, "useDepthMapShadows", usesDepthMap, status );
			if( usesDepthMap && areObjectAndParentsVisible( lightPath ) ) 
			{
				// philippe : this is the default and can be overriden
				// by the everyFrame/renderAtFrame attributes.
				//
				thisJob.renderFrame           = liqglo.liqglo_lframe;
				thisJob.everyFrame            = true;
				thisJob.shadowObjectSet       = "";
				thisJob.shadowArchiveRibDone  = false;
				thisJob.skip                  = false;
				//
				// We have a shadow job, so find out if we need to use deep shadows,
				// and the pixel sample count
				//
				thisJob.deepShadows                 = false;
				thisJob.shadowPixelSamples          = 1;
				thisJob.shadowVolumeInterpretation  = 1;
				thisJob.shadingRateFactor           = 1.0;
				thisJob.shadowAggregation			= 0;

				// philippe : we grab the job's resolution now instead of in the output phase
				// that way , we can make sure one light can generate many shadow maps
				// with different resolutions
				thisJob.aspectRatio = 1.0;
				liquidGetPlugValue( fnLightNode, "dmapResolution", thisJob.width, status );
				thisJob.height = thisJob.width;

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
					liquidGetPlugValue( fnLightShaderNode, "deepShadows", thisJob.deepShadows, status );

					// Only use the pixel samples and volume interpretation with deep shadows.
					//
					if( thisJob.deepShadows )
					{
						liquidGetPlugValue( fnLightShaderNode, "pixelSamples", thisJob.shadowPixelSamples, status );
						liquidGetPlugValue( fnLightShaderNode, "volumeInterpretation", thisJob.shadowVolumeInterpretation, status );
					}

					// philippe : check the shadow rendering frequency
					//
					liquidGetPlugValue( fnLightShaderNode, "everyFrame", thisJob.everyFrame, status );

					// philippe : this is crucial, as we rely on the renderFrame to check
					// which frame the scene should be scanned for that job.
					// If the job is a shadow rendering once only at a given frame, we take the
					// renderAtFrame attribute, otherwise, the current time.
					//
					if( !thisJob.everyFrame ) 
						liquidGetPlugValue( fnLightShaderNode, "renderAtFrame", thisJob.renderFrame, status );  

					// Check if the shadow aggregation option is used
					liquidGetPlugValue( fnLightShaderNode, "aggregateShadowMaps", thisJob.shadowAggregation, status );  

					// philippe : check the shadow geometry set
					//
					liquidGetPlugValue( fnLightShaderNode, "geometrySet", thisJob.shadowObjectSet, status );
					liquidGetPlugValue( fnLightShaderNode, "shadingRateFactor", thisJob.shadingRateFactor, status );
				} 
				else 
				{
					/* Here we support the same options as those found on light shader nodes
					but we look for dynamic attributes, so we need a bit more error checking.
					*/
					//MPlug paramPlug = fnLightNode.findPlug( "deepShadows", &status );
					liquidGetPlugValue( fnLightNode, "deepShadows", thisJob.deepShadows, status );
					if( thisJob.deepShadows ) 
					{
						liquidGetPlugValue( fnLightNode, "pixelSamples", thisJob.shadowPixelSamples, status );
						liquidGetPlugValue( fnLightNode, "volumeInterpretation", thisJob.shadowVolumeInterpretation, status );
					}
					liquidGetPlugValue( fnLightNode, "everyFrame", thisJob.everyFrame, status );
					if( !thisJob.everyFrame ) 
						liquidGetPlugValue( fnLightNode, "renderAtFrame", thisJob.renderFrame, status );  

					liquidGetPlugValue( fnLightNode, "geometrySet", thisJob.shadowObjectSet, status );  
					liquidGetPlugValue( fnLightNode, "shadingRateFactor", thisJob.shadingRateFactor, status ); 
				}
				// this will store the shadow camera path and the test's result
				bool lightHasShadowCam = false;
				MDagPathArray shadowCamPath;

				if( lightPath.hasFn( MFn::kSpotLight ) || lightPath.hasFn( MFn::kDirectionalLight ) ) 
				{
					bool computeShadow = true;
					thisJob.hasShadowCam = false;
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
						liquidGetPlugValue( fnLightShaderNode, "generateMainShadow", computeShadow, status ); 

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
					thisJob.path = lightPath;
					thisJob.name = fnLightNode.name();
					thisJob.texName = "";
					thisJob.isShadow = true;
					thisJob.isPoint = false;
					thisJob.isShadowPass = false;

					// check to see if the minmax shadow option is used
					thisJob.isMinMaxShadow = false;
					liquidGetPlugValue( fnLightNode, "liquidMinMaxShadow", thisJob.isMinMaxShadow, status ); 
					// check to see if the midpoint shadow option is used
					thisJob.isMidPointShadow = false;
					liquidGetPlugValue( fnLightNode, "useMidDistDmap", thisJob.isMidPointShadow, status ); 
					// in lazy compute mode, we check if the map is already on disk first.
					if( m_lazyCompute && computeShadow ) 
					{
						MString fileName( generateFileName( (fileGenMode) fgm_shadow_tex, thisJob ) );
						if( fileExists( fileName ) ) 
							computeShadow = false;
					}
					//
					// store the main shadow map    *****************************
					//
					if( computeShadow )
						jobList.push_back( thisJob );
					// We have to handle point lights differently as they need 6 shadow maps!
				} 
				else if( lightPath.hasFn(MFn::kPointLight) ) 
				{
					for ( unsigned dirOn( 0 ); dirOn < 6; dirOn++ ) 
					{
						thisJob.hasShadowCam = false;
						thisJob.path = lightPath;
						thisJob.name = fnLightNode.name();
						thisJob.isShadow = true;
						thisJob.isShadowPass = false;
						thisJob.isPoint = true;
						thisJob.pointDir = ( PointLightDirection )dirOn;

						// check to see if the midpoint shadow option is used
						thisJob.isMidPointShadow = false;
						liquidGetPlugValue( fnLightNode, "useMidDistDmap", thisJob.isMidPointShadow, status );

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
							liquidGetPlugValue( fnLightShaderNode, "generateMainShadow", computeShadow, status );

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
						MString fileName( generateFileName( ( fileGenMode )fgm_shadow_tex, thisJob ) );
						if( m_lazyCompute ) 
							if( fileExists( fileName ) ) 
								computeShadow = false;
						if( computeShadow ) 
							jobList.push_back( thisJob );
					}
				}
				// if the job has shadow cameras, we will store them here
				//
				if( lightHasShadowCam )
				{
					int isAggregate = thisJob.shadowAggregation;
					for( unsigned i( 0 ); i < shadowCamPath.length(); i++ )
					{
						if( !i && isAggregate )
							thisJob.shadowAggregation = 0;
						else if ( isAggregate )
							thisJob.shadowAggregation = 1;
						else
							thisJob.shadowAggregation = 0;
						thisJob.shadowCamPath = shadowCamPath[ i ];
						thisJob.hasShadowCam = true;

						MFnDependencyNode shadowCamDepNode( shadowCamPath[ i ].node() );
						thisJob.name = shadowCamDepNode.name();
						if( isAggregate )
							thisJob.texName = fnLightNode.name(); //MFnDependencyNode( shadowCamPath[ i ].node() ).name();
						//					else
						//						thisJob.texName = "";
						//						thisJob.name = shadowCamDepNode.name();
						if( liquidGetPlugValue( shadowCamDepNode, "liqShadowResolution", thisJob.width, status ) == MS::kSuccess )
							thisJob.height = thisJob.width;
						liquidGetPlugValue( shadowCamDepNode, "liqMidPointShadow", thisJob.isMidPointShadow, status );
						thisJob.midPointRatio = 0;
						liquidGetPlugValue( shadowCamDepNode, "liqMidPointRatio", thisJob.midPointRatio, status );
						liquidGetPlugValue( shadowCamDepNode, "liqDeepShadows", thisJob.deepShadows, status );
						liquidGetPlugValue( shadowCamDepNode, "liqPixelSamples", thisJob.shadowPixelSamples, status );
						liquidGetPlugValue( shadowCamDepNode, "liqVolumeInterpretation", thisJob.shadowVolumeInterpretation, status );
						liquidGetPlugValue( shadowCamDepNode, "liqEveryFrame", thisJob.everyFrame, status );
						// as previously : this is important as thisJob.renderFrame corresponds to the
						// scene scanning time.
						if( thisJob.everyFrame )
							thisJob.renderFrame = liqglo.liqglo_lframe;
						else
							liquidGetPlugValue( shadowCamDepNode, "liqRenderAtFrame", thisJob.renderFrame, status );
						liquidGetPlugValue( shadowCamDepNode, "liqGeometrySet", thisJob.shadowObjectSet, status );
						liquidGetPlugValue( shadowCamDepNode, "liqShadingRateFactor", thisJob.shadingRateFactor, status );
						// test if the file is already on disk...
						if( m_lazyCompute )
						{
							MString fileName( generateFileName( ( fileGenMode )fgm_shadow_tex, thisJob ) );
							if( fileExists( fileName ) )
								continue;
						}
						jobList.push_back( thisJob );
					}
				}
			} // useDepthMap
			//cout <<thisJob.name.asChar()<<" -> shd:"<<thisJob.isShadow<<" ef:"<<thisJob.everyFrame<<" raf:"<<thisJob.renderFrame<<" set:"<<thisJob.shadowObjectSet.asChar()<<endl;
		} // light dagIterator

		MDagPath cameraPath;
		MItDag dagCameraIterator( MItDag::kDepthFirst, MFn::kCamera, &returnStatus );
		for ( ; !dagCameraIterator.isDone(); dagCameraIterator.next() ) 
		{
			if( !dagCameraIterator.getPath(cameraPath) ) 
				continue;
			bool usesDepthMap( false );
			MFnCamera fnCameraNode( cameraPath );
			liquidGetPlugValue( fnCameraNode, "useDepthMapShadows", usesDepthMap, status );
			if( usesDepthMap && areObjectAndParentsVisible( cameraPath ) ) 
			{
				//
				// We have a shadow job, so find out if we need to use deep shadows,
				// and the pixel sample count
				//
				thisJob.deepShadows = false;
				thisJob.shadowPixelSamples = 1;
				thisJob.shadowVolumeInterpretation = 1;
				fnCameraNode.findPlug( "deepShadows" ).getValue( thisJob.deepShadows );
				// Only use the pixel samples and volume interpretation with deep shadows.
				//
				if( thisJob.deepShadows )
				{
					fnCameraNode.findPlug( "pixelSamples" ).getValue( thisJob.shadowPixelSamples );
					fnCameraNode.findPlug( "volumeInterpretation" ).getValue( thisJob.shadowVolumeInterpretation );
				}

				thisJob.hasShadowCam = true;
				thisJob.shadowCamPath = cameraPath;
				thisJob.path = cameraPath;
				thisJob.name = fnCameraNode.name();
				thisJob.isShadow = true;
				thisJob.isPoint = false;
				thisJob.isShadowPass = false;

				// check to see if the minmax shadow option is used
				thisJob.isMinMaxShadow = false;
				status.clear();
				MPlug liquidMinMaxShadow = fnCameraNode.findPlug( "liquidMinMaxShadow", &status );
				if( status == MS::kSuccess ) 
					liquidMinMaxShadow.getValue( thisJob.isMinMaxShadow );

				// check to see if the midpoint shadow option is used
				thisJob.isMidPointShadow = false;
				status.clear();
				MPlug liquidMidPointShadow = fnCameraNode.findPlug( "useMidDistDmap", &status );
				if( status == MS::kSuccess ) 
					liquidMidPointShadow.getValue( thisJob.isMidPointShadow );

				bool computeShadow( true );
				if( m_lazyCompute ) 
				{
					MString fileName( generateFileName( ( fileGenMode )fgm_shadow_tex, thisJob ) );
					if( fileExists( fileName ) ) continue;
				}

				if( computeShadow ) 
					jobList.push_back( thisJob );
			}
		} // camera dagIterator
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
	MFnCamera fnCameraNode( cameraPath );
	thisJob.renderFrame   = liqglo.liqglo_lframe;
	thisJob.everyFrame    = true;
	thisJob.isPoint       = false;
	thisJob.path          = cameraPath;
	thisJob.name          = fnCameraNode.name();
	thisJob.isShadow      = false;
	thisJob.skip          = false;
	thisJob.name         += "SHADOWPASS";
	thisJob.isShadowPass  = true;
	if( m_outputShadowPass ) 
		jobList.push_back( thisJob );

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
			else if( !thisJob.everyFrame && ( liqglo.liqglo_noSingleFrameShadows || liqglo.liqglo_lframe > frameNumbers[ 0 ] && thisJob.renderFrame != liqglo.liqglo_lframe ) )
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
	}

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
	struct liqGlobalVariable &liqglo__,
	liqRenderScript &jobScript__
	)
{	
	int currentBlock( 0 );
	liqShaderFactory::instance().clearShaders();

	liqglo__.liqglo_lframe = frameNumbers[ frameIndex ];

	if( m_showProgress ) 
		printProgress( 1, frameNumbers.size(), frameIndex );

	liqRenderScript::Job frameScriptJob;

	m_alfShadowRibGen = false;
	liqglo__.liqglo_preReadArchive.clear();
	liqglo__.liqglo_preRibBox.clear();
	liqglo__.liqglo_preReadArchiveShadow.clear();
	liqglo__.liqglo_preRibBoxShadow.clear();

	// make sure all the global strings are parsed for this frame
	const MString frameRenderCommand( parseString( liqglo__.liquidRenderer.renderCommand + " " + liqglo__.liquidRenderer.renderCmdFlags, false ));
	const MString frameRibgenCommand(parseString( m_ribgenCommand, false ));
	const MString framePreCommand(parseString( m_preCommand, false));
	const MString framePreFrameCommand(parseString( m_preFrameCommand, false ));
	const MString framePostFrameCommand(parseString( m_postFrameCommand, false ));

	if( useRenderScript ) 
	{
		if( m_deferredGen ) 
		{
			if( ( frameIndex % m_deferredBlockSize ) == 0 ) 
			{
				if( m_deferredBlockSize == 1 ) 
					currentBlock = liqglo__.liqglo_lframe;
				else 
					currentBlock++;

				liqRenderScript::Job deferredJob;
				addDefferedJob(deferredJob, currentBlock, frameIndex,
					framePreCommand, frameRibgenCommand, liqglo__.tempDefname			
					);
				jobScript__.addJob(deferredJob);
			}
		}//if( m_deferredGen )
		if( !m_justRib ) 
		{
			stringstream titleStream;
			titleStream << liqglo__.liqglo_sceneName.asChar() << "Frame" << liqglo__.liqglo_lframe;
			frameScriptJob.title = titleStream.str();

			if( m_deferredGen ) 
			{
				stringstream ss;
				ss << liqglo__.liqglo_sceneName.asChar() << "FrameRIBGEN" << currentBlock;
				liqRenderScript::Job instanceJob;
				instanceJob.isInstance = true;
				instanceJob.title = ss.str();
				frameScriptJob.childJobs.push_back(instanceJob);
			}
		}
	}//if( useRenderScript ) 

	//***************************************************************
	LIQDEBUGPRINTF( "-> building jobs\n" );
	// Hmmmmmm not really clean ....
	if( buildJobs__() != MS::kSuccess ) 
		return TCB_Break;//break;
	//***************************************************************

	if( !m_deferredGen ) 
	{
		if( m_showProgress ) 
			printProgress( 2, frameNumbers.size(), frameIndex );

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
						scanScene( liqglo__.liqglo_sampleTimes[ msampleOn ] , msampleOn );
				} else {
					liqglo__.liqglo_sampleTimes[ 0 ] = scanTime;
					liqglo__.liqglo_sampleTimesOffsets[ 0 ] = 0;
					scanScene( scanTime, 0 );
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

			// build the shadow archive name for the job
			{
				bool renderAllFrames( liqglo__.liqglo_currentJob.everyFrame );
				long refFrame( liqglo__.liqglo_currentJob.renderFrame );
				MString geoSet( liqglo__.liqglo_currentJob.shadowObjectSet );
				baseShadowName = generateShadowArchiveName( renderAllFrames, refFrame, geoSet );
				baseShadowName = liquidGetRelativePath( liqglo__.liqglo_relativeFileNames, baseShadowName, liqglo__.liqglo_ribDir );
			}

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
			if( liqglo__.liqglo_currentJob.isShadow && !liqglo__.liqglo_currentJob.shadowArchiveRibDone && !fullShadowRib ) 
			{
				//
				//  create the read-archive shadow files
				//
#ifndef RENDER_PIPE
				liquidMessage( "Beginning RIB output to '" + string( baseShadowName.asChar() ) + "'", messageInfo );
				RiBegin( const_cast< RtToken >( baseShadowName.asChar() ) );
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
				if( worldPrologue() != MS::kSuccess ) 
					break;
				if( liqglo__.liqglo_currentJob.isShadow && liqglo__.liqglo_currentJob.deepShadows && m_outputLightsInDeepShadows ) 
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
				fclose( liqglo__.liqglo_ribFP );
#endif
				liqglo__.liqglo_ribFP = NULL;

				// mark all other jobs with the same set as done
				vector<structJob>::iterator iterCheck = jobList.begin();
				while ( iterCheck != jobList.end() ) 
				{
					if( iterCheck->shadowObjectSet == liqglo__.liqglo_currentJob.shadowObjectSet &&
						iterCheck->everyFrame == liqglo__.liqglo_currentJob.everyFrame &&
						iterCheck->renderFrame == liqglo__.liqglo_currentJob.renderFrame
						)
						iterCheck->shadowArchiveRibDone = true;
					++iterCheck;
				}

				m_alfShadowRibGen = true;
			}//if( liqglo_currentJob.isShadow && !liqglo_currentJob.shadowArchiveRibDone && !fullShadowRib ) 

#ifndef RENDER_PIPE
			liquidMessage( "Beginning RIB output to '" + string( liqglo__.liqglo_currentJob.ribFileName.asChar() ) + "'", messageInfo );
			RiBegin( const_cast< RtToken >( liqglo__.liqglo_currentJob.ribFileName.asChar() ) );

#ifdef DELIGHT
			LIQDEBUGPRINTF( "-> setting binary option\n" );
			{
				RtString format[1] = {"ascii"};
				if( liqglo__.liqglo_doBinary ) 
					format[0] = "binary";
				RiOption( "rib", "format", ( RtPointer )&format, RI_NULL);
			}
#endif
#else
			liqglo__.liqglo_ribFP = fopen( liqglo__.liqglo_currentJob.ribFileName.asChar(), "w" );
			if( liqglo__.liqglo_ribFP ) 
			{
				RtInt ribFD = fileno( liqglo__.liqglo_ribFP );
				RiOption( ( RtToken )"rib", ( RtToken )"pipe", &ribFD, RI_NULL );
			} 
			else
			{
				liquidMessage( "Error opening RIB -- writing to stdout.\n", messageError );
			}

			liquidMessage( "Beginning RI output directly to renderer", messageInfo );
			RiBegin( RI_NULL );
#endif
			if( liqglo__.liqglo_currentJob.isShadow && !fullShadowRib ) 
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
					if( !liqglo__.liqglo_currentJob.isShadow || ( liqglo__.liqglo_currentJob.isShadow && liqglo__.liqglo_currentJob.deepShadows && m_outputLightsInDeepShadows) ) 
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
					cout <<"Finished RIB generation "<<liqglo__.liqglo_currentJob.ribFileName.asChar()<<endl;
				}
			}
			RiEnd();
#ifdef RENDER_PIPE
			fclose( liqglo_ribFP );
#endif
			liqglo__.liqglo_ribFP = NULL;
			if( m_showProgress ) 
				printProgress( 3, frameNumbers.size(), frameIndex );
		}//for (; iter != jobList.end(); ++iter ) 
	}//if( !m_deferredGen ) 

	// set the rib file for the 'view last rib' menu command
	// NOTE: this may be overridden later on in certain code paths
	//- omitted temporarily
	//if( !m_deferredGen )
	//	lastRibName = liqglo__.liqglo_currentJob.ribFileName;
	// now we re-iterate through the job list to write out the alfred file if we are using it
	if( useRenderScript && !m_justRib ) 
	{
		bool alf_textures = false;
		bool alf_shadows = false;
		bool alf_refmaps = false;

		// write out make texture pass
		LIQDEBUGPRINTF( "-> Generating job for MakeTexture pass\n");
		if( txtList.size() ) 
		{
			liqRenderScript::Job textureJob;
			makeTexturePass(txtList, textureJob, 
				alf_textures, alf_shadows, alf_refmaps 
				);
			frameScriptJob.childJobs.push_back( textureJob );
		}//if( txtList.size() )

		// write out shadows
		if( liqglo__.liqglo_doShadows ) 
		{
			LIQDEBUGPRINTF( "-> writing out shadow information to alfred file.\n" );
			if( shadowList.size() ) 
			{
				liqRenderScript::Job shadowJob;
				makeShadowPass(shadowList, shadowJob, 
					alf_textures, alf_shadows, alf_refmaps, 
					framePreCommand, frameRenderCommand, 
					currentBlock
					);
				frameScriptJob.childJobs.push_back( shadowJob );
			}//if( shadowList.size() )
		}//if( liqglo__.liqglo_doShadows ) 
		LIQDEBUGPRINTF( "-> finished writing out shadow information to render script file.\n" );

		// write out make reflection pass
		if( refList.size() ) 
		{	
			liqRenderScript::Job reflectJob;
			makeReflectionPass(refList, reflectJob, 
				alf_textures, alf_shadows, alf_refmaps
				);
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
		}//if( m_outputHeroPass ) 
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
		}//if( m_outputShadowPass )

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
		}//if( cleanRib || ( framePostFrameCommand != MString( "" ) ) ) 
		if( m_outputHeroPass ) 
			frameScriptJob.chaserCommand = (string( "sho \"" ) + frameJob->imageName.asChar() + "\"" );
		if( m_outputShadowPass ) 
			frameScriptJob.chaserCommand = (string( "sho \"" ) + shadowPassJob->imageName.asChar() + "\"" );
		//- omitted temporarily
		//if( m_outputShadowPass && !m_outputHeroPass ) 
		//	lastRibName = liquidGetRelativePath( liqglo__.liqglo_relativeFileNames, shadowPassJob->ribFileName, liqglo__.liqglo_projectDir );
		//else 
		//	lastRibName = liquidGetRelativePath( liqglo__.liqglo_relativeFileNames, frameJob->ribFileName, liqglo__.liqglo_projectDir );
	}//if( useRenderScript && !m_justRib ) 

	jobScript__.addJob( frameScriptJob );

	if( ( ribStatus != kRibOK ) && !m_deferredGen ) 
		return TCB_Break;//break;

	return TCB_OK;
}