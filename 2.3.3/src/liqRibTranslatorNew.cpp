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
#include "./common/prerequest_maya.h"
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
#include <liqRibCamera.h>

#include "common/mayacheck.h"
#include "renderermgr.h"
#include "shadergraph/shadermgr.h"

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

#if defined(_WIN32)/* && !defined(DEFINED_LIQUIDVERSION)*/
// unix build gets this from the Makefile
extern const char *LIQUIDVERSION;
#endif

liqRibTranslator* liqRibTranslator::mInstance = NULL;

/**
* This method actually does the renderman output.
*/
MStatus liqRibTranslator::_doItNew( const MArgList& args , const MString& originalLayer )
{
	// append the progress flag for render job feedback
	if( useRenderScript ) 
		if( ( m_renderCommand == MString( "render" ) ) || ( m_renderCommand == MString( "prman" ) ) || ( m_renderCommand == MString( "renderdl" ) ) ) 
			m_renderCommand = m_renderCommand + " -Progress";

	if( !liqglo.m_deferredGen && m_justRib ) 
		useRenderScript = false;
	liquidMessage2(messageInfo,"useRenderScript=%d", useRenderScript);

	if(useRenderScript){
		return _doItNewWithRenderScript(args, originalLayer);
	}else{
		return _doItNewWithoutRenderScript(args, originalLayer);
	}

}
//
void liqRibTranslator::calaculateSamplingTime(const long scanTime__)
{
	float sampleinc( ( liqglo.liqglo_shutterTime * m_blurTime ) / ( liqglo.liqglo_motionSamples - 1 ) );
	for ( unsigned msampleOn( 0 ); msampleOn < liqglo.liqglo_motionSamples; msampleOn++ ) 
	{
		float subframe;
		switch( liqglo.shutterConfig ) 
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
				currentShader.buildJobs();
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

	structJob thisJob;
	{
		tRibCameraMgr::gatherDataForJob(
			liqglo, thisJob, jobList,
			m_outputShadowPass, m_outputHeroPass
		);
	}

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
			structJob/*liqglo__.liqglo_*/ &currentJob = *iter;

			if( /*liqglo__.liqglo_*/currentJob.skip ) 
				continue;

			//cout <<">> outputing job ["<<liqglo_lframe<<"] ->"<<liqglo_currentJob.name.asChar()<<" -> "<<liqglo_currentJob.imageName.asChar()<<endl;
			// set the scan time based on the job's render frame
			//
			scanTime = /*liqglo__.liqglo_*/currentJob.renderFrame;
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
				if( liqglo.doCameraMotion || liqglo__.liqglo_doMotion || liqglo__.liqglo_doDef ) 
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
				//liqglo__.liqglo_currentJob = *iter;
			}
			//
			// start scene parsing ------------------------------------------------------------------
			//
			if( /*liqglo__.liqglo_*/currentJob.isShadowPass ) 
				liqglo__.liqglo_isShadowPass = true;
			else 
				liqglo__.liqglo_isShadowPass = false;


			//************************************************************************************
			LIQDEBUGPRINTF( "-> setting RiOptions\n" );
			//************************************************************************************
			
			liquid::RendererMgr::getInstancePtr()->
				getRenderer()->setRenderScriptFormatAndCompress(liqglo__.liqglo_doBinary, liqglo__.liqglo_doCompression);

			// world RiReadArchives and Rib Boxes ************************************************
			//
			if( /*liqglo__.liqglo_*/currentJob.isShadow && !liqglo.fullShadowRib )
			{
				tShadowRibWriterMgr shadowRibWriterMgr;
				TempControlBreak tcb = 
					shadowRibWriterMgr.write(
					liqglo__, 
					/*liqglo__.liqglo_*/currentJob, 
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
					/*liqglo__.liqglo_*/currentJob, 
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
	liquid::RendererMgr::getInstancePtr()->getRenderer()->doRenderView();
}
//
void liqRibTranslator::doTextures(const std::vector<structJob> &txtList_)
{
	liquid::RendererMgr::getInstancePtr()->getRenderer()->doTextures(txtList_);
}
//
void liqRibTranslator::doShadows(const std::vector<structJob> &shadowList_)
{
	liquid::RendererMgr::getInstancePtr()->getRenderer()->doShadows(shadowList_);
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

	returnStatus__ = tLightMgr::buildShadowJob(thisJob__, m_lazyCompute);

	returnStatus__ = tLightMgr::buildShadowCameraJob(thisJob__, m_lazyCompute);


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
				iter__->width = liqglo.cam_width;
				iter__->height = liqglo.cam_height;
				// scanScene: Renderman specifies shutter by time open
				// so we need to convert shutterAngle to time.
				// To do this convert shutterAngle to degrees and
				// divide by 360.
				//
				iter__->camera[sample__].shutter = fnCamera.shutterAngle() * 0.5 / M_PI;
				liqglo.liqglo_shutterTime = iter__->camera[sample__].shutter;
				iter__->camera[sample__].orthoWidth     = fnCamera.orthoWidth();
				iter__->camera[sample__].orthoHeight    = fnCamera.orthoWidth() * ((float)liqglo.cam_height / (float)liqglo.cam_width);
				iter__->camera[sample__].motionBlur     = fnCamera.isMotionBlur();
				iter__->camera[sample__].focalLength    = fnCamera.focalLength();
				iter__->camera[sample__].focalDistance  = fnCamera.focusDistance();
				iter__->camera[sample__].fStop          = fnCamera.fStop();
				iter__->camera[sample__].name           = fnCamera.fullPathName();

				// film back offsets
				double hSize, vSize, hOffset, vOffset;
				fnCamera.getFilmFrustum( fnCamera.focalLength(), hSize, vSize, hOffset, vOffset );

				double imr = ((float)liqglo.cam_width / (float)liqglo.cam_height);
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
				if( liqglo.liqglo_rotateCamera == true ) 
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
				iter__->camera[sample__].hFOV = fnCamera.horizontalFieldOfView()/liqglo.fov_ratio;
				iter__->aspectRatio = liqglo.aspectRatio;

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
					iter__->format = liqglo.outFormat;
				}
				boolPlug = fnCamera.findPlug( "mask" );
				boolPlug.getValue( isOn );
				if( isOn ) 
				{
					// We are writing alpha channel info
					//
					iter__->imageMode += "a";
					iter__->format = liqglo.outFormat;
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
		iter__->camera[sample__].name        = fnCamera.fullPathName();

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
	iter__->camera[sample__].name= fnLight.fullPathName();
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
MStatus liqRibTranslator::ribPrologue__(const structJob &currentJob)
{
	if( liqglo.m_exportReadArchive ) 
	{
		ribStatus = kRibBegin;
		return MS::kSuccess;
	}

	//user
	char* user = NULL;
#ifndef _WIN32
	uid_t userId = getuid();
	struct passwd *userPwd = getpwuid( userId );
	user = userPwd->pw_name;
#else
	user = getenv("USERNAME");
#endif

	//time
	time_t now;
	time( &now );

	liquid::RendererMgr::getInstancePtr()->getRenderer()->ribPrologue_comment(
		LIQUIDVERSION,
		(liqglo.liqglo_projectDir + liqglo.liqglo_sceneName).asChar(),
		user, now
		);

	liquid::RendererMgr::getInstancePtr()->getRenderer()->ribPrologue_begin(currentJob);

	liquid::RendererMgr::getInstancePtr()->getRenderer()->ribPrologue_options(currentJob);

	ribStatus = kRibBegin;
	return MS::kSuccess;
}

//
MStatus liqRibTranslator::ribEpilogue__(const structJob &currentJob)
{
	liquid::RendererMgr::getInstancePtr()->getRenderer()->ribPrologue_end(currentJob);

	if(ribStatus == kRibBegin) 
		ribStatus = kRibOK;
	return (ribStatus == kRibOK ? MS::kSuccess : MS::kFailure);
}
//
MStatus liqRibTranslator::framePrologue__( long lframe, const structJob &currentJob)
{
	LIQDEBUGPRINTF( "-> Beginning Frame Prologue__\n" );
	ribStatus = kRibFrame;

	if( liqglo.m_exportReadArchive )
	{
		return MS::kSuccess;
	}
	liquid::RendererMgr::getInstancePtr()->getRenderer()->framePrologue(lframe, currentJob);



	return MS::kSuccess;
}
//
MStatus liqRibTranslator::worldPrologue__(const structJob &currentJob)
{
	return liquid::RendererMgr::getInstancePtr()->getRenderer()->worldPrologue(currentJob);
}

//
MStatus liqRibTranslator::lightBlock__(const structJob &currentJob)
{
	MStatus returnStatus = MS::kSuccess;
	LIQDEBUGPRINTF( "-> Writing lights.\n" );
	// If this is a readArchive that we are exporting then ignore this header information
	if( !liqglo.m_exportReadArchive )
	{
		RNMAP::iterator rniter;
		int nbLight = 0;
		for ( rniter = htable->RibNodeMap.begin(); rniter != htable->RibNodeMap.end(); rniter++ )
		{
			LIQ_CHECK_CANCEL_REQUEST;
			liqRibNodePtr   ribNode = (*rniter).second;

			if( ribNode->object(0)->ignore || ribNode->object(0)->type != MRT_Light )
				continue;

			liquid::RendererMgr::getInstancePtr()->
				getRenderer()->exportLight(ribNode, currentJob);
		
			nbLight++;
		}
	}
	return returnStatus;
}

//
MStatus liqRibTranslator::coordSysBlock__(const structJob &currentJob)
{
	MStatus returnStatus = MS::kSuccess;
	LIQDEBUGPRINTF( "-> Writing coordinate systems.\n" );
	RNMAP::iterator rniter;
	for ( rniter = htable->RibNodeMap.begin(); rniter != htable->RibNodeMap.end(); rniter++ ) 
	{
		LIQ_CHECK_CANCEL_REQUEST;
		liqRibNodePtr   ribNode = (*rniter).second;
		if( ribNode->object(0)->ignore || ribNode->object(0)->type != MRT_Coord ) 
			continue;
		if( liqglo.m_outputComments )
			RiArchiveRecord( RI_COMMENT, "Name: %s", ribNode->name.asChar(), RI_NULL );

		RiAttributeBegin();
		RiAttribute( "identifier", "name", &getLiquidRibName( ribNode->name.asChar() ), RI_NULL );

		RtMatrix ribMatrix;
		MMatrix matrix;
		MDagPath path;

		matrix = ribNode->object(0)->matrix( path.instanceNumber() );
		matrix.get( ribMatrix );
		if( liqglo.liqglo_relativeTransforms ) 
			RiConcatTransform( ribMatrix ); 
		else 
			RiTransform( ribMatrix );

		ribNode->object(0)->writeObject("", currentJob);
		ribNode->object(0)->written = 1;
		RiAttributeEnd();
	}
	return returnStatus;
}

//
//
MStatus liqRibTranslator::preGeometryMel()
{
	// Moritz: Added Pre-Geometry RIB for insertion right before any primitives
	MFnDependencyNode globalsNode( liqglo.rGlobalObj );
	MPlug prePostplug( globalsNode.findPlug( "preGeomMel" ) );
	MString melcommand( prePostplug.asString() );
	if( m_preGeomRIB != "" || melcommand.length() )
	{
		RiArchiveRecord( RI_COMMENT,  " Pre-Geometry RIB from liquid globals");
		MGlobal::executeCommand( melcommand );
		RiArchiveRecord( RI_VERBATIM, ( char* ) m_preGeomRIB.asChar() );
		RiArchiveRecord( RI_VERBATIM, "\n");
	}
	return MS::kSuccess;
}
MStatus liqRibTranslator::postGeometryMel()
{
	return MS::kSuccess;
}
// retrieve the shadow set object
MObject liqRibTranslator::getShadowSetObject(const structJob &currentJob)
{	
	MStatus status;
	MObject shadowSetObj;
	if( currentJob.isShadow && currentJob.shadowObjectSet != "" ) 
	{
		MObject tmp;
		tmp = getNodeByName( currentJob.shadowObjectSet, &status );
		if( status == MS::kSuccess ) 
			shadowSetObj = tmp;
		else 
		{
			MString warn;
			warn += "Liquid : set " + currentJob.shadowObjectSet + " in shadow " + currentJob.name + " does not exist !";
			MGlobal:: displayWarning( warn );
			cout << warn.asChar() << endl;
		}
		status.clear();
	}
	return shadowSetObj;
}
MStatus liqRibTranslator::preTransformMel(const MObject &transform__)
{
	// Alf: preTransformMel
	MFnDagNode fnTransform( transform__ );
	MPlug prePostPlug = fnTransform.findPlug( "liqPreTransformMel" );
	m_preTransformMel = prePostPlug.asString();

	if( m_preTransformMel != "" )
		MGlobal::executeCommand( m_preTransformMel );
	
	return MS::kSuccess;
}
MStatus liqRibTranslator::postTransformMel(const MObject &transform__)
{
	// Alf: postTransformMel
	MFnDagNode fnTransform( transform__ );
	MPlug prePostPlug = fnTransform.findPlug( "liqPostTransformMel" );
	m_postTransformMel = prePostPlug.asString();
	if( m_postTransformMel != "" )
		MGlobal::executeCommand( m_postTransformMel );
	return MS::kSuccess;
}
//
MStatus liqRibTranslator::tRiIlluminate(const structJob &currentJob__, const liqRibNodePtr ribNode__)
{
	// Moritz: only write out light linking if we're not in a shadow pass

		MObjectArray linkLights;

		// light linking mode - Alf
		// inclusive - lights are off by default and objects list included lights
		// exclusive - lights are on by default and objects list ignored lights
		// liquid Light sets - ignores the maya light linker
		if( m_liquidSetLightLinking )
			ribNode__->getSetLights( linkLights );
		else
			ribNode__->getLinkLights( linkLights, liqglo.m_illuminateByDefault );

		for( unsigned i( 0 ); i < linkLights.length(); i++ )
		{
			MFnDagNode lightFnDag( linkLights[i] );
			MString nodeName = lightFnDag.fullPathName();
			if( htable )
			{
				//RibNode * ln = htable->find( light, MRT_Light );
				MDagPath nodeDagPath;
				lightFnDag.getPath( nodeDagPath );
				liqRibNodePtr  ln( htable->find( lightFnDag.fullPathName(), nodeDagPath, MRT_Light ) );
				if( NULL != ln )
				{
					liquid::RendererMgr::getInstancePtr()->
						getRenderer()->exportLightLinks(
						currentJob__, ribNode__, ln, liqglo.m_illuminateByDefault);
				}
			}
		}

	return MS::kSuccess;
}
//
MStatus liqRibTranslator::MaxtrixMotionBlur(const liqRibNodePtr ribNode__, MDagPath &path__, const bool bMotionBlur)
{
	MMatrix matrix;

	if( bMotionBlur)
	{
		LIQDEBUGPRINTF( "-> writing matrix motion blur data\n" );
		// Moritz: replaced RiMotionBegin call with ..V version to allow for more than five motion samples
		if(liqglo.liqglo_relativeMotion)
			RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimesOffsets );
		else
			RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimes );
	}
	RtMatrix ribMatrix;
	matrix = ribNode__->object( 0 )->matrix( path__.instanceNumber() );
	matrix.get( ribMatrix );

	if( liqglo.liqglo_relativeTransforms ) 
		RiConcatTransform( ribMatrix ); else RiTransform( ribMatrix );

	// Output the world matrices for the motionblur
	// This will override the current transformation setting
	if( bMotionBlur)
	{
		path__ = ribNode__->path();
		RtMatrix ribMatrix;
		for( unsigned mm( 1 ); mm < liqglo.liqglo_motionSamples; mm++ ) {
			matrix = ribNode__->object( mm )->matrix( path__.instanceNumber() );
			matrix.get( ribMatrix );
			if( liqglo.liqglo_relativeTransforms ) 
				RiConcatTransform( ribMatrix );
			else 
				RiTransform( ribMatrix );
		}
		RiMotionEnd();
	}
	return MS::kSuccess;
}
MStatus liqRibTranslator::preShapeMel(const MObject &transform__)
{
	// Alf: preShapeMel
	MFnDagNode fnTransform( transform__ );
	MPlug prePostPlug = fnTransform.findPlug( "liqPreShapeMel" );
	m_preShapeMel = prePostPlug.asString();
	if( m_preShapeMel != "" )
		MGlobal::executeCommand( m_preShapeMel );
	return MS::kSuccess;
}
MStatus liqRibTranslator::postShapeMel(const MObject &transform__)
{			
	// Alf: postShapeMel
	MFnDagNode fnTransform( transform__ );
	MPlug prePostPlug = fnTransform.findPlug( "liqPostShapeMel" );
	m_postShapeMel = prePostPlug.asString();
	if( m_postShapeMel != "" )
		MGlobal::executeCommand( m_postShapeMel );

	return MS::kSuccess;
}
MStatus liqRibTranslator::checkSurfaceShader(
	const MDagPath &path__,
	const liqRibNodePtr &ribNode__,
	bool &hasSurfaceShader__,
	liqDetailShaderKind &hasCustomSurfaceShader__,
	 MString &shaderRibBox__)
{
	MStatus status;

	MPlug rmanShaderPlug;
	// Check for surface shader
	status.clear();
	MFnDagNode fnDagNode( path__ );
	rmanShaderPlug = fnDagNode.findPlug( MString( "liquidSurfaceShaderNode" ), &status );
	if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
	{ 
		status.clear(); 
		rmanShaderPlug = ribNode__->assignedShadingGroup.findPlug( MString( "liquidSurfaceShaderNode" ), &status ); 
		MString plugname(rmanShaderPlug.name());
	}
	if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
	{ 
		status.clear(); 
		rmanShaderPlug = ribNode__->assignedShader.findPlug( MString( "liquidSurfaceShaderNode" ), &status ); 
		MString plugname(rmanShaderPlug.name());
	}
	if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
	{ 
		status.clear(); 
		rmanShaderPlug = ribNode__->assignedShadingGroup.findPlug( MString( "surfaceShader" ), &status ); 
		MString plugname(rmanShaderPlug.name());
	}
	if( status == MS::kSuccess && !rmanShaderPlug.isNull() ) 
	{
		if( rmanShaderPlug.isConnected() ) 
		{
			MPlugArray rmShaderNodeArray;
			rmanShaderPlug.connectedTo( rmShaderNodeArray, true, true );
			MObject rmShaderNodeObj;
			rmShaderNodeObj = rmShaderNodeArray[0].node();
			MFnDependencyNode shaderDepNode( rmShaderNodeObj );
			//std::cout <<"path="<<path.fullPathName()<<", shaderDepNode.typeName()="<<shaderDepNode.typeName()<<std::endl;
			// philippe : we must check the node type to avoid checking in regular maya shaders
			if( shaderDepNode.typeName() == "liquidSurface" || shaderDepNode.typeName() == "oldBlindDataBase" ) 
			{ //cout <<"setting shader"<<endl;
				ribNode__->assignedShader.setObject( rmShaderNodeObj );
				hasSurfaceShader__ = true;
			} 
			else 
			{ // Is it a custom shading node ?
				MPxNode *mpxNode = shaderDepNode.userNode();
				liqCustomNode *customNode = NULL;
				if( mpxNode && ( customNode = dynamic_cast<liqCustomNode*>(mpxNode) ) ) 
				{ // customNode will be null if can't be casted to a liqCustomNode
					ribNode__->assignedShader.setObject( rmShaderNodeObj );
					hasSurfaceShader__ = true;
					hasCustomSurfaceShader__ = liqCustomPxShaderNode;
				} 
				else 
				{ // Try to find a liqRIBBox attribute
					MPlug ribbPlug = shaderDepNode.findPlug( MString( "liqRIBBox" ), &status );
					if( status == MS::kSuccess ) 
					{
						ribbPlug.getValue( shaderRibBox__ );
						if( shaderRibBox__.substring(0,2) == "*H*" ) 
						{
							MString parseThis = shaderRibBox__.substring(3, shaderRibBox__.length() - 1 );
							shaderRibBox__ = parseThis;
						} 
						else if( shaderRibBox__.substring(0,3) == "*SH*" ) 
						{
							MString parseThis = shaderRibBox__.substring(3, shaderRibBox__.length() - 1 );
							shaderRibBox__ = parseThis;
						}
						hasSurfaceShader__ = true;
						hasCustomSurfaceShader__ = liqRibBoxShader;
					}
					// else {
					//liquidMessage( "Do noy know how to handle " + string( shaderDepNode.typeName().asChar() ), messageError );
					//}
				}
			}
		}
	}
	return MS::kSuccess;
}
//
MStatus liqRibTranslator::checkDisplacementShader(
								const MDagPath &path__,
								const liqRibNodePtr &ribNode__,
								bool &hasDisplacementShader__ 
								//liqDetailShaderKind &hasCustomSurfaceShader__,
								//MString &shaderRibBox__
								)
{	
	MStatus status;
	MPlug rmanShaderPlug;
	MFnDagNode fnDagNode( path__ );

	status.clear();
	rmanShaderPlug = fnDagNode.findPlug( MString( "liquidDispShaderNode" ), &status );
	if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
	{ 
		status.clear(); 
		rmanShaderPlug = ribNode__->assignedShadingGroup.findPlug( MString( "liquidDispShaderNode" ), &status ); 
	}
	if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
	{ 
		status.clear(); 
		rmanShaderPlug = ribNode__->assignedDisp.findPlug( MString( "liquidDispShaderNode" ), &status ); 
	}
	if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
	{ 
		status.clear(); 
		rmanShaderPlug = ribNode__->assignedShadingGroup.findPlug( MString( "displacementShader" ), &status ); 
	}
	if( ( status == MS::kSuccess ) && !rmanShaderPlug.isNull() && !m_ignoreDisplacements ) 
	{
		if( rmanShaderPlug.isConnected() ) 
		{
			MPlugArray rmShaderNodeArray;
			rmanShaderPlug.connectedTo( rmShaderNodeArray, true, true );
			MObject rmShaderNodeObj;
			rmShaderNodeObj = rmShaderNodeArray[0].node();
			MFnDependencyNode shaderDepNode( rmShaderNodeObj );
			// philippe : we must check the node type to avoid checking in regular maya shaders
			if( shaderDepNode.typeName() == "liquidDisplacement" || shaderDepNode.typeName() == "oldBlindDataBase" ) 
			{
				ribNode__->assignedDisp.setObject( rmShaderNodeObj );
				hasDisplacementShader__ = true;
			}
		}
	}
	return MS::kSuccess;
}
//
MStatus liqRibTranslator::checkVolumeShader(
						  const MDagPath &path__, 
						  const liqRibNodePtr &ribNode__,
						  bool &hasVolumeShader__ 
						  //liqDetailShaderKind &hasCustomSurfaceShader__,
						  //MString &shaderRibBox__
						  )
{	
	MStatus status;
	MPlug rmanShaderPlug;
	MFnDagNode fnDagNode( path__ );

	status.clear();
	rmanShaderPlug = fnDagNode.findPlug( MString( "liquidVolumeShaderNode" ), &status );
	if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
	{ 
		status.clear(); 
		rmanShaderPlug = ribNode__->assignedShadingGroup.findPlug( MString( "liquidVolumeShaderNode" ), &status ); 
	}
	if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
	{ 
		status.clear(); 
		rmanShaderPlug = ribNode__->assignedVolume.findPlug( MString( "liquidVolumeShaderNode" ), &status ); 
	}
	if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
	{ 
		status.clear(); 
		rmanShaderPlug = ribNode__->assignedShadingGroup.findPlug( MString( "volumeShader" ), &status ); 
	}
	if( ( status == MS::kSuccess ) && !rmanShaderPlug.isNull() && !m_ignoreVolumes ) 
	{
		if( rmanShaderPlug.isConnected() ) 
		{
			MPlugArray rmShaderNodeArray;
			rmanShaderPlug.connectedTo( rmShaderNodeArray, true, true );
			MObject rmShaderNodeObj;
			rmShaderNodeObj = rmShaderNodeArray[0].node();
			MFnDependencyNode shaderDepNode( rmShaderNodeObj );
			// philippe : we must check the node type to avoid checking in regular maya shaders
			if( shaderDepNode.typeName() == "liquidVolume" || shaderDepNode.typeName() == "oldBlindDataBase" ) 
			{
				ribNode__->assignedVolume.setObject( rmShaderNodeObj );
				hasVolumeShader__ = true;
			}
		}
	}
	return MS::kSuccess;
}
//
MStatus liqRibTranslator::displacementBounds(const liqRibNodePtr &ribNode__)
{
	MStatus status;

	float surfaceDisplacementBounds = 0.0;
	MString surfaceDisplacementBoundsSpace = "shader";
	MString tmpSpace = "";
	status.clear();
	if( !ribNode__->assignedShader.object().isNull() ) 
	{
		MPlug sDBPlug = ribNode__->assignedShader.findPlug( MString( "displacementBound" ), &status );
		if( status == MS::kSuccess ) 
			sDBPlug.getValue( surfaceDisplacementBounds );
		MPlug sDBSPlug = ribNode__->assignedShader.findPlug( MString( "displacementBoundSpace" ), &status );
		if( status == MS::kSuccess ) 
			sDBSPlug.getValue( tmpSpace );
		if( tmpSpace != "" ) 
			surfaceDisplacementBoundsSpace = tmpSpace;
	}
	float dispDisplacementBounds = 0.0;
	MString dispDisplacementBoundsSpace = "shader";
	tmpSpace = "";
	status.clear();
	if( !ribNode__->assignedDisp.object().isNull() ) 
	{
		MPlug dDBPlug = ribNode__->assignedDisp.findPlug( MString( "displacementBound" ), &status );
		if( status == MS::kSuccess ) 
			dDBPlug.getValue( dispDisplacementBounds );
		MPlug sDBSPlug = ribNode__->assignedDisp.findPlug( MString( "displacementBoundSpace" ), &status );
		if( status == MS::kSuccess ) 
			sDBSPlug.getValue( tmpSpace );
		if( tmpSpace != "" ) 
			dispDisplacementBoundsSpace = tmpSpace;
	}
	if( ( dispDisplacementBounds != 0.0 ) && ( dispDisplacementBounds > surfaceDisplacementBounds ) ) 
	{
		RtString coordsys( const_cast< char* >( dispDisplacementBoundsSpace.asChar() ) );
		RiAttribute( "displacementbound", (RtToken) "sphere", &dispDisplacementBounds, "coordinatesystem", &coordsys, RI_NULL );
	} 
	else if( ( surfaceDisplacementBounds != 0.0 ) ) 
	{
		RtString coordsys( const_cast< char* >( surfaceDisplacementBoundsSpace.asChar() ) );
		RiAttribute( "displacementbound", (RtToken) "sphere", &surfaceDisplacementBounds, "coordinatesystem", &coordsys, RI_NULL );
	}
	return MS::kSuccess;
}
//
MStatus liqRibTranslator::objectShadowAttribute(const liqRibNodePtr &ribNode__)
{

	return MS::kSuccess;
}

MStatus liqRibTranslator::objectNonShadowAttribute(const liqRibNodePtr &ribNode__)
{
	RtInt off( 0 );
	RtInt on( 1 );
	if( !ribNode__->shading.diceRasterOrient ) 
		RiAttribute( "dice", (RtToken) "rasterorient", &off, RI_NULL );
	if( ribNode__->shading.doubleShaded ) 
		RiAttribute( "sides", (RtToken) "doubleshaded", &on, RI_NULL );
	if( liqglo.liquidRenderer.supports_RAYTRACE ) 
	{
		if( ribNode__->trace.sampleMotion ) 
			RiAttribute( "trace", (RtToken) "samplemotion", &on, RI_NULL );
		if( ribNode__->trace.displacements ) 
			RiAttribute( "trace", (RtToken) "displacements", &on, RI_NULL );
		if( ribNode__->trace.bias != 0.01f ) 
		{
			RtFloat bias( ribNode__->trace.bias );
			RiAttribute( "trace", (RtToken) "bias", &bias, RI_NULL );
		}
		if( ribNode__->trace.maxDiffuseDepth != 1 ) 
		{
			RtInt mddepth( ribNode__->trace.maxDiffuseDepth );
			RiAttribute( "trace", (RtToken) "maxdiffusedepth", &mddepth, RI_NULL );
		}
		if( ribNode__->trace.maxSpecularDepth != 2 ) 
		{
			RtInt msdepth( ribNode__->trace.maxSpecularDepth );
			RiAttribute( "trace", (RtToken) "maxspeculardepth", &msdepth, RI_NULL );
		}
	}
	if( !ribNode__->visibility.camera ) 
		RiAttribute( "visibility", (RtToken) "camera", &off, RI_NULL );

	// old-style raytracing visibility support
	// philippe: if raytracing is off in the globals, trace visibility is turned off for all objects, transmission is set to TRANSPARENT for all objects
	if( liqglo.liquidRenderer.supports_RAYTRACE && !liqglo.liquidRenderer.supports_ADVANCED_VISIBILITY ) 
	{
		if( liqglo.rt_useRayTracing && ribNode__->visibility.trace ) {
			RtInt on( 1 );
			RiAttribute( "visibility", (RtToken) "trace", &on, RI_NULL );
		}
		if( liqglo.rt_useRayTracing && ribNode__->visibility.transmission != liqRibNode::visibility::TRANSMISSION_TRANSPARENT ) 
		{
			RtString trans;
			switch( ribNode__->visibility.transmission ) 
			{
			case liqRibNode::visibility::TRANSMISSION_OPAQUE:
				trans = "opaque";
				break;
			case liqRibNode::visibility::TRANSMISSION_OS:
				trans = "Os";
				break;
			case liqRibNode::visibility::TRANSMISSION_SHADER:
			default:
				trans = "shader";
			}
			RiAttribute( "visibility", (RtToken) "string transmission", &trans, RI_NULL );
		}
	}
	// philippe : prman 12.5 visibility support
#ifdef GENERIC_RIBLIB      
	extern int useAdvancedVisibilityAttributes;
	useAdvancedVisibilityAttributes = false;
#endif
	if( liqglo.liquidRenderer.supports_RAYTRACE && liqglo.liquidRenderer.supports_ADVANCED_VISIBILITY ) 
	{
		RtInt on( 1 );
		RtString mode;
#ifdef GENERIC_RIBLIB         
		useAdvancedVisibilityAttributes = true;
#endif
		if( liqglo.rt_useRayTracing && ribNode__->visibility.diffuse ) 
			RiAttribute( "visibility", (RtToken) "int diffuse", &on, RI_NULL );

		if( liqglo.rt_useRayTracing && ribNode__->visibility.specular ) 
			RiAttribute( "visibility", (RtToken) "int specular", &on, RI_NULL );

		if( liqglo.rt_useRayTracing && ribNode__->visibility.newtransmission ) 
			RiAttribute( "visibility", (RtToken) "int transmission", &on, RI_NULL );

		if( liqglo.rt_useRayTracing && ribNode__->visibility.camera ) 
			RiAttribute( "visibility", (RtToken) "int camera", &on, RI_NULL );

		if( liqglo.rt_useRayTracing && ribNode__->visibility.photon ) 
			RiAttribute( "visibility", (RtToken) "int photon", &on, RI_NULL );

		if( liqglo.rt_useRayTracing && ribNode__->visibility.midpoint ) 
			RiAttribute( "visibility", (RtToken) "int midpoint", &on, RI_NULL );

		if( liqglo.rt_useRayTracing && ribNode__->hitmode.diffuse != liqRibNode::hitmode::DIFFUSE_HITMODE_PRIMITIVE ) 
		{
			switch( ribNode__->hitmode.diffuse ) 
			{
			case liqRibNode::hitmode::DIFFUSE_HITMODE_SHADER:
				mode = "shader";
				break;
			case liqRibNode::hitmode::DIFFUSE_HITMODE_PRIMITIVE:
			default:
				mode = "primitive";
			}
			RiAttribute( "shade", (RtToken) "string diffusehitmode", &mode, RI_NULL );
		}

		if( liqglo.rt_useRayTracing && ribNode__->hitmode.specular != liqRibNode::hitmode::SPECULAR_HITMODE_SHADER ) 
		{
			switch( ribNode__->hitmode.specular ) 
			{
			case liqRibNode::hitmode::SPECULAR_HITMODE_PRIMITIVE:
				mode = "primitive";
				break;
			case liqRibNode::hitmode::SPECULAR_HITMODE_SHADER:
			default:
				mode = "shader";
			}
			RiAttribute( "shade", (RtToken) "string specularhitmode", &mode, RI_NULL );
		}

		if( liqglo.rt_useRayTracing && ribNode__->hitmode.transmission != liqRibNode::hitmode::TRANSMISSION_HITMODE_SHADER ) 
		{
			switch( ribNode__->hitmode.transmission ) 
			{
			case liqRibNode::hitmode::TRANSMISSION_HITMODE_PRIMITIVE:
				mode = "primitive";
				break;
			case liqRibNode::hitmode::TRANSMISSION_HITMODE_SHADER:
			default:
				mode = "shader";
			}
			RiAttribute( "shade", (RtToken) "string transmissionhitmode", &mode, RI_NULL );
		}

		if( ribNode__->hitmode.camera != liqRibNode::hitmode::CAMERA_HITMODE_SHADER ) 
		{
			switch( ribNode__->hitmode.camera ) 
			{
			case liqRibNode::hitmode::CAMERA_HITMODE_PRIMITIVE:
				mode = "primitive";
				break;
			case liqRibNode::hitmode::CAMERA_HITMODE_SHADER:
			default:
				mode = "shader";
			}
			RiAttribute( "shade", (RtToken) "string camerahitmode", &mode, RI_NULL );
		}
	}

	if( liqglo.liquidRenderer.supports_RAYTRACE ) 
	{
		if( ribNode__->irradiance.shadingRate != 1.0f ) 
		{
			RtFloat rate = ribNode__->irradiance.shadingRate;
			RiAttribute( "irradiance", (RtToken) "shadingrate", &rate, RI_NULL );
		}

		if( ribNode__->irradiance.nSamples != 64 ) 
		{
			RtInt samples = ribNode__->irradiance.nSamples;
			RiAttribute( "irradiance", (RtToken) "nsamples", &samples, RI_NULL );
		}

		if( ribNode__->irradiance.maxError != 0.5f ) 
		{
			RtFloat merror = ribNode__->irradiance.maxError;
			RiAttribute( "irradiance", (RtToken) "float maxerror", &merror, RI_NULL );
		}

		if( ribNode__->irradiance.maxPixelDist != 30.0f ) 
		{
			RtFloat mpd = ribNode__->irradiance.maxPixelDist;
			RiAttribute( "irradiance", (RtToken) "float maxpixeldist", &mpd, RI_NULL );
		}

		if( ribNode__->irradiance.handle != "" ) 
		{
			RtString handle = const_cast< char* >( ribNode__->irradiance.handle.asChar() );
			RiAttribute( "irradiance", (RtToken) "handle", &handle, RI_NULL );
		}

		if( ribNode__->irradiance.fileMode != liqRibNode::irradiance::FILEMODE_NONE ) 
		{
			RtString mode;
			switch( ribNode__->irradiance.fileMode ) 
			{
			case liqRibNode::irradiance::FILEMODE_READ:
				mode = "r";
				break;
			case liqRibNode::irradiance::FILEMODE_WRITE:
				mode = "w";
				break;
			case liqRibNode::irradiance::FILEMODE_READ_WRITE:
			default:
				mode = "rw";
			}
			RiAttribute( "irradiance", (RtToken) "filemode", &mode, RI_NULL );
		}

		if( ribNode__->photon.globalMap != "" ) 
		{
			RtString map = const_cast< char* >( ribNode__->photon.globalMap.asChar() );
			RiAttribute( "photon", (RtToken) "globalmap", &map, RI_NULL );
		}

		if( ribNode__->photon.causticMap != "" ) 
		{
			RtString map = const_cast< char* >( ribNode__->photon.causticMap.asChar() );
			RiAttribute( "photon", (RtToken) "causticmap", &map, RI_NULL );
		}

		if( ribNode__->photon.shadingModel != liqRibNode::photon::SHADINGMODEL_MATTE ) 
		{
			RtString model;
			switch( ribNode__->photon.shadingModel  ) {
			case liqRibNode::photon::SHADINGMODEL_GLASS:
				model = "glass";
				break;
			case liqRibNode::photon::SHADINGMODEL_WATER:
				model = "water";
				break;
			case liqRibNode::photon::SHADINGMODEL_CHROME:
				model = "chrome";
				break;
			case liqRibNode::photon::SHADINGMODEL_TRANSPARENT:
				model = "chrome";
				break;
			case liqRibNode::photon::SHADINGMODEL_DIALECTRIC:
				model = "dielectric";
				break;
			case liqRibNode::photon::SHADINGMODEL_MATTE:
			default:
				model = "matte";
			}
			RiAttribute( "photon", (RtToken) "shadingmodel", &model, RI_NULL );
		}

		if( ribNode__->photon.estimator != 100 ) 
		{
			RtInt estimator = ribNode__->photon.estimator;
			RiAttribute( "photon", (RtToken) "estimator", &estimator, RI_NULL );
		}

	}

	// 3Delight sss group
	if( ribNode__->delightSSS.doScatter && liqglo.liquidRenderer.renderName == MString("3Delight") )
	{
#ifdef GENERIC_RIBLIB         
		useAdvancedVisibilityAttributes = true;
#endif			  
		RtString groupName = const_cast< char* >( ribNode__->delightSSS.groupName.asChar() );
		RiAttribute( "visibility", (RtToken) "string subsurface", &groupName, RI_NULL );

		RtColor scattering, absorption;
		scattering[0] = ribNode__->delightSSS.scattering.r;
		scattering[1] = ribNode__->delightSSS.scattering.g;
		scattering[2] = ribNode__->delightSSS.scattering.b;

		absorption[0] = ribNode__->delightSSS.absorption.r;
		absorption[1] = ribNode__->delightSSS.absorption.g;
		absorption[2] = ribNode__->delightSSS.absorption.b;

		if ( scattering[0] && scattering[1] && scattering[2] )
			RiAttribute( "subsurface",
			(RtToken) "scattering", &scattering,
			(RtToken) "absorption", &absorption,
			RI_NULL );

		RtFloat refractionindex = ribNode__->delightSSS.refraction;
		RtFloat shadingrate = ribNode__->delightSSS.shadingRate;
		RtFloat scale = ribNode__->delightSSS.scale;

		RiAttribute( "subsurface",
			(RtToken) "refractionindex", &refractionindex,
			(RtToken) "shadingrate", &shadingrate,
			(RtToken) "scale", &scale, 
			RI_NULL );

		RtColor meanfreepath, reflectance;
		meanfreepath[0] = ribNode__->delightSSS.meanfreepath.r;
		meanfreepath[1] = ribNode__->delightSSS.meanfreepath.g;
		meanfreepath[2] = ribNode__->delightSSS.meanfreepath.b;

		reflectance[0] = ribNode__->delightSSS.reflectance.r;
		reflectance[1] = ribNode__->delightSSS.reflectance.g;
		reflectance[2] = ribNode__->delightSSS.reflectance.b;

		if ( reflectance[0] && reflectance[1] && reflectance[2] )
			RiAttribute( "subsurface",
			(RtToken) "meanfreepath", &meanfreepath,
			(RtToken) "reflectance", &reflectance, 
			RI_NULL );

		if ( ribNode__->delightSSS.referencecamera != "" )
		{
			RtString referenceCamera = const_cast< char* >( ribNode__->delightSSS.referencecamera.asChar() );
			RiAttribute( "subsurface", (RtToken) "string referencecamera", &referenceCamera, RI_NULL );
		}
	}

	//strategy
	{
		if(ribNode__->strategy.strategy_!="grids"){
			RtString strategy = const_cast<char*>(ribNode__->strategy.strategy_.asChar());
			RiAttribute("shade",(RtToken)"string strategy", &strategy, RI_NULL);
		}

		if(ribNode__->strategy.volumeIntersectionStrategy!="exclusive"){
			RtString volumeIntersectionStrategy = const_cast<char*>(ribNode__->strategy.volumeIntersectionStrategy.asChar());
			RiAttribute("shade",(RtToken)"string volumeintersectionstrategy", &volumeIntersectionStrategy, RI_NULL);
		}

		if(ribNode__->strategy.volumeIntersectionPriority >0.0001){
			RtFloat volumeIntersectionPriority = ribNode__->strategy.volumeIntersectionPriority;
			RiAttribute("shade",(RtToken)"float volumeintersectionpriority", &volumeIntersectionPriority, RI_NULL);
		}
	}

	//trim curve 
	{
		RtString sense = "inside";

		switch(ribNode__->trimcurve.sense){
				case liqRibNode::trimcurve::INSIDE:  
					{
						sense  = "inside";
						//RiAttribute("trimcurve",(RtToken)"string sense", &sense, RI_NULL);//default value, need not to write.
					}break;
				case liqRibNode::trimcurve::OUTSIDE:
					{
						sense  = "outside";
						RiAttribute("trimcurve",(RtToken)"string sense", &sense, RI_NULL);	
					}break;
				default:
					assert(0);
		}

	}//trim curve 

	//stitch
	{
		if( ribNode__->stitch.enable != true ){
			RtInt enable = (ribNode__->stitch.enable)? 1: 0;
			RiAttribute("stitch",(RtToken)"int enable", &enable, RI_NULL);	
		}
		if( ribNode__->stitch.traceenable != false ){
			RtInt traceenable = (ribNode__->stitch.traceenable)? 1: 0;
			RiAttribute("stitch",(RtToken)"int traceenable", &traceenable, RI_NULL);	
		}
		if( ribNode__->stitch.newgroup != false ){
			RtInt newgroup = (ribNode__->stitch.newgroup)? 1: 0;
			RiAttribute("stitch",(RtToken)"int newgroup", &newgroup, RI_NULL);	
		}	
	}//stitch

	//stochastic
	{
		if( ribNode__->stochastic.sigma != 0 ){
			RtInt sigma = ribNode__->stochastic.sigma;
			RiAttribute("stochastic",(RtToken)"int sigma", &sigma, RI_NULL);	
		}
		if( ribNode__->stochastic.pointfalloff != 0 ){
			RtInt pointfalloff = ribNode__->stochastic.pointfalloff;
			RiAttribute("stochastic",(RtToken)"int pointfalloff", &pointfalloff, RI_NULL);	
		}
	}//stochastic

	//dice
	{
		if( ribNode__->dice.binary != 0 ){
			RtInt binary = ribNode__->dice.binary;
			RiAttribute("dice",(RtToken)"int binary", &binary, RI_NULL);
		}
		if( ribNode__->dice.hair != 0 ){
			RtInt hair = ribNode__->dice.hair;
			RiAttribute("dice",(RtToken)"int hair", &hair, RI_NULL);
		}
		//strategy
		RtString strategy = "planarprojection";
		switch(ribNode__->dice.strategy){
				  case liqRibNode::dice::PLANAR_PROJECTION:
					  {
						  strategy = "planarprojection";
						  //RiAttribute("dice",(RtToken)"string strategy", &strategy, RI_NULL); //default value
					  }break;
				  case liqRibNode::dice::SPHERICAL_PROJECTION:
					  {
						  strategy = "sphericalprojection";
						  RiAttribute("dice",(RtToken)"string strategy", &strategy, RI_NULL);
					  }break;
				  default:
					  assert(0);
		}
		//referencecamera
		RtString referencecamera = "worldcamera";
		switch(ribNode__->dice.referencecamera){
				  case liqRibNode::dice::WORLD_CAMERA:
					  {
						  referencecamera = "worldcamera";
						  //RiAttribute("dice",(RtToken)"string referencecamera", &referencecamera, RI_NULL); //default value
					  }break;
				  case liqRibNode::dice::FRAME_CAMERA:
					  {
						  referencecamera = "framecamera";
						  RiAttribute("dice",(RtToken)"string referencecamera", &referencecamera, RI_NULL);
					  }break;
				  default:
					  assert(0);
		}

	}//dice

	//derivatives
	{
		if( ribNode__->derivatives.centered != 1 ){
			RtInt centered = ribNode__->derivatives.centered;
			RiAttribute("derivatives",(RtToken)"int centered", &centered, RI_NULL);
		}
		if( ribNode__->derivatives.extrapolate != 1 ){
			RtInt extrapolate = ribNode__->derivatives.extrapolate;
			RiAttribute("derivatives",(RtToken)"int extrapolate", &extrapolate, RI_NULL);
		}
	}//derivatives

	//procedural
	{
		if( ribNode__->procedural.attribute.length()>0 ){
			RtString attribute = const_cast<char*>(ribNode__->procedural.attribute.asChar());
			RiAttribute("procedural",(RtToken)"string attribute", &attribute, RI_NULL);
		}
	}//procedural

	if( ribNode__->motion.deformationBlur || ribNode__->motion.transformationBlur && ribNode__->motion.factor != 1.0f ) 
		RiGeometricApproximation( "motionfactor", ribNode__->motion.factor );

	ribNode__->writeUserAttributes();

	return MS::kSuccess;
}
//
//MStatus liqRibTranslator::writeShader(
//	const bool writeShaders__, 
//	const liqRibNodePtr &ribNode__,
//	const bool hasVolumeShader__,
//	const bool hasSurfaceShader__,
//	const bool hasCustomSurfaceShader__,
//	//const bool hasDisplacementShader__,
//	const MString &shaderRibBox__,
//	const MDagPath &path__,
//	const structJob &currentJob
//	
//	)
//{
//	const bool isShadowJob = currentJob.isShadow; 
//	const bool isDeepShadowJob = currentJob.deepShadows;
//
//		MStatus status;
//
//		if( writeShaders__ ) 
//		{
//			liqRIBMsg("[5] hasVolumeShader=%d, m_ignoreVolumes=%d", hasVolumeShader__, m_ignoreVolumes );
//			if( hasVolumeShader__ && !m_ignoreVolumes ) 
//			{
//				//liqShader& currentShader( liqGetShader( ribNode__->assignedVolume.object() ) );
//				liqShader& currentShader = liqShaderFactory::instance().getShader( ribNode__->assignedVolume.object() );
//				liqRIBMsg("[1] liqglo_currentJob.isShadow=%d, currentShader.outputInShadow=%d", isShadowJob, currentShader.outputInShadow );
//				// per shader shadow pass override
//				if( !isShadowJob || currentShader.outputInShadow )
//				{
//					currentShader.write(liqglo.liqglo_shortShaderNames, 0);
//				}
//			}
//
//			if( hasSurfaceShader__ && !m_ignoreSurfaces )
//			{
//				if( hasCustomSurfaceShader__ )
//				{
//					if( hasCustomSurfaceShader__ == liqCustomPxShaderNode )
//					{  // Just call the write method of the custom shader
//						MFnDependencyNode customShaderDepNode( ribNode__->assignedShader.object() );
//						MPxNode *mpxNode = customShaderDepNode.userNode();
//						liqCustomNode *customNode( NULL );
//						if( mpxNode && ( customNode = dynamic_cast<liqCustomNode*>( mpxNode ) ) )
//							customNode->liquidWrite();
//						else
//							;// Should never happen in theory ... but what is the way to report a problem ???
//					}
//					else
//					{ 
//						// Default : just write the contents of the rib box
//						RiArchiveRecord( RI_VERBATIM, ( char* )shaderRibBox__.asChar() );
//						RiArchiveRecord( RI_VERBATIM, "\n" );
//					}
//				}
//				else
//				{
//					//liqShader& currentShader( liqGetShader( ribNode__->assignedShader.object() ) );
//					liqShader& currentShader = liqShaderFactory::instance().getShader( ribNode__->assignedShader.object() );
//					
//					F1(ribNode__, currentShader);
//
//					liqRIBMsg("[2] liqglo_currentJob.isShadow=%d, currentShader.outputInShadow=%d", isShadowJob, currentShader.outputInShadow );
//					// per shader shadow pass override
//					if( !isShadowJob || currentShader.outputInShadow )
//					{
//						currentShader.write(liqglo.liqglo_shortShaderNames, 0);
//					}
//
//					//if( outputSurfaceShader )
//					//{
//					//	scoped_array< RtToken > tokenArray( new RtToken[ currentShader.tokenPointerArray.size() ] );
//					//	scoped_array< RtPointer > pointerArray( new RtPointer[ currentShader.tokenPointerArray.size() ] );
//					//	assignTokenArrays( currentShader.tokenPointerArray.size(), &currentShader.tokenPointerArray[ 0 ], tokenArray.get(), pointerArray.get() );
//
//					//	char* shaderFileName;
//					//	LIQ_GET_SHADER_FILE_NAME( shaderFileName, liqglo_shortShaderNames, currentShader );
//
//					//	// check shader space transformation
//					//	if( currentShader.shaderSpace != "" )
//					//	{
//					//		RiTransformBegin();
//					//		RiCoordSysTransform( ( RtString )currentShader.shaderSpace.asChar() );
//					//	}
//					//	// output shader
//					//	// its one less as the tokenPointerArray has a preset size of 1 not 0
//					//	int shaderParamCount = currentShader.tokenPointerArray.size() - 1;
//					//	RiSurfaceV ( shaderFileName, shaderParamCount, tokenArray.get(), pointerArray.get() );
//					//	if( currentShader.shaderSpace != "" )
//					//		RiTransformEnd();
//					//}
//				}
//			}else{//if( hasSurfaceShader && !m_ignoreSurfaces )
//				F2(m_shaderDebug, ribNode__);
//
//				if( !m_ignoreSurfaces ) 
//				{
//					MObject shadingGroup = ribNode__->assignedShadingGroup.object();
//					MObject shader = ribNode__->findShader( shadingGroup );
//					//
//					// here we check for regular shader nodes first
//					// and assign default shader to shader-less nodes.
//					//
//					if( m_shaderDebug ) {
//						liqRIBMsg("shader debug is turned on, so the surface is constant.");
//						RiSurface( "constant", RI_NULL );
//						LIQDEBUGPRINTF("add more constant parameters here. take /RMS-1.0.1-Maya2008/lib/shaders/src/mtorBlinn.sl as an example.(?)");
//					}
//					// 					else if( shader.apiType() == MFn::kLambert ){ 
//					// 						RiSurface( "matte", RI_NULL );
//					// 						LIQDEBUGPRINTF("add more lambert parameters here. take //RMS-1.0.1-Maya2008/lib/shaders/src/mtorLambert.sl as an example.");
//					// 					}else if( shader.apiType() == MFn::kPhong ) {
//					// 						RiSurface( "plastic", RI_NULL );
//					// 						LIQDEBUGPRINTF("add more phong parameters here. take /RMS-1.0.1-Maya2008/lib/shaders/src/mtorPhong.sl as an example.");
//					// 					}
//					else if( path__.hasFn( MFn::kPfxHair ) ) 
//					{
//						// get some of the hair system parameters
//						RtFloat translucence = 0, specularPower = 0;
//						RtColor specularColor;
//
//						getPfxHairData(path__, translucence, specularPower, specularColor);
//
//						RiSurface(  "liquidpfxhair",
//							"float specularpower", &specularPower,
//							"float translucence",  &translucence,
//							"color specularcolor", &specularColor,
//							RI_NULL );
//					} 
//					else if( path__.hasFn( MFn::kPfxToon ) ) {
//						RiSurface( "liquidpfxtoon", RI_NULL );
//					}else if( path__.hasFn( MFn::kPfxGeometry ) ){
//						RiSurface( "liquidpfx", RI_NULL );
//					}else {
//						//RiSurface( "plastic", RI_NULL );
//						MFnDependencyNode shaderFn(shader);
//						RiSurface( const_cast<char*>(shaderFn.name().asChar()), RI_NULL );
//					}
//				}
//			}//if( hasSurfaceShader && !m_ignoreSurfaces )else
//		} //if( writeShaders ) 
//		else if( isDeepShadowJob ) 
//		{
//			liqRIBMsg("[7] liqglo_currentJob[.deepShadows=%d, .isShadow=%d ], hasSurfaceShader=%d, hasCustomSurfaceShader=%d",
//				isDeepShadowJob, isShadowJob, hasSurfaceShader__, hasCustomSurfaceShader__ );
//
//			// if the current job is a deep shadow,
//			// we still want to output primitive color and opacity and surface shader
//			// In case of custom shaders, what should we do ? Stephane.
//			if( hasSurfaceShader__ && ! hasCustomSurfaceShader__ ) 
//			{
//				//liqShader & currentShader = liqGetShader( ribNode__->assignedShader.object());
//				liqShader &currentShader = liqShaderFactory::instance().getShader( ribNode__->assignedShader.object() );
//
//				F1(ribNode__, currentShader);
//
//				liqRIBMsg("[8] currentShader[.name=%s, .filename=%s, .outputInShadow=%d]", currentShader.name.c_str(), currentShader.file.c_str(), currentShader.outputInShadow );
//				if(currentShader.outputInShadow){
//					currentShader.write(liqglo.liqglo_shortShaderNames, 0);
//				}
//			} 
//			else //if( hasSurfaceShader__ && ! hasCustomSurfaceShader__ ) 
//			{
//				F2(false, ribNode__ );
//
//				if( path__.hasFn( MFn::kPfxHair ) ) 
//				{
//					// get some of the hair system parameters
//					RtFloat translucence = 0, specularPower = 0;
//					RtColor specularColor;
//
//					getPfxHairData(path__, translucence, specularPower, specularColor);
//
//					RiSurface(  "liquidPfxHair",
//						"float specularPower", &specularPower,
//						"float translucence",  &translucence,
//						"color specularColor", &specularColor,
//						RI_NULL );
//				}
//			}
//		}else {
//			RiSurface( "null", RI_NULL );
//		}
//
//
//	return MS::kSuccess;
//}
//
MStatus liqRibTranslator::objectBlock__(const structJob &currentJob)
{
	MStatus returnStatus = MS::kSuccess;
	MStatus status;
	attributeDepth = 0;

	LIQDEBUGPRINTF( "-> objectBlock\n" );

	if( m_ignoreSurfaces ) 
		RiSurface( "matte", RI_NULL );

	// Moritz: Added Pre-Geometry RIB for insertion right before any primitives
	preGeometryMel();

	// retrieve the shadow set object
	MObject shadowSetObj(getShadowSetObject(currentJob));
	MFnSet shadowSet( shadowSetObj, &status );

	//MMatrix matrix;
	for ( RNMAP::iterator rniter( htable->RibNodeMap.begin() ); rniter != htable->RibNodeMap.end(); rniter++ ) 
	{
		LIQ_CHECK_CANCEL_REQUEST;

		liqRibNodePtr ribNode( rniter->second );

		if( ( !ribNode ) || ( ribNode->object(0)->type == MRT_Light ) ) 
			continue;
		if( ribNode->object(0)->type == MRT_Coord || ribNode->object(0)->type == MRT_ClipPlane ) 
			continue;
		if( ( !currentJob.isShadow ) && ( ribNode->object(0)->ignore ) ) 
			continue;
		if( ( currentJob.isShadow ) && ( ribNode->object(0)->ignoreShadow ) ) 
			continue;
		// test against the set
		if( ( currentJob.isShadow ) 
			&& ( currentJob.shadowObjectSet != "" ) 
			&& ( !shadowSetObj.isNull() ) 
			&& ( !shadowSet.isMember( ribNode->path().transform(), &status ) ) ) 
		{
			//cout <<"SET FILTER : object "<<ribNode->name.asChar()<<" is NOT in "<<liqglo_currentJob.shadowObjectSet.asChar()<<endl;
			continue;
		}
		//
		oneObjectBlock(ribNode, currentJob );

	}//for ( RNMAP::iterator rniter(...
	while ( attributeDepth > 0 ) 
	{
		RiAttributeEnd();
		attributeDepth--;
	}
	return returnStatus;
}
//
MStatus liqRibTranslator::worldEpilogue__()
{
	return worldEpilogue();
}
//
MStatus liqRibTranslator::frameEpilogue__( long scanTime)
{
	if( ribStatus == kRibFrame) 
	{
		ribStatus = kRibBegin;
		liquid::RendererMgr::getInstancePtr()->getRenderer()->frameEpilogue(scanTime);
	}
	return (ribStatus == kRibBegin ? MS::kSuccess : MS::kFailure);

}
//
MStatus liqRibTranslator::_doItNewWithoutRenderScript(
	const MArgList& args , const MString& originalLayer )
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

	// check to see if the output camera, if specified, is available
	if( liqglo.liquidBin && ( liqglo.renderCamera == "" ) ) 
	{
		liquidMessage( "No render camera specified!", messageError );
		return MS::kFailure;
	}
	if( liqglo.renderCamera != "" ) 
	{
		MStatus selectionStatus;
		MSelectionList camList;
		selectionStatus = camList.add( liqglo.renderCamera );
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
		liqRibTranslator::m_escHandler.beginComputation();

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


		liqRenderScript jobScript;
		// 		liqRenderScript::Job preJobInstance;
		// 		preJobInstance.title = "liquid pre-job";
		// 		preJobInstance.isInstance = true;
		tJobScriptMgr jobScriptMgr(jobScript);


		// build the frame array
		//
		if( liqglo.m_renderView ) 
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

			///////////////////////////////////////////////////
			TempControlBreak tcb = 
				processOneFrame(frameIndex, liqglo);
			PROCESS_TEMP_CONTROL_BREAK_CONTINUE_RETURN(tcb)
			///////////////////////////////////////////////////

			jobScript.addJob( frameScriptJob );


			if( ( ribStatus != kRibOK ) && !liqglo.m_deferredGen ) 
				break;

		} // frame for-loop

		LIQDEBUGPRINTF( "-> ending escape handler.\n" );
		liqRibTranslator::m_escHandler.endComputation();

		if( !liqglo.m_deferredGen ) 
			liquidMessage( "Finished creating RIB", messageInfo );
		
		structJob currentJob____ = *(jobList.rbegin());//I guess liqglo.liqglo_currentJob is jobList.rbegin()

		LIQDEBUGPRINTF( "-> clearing job list.\n" );
		jobList.clear();
		jobScript.clear();

		// set the attributes on the liquidGlobals for the last rib file and last alfred script name
		LIQDEBUGPRINTF( "-> setting lastAlfredScript and lastRibFile.\n" );
		MGlobal::executeCommand("if(!attributeExists(\"lastRenderScript\",\"liquidGlobals\")) { addAttr -ln \"lastRenderScript\" -dt \"string\" liquidGlobals; }");
		MFnDependencyNode rGlobalNode( liqglo.rGlobalObj );
		MPlug nPlug;
		nPlug = rGlobalNode.findPlug( "lastRenderScript" );
		nPlug.setValue( renderScriptName );
#if (Refactoring == 0)
		nPlug = rGlobalNode.findPlug( "lastRibFile" );
		nPlug.setValue( lastRibName );
#endif
		LIQDEBUGPRINTF( "-> spawning command.\n" );
		if( liqglo.launchRender ) 
		{
			{
				// launch renders directly
				liquidMessage( string(), messageInfo ); // emit a '\n'
				//int exitstat = 0;

				// write out make texture pass
				doTextures(txtList);

				if( liqglo.liqglo_doShadows ) 
				{
					doShadows(shadowList);
				}

				//if( !exitstat ){
				liquidMessage( "Rendering hero pass... ", messageInfo );
				cout << "[!] Rendering hero pass..." << endl;

				//structJob &currentJob____ = *(jobList.rbegin());//I guess liqglo.liqglo_currentJob is jobList.rbegin()
				if( currentJob____.skip ) 
				{
					cout << "    - skipping '" << currentJob____.ribFileName.asChar() << "'" << endl;
					liquidMessage( "    - skipping '" + string( currentJob____.ribFileName.asChar() ) + "'", messageInfo );
				} 
				else 
				{
					liquid::RendererMgr::getInstancePtr()->getRenderer()->renderAll_local(currentJob____);
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
		liqRibTranslator::m_escHandler.endComputation();
		return MS::kFailure;
	} 
	catch ( ... ) 
	{
		liquidMessage( "Unknown exception thrown", messageError );
		/*if( htable && hashTableInited ) delete htable;
		freeShaders();*/
		liqRibTranslator::m_escHandler.endComputation();
		return MS::kFailure;
	}
}
//
MStatus liqRibTranslator::_doItNewWithRenderScript(
	const MArgList& args , const MString& originalLayer )
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

	// check to see if the output camera, if specified, is available
	if( liqglo.liquidBin && ( liqglo.renderCamera == "" ) ) 
	{
		liquidMessage( "No render camera specified!", messageError );
		return MS::kFailure;
	}
	if( liqglo.renderCamera != "" ) 
	{
		MStatus selectionStatus;
		MSelectionList camList;
		selectionStatus = camList.add( liqglo.renderCamera );
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
		liqRibTranslator::m_escHandler.beginComputation();

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


		liqRenderScript jobScript;
		// 		liqRenderScript::Job preJobInstance;
		// 		preJobInstance.title = "liquid pre-job";
		// 		preJobInstance.isInstance = true;
		tJobScriptMgr jobScriptMgr(jobScript);

		if( true/*useRenderScript*/ ) 
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
		if( liqglo.m_renderView ) 
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

			if( true/*useRenderScript*/ ) 
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
			}
			if(true/*useRenderScript*/ && !m_justRib)
			{
				if( liqglo.m_deferredGen ) 
				{
					stringstream ss;
					ss << liqglo.liqglo_sceneName.asChar() << "FrameRIBGEN" << currentBlock;
					frameScriptJobMgr.addInstanceJob(true, ss.str() );
				}
			}//if( useRenderScript ) 
			///////////////////////////////////////////////////
			TempControlBreak tcb = 
				processOneFrame(frameIndex, liqglo);
			PROCESS_TEMP_CONTROL_BREAK_CONTINUE_RETURN(tcb)
			///////////////////////////////////////////////////
			// now we re-iterate through the job list to write out the alfred file if we are using it
			if( true/*useRenderScript*/ && !m_justRib ) 
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
						structJob &currentJob____ = *(jobList.rbegin());//I guess liqglo.liqglo_currentJob is jobList.rbegin()
						MString     baseShadowName(getBaseShadowName(currentJob____));
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

		if( true/*useRenderScript*/ ) 
		{
			if( m_preJobCommand != MString( "" ) ) 
			{
				liqRenderScript::Job preJobInstance;
				preJobInstance.title = "liquid pre-job";
				preJobInstance.isInstance = true;
				jobScript.addLeafDependency( preJobInstance );
			}
		}
		if(true/*useRenderScript*/ && !m_justRib)
		{
			// clean up the alfred file in the future
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
			jobScriptMgr.writeRenderScript(m_renderScriptFormat, renderScriptName);
		}
		LIQDEBUGPRINTF( "-> ending escape handler.\n" );
		liqRibTranslator::m_escHandler.endComputation();

		if( !liqglo.m_deferredGen ) 
			liquidMessage( "Finished creating RIB", messageInfo );
		LIQDEBUGPRINTF( "-> clearing job list.\n" );
		jobList.clear();
		jobScript.clear();

		// set the attributes on the liquidGlobals for the last rib file and last alfred script name
		LIQDEBUGPRINTF( "-> setting lastAlfredScript and lastRibFile.\n" );
		MGlobal::executeCommand("if(!attributeExists(\"lastRenderScript\",\"liquidGlobals\")) { addAttr -ln \"lastRenderScript\" -dt \"string\" liquidGlobals; }");
		MFnDependencyNode rGlobalNode( liqglo.rGlobalObj );
		MPlug nPlug;
		nPlug = rGlobalNode.findPlug( "lastRenderScript" );
		nPlug.setValue( renderScriptName );
#if (Refactoring == 0)
		nPlug = rGlobalNode.findPlug( "lastRibFile" );
		nPlug.setValue( lastRibName );
#endif
		LIQDEBUGPRINTF( "-> spawning command.\n" );
		if( liqglo.launchRender ) 
		{
			if( true/*useRenderScript*/ ) 
			{
				if( m_renderScriptCommand == "" ) 
					m_renderScriptCommand = "alfred";

				if( m_renderScriptFormat == NONE ) 
					liquidMessage( "No render script format specified to Liquid, and direct render execution not selected.", messageWarning );

#ifdef _WIN32
				// Moritz: Added quotes to render script name as it may contain spaces in bloody Windoze
				// Note: also adding quotes to the path (aka project dir) breaks ShellExecute() -- cost me one hour to trace this!!!
				// Bloody, damn, asinine Windoze!!!
				cout << "5.liqProcessLauncher::execute("<<m_renderScriptCommand<<","<<renderScriptName <<","<<liqglo.liqglo_projectDir<<","<< false <<")"<< endl;
				liqProcessLauncher::execute( m_renderScriptCommand, "\"" + renderScriptName + "\"", liqglo.liqglo_projectDir, false );
#else
				liqProcessLauncher::execute( m_renderScriptCommand, renderScriptName, liqglo.liqglo_projectDir, false );
#endif
				if( liqglo.m_renderView ) 
				{
					doRenderView();
				}
			}
		} // if( launchRender )

		postActions(originalLayer);

		return ( (ribStatus == kRibOK || liqglo.m_deferredGen) ? MS::kSuccess : MS::kFailure);

	} 
	catch ( MString errorMessage ) 
	{
		liquidMessage( errorMessage.asChar(), messageError );
		/*if( htable && hashTableInited ) delete htable;
		freeShaders();*/
		liqRibTranslator::m_escHandler.endComputation();
		return MS::kFailure;
	} 
	catch ( ... ) 
	{
		liquidMessage( "Unknown exception thrown", messageError );
		/*if( htable && hashTableInited ) delete htable;
		freeShaders();*/
		liqRibTranslator::m_escHandler.endComputation();
		return MS::kFailure;
	}
}
//
void liqRibTranslator::F1(
						  const liqRibNodePtr &ribNode__,  liqShader &currentShader
						  )
{
	// Output color overrides or color
	if(ribNode__->shading.color.r != -1.0)
	{
		RtColor rColor;
		rColor[0] = ribNode__->shading.color[0];
		rColor[1] = ribNode__->shading.color[1];
		rColor[2] = ribNode__->shading.color[2];
		RiColor( rColor );
	}
	else
		RiColor( currentShader.rmColor );

	if(ribNode__->shading.opacity.r != -1.0)
	{
		RtColor rOpacity;
		rOpacity[0] = ribNode__->shading.opacity[0];
		rOpacity[1] = ribNode__->shading.opacity[1];
		rOpacity[2] = ribNode__->shading.opacity[2];
		RiOpacity( rOpacity );
	}
	else
		RiOpacity( currentShader.rmOpacity );
}

////////////////////////////////////////
void liqRibTranslator::F2(
						  const bool m_shaderDebug, const liqRibNodePtr &ribNode__
						  )
{ 
	if( m_shaderDebug ) 
	{
		RtColor rColor,rOpacity;
		liqRIBMsg("shader debug is turned on, so the object is red.");
		// shader debug on !! everything goes red and opaque !!!
		rColor[0] = 1.;
		rColor[1] = 0.;
		rColor[2] = 0.;
		RiColor( rColor );

		rOpacity[0] = 1.;
		rOpacity[1] = 1.;
		rOpacity[2] = 1.;
		RiOpacity( rOpacity );
	}else{
		if(ribNode__->shading.color.r != -1.0) 
		{
			RtColor rColor;
			rColor[0] = ribNode__->shading.color[0];
			rColor[1] = ribNode__->shading.color[1];
			rColor[2] = ribNode__->shading.color[2];
			RiColor( rColor );
		} 
		else if( ( ribNode__->color.r != -1.0 ) ) 
		{
			RtColor rColor;
			rColor[0] = ribNode__->color[0];
			rColor[1] = ribNode__->color[1];
			rColor[2] = ribNode__->color[2];
			RiColor( rColor );
		}

		if(ribNode__->shading.opacity.r != -1.0) 
		{
			RtColor rOpacity;
			rOpacity[0] = ribNode__->shading.opacity[0];
			rOpacity[1] = ribNode__->shading.opacity[1];
			rOpacity[2] = ribNode__->shading.opacity[2];
			RiOpacity( rOpacity );
		} 
		else if( ( ribNode__->opacity.r != -1.0 ) ) 
		{	
			RtColor rOpacity;
			rOpacity[0] = ribNode__->opacity[0];
			rOpacity[1] = ribNode__->opacity[1];
			rOpacity[2] = ribNode__->opacity[2];
			RiOpacity( rOpacity );
		}
	}
}

////////////////////////////////////
void liqRibTranslator::getPfxHairData(const MDagPath &path__,
	RtFloat &translucence, RtFloat &specularPower, RtColor &specularColor
)
{
	MStatus status;

	//cout <<"getting pfxHair shading params..."<<endl;
	MObject hairSystemObj;
	MFnDependencyNode pfxHairNode( path__.node() );
	MPlug plugToHairSystem = pfxHairNode.findPlug( "renderHairs", &status );
	MPlugArray hsPlugs;
	status.clear();
	if( plugToHairSystem.connectedTo( hsPlugs, true, false, &status ) ) 
		if( status == MS::kSuccess ) 
			hairSystemObj = hsPlugs[0].node();

	if( hairSystemObj != MObject::kNullObj ) 
	{
		MFnDependencyNode hairSystemNode(hairSystemObj);
		MPlug paramPlug;
		status.clear();
		paramPlug = hairSystemNode.findPlug( "translucence", &status );
		if( status == MS::kSuccess ) 
			paramPlug.getValue( translucence );
		status.clear();
		paramPlug = hairSystemNode.findPlug( "specularColor", &status );
		if( status == MS::kSuccess ) 
		{
			paramPlug.child(0).getValue( specularColor[0] );
			paramPlug.child(1).getValue( specularColor[1] );
			paramPlug.child(2).getValue( specularColor[2] );
		}
		status.clear();
		paramPlug = hairSystemNode.findPlug( "specularPower", &status );
		if( status == MS::kSuccess ) 
			paramPlug.getValue( specularPower );
	}
}
//
void liqRibTranslator::oneObjectBlock(
	const liqRibNodePtr &ribNode,
	const structJob &currentJob
	)
{
	MDagPath path = ribNode->path();
	MObject transform = path.transform();
	MFnDagNode dagFn;

		if( liqglo.m_outputComments ) 
			RiArchiveRecord( RI_COMMENT, "Name: %s", ribNode->name.asChar(), RI_NULL );

		RiAttributeBegin();
		RiAttribute( "identifier", "name", &getLiquidRibName( ribNode->name.asChar() ), RI_NULL );

		// Alf: preTransformMel
		preTransformMel(transform);

		if( !ribNode->grouping.membership.empty() ) 
		{
			RtString members( const_cast< char* >( ribNode->grouping.membership.c_str() ) );
			RiAttribute( "grouping", "membership", &members, RI_NULL );
		}

		if( ribNode->shading.matte || ribNode->mayaMatteMode ) 
			RiMatte( RI_TRUE );

		// If this is a single sided object, then turn that on (RMan default is Sides 2)
		if( !ribNode->doubleSided ) 
			RiSides( 1 );

		if( ribNode->reversedNormals ) 
			RiReverseOrientation();

		LIQDEBUGPRINTF( "-> object name: %s\n", ribNode->name.asChar() );
		MObject object;

		// Moritz: only write out light linking if we're not in a shadow pass
		if( !  currentJob.isShadow 
			|| (currentJob.deepShadows && m_outputLightsInDeepShadows && !m_ignoreLights) )
		{
			tRiIlluminate(currentJob, ribNode);
		}
		bool bMotionBlur =
			ribNode->motion.transformationBlur &&
			( ribNode->object( 1 ) ) &&
			//( ribNode->object(0)->type != MRT_Locator ) && // Why the fuck do we not allow motion blur for locators?
			( !currentJob.isShadow || currentJob.deepShadows );

		bool bMatrixMotionBlur = 
			liqglo.liqglo_doMotion 
			&& bMotionBlur;

		MaxtrixMotionBlur(ribNode, path, bMatrixMotionBlur);

		// Alf: postTransformMel
		postTransformMel(transform);

		bool hasSurfaceShader( false );
		liqDetailShaderKind hasCustomSurfaceShader( liqRegularShaderNode );
		MString shaderRibBox( "" );
		bool hasDisplacementShader( false );
		bool hasVolumeShader( false );

		// Check for surface shader
		checkSurfaceShader(path, ribNode, hasSurfaceShader, hasCustomSurfaceShader, shaderRibBox);
		// Check for displacement shader
		checkDisplacementShader(path, ribNode, hasDisplacementShader);
		// Check for volume shader
		checkVolumeShader(path, ribNode, hasVolumeShader);
		// displacement bounds
		displacementBounds(ribNode);

		LIQDEBUGPRINTF( "-> writing node attributes\n" );
		// if the node's shading rate == -1,
		// it means it hasn't been overriden by a liqShadingRate attribute.
		// No need to output it then.
		if( ribNode->shading.shadingRate > 0 )
			RiShadingRate ( ribNode->shading.shadingRate );

		if( currentJob.isShadow ) 
		{
			objectShadowAttribute(ribNode);
		}else{
			objectNonShadowAttribute(ribNode);
		}

		bool writeShaders( true );
// 
// 		if( currentJob.isShadow &&
// 			(    ( !currentJob.deepShadows && !m_outputShadersInShadows ) 
// 			  || (  currentJob.deepShadows && !m_outputShadersInDeepShadows ) 
// 			)
// 		  )
// 		{
// 			writeShaders = false;
// 		} 
// 		liqRIBMsg("[6] writeShaders=%d=%d && ((!%d&&!%d)||(%d&&!%d) ", writeShaders, 
// 			currentJob.isShadow, 
//			currentJob.deepShadows, m_outputShadersInShadows, currentJob.deepShadows, m_outputShadersInDeepShadows );

		if( !currentJob.isShadow )
		{
			writeShader_(
				true,//writeShaders
				ribNode,
				hasVolumeShader,
				hasSurfaceShader,
				hasCustomSurfaceShader,
				//hasDisplacementShader,
				shaderRibBox,
				path,
				currentJob
				);
			liqRIBMsg("[4] hasDisplacementShader=%d, m_ignoreDisplacements=%d", hasDisplacementShader, m_ignoreDisplacements );
			if( hasDisplacementShader && !m_ignoreDisplacements ) 
			{
				//liqShader & currentShader = liqGetShader( ribNode__->assignedDisp.object() );
				liqShader &currentShader = liqShaderFactory::instance().getShader( ribNode->assignedDisp.object() );

				liqRIBMsg("[3] liqglo_currentJob.isShadow=%d, currentShader.outputInShadow=%d", currentJob.isShadowJob, currentShader.outputInShadow );
				// per shader shadow pass override
				if( true/*!currentJob.isShadow || currentShader.outputInShadow*/ )
				{
					//currentShader.write();//use ShadingGroup reference instead.
				}

				//if( !currentShader.hasErrors && outputDispShader )
				//{
				//	scoped_array< RtToken > tokenArray( new RtToken[ currentShader.tokenPointerArray.size() ] );
				//	scoped_array< RtPointer > pointerArray( new RtPointer[ currentShader.tokenPointerArray.size() ] );
				//	assignTokenArrays( currentShader.tokenPointerArray.size(), &currentShader.tokenPointerArray[ 0 ], tokenArray.get(), pointerArray.get() );

				//	char *shaderFileName;
				//	LIQ_GET_SHADER_FILE_NAME(shaderFileName, liqglo_shortShaderNames, currentShader );
				//	// check shader space transformation
				//	if( currentShader.shaderSpace != "" )
				//	{
				//		RiTransformBegin();
				//		RiCoordSysTransform( ( RtString )currentShader.shaderSpace.asChar() );
				//	}
				//	// output shader
				//	int shaderParamCount = currentShader.tokenPointerArray.size() - 1;
				//	RiDisplacementV ( shaderFileName, shaderParamCount, tokenArray.get(), pointerArray.get() );
				//	if( currentShader.shaderSpace != "" )
				//		RiTransformEnd();
				//}
			}

			writeShadingGroup(ribNode->name);

		}else{
			//currentJob.isShadow==true

			writeShader_forShadow(
				true,//the value is changed  in the function.
				ribNode,
				hasVolumeShader,
				hasSurfaceShader,
				hasCustomSurfaceShader,
				//hasDisplacementShader,
				shaderRibBox,
				path,
				currentJob
				);
			liqRIBMsg("[4] hasDisplacementShader=%d, m_ignoreDisplacements=%d", hasDisplacementShader, m_ignoreDisplacements );
			if( hasDisplacementShader && !m_ignoreDisplacements ) 
			{
				//liqShader & currentShader = liqGetShader( ribNode__->assignedDisp.object() );
				liqShader &currentShader = liqShaderFactory::instance().getShader( ribNode->assignedDisp.object() );

				liqRIBMsg("[3] liqglo_currentJob.isShadow=%d, currentShader.outputInShadow=%d", currentJob.isShadowJob, currentShader.outputInShadow );
				// per shader shadow pass override
				if( /*!currentJob.isShadow || */currentShader.outputInShadow )
				{
					currentShader.write();
				}

				//if( !currentShader.hasErrors && outputDispShader )
				//{
				//	scoped_array< RtToken > tokenArray( new RtToken[ currentShader.tokenPointerArray.size() ] );
				//	scoped_array< RtPointer > pointerArray( new RtPointer[ currentShader.tokenPointerArray.size() ] );
				//	assignTokenArrays( currentShader.tokenPointerArray.size(), &currentShader.tokenPointerArray[ 0 ], tokenArray.get(), pointerArray.get() );

				//	char *shaderFileName;
				//	LIQ_GET_SHADER_FILE_NAME(shaderFileName, liqglo_shortShaderNames, currentShader );
				//	// check shader space transformation
				//	if( currentShader.shaderSpace != "" )
				//	{
				//		RiTransformBegin();
				//		RiCoordSysTransform( ( RtString )currentShader.shaderSpace.asChar() );
				//	}
				//	// output shader
				//	int shaderParamCount = currentShader.tokenPointerArray.size() - 1;
				//	RiDisplacementV ( shaderFileName, shaderParamCount, tokenArray.get(), pointerArray.get() );
				//	if( currentShader.shaderSpace != "" )
				//		RiTransformEnd();
				//}
			}
		}


		//////////////////////////////////////////////////////////////////////////
		if( ribNode->rib.hasBox() ) 
			RiArchiveRecord( RI_COMMENT, " RIB Box:\n%s", ribNode->rib.box.asChar() );
		if( ribNode->rib.hasGenerator() ){
			MGlobal::executeCommand( ribNode->rib.generator, false, false );
		}
		if( ribNode->rib.hasReadArchive() ) 
			RiArchiveRecord( RI_VERBATIM, " ReadArchive \"%s\" \n", ribNode->rib.readArchive.asChar() );
		if( ribNode->rib.hasDelayedReadArchive() ) 
		{
			RiArchiveRecord( RI_VERBATIM, " Procedural \"DelayedReadArchive\" [ \"%s\" ] [ %f %f %f %f %f %f ] \n", ribNode->rib.delayedReadArchive.asChar(), ribNode->bound[0],ribNode->bound[3],ribNode->bound[1],ribNode->bound[4],ribNode->bound[2],ribNode->bound[5] );
			// should be using the bounding box node - Alf
			/* {
			// this is a visual display of the archive's bounding box
			RiAttributeBegin();
			RtColor debug;
			debug[0] = debug[1] = 1;
			debug[2] = 0;
			RiColor( debug );
			debug[0] = debug[1] = debug[2] = 0.250;
			RiOpacity( debug );
			RiSurface( "defaultsurface", RI_NULL );
			RiArchiveRecord( RI_VERBATIM, "Attribute \"visibility\" \"int diffuse\" [0]\n" );
			RiArchiveRecord( RI_VERBATIM, "Attribute \"visibility\" \"int specular\" [0]\n" );
			RiArchiveRecord( RI_VERBATIM, "Attribute \"visibility\" \"int transmission\" [0]\n" );
			float xmin = ribNode->bound[0];
			float ymin = ribNode->bound[1];
			float zmin = ribNode->bound[2];
			float xmax = ribNode->bound[3];
			float ymax = ribNode->bound[4];
			float zmax = ribNode->bound[5];
			RiSides( 2 );
			RiArchiveRecord( RI_VERBATIM, "Polygon \"P\" [ %f %f %f  %f %f %f  %f %f %f  %f %f %f ]\n", xmin,ymax,zmin, xmax,ymax,zmin, xmax,ymax,zmax, xmin,ymax,zmax );
			RiArchiveRecord( RI_VERBATIM, "Polygon \"P\" [ %f %f %f  %f %f %f  %f %f %f  %f %f %f ]\n", xmin,ymin,zmin, xmax,ymin,zmin, xmax,ymin,zmax, xmin,ymin,zmax );
			RiArchiveRecord( RI_VERBATIM, "Polygon \"P\" [ %f %f %f  %f %f %f  %f %f %f  %f %f %f ]\n", xmin,ymax,zmax, xmax,ymax,zmax, xmax,ymin,zmax, xmin,ymin,zmax );
			RiArchiveRecord( RI_VERBATIM, "Polygon \"P\" [ %f %f %f  %f %f %f  %f %f %f  %f %f %f ]\n", xmin,ymax,zmin, xmax,ymax,zmin, xmax,ymin,zmin, xmin,ymin,zmin );
			RiAttributeEnd();
			} */
		}
		//////////////////////////////////////////////////////////////////////////
		
		// Alf: preShapeMel
		preShapeMel(transform);

		if( !ribNode->ignoreShapes ) 
		{
			liqRIBMsg("ribNode->object(0)->type= %d, path=%s",ribNode->object(0)->type, ribNode->path().fullPathName().asChar() );
			// check to see if we are writing a curve to set the proper basis
			if( ribNode->object(0)->type == MRT_NuCurve
				|| ribNode->object(0)->type == MRT_PfxHair
				|| ribNode->object(0)->type == MRT_PfxTube
				|| ribNode->object(0)->type == MRT_PfxLeaf
				|| ribNode->object(0)->type == MRT_PfxPetal 
				|| ribNode->object(0)->type == MRT_Curves )
			{
				RiBasis( RiBSplineBasis, 1, RiBSplineBasis, 1 );
			} 
			bool hasRibBoxData=ribNode->rib.hasGenerator()
							|| ribNode->rib.hasReadArchive()  
							|| ribNode->rib.hasDelayedReadArchive();
			if(hasRibBoxData)
			{
				//if ribNode is tagged as readArchive or delayedReadArchive, 
				//we do not output its geometry data.
				liqRIBMsg("%s has ribbox data,so we do not output the deometry.", ribNode->name.asChar());
			}else{
				bool bGeometryMotion = 
					liqglo.liqglo_doDef 
					&& bMotionBlur
					&& ( ribNode->object(0)->type != MRT_RibGen );

				if( bGeometryMotion )
				{
#define GeometryMotionBlur_SimpleEdition
#ifndef GeometryMotionBlur_SimpleEdition
					// For each grain, open a new motion block...
					for( unsigned i( 0 ); i < ribNode->object( 0 )->granularity(); i++ ) //granularity() is always 1.
					{
						if( ribNode->object( 0 )->isNextObjectGrainAnimated() ) //isNextObjectGrainAnimated() is always true.
						{
							if(liqglo.liqglo_relativeMotion)
								RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimesOffsets );
							else
								RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimes );

							for ( unsigned msampleOn( 0 ); msampleOn < liqglo.liqglo_motionSamples; msampleOn++ )
							{ 
								_writeObject(ribNode, currentJob, true, msampleOn);
							}
							RiMotionEnd();
						}else {
							RiArchiveRecord( RI_COMMENT, "the the next object grain is not animated" );

							_writeObject(ribNode, currentJob, false, 0);
						}
					}
#else
					if(liqglo.liqglo_relativeMotion)
						RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimesOffsets );
					else
						RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimes );

					for ( unsigned msampleOn( 0 ); msampleOn < liqglo.liqglo_motionSamples; msampleOn++ )
					{ 
						_writeObject(ribNode, currentJob, true, msampleOn);
					}
					RiMotionEnd();
#endif
				}else{
					//ribNode->object( 0 )->writeObject();
					_writeObject(ribNode, currentJob, false, 0);
				}// if(bGeometryMotion)
			}//if(hasRibBoxData)


			// Alf: postShapeMel
			postShapeMel(transform);
		} // else RiArchiveRecord( RI_COMMENT, " Shapes Ignored !!" );
		RiAttributeEnd();
}
//
MStatus liqRibTranslator::writeShader_(
									  const bool writeShaders__, 
									  const liqRibNodePtr &ribNode__,
									  const bool hasVolumeShader__,
									  const bool hasSurfaceShader__,
									  const bool hasCustomSurfaceShader__,
									  //const bool hasDisplacementShader__,
									  const MString &shaderRibBox__,
									  const MDagPath &path__,
									  const structJob &currentJob

									  )
{
	const bool isShadowJob = currentJob.isShadow;//false 
	const bool isDeepShadowJob = currentJob.deepShadows;//false

	MStatus status;

	if( true ) 
	{
		liqRIBMsg("[5] hasVolumeShader=%d, m_ignoreVolumes=%d", hasVolumeShader__, m_ignoreVolumes );
		if( hasVolumeShader__ && !m_ignoreVolumes ) 
		{
			//liqShader& currentShader( liqGetShader( ribNode__->assignedVolume.object() ) );
			liqShader& currentShader = liqShaderFactory::instance().getShader( ribNode__->assignedVolume.object() );
			liqRIBMsg("[1] liqglo_currentJob.isShadow=%d, currentShader.outputInShadow=%d", isShadowJob, currentShader.outputInShadow );
			// per shader shadow pass override
			if( !isShadowJob || currentShader.outputInShadow )
			{
				//currentShader.write();//use ShadingGroup reference instead.
			}
		}

		if( hasSurfaceShader__ && !m_ignoreSurfaces )
		{
			if( hasCustomSurfaceShader__ )
			{
				if( hasCustomSurfaceShader__ == liqCustomPxShaderNode )
				{  // Just call the write method of the custom shader
					MFnDependencyNode customShaderDepNode( ribNode__->assignedShader.object() );
					MPxNode *mpxNode = customShaderDepNode.userNode();
					liqCustomNode *customNode( NULL );
					if( mpxNode && ( customNode = dynamic_cast<liqCustomNode*>( mpxNode ) ) )
						customNode->liquidWrite();
					else
						;// Should never happen in theory ... but what is the way to report a problem ???
				}
				else
				{ 
					// Default : just write the contents of the rib box
					RiArchiveRecord( RI_VERBATIM, ( char* )shaderRibBox__.asChar() );
					RiArchiveRecord( RI_VERBATIM, "\n" );
				}
			}
			else
			{
				//liqShader& currentShader( liqGetShader( ribNode__->assignedShader.object() ) );
				liqShader& currentShader = liqShaderFactory::instance().getShader( ribNode__->assignedShader.object() );

				F1(ribNode__, currentShader);

				liqRIBMsg("[2] liqglo_currentJob.isShadow=%d, currentShader.outputInShadow=%d", isShadowJob, currentShader.outputInShadow );
				// per shader shadow pass override
				if( !isShadowJob || currentShader.outputInShadow )
				{
					//currentShader.write();//use ShadingGroup reference instead.
				}

				//if( outputSurfaceShader )
				//{
				//	scoped_array< RtToken > tokenArray( new RtToken[ currentShader.tokenPointerArray.size() ] );
				//	scoped_array< RtPointer > pointerArray( new RtPointer[ currentShader.tokenPointerArray.size() ] );
				//	assignTokenArrays( currentShader.tokenPointerArray.size(), &currentShader.tokenPointerArray[ 0 ], tokenArray.get(), pointerArray.get() );

				//	char* shaderFileName;
				//	LIQ_GET_SHADER_FILE_NAME( shaderFileName, liqglo_shortShaderNames, currentShader );

				//	// check shader space transformation
				//	if( currentShader.shaderSpace != "" )
				//	{
				//		RiTransformBegin();
				//		RiCoordSysTransform( ( RtString )currentShader.shaderSpace.asChar() );
				//	}
				//	// output shader
				//	// its one less as the tokenPointerArray has a preset size of 1 not 0
				//	int shaderParamCount = currentShader.tokenPointerArray.size() - 1;
				//	RiSurfaceV ( shaderFileName, shaderParamCount, tokenArray.get(), pointerArray.get() );
				//	if( currentShader.shaderSpace != "" )
				//		RiTransformEnd();
				//}
			}
		}else{//if( hasSurfaceShader && !m_ignoreSurfaces )
			F2(m_shaderDebug, ribNode__);

			if( !m_ignoreSurfaces ) 
			{
				MObject shadingGroup = ribNode__->assignedShadingGroup.object();
				MObject shader = ribNode__->findShader( shadingGroup );
				//
				// here we check for regular shader nodes first
				// and assign default shader to shader-less nodes.
				//
				if( m_shaderDebug ) {
					liqRIBMsg("shader debug is turned on, so the surface is constant.");
					RiSurface( "constant", RI_NULL );
					LIQDEBUGPRINTF("add more constant parameters here. take /RMS-1.0.1-Maya2008/lib/shaders/src/mtorBlinn.sl as an example.(?)");
				}
				//else if( shader.apiType() == MFn::kLambert ){ 
				//	RiSurface( "matte", RI_NULL );
				//	LIQDEBUGPRINTF("add more lambert parameters here. take //RMS-1.0.1-Maya2008/lib/shaders/src/mtorLambert.sl as an example.");
				//}else if( shader.apiType() == MFn::kPhong ) {
				//	RiSurface( "plastic", RI_NULL );
				//	LIQDEBUGPRINTF("add more phong parameters here. take /RMS-1.0.1-Maya2008/lib/shaders/src/mtorPhong.sl as an example.");
				//}
				else if( path__.hasFn( MFn::kPfxHair ) ) 
				{
					// get some of the hair system parameters
					RtFloat translucence = 0, specularPower = 0;
					RtColor specularColor;

					getPfxHairData(path__, translucence, specularPower, specularColor);

					RiSurface(  "liquidpfxhair",
						"float specularpower", &specularPower,
						"float translucence",  &translucence,
						"color specularcolor", &specularColor,
						RI_NULL );
				} 
				else if( path__.hasFn( MFn::kPfxToon ) ) {
					RiSurface( "liquidpfxtoon", RI_NULL );
				}else if( path__.hasFn( MFn::kPfxGeometry ) ){
					RiSurface( "liquidpfx", RI_NULL );
				}else {
					//RiSurface( "plastic", RI_NULL );
					MFnDependencyNode shaderFn(shader);
					RiSurface( const_cast<char*>(shaderFn.name().asChar()), RI_NULL );
				}
			}
		}//if( hasSurfaceShader && !m_ignoreSurfaces )else
	} //if( writeShaders ) 
 


	return MS::kSuccess;
}
MStatus liqRibTranslator::writeShader_forShadow(
									  /*const*/ bool writeShaders__, 
									  const liqRibNodePtr &ribNode__,
									  const bool hasVolumeShader__,
									  const bool hasSurfaceShader__,
									  const bool hasCustomSurfaceShader__,
									  //const bool hasDisplacementShader__,
									  const MString &shaderRibBox__,
									  const MDagPath &path__,
									  const structJob &currentJob

									  )
{
	assert(currentJob.isShadow == true);

	//const bool isDeepShadowJob = ;
	
	if(    ( !currentJob.deepShadows && !m_outputShadersInShadows ) // shadow
		|| (  currentJob.deepShadows && !m_outputShadersInDeepShadows ) )//deep shadow
	{
		writeShaders__ = false;
	}

	MStatus status;

	if( writeShaders__ ) 
	{
		liqRIBMsg("[5] hasVolumeShader=%d, m_ignoreVolumes=%d", hasVolumeShader__, m_ignoreVolumes );
		if( hasVolumeShader__ && !m_ignoreVolumes ) 
		{
			//liqShader& currentShader( liqGetShader( ribNode__->assignedVolume.object() ) );
			liqShader& currentShader = liqShaderFactory::instance().getShader( ribNode__->assignedVolume.object() );
			liqRIBMsg("[1] currentShader.outputInShadow=%d", currentShader.outputInShadow );
			// per shader shadow pass override
			if( /* !isShadowJob ||*/ currentShader.outputInShadow )
			{
				currentShader.write();
			}
		}

		if( hasSurfaceShader__ && !m_ignoreSurfaces )
		{
			if( hasCustomSurfaceShader__ )
			{
				if( hasCustomSurfaceShader__ == liqCustomPxShaderNode )
				{  // Just call the write method of the custom shader
					MFnDependencyNode customShaderDepNode( ribNode__->assignedShader.object() );
					MPxNode *mpxNode = customShaderDepNode.userNode();
					liqCustomNode *customNode( NULL );
					if( mpxNode && ( customNode = dynamic_cast<liqCustomNode*>( mpxNode ) ) )
						customNode->liquidWrite();
					else
						;// Should never happen in theory ... but what is the way to report a problem ???
				}
				else
				{ 
					// Default : just write the contents of the rib box
					RiArchiveRecord( RI_VERBATIM, ( char* )shaderRibBox__.asChar() );
					RiArchiveRecord( RI_VERBATIM, "\n" );
				}
			}
			else
			{
				//liqShader& currentShader( liqGetShader( ribNode__->assignedShader.object() ) );
				liqShader& currentShader = liqShaderFactory::instance().getShader( ribNode__->assignedShader.object() );

				F1(ribNode__, currentShader);

				liqRIBMsg("[2] currentShader.outputInShadow=%d", currentShader.outputInShadow );
				// per shader shadow pass override
				if( /*!isShadowJob ||*/ currentShader.outputInShadow )
				{
					currentShader.write();
				}

				//if( outputSurfaceShader )
				//{
				//	scoped_array< RtToken > tokenArray( new RtToken[ currentShader.tokenPointerArray.size() ] );
				//	scoped_array< RtPointer > pointerArray( new RtPointer[ currentShader.tokenPointerArray.size() ] );
				//	assignTokenArrays( currentShader.tokenPointerArray.size(), &currentShader.tokenPointerArray[ 0 ], tokenArray.get(), pointerArray.get() );

				//	char* shaderFileName;
				//	LIQ_GET_SHADER_FILE_NAME( shaderFileName, liqglo_shortShaderNames, currentShader );

				//	// check shader space transformation
				//	if( currentShader.shaderSpace != "" )
				//	{
				//		RiTransformBegin();
				//		RiCoordSysTransform( ( RtString )currentShader.shaderSpace.asChar() );
				//	}
				//	// output shader
				//	// its one less as the tokenPointerArray has a preset size of 1 not 0
				//	int shaderParamCount = currentShader.tokenPointerArray.size() - 1;
				//	RiSurfaceV ( shaderFileName, shaderParamCount, tokenArray.get(), pointerArray.get() );
				//	if( currentShader.shaderSpace != "" )
				//		RiTransformEnd();
				//}
			}
		}else{//if( hasSurfaceShader && !m_ignoreSurfaces )
			F2(m_shaderDebug, ribNode__);

			if( !m_ignoreSurfaces ) 
			{
				MObject shadingGroup = ribNode__->assignedShadingGroup.object();
				MObject shader = ribNode__->findShader( shadingGroup );
				//
				// here we check for regular shader nodes first
				// and assign default shader to shader-less nodes.
				//
				if( m_shaderDebug ) {
					liqRIBMsg("shader debug is turned on, so the surface is constant.");
					RiSurface( "constant", RI_NULL );
					LIQDEBUGPRINTF("add more constant parameters here. take /RMS-1.0.1-Maya2008/lib/shaders/src/mtorBlinn.sl as an example.(?)");
				}
 				//else if( shader.apiType() == MFn::kLambert ){ 
 				//	RiSurface( "matte", RI_NULL );
 				//	LIQDEBUGPRINTF("add more lambert parameters here. take //RMS-1.0.1-Maya2008/lib/shaders/src/mtorLambert.sl as an example.");
 				//}else if( shader.apiType() == MFn::kPhong ) {
 				//	RiSurface( "plastic", RI_NULL );
 				//	LIQDEBUGPRINTF("add more phong parameters here. take /RMS-1.0.1-Maya2008/lib/shaders/src/mtorPhong.sl as an example.");
 				//}
				else if( path__.hasFn( MFn::kPfxHair ) ) 
				{
					// get some of the hair system parameters
					RtFloat translucence = 0, specularPower = 0;
					RtColor specularColor;

					getPfxHairData(path__, translucence, specularPower, specularColor);

					RiSurface(  "liquidpfxhair",
						"float specularpower", &specularPower,
						"float translucence",  &translucence,
						"color specularcolor", &specularColor,
						RI_NULL );
				} 
				else if( path__.hasFn( MFn::kPfxToon ) ) {
					RiSurface( "liquidpfxtoon", RI_NULL );
				}else if( path__.hasFn( MFn::kPfxGeometry ) ){
					RiSurface( "liquidpfx", RI_NULL );
				}else {
					//RiSurface( "plastic", RI_NULL );
					MFnDependencyNode shaderFn(shader);
					RiSurface( const_cast<char*>(shaderFn.name().asChar()), RI_NULL );
				}
			}
		}//if( hasSurfaceShader && !m_ignoreSurfaces )else
	} //if( writeShaders ) 
	else if( currentJob.deepShadows ) 
	{
		liqRIBMsg("[7] liqglo_currentJob[   ], hasSurfaceShader=%d, hasCustomSurfaceShader=%d",
			hasSurfaceShader__, hasCustomSurfaceShader__ );

		// if the current job is a deep shadow,
		// we still want to output primitive color and opacity and surface shader
		// In case of custom shaders, what should we do ? Stephane.
		if( hasSurfaceShader__ && ! hasCustomSurfaceShader__ ) 
		{
			//liqShader & currentShader = liqGetShader( ribNode__->assignedShader.object());
			liqShader &currentShader = liqShaderFactory::instance().getShader( ribNode__->assignedShader.object() );

			F1(ribNode__, currentShader);

			liqRIBMsg("[8] currentShader[.name=%s, .filename=%s, .outputInShadow=%d]", currentShader.name.c_str(), currentShader.file.c_str(), currentShader.outputInShadow );
			if(currentShader.outputInShadow){
				currentShader.write();
			}
		} 
		else //if( hasSurfaceShader__ && ! hasCustomSurfaceShader__ ) 
		{
			F2(false, ribNode__ );

			if( path__.hasFn( MFn::kPfxHair ) ) 
			{
				// get some of the hair system parameters
				RtFloat translucence = 0, specularPower = 0;
				RtColor specularColor;

				getPfxHairData(path__, translucence, specularPower, specularColor);

				RiSurface(  "liquidPfxHair",
					"float specularPower", &specularPower,
					"float translucence",  &translucence,
					"color specularColor", &specularColor,
					RI_NULL );
			}
		}
	}else {
		RiSurface( "null", RI_NULL );
	}


	return MS::kSuccess;
}
//
void liqRibTranslator::writeShadingGroup(const MString& meshname)
{
	RiArchiveRecord( RI_COMMENT, "use Shading Group reference:" );
	{
		MStringArray shadingGroupNode;
		{
			MString cmd = "listConnections -type \"shadingEngine\" -destination on (\""+meshname+"\" + \".instObjGroups\")";
			IfMErrorWarn(MGlobal::executeCommand( cmd, shadingGroupNode));
		}
		MString shadingGroupFileName;
		{
			MString wsdir;
			IfMErrorWarn(MGlobal::executeCommand( "workspace -q -rd", wsdir));
			MString shaderdir;
			IfMErrorWarn(MGlobal::executeCommand( "getAttr \"liquidGlobals.shaderDirectory\"", shaderdir));
			shaderdir = wsdir + shaderdir;

			IfMErrorWarn(MGlobal::executeCommand( "toLinuxPath(\""+shaderdir+"/"+MString(shadingGroupNode[0])+"\")", shadingGroupFileName));
		}
		RiReadArchive( const_cast< RtToken >((shadingGroupFileName+".rmsg").asChar()), NULL, RI_NULL );
	}
}