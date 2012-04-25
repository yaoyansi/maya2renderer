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


#include "./common/prerequest_std.h"

// Renderman Headers
//extern "C" {
#include "ri_interface.h"
//}


// Maya headers
#include "./common/prerequest_maya.h"
#include "./common/mayacheck.h"
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
#include "renderermgr.h"
#include "shadergraph/shadermgr.h"

using namespace boost;
using namespace std;

typedef int RtError;


#if defined(_WIN32)/* && !defined(DEFINED_LIQUIDVERSION)*/
// unix build gets this from the Makefile
extern const char *LIQUIDVERSION;
#endif

//void liqRibTranslator::freeShaders( void )
//{
//  LIQDEBUGPRINTF( "-> freeing shader data.\n" );
//  m_shaders.clear();
//  LIQDEBUGPRINTF( "-> finished freeing shader data.\n" );
//}

// Hmmmmm should change magic to Liquid
MString liqRibTranslator::magic("##Liquid");

#if(Refactoring==1)
static structJob liqglo_currentJob;
#endif
MComputation liqRibTranslator::m_escHandler;
/**
* Creates a new instance of the translator.
*/
void *liqRibTranslator::creator()
{
	mInstance = new liqRibTranslator();	
	return mInstance;// will be deleted by maya
}

// void liqRibTranslator::scanExpressions( liqRibLightData *light )
// {
// 	if( light != NULL ) 
// 	{
// 		vector<liqTokenPointer>::iterator iter = light->tokenPointerArray.begin();
// 		while ( iter != (light->tokenPointerArray.end()) ) 
// 		{
// 			if( iter->getParameterType() == rString ) 
// 			{
// 				liqTokenPointer i = *iter;
// 				processExpression( &i, light );
// 			}
// 			++iter;
// 		}
// 	}
// }

//liqShader & liqRibTranslator::liqGetShader( MObject shaderObj )
//{
//  MString rmShaderStr;
//
//  MFnDependencyNode shaderNode( shaderObj );
//  MPlug rmanShaderNamePlug = shaderNode.findPlug( MString( "rmanShaderLong" ) );
//  rmanShaderNamePlug.getValue( rmShaderStr );
//
//  LIQDEBUGPRINTF( "-> Using Renderman Shader %s\n", rmShaderStr.asChar() );
//
//  vector<liqShader>::iterator iter = m_shaders.begin();
//  while ( iter != m_shaders.end() )
//  {
//    string shaderNodeName = shaderNode.name().asChar();
//    if( iter->name == shaderNodeName ) 
//    {
//      // Already got it : nothing to do
//      return *iter;
//    }
//    ++iter;
//  }
//  liqShader currentShader( shaderObj );
//  m_shaders.push_back( currentShader );
//  return m_shaders.back();
//}

MStatus liqRibTranslator::liqShaderParseVectorAttr ( liqShader & currentShader, MFnDependencyNode & shaderNode, const char * argName, ParameterType pType )
{
	CM_TRACE_FUNC("liqRibTranslator::liqShaderParseVectorAttr(&currentShader,&shaderNode,"<<argName<<","<<pType<<")");

	MStatus status = MS::kSuccess;
	MPlug triplePlug = shaderNode.findPlug( argName, &status );
	if( status == MS::kSuccess ) 
	{
		float x, y, z;
		currentShader.tokenPointerArray.rbegin()->set( argName, pType, false, false, 0 );
		triplePlug.child( 0 ).getValue( x );
		triplePlug.child( 1 ).getValue( y );
		triplePlug.child( 2 ).getValue( z );
		currentShader.tokenPointerArray.rbegin()->setTokenFloat( 0, x, y, z );
		currentShader.tokenPointerArray.push_back( liqTokenPointer() );
		//currentShader.numTPV++;
	}
	return status;
}

void liqRibTranslator::printProgress( unsigned stat, unsigned numFrames, unsigned where )
// for printing the progress to the Maya Console or stdout. If alfred is being used it
// will print it in a format that causes the correct formatting for the progress meters
//
// TODO - should be able to set the progress output format somehow to cater for
// different render pipelines - with a user-specifiable string in printf format?
{
	//CM_TRACE_FUNC("liqRibTranslator::printProgress("<<stat<<","<<numFrames<<","<<where<<")");

	float statSize   = ( ( 1 / ( float )( numFrames + 1 ) ) / 4 ) * ( float )stat * 100.0;
	float progressf  = ( ( ( float )where / ( float )( numFrames + 1 ) ) * 100.0 ) + statSize;
	int progress     = ( int ) progressf;

	if( liqglo.liquidBin ) 
		printf( "ALF_PROGRESS %d%%\n", progress );
	else 
	{
		stringstream progressOutput;
		progressOutput << "Progress: frame "<< where <<", " << progress << "%" << ends;
		liquidMessage( progressOutput.str(), messageInfo );
	}
}

/**
* Checks to see if the liquidGlobals are available.
*/
bool liqRibTranslator::liquidInitGlobals()
{
	//CM_TRACE_FUNC("liqRibTranslator::liquidInitGlobals()");

	//trace log is not created, can't call CM_TRACE_FUNC("liqRibTranslator::liquidInitGlobals()");
	MStatus status;
	MSelectionList rGlobalList;
	status = rGlobalList.add( "liquidGlobals" );
	if( rGlobalList.length() > 0 ) 
	{
		status.clear();
		status = rGlobalList.getDependNode( 0, liqglo.rGlobalObj );
		if( status == MS::kSuccess ) 
			return true;
		else 
			return false;
	} 
	return false;
}

/**
* Class constructor.
*/
liqRibTranslator::liqRibTranslator()
{
	//CM_TRACE_FUNC("liqRibTranslator::liqRibTranslator()");

	char* envTmp;
	if( ( envTmp = getenv( "TMP" ) ) ||
		( envTmp = getenv( "TEMP" ) ) ||
		( envTmp = getenv( "TEMPDIR" ) ) ) 
	{
		m_systemTempDirectory = envTmp;
		m_systemTempDirectory = liquidSanitizePath( m_systemTempDirectory );
		LIQ_ADD_SLASH_IF_NEEDED( m_systemTempDirectory );
	}
	else 
	{
#ifndef _WIN32
		m_systemTempDirectory = "/tmp/";
#else
		m_systemTempDirectory = "%SystemRoot%/Temp/";
#endif
	}



	liqglo.liqglo_shortShaderNames = false;
	liqglo.liqglo_relativeFileNames = false;

	liqglo.frameNumbers.clear();

	m_showProgress = false;
	liqglo.m_deferredBlockSize = 1;
	liqglo.m_deferredGen = false;

	m_outputHeroPass = true;
	m_useNewTranslator = true;
	m_OutputShaderGraph = false;
	m_outputDebugMsgToRib = false;
	m_outputShadowPass = false;
	liqglo.m_illuminateByDefault = false;
	m_liquidSetLightLinking = false;
	m_ignoreLights = false;
	m_ignoreSurfaces = false;
	m_ignoreDisplacements = false;
	m_ignoreVolumes = false;
	m_renderAllCurves = false;
	m_renderSelected = false;
	liqglo.m_exportReadArchive = false;
	liqglo.useNetRman = false;
	liqglo.remoteRender = false;
	useRenderScript = true;
	liqglo.cleanRib = false;
	cleanRenderScript = false;
	liqglo.liqglo_doBinary = false;
	liqglo.liqglo_doCompression = false;
	initCameraParameters();


	liqglo.liqglo_doMotion = false;          // matrix motion blocks
	liqglo.liqglo_doDef = false;             // geometry motion blocks
	liqglo.liqglo_relativeMotion = false;

	liqglo.liqglo_doExtensionPadding = false;       // pad the frame number in the rib file names
	liqglo.liqglo_doShadows = true;          // render shadows
	liqglo.liqglo_shapeOnlyInShadowNames = false;
	liqglo.liqglo_noSingleFrameShadows = false;
	liqglo.liqglo_singleFrameShadowsOnly = false;
	m_justRib = false;
	cleanShadows = 0;                 // render shadows
	cleanTextures = 0;                // render shadows
	
	initOtherParameters();

	depth = 1;

	m_animation = false;
	m_useFrameExt = true;  // Use frame extensions

	liqglo.liqglo_motionSamples = 2;
	liqglo.liqglo_FPS = 24.0;
	width = 360;
	height = 243;

	liqglo.liqglo_outPadding = 0;
	ignoreFilmGate = true;
	m_lazyCompute = false;
	m_outputShadersInShadows = false;
	m_outputShadersInDeepShadows = false;
	m_outputLightsInDeepShadows = false;
	liqglo.m_alfredExpand = false;
#ifdef DEBUG
	debugMode = 1;
#else
	debugMode = 0;
#endif
	m_errorMode = 0;
//	extension = ".rib";

	initLimitsParameters();

	liqglo.liqglo_shutterTime = 0.5;
	liqglo.liqglo_shutterEfficiency = 1.0;

	m_blurTime = 1.0;
	liqglo.fullShadowRib = false;
	baseShadowName = "";

	liqglo.liqglo_projectDir = m_systemTempDirectory;

	m_tmpDir = "rmantmp/";
	liqglo.liqglo_preReadArchive.clear();
	liqglo.liqglo_preRibBox.clear();
	liqglo.m_alfredTags.clear();
	liqglo.m_alfredServices.clear();
	liqglo.m_dirmaps.clear();
	liqglo.m_defGenKey.clear();
	liqglo.m_defGenService.clear();
	m_preFrameMel.clear();
	m_postFrameMel.clear();
	liqglo.m_preCommand.clear();
	m_preJobCommand.clear();
	m_postJobCommand.clear();
	m_postFrameCommand.clear();
	m_preFrameCommand.clear();
	m_preTransformMel.clear();
	m_postTransformMel.clear();
	m_preShapeMel.clear();
	m_postShapeMel.clear();
	liqglo.m_outputComments = false;
	m_shaderDebug = false;
	// raytracing
	liqglo.rt_useRayTracing = false;
	liqglo.rt_traceBreadthFactor = 1.0;
	liqglo.rt_traceDepthFactor = 1.0;
	liqglo.rt_traceMaxDepth = 10;
	liqglo.rt_traceSpecularThreshold = 10.0;
	liqglo.rt_traceRayContinuation = 1;
	liqglo.rt_traceCacheMemory = 30720;
	liqglo.rt_traceDisplacements = false;
	liqglo.rt_traceSampleMotion = false;
	liqglo.rt_traceBias = 0.05;
	liqglo.rt_traceMaxDiffuseDepth = 2;
	liqglo.rt_traceMaxSpecularDepth = 2;
	liqglo.liqglo_shotName.clear();
	liqglo.liqglo_shotVersion.clear();
	liqglo.liqglo_layer.clear();

#ifdef AIR
	m_renderCommand = "air";
#elif defined( AQSIS )
	m_renderCommand = "aqsis";
#elif defined( DELIGHT )
	m_renderCommand = "renderdl";
#elif defined( PIXIE )
	m_renderCommand = "rndr";
#elif defined( PRMAN )
#ifdef _WIN32
	m_renderCommand = "prman";
#else
	m_renderCommand = "render";
#endif
#endif
	
	 m_minCPU =  m_maxCPU = 1;

	m_ribgenCommand = "liquid";
	createOutputDirectories = true;
	liqglo.liqglo_expandShaderArrays = false;



	initStatisticsParameters();

	initHinderParameters();


	liqglo.liqglo_isShadowPass = false;



	liqglo.m_preWorldRIB.clear();
	liqglo.m_postWorldRIB.clear();
	m_preGeomRIB.clear();

	m_renderScriptFormat = XML;

	liqglo.liqglo_useMtorSubdiv = false;
	liqglo.liqglo_outputMayaPolyCreases = false;
	liqglo.liqglo_renderAllCurves = false;
	liqglo.liqglo_hider = htHidden;

	liqglo.liqglo_ribDir = "rib";
	liqglo.liqglo_textureDir = "rmantex";

	liqglo.liqglo_shaderPath = "&:@:.:~:rmanshader";
	liqglo.liqglo_texturePath = "&:@:.:~:" + liqglo.liqglo_textureDir;
	liqglo.liqglo_archivePath = "&:@:.:~:" + liqglo.liqglo_ribDir;
	liqglo.liqglo_proceduralPath = "&:@:.:~";



	MString tmphome( getenv( "LIQUIDHOME" ) );
	tmphome = liquidSanitizeSearchPath( tmphome );

	if( tmphome != "" ) 
	{
		liqglo.liqglo_shaderPath += ":" + tmphome + "/lib/shaders";
		liqglo.liqglo_texturePath += ":" + tmphome + "/lib/textures";
		liqglo.liqglo_archivePath += ":" + tmphome + "/lib/rib";
	}

	liqglo.liqglo_shaderPath += ":" + tmphome + "/lib/shaders";
	liqglo.liqglo_texturePath += ":" + tmphome + "/lib/textures";
	liqglo.liqglo_archivePath += ":" + tmphome + "/lib/rib";
}


/**
* Class destructor
*/
liqRibTranslator::~liqRibTranslator()
{
	//CM_TRACE_FUNC("liqRibTranslator::~liqRibTranslator()");

	//delete mInstance;
	//mInstance = NULL;
}

/**
* Error handling function.
* This gets called when the RIB library detects an error.
*/
#if defined( DELIGHT ) || defined( ENTROPY ) ||  defined( PRMAN ) || defined( AIR ) || defined( PIXIE ) || defined( GENERIC_RIBLIB ) 
void liqRibTranslatorErrorHandler( RtInt code, RtInt severity, char* message )
#else
void liqRibTranslatorErrorHandler( RtInt code, RtInt severity, const char* message )
#endif
{
	liquidMessage2(messageError, "The renderman library is reporting and error! Code: %d  Severity: %d", code, severity );
	MString error( message );
	throw error;
}

MSyntax liqRibTranslator::syntax()
{
	//CM_TRACE_FUNC("liqRibTranslator::syntax()");

	MSyntax syntax;

	syntax.addFlag("lr",    "launchRender");
	syntax.addFlag("nolr",  "noLaunchRender");
	syntax.addFlag("GL",    "useGlobals");
	syntax.addFlag("sel",   "selected");
	syntax.addFlag("ra",    "readArchive");
	syntax.addFlag("acv",   "allCurves");
	syntax.addFlag("tif",   "tiff");
	syntax.addFlag("dof",   "dofOn");
	syntax.addFlag("bin",   "doBinary");
	syntax.addFlag("sh",    "shadows");
	syntax.addFlag("nsh",   "noShadows");
	syntax.addFlag("zip",   "doCompression");
	syntax.addFlag("cln",   "cleanRib");
	syntax.addFlag("pro",   "progress");
	syntax.addFlag("mb",    "motionBlur");
	syntax.addFlag("rmot",  "relativeMotion");
	syntax.addFlag("db",    "deformationBlur");
	syntax.addFlag("d",     "debug");
	syntax.addFlag("net",   "netRender");
	syntax.addFlag("fsr",   "fullShadowRib");
	syntax.addFlag("rem",   "remote");
	syntax.addFlag("rs",    "renderScript");
	syntax.addFlag("nrs",   "noRenderScript");
	syntax.addFlag("err",   "errHandler");
	syntax.addFlag("sdb",   "shaderDebug");
	syntax.addFlag("n",     "sequence",         MSyntax::kLong, MSyntax::kLong, MSyntax::kLong);
	syntax.addFlag("fl",    "frameList",        MSyntax::kString);
	syntax.addFlag("m",     "mbSamples",        MSyntax::kLong);
	syntax.addFlag("dbs",   "defBlock");
	syntax.addFlag("cam",   "camera",           MSyntax::kString);
	syntax.addFlag("rcam",  "rotateCamera");
	syntax.addFlag("s",     "samples",          MSyntax::kLong);
	syntax.addFlag("rnm",   "ribName",          MSyntax::kString);
	syntax.addFlag("pd",    "projectDir",       MSyntax::kString);
	syntax.addFlag("rel",   "relativeDirs");
	syntax.addFlag("prm",   "preFrameMel",      MSyntax::kString);
	syntax.addFlag("pom",   "postFrameMel",     MSyntax::kString);
	syntax.addFlag("rid",   "ribdir",           MSyntax::kString);
	syntax.addFlag("txd",   "texdir",           MSyntax::kString);
	syntax.addFlag("tmd",   "tmpdir",           MSyntax::kString);
	syntax.addFlag("pid",   "picdir",           MSyntax::kString);
	syntax.addFlag("pec",   "preCommand",       MSyntax::kString);
	syntax.addFlag("poc",   "postJobCommand",   MSyntax::kString);
	syntax.addFlag("pof",   "postFrameCommand", MSyntax::kString);
	syntax.addFlag("prf",   "preFrameCommand",  MSyntax::kString);
	syntax.addFlag("rec",   "renderCommand",    MSyntax::kString);
	syntax.addFlag("rgc",   "ribgenCommand",    MSyntax::kString);
	syntax.addFlag("blt",   "blurTime",         MSyntax::kDouble);
	syntax.addFlag("sr",    "shadingRate",      MSyntax::kDouble);
	syntax.addFlag("bs",    "bucketSize",       MSyntax::kLong, MSyntax::kLong);
	syntax.addFlag("pf",    "pixelFilter",      MSyntax::kLong, MSyntax::kLong, MSyntax::kLong);
	syntax.addFlag("gs",    "gridSize",         MSyntax::kLong);
	syntax.addFlag("txm",   "texmem",           MSyntax::kLong);
	syntax.addFlag("es",    "eyeSplits",        MSyntax::kLong);
	syntax.addFlag("ar",    "aspect",           MSyntax::kDouble);
	syntax.addFlag("x",     "width",            MSyntax::kLong);
	syntax.addFlag("y",     "height",           MSyntax::kLong);
	syntax.addFlag("cw",    "cropWindow",       MSyntax::kLong, MSyntax::kLong, MSyntax::kLong, MSyntax::kLong);
	syntax.addFlag("def",   "deferred");
	syntax.addFlag("ndf",   "noDef");
	syntax.addFlag("pad",   "padding",          MSyntax::kLong);
	syntax.addFlag("rgo",   "ribGenOnly");
	syntax.addFlag("sfso",  "singleFrameShadowsOnly");
	syntax.addFlag("nsfs",  "noSingleFrameShadows");
	syntax.addFlag("rv",    "renderView");
	syntax.addFlag("rvl",   "renderViewlocal");
	syntax.addFlag("rvp",   "renderViewPort",  MSyntax::kLong);
	syntax.addFlag("shn",   "shotName",        MSyntax::kString);
	syntax.addFlag("shv",   "shotVersion",     MSyntax::kString);
	syntax.addFlag("lyr",   "layer",           MSyntax::kString);
//	syntax.addFlag("lrp",   "currentLayerRifParameters",           MSyntax::kString);

	return syntax;
}

/**
* Read the values from the command line and set the internal values.
*/
MStatus liqRibTranslator::liquidDoArgs( MArgList args )
{
	//CM_TRACE_FUNC("liqRibTranslator::liquidDoArgs(args)");

	MStatus status;
	MString argValue;

	LIQDEBUGPRINTF( "-> processing arguments\n" );

	// Parse the arguments and set the options.
	if( args.length() == 0 ) 
	{
		liquidMessage( "Doing nothing, no parameters given", messageError );
		return MS::kFailure;
	}
	// find the activeView for previews;
	width        = M3dView::active3dView().portWidth();
	height       = M3dView::active3dView().portHeight();

	// get the current project directory
	MString MELCommand = "workspace -q -rd";
	MString MELReturn;
	MGlobal::executeCommand( MELCommand, MELReturn );
	liqglo.liqglo_projectDir = MELReturn;

	// get the current scene name
	//liqglo.liqglo_sceneName = liquidTransGetSceneName();

	// setup default animation parameters
	liqglo.frameNumbers.push_back( ( int )MAnimControl::currentTime().as( MTime::uiUnit() ) );

	// check to see if the correct project directory was found
	/*if( !fileFullyAccessible( liqglo_projectDir ) ) {
	liqglo_projectDir = m_systemTempDirectory;
	liquidMessage( "Trying to set project directory to system temp directory '" + string( liqglo_projectDir.asChar() ) + "'.", messageWarning );
	}*/
	LIQ_ADD_SLASH_IF_NEEDED( liqglo.liqglo_projectDir );
	if( !fileFullyAccessible( liqglo.liqglo_projectDir ) ) 
	{
		liquidMessage( "Cannot find project directory, '" + string( liqglo.liqglo_projectDir.asChar() ) + "'. Defaulting to system temp directory!", messageWarning );
		liqglo.liqglo_projectDir = m_systemTempDirectory;
	}

	bool GL_read( false );

	for( unsigned i( 0 ); i < args.length(); i++ ) 
	{
		MString arg = args.asString( i, &status );
		if((arg == "-lr") || (arg == "-launchRender")) 
		{
			LIQCHECKSTATUS(status, "error in -launchRender parameter");
			liqglo.launchRender = true;
		} 
		else if((arg == "-nolr") || (arg == "-noLaunchRender")) 
		{
			LIQCHECKSTATUS(status, "error in -noLaunchRender parameter");
			liqglo.launchRender = false;
		} 
		else if((arg == "-GL") || (arg == "-useGlobals")) 
		{
			LIQCHECKSTATUS(status, "error in -useGlobals parameter");
			//load up all the render global parameters!
			if( liquidInitGlobals() && !GL_read ) 
				liquidReadGlobals();
			//liquidMessage( "Globals loaded...", messageInfo );
			GL_read = true;
		} 
		else if((arg == "-sel") || (arg == "-selected")) 
		{
			LIQCHECKSTATUS(status, "error in -selected parameter");
			m_renderSelected = true;
		} 
		else if((arg == "-ra") || (arg == "-readArchive")) 
		{
			LIQCHECKSTATUS(status, "error in -readArchive parameter");
			liqglo.m_exportReadArchive = true;
		} 
		else if((arg == "-acv") || (arg == "-allCurves")) 
		{
			LIQCHECKSTATUS(status, "error in -allCurves parameter" );
			m_renderAllCurves = true;
		} 
		else if((arg == "-tif") || (arg == "-tiff")) 
		{
			LIQCHECKSTATUS(status, "error in -tiff parameter");
			liqglo.outFormat = "tiff";
		} 
		else if((arg == "-dof") || (arg == "-dofOn")) 
		{
			LIQCHECKSTATUS(status, "error in -dofOn parameter");
			liqglo.doDof = true;
		} 
		else if((arg == "-bin") || (arg == "-doBinary")) 
		{
			LIQCHECKSTATUS(status, "error in -doBinary parameter");
			liqglo.liqglo_doBinary = true;
		} 
		else if((arg == "-sh") || (arg == "-shadows")) 
		{
			LIQCHECKSTATUS(status, "error in -shadows parameter");
			liqglo.liqglo_doShadows = true;
		} 
		else if((arg == "-nsh") || (arg == "-noShadows")) 
		{
			LIQCHECKSTATUS(status, "error in -noShadows parameter");
			liqglo.liqglo_doShadows = false;
		} 
		else if((arg == "-zip") || (arg == "-doCompression")) 
		{
			LIQCHECKSTATUS(status, "error in -doCompression parameter");
			liqglo.liqglo_doCompression = true;
		} 
		else if((arg == "-cln") || (arg == "-cleanRib")) 
		{
			LIQCHECKSTATUS(status, "error in -cleanRib parameter");
			liqglo.cleanRib = true;
		} 
		else if((arg == "-cmd") || (arg == "-createMissingDirs")) 
		{
			LIQCHECKSTATUS(status, "error in -createMissingDirs parameter");
			createOutputDirectories = true;
		} 
		else if((arg == "-pro") || (arg == "-progress")) 
		{
			LIQCHECKSTATUS(status, "error in -progress parameter");
			m_showProgress = true;
		} 
		else if((arg == "-mb") || (arg == "-motionBlur")) 
		{
			LIQCHECKSTATUS(status, "error in -motionBlur parameter");
			liqglo.liqglo_doMotion = true;
		} 
		else if((arg == "-db") || (arg == "-deformationBlur")) 
		{
			LIQCHECKSTATUS(status, "error in -deformationBlur parameter");
			liqglo.liqglo_doDef = true;
		} 
		else if((arg == "-d") || (arg == "-debug")) 
		{
			LIQCHECKSTATUS(status, "error in -debug parameter");
			debugMode = 1;
		} 
		else if((arg == "-net") || (arg == "-netRender")) 
		{
			LIQCHECKSTATUS(status, "error in -netRender parameter");
			liqglo.useNetRman = true;
		} 
		else if((arg == "-fsr") || (arg == "-fullShadowRib")) 
		{
			LIQCHECKSTATUS(status, "error in -fullShadowRib parameter");
			liqglo.fullShadowRib = true;
		} 
		else if((arg == "-rem") || (arg == "-remote")) 
		{
			LIQCHECKSTATUS(status, "error in -remote parameter");
			liqglo.remoteRender = true;
		} 
		else if((arg == "-rs") || (arg == "-renderScript")) 
		{
			LIQCHECKSTATUS(status, "error in -renderScript parameter");
			useRenderScript = true;
		} 
		else if((arg == "-nrs") || (arg == "-noRenderScript")) 
		{
			LIQCHECKSTATUS(status, "error in -noRenderScript parameter");
			useRenderScript = false;
		} 
		else if((arg == "-err") || (arg == "-errHandler")) 
		{
			LIQCHECKSTATUS(status, "error in -errHandler parameter");
			m_errorMode = 1;
		} 
		else if((arg == "-sdb") || (arg == "-shaderDebug")) 
		{
			LIQCHECKSTATUS(status, "error in -shaderDebug parameter");
			m_shaderDebug = true;
		} 
		else if((arg == "-n") || (arg == "-sequence")) 
		{
			LIQCHECKSTATUS(status, "error in -sequence parameter");   i++;
			argValue = args.asString( i, &status );
			int first( argValue.asInt() );
			LIQCHECKSTATUS(status, "error in -sequence parameter");  i++;
			argValue = args.asString( i, &status );
			int last( argValue.asInt() );
			LIQCHECKSTATUS(status, "error in -sequence parameter");  i++;
			argValue = args.asString( i, &status );
			int step( argValue.asInt() );
			LIQCHECKSTATUS(status, "error in -sequence parameter");
			m_animation = true;
			if( first > last ) 
				step = -abs( step );
			// Fill our vector with frames
			liqglo.frameNumbers.clear();
			for ( int frame( first ); frame <= last; frame += step ) 
				liqglo.frameNumbers.push_back( frame );
		} 
		else if((arg == "-fl") || (arg == "-frameList") ) 
		{
			LIQCHECKSTATUS(status, "error in -fl/-frameList");   i++;
			argValue = args.asString( i, &status );
			// fill our vector with frames
			liqglo.frameNumbers = generateFrameNumbers( string( argValue.asChar() ) );
			if( liqglo.frameNumbers.size() ) { 
				m_animation = true;
				//liquidMessage2(messageInfo, ">>> render frames: ");
				//for( unsigned i(0) ; i < frameNumbers.size() ; i++ )
				//  liquidMessage2(messageInfo, "%d ", frameNumbers[i] );
				//liquidMessage2(messageInfo, "\n");
			}
		} 
		else if((arg == "-m") || (arg == "-mbSamples")) 
		{
			LIQCHECKSTATUS(status, "error in -mbSamples parameter");   i++;
			argValue = args.asString( i, &status );
			liqglo.liqglo_motionSamples = argValue.asInt();
			LIQCHECKSTATUS(status, "error in -mbSamples parameter");
		} 
		else if((arg == "-rmot") || (arg == "-relativeMotion")) 
		{
			LIQCHECKSTATUS(status, "error in -relativeMotion parameter");
			liqglo.liqglo_relativeMotion = true;
		} 
		else if((arg == "-dbs") || (arg == "-defBlock")) 
		{
			LIQCHECKSTATUS(status, "error in -defBlock parameter");   i++;
			argValue = args.asString( i, &status );
			liqglo.m_deferredBlockSize = argValue.asInt();
			LIQCHECKSTATUS(status, "error in -defBlock parameter");
		} 
		else if((arg == "-cam") || (arg == "-camera")) 
		{
			LIQCHECKSTATUS(status, "error in -camera parameter");   i++;
			liqglo.renderCamera = args.asString( i, &status );
			liqglo.liqglo_renderCamera = liqglo.renderCamera;
			LIQCHECKSTATUS(status, "error in -camera parameter");
		} 
		else if((arg == "-rcam") || (arg == "-rotateCamera")) 
		{
			LIQCHECKSTATUS(status, "error in -rotateCamera parameter");
			liqglo.liqglo_rotateCamera = true;
		} 
		else if((arg == "-s") || (arg == "-samples")) 
		{
			LIQCHECKSTATUS(status, "error in -samples parameter");  i++;
			argValue = args.asString( i, &status );
			liqglo.pixelSamples = argValue.asInt();
			LIQCHECKSTATUS(status, "error in -samples parameter");
		} 
		else if((arg == "-rnm") || (arg == "-ribName")) 
		{
			LIQCHECKSTATUS(status, "error in -ribName parameter");  i++;
			MString parsingString = args.asString( i, &status );
			//Note:  -ribName is set to liqglo.liqglo_sceneName originally. 
			//       Because we replace liqglo.liqglo_sceneName with liquidTransGetSceneName(), and delete liqglo.liqglo_sceneName,
			//       we use liqglo.liqglo_ribName to store the ribName which passed by commandline parameter '-ribName'
			//  [2/17/2012 yaoyansi]
			assert(0&&"warrning: ribName is store in liqglo.liqglo_ribName instead of liqglo.liqglo_sceneName.[2/17/2012 yaoyansi]");
#if 0
			liqglo.liqglo_sceneName = parseString( parsingString );
#else
			liqglo.liqglo_ribName = parseString( parsingString );
#endif
			LIQCHECKSTATUS(status, "error in -ribName parameter");
		} 
		else if((arg == "-rel") || (arg == "-relativeDirs")) 
		{
			LIQCHECKSTATUS(status, "error in -relativeDirs parameter");
			liqglo.liqglo_relativeFileNames = true;
		} 
		else if((arg == "-pd") || (arg == "-projectDir")) 
		{
			LIQCHECKSTATUS(status, "error in -projectDir parameter");  i++;
			MString parsingString = args.asString( i, &status );
			liqglo.liqglo_projectDir = parseString( parsingString, false );
			LIQ_ADD_SLASH_IF_NEEDED( liqglo.liqglo_projectDir );
#ifdef _WIN32
			int dirMode = 6; // dummy arg
			int mkdirMode = 0;
#else
			mode_t dirMode, mkdirMode;
			dirMode = R_OK|W_OK|X_OK|F_OK;
			mkdirMode = S_IRWXU|S_IRWXG|S_IRWXO;
#endif
			if( createOutputDirectories ) 
				makeFullPath( liqglo.liqglo_projectDir.asChar(), mkdirMode );
			if( !fileFullyAccessible( liqglo.liqglo_projectDir ) ) 
			{
				liquidMessage( "Cannot find or access Maya project directory; defaulting to system temp directory!", messageWarning );
				liqglo.liqglo_projectDir = m_systemTempDirectory;
			}
			LIQCHECKSTATUS(status, "error in -projectDir parameter");
		} 
		else if((arg == "-prm") || (arg == "-preFrameMel")) 
		{
			LIQCHECKSTATUS(status, "error in -preFrameMel parameter");  i++;
			m_preFrameMel =  args.asString( i, &status );
			LIQCHECKSTATUS(status, "error in -preFrameMel parameter");
		} 
		else if((arg == "-pom") || (arg == "-postFrameMel")) 
		{
			LIQCHECKSTATUS(status, "error in -postFrameMel parameter");  i++;
			m_postFrameMel = args.asString( i, &status );
			LIQCHECKSTATUS(status, "error in -postFrameMel parameter");
		} 
		else if((arg == "-rid") || (arg == "-ribdir")) 
		{
			LIQCHECKSTATUS(status, "error in -ribdir parameter");  i++;
			MString parsingString = args.asString( i, &status );
			liqglo.liqglo_ribDir = parseString( parsingString, false );
			LIQCHECKSTATUS(status, "error in -ribdir parameter");
		} 
		else if((arg == "-txd") || (arg == "-texdir")) 
		{
			LIQCHECKSTATUS(status, "error in -texdir parameter");  i++;
			MString parsingString = args.asString( i, &status );
			liqglo.liqglo_textureDir = parseString( parsingString, false );
			LIQCHECKSTATUS(status, "error in -texdir parameter");
		} 
		else if((arg == "-tmd") || (arg == "-tmpdir")) 
		{
			LIQCHECKSTATUS(status, "error in -tmpdir parameter");  i++;
			MString parsingString = args.asString( i, &status );
			m_tmpDir = parseString( parsingString, false );
			LIQCHECKSTATUS(status, "error in -tmpdir parameter");
		} 
		else if((arg == "-pid") || (arg == "-picdir")) 
		{
			LIQCHECKSTATUS(status, "error in -picdir parameter");  i++;
			MString parsingString = args.asString( i, &status );
			liqglo.m_pixDir = parseString( parsingString, false );
			LIQCHECKSTATUS(status, "error in -picdir parameter");
		} 
		else if((arg == "-pec") || (arg == "-preCommand")) 
		{
			LIQCHECKSTATUS(status, "error in -preCommand parameter");  i++;
			liqglo.m_preCommand = args.asString( i, &status );
			LIQCHECKSTATUS(status, "error in -preCommand parameter");
		} 
		else if((arg == "-poc") || (arg == "-postJobCommand")) 
		{
			LIQCHECKSTATUS(status, "error in -postJobCommand parameter");  i++;
			MString varVal = args.asString( i, &status );
			m_postJobCommand = parseString( varVal );
			LIQCHECKSTATUS(status, "error in -postJobCommand parameter");
		} 
		else if((arg == "-pof") || (arg == "-postFrameCommand")) 
		{
			LIQCHECKSTATUS(status, "error in -postFrameCommand parameter");  i++;
			m_postFrameCommand = args.asString( i, &status );
			LIQCHECKSTATUS(status, "error in -postFrameCommand parameter");
		} 
		else if((arg == "-prf") || (arg == "-preFrameCommand")) 
		{
			LIQCHECKSTATUS(status, "error in -preFrameCommand parameter");  i++;
			m_preFrameCommand = args.asString( i, &status );
			LIQCHECKSTATUS(status, "error in -preFrameCommand parameter");
		} 
		else if((arg == "-rec") || (arg == "-renderCommand")) 
		{
			LIQCHECKSTATUS(status, "error in -renderCommand parameter");  i++;
			m_renderCommand = args.asString( i, &status );
			LIQCHECKSTATUS(status, "error in -renderCommand parameter");
		} 
		else if((arg == "-rgc") || (arg == "-ribgenCommand")) 
		{
			LIQCHECKSTATUS(status, "error in -ribgenCommand parameter");  i++;
			m_ribgenCommand = args.asString( i, &status );
			LIQCHECKSTATUS(status, "error in -ribgenCommand parameter");
		} 
		else if((arg == "-blt") || (arg == "-blurTime")) 
		{
			LIQCHECKSTATUS(status, "error in -blurTime parameter");  i++;
			argValue = args.asString( i, &status );
			m_blurTime = argValue.asDouble();
			LIQCHECKSTATUS(status, "error in -blurTime parameter");
		} 
		else if((arg == "-sr") || (arg == "-shadingRate")) 
		{
			LIQCHECKSTATUS(status, "error in -shadingRate parameter");  i++;
			argValue = args.asString( i, &status );
			liqglo.shadingRate = argValue.asDouble();
			LIQCHECKSTATUS(status, "error in -shadingRate parameter");
		} 
		else if((arg == "-bs") || (arg == "-bucketSize")) 
		{
			LIQCHECKSTATUS(status, "error in -bucketSize parameter");  i++;
			argValue = args.asString( i, &status );
			liqglo.bucketSize[0] = argValue.asInt();
			LIQCHECKSTATUS(status, "error in -bucketSize parameter");  i++;
			argValue = args.asString( i, &status );
			liqglo.bucketSize[1] = argValue.asInt();
			LIQCHECKSTATUS(status, "error in -bucketSize parameter");
		} 
		else if((arg == "-pf") || (arg == "-pixelFilter")) 
		{
			LIQCHECKSTATUS(status, "error in -pixelFilter parameter");  i++;
			argValue = args.asString( i, &status );
			liqglo.m_rFilter = argValue.asInt();
			LIQCHECKSTATUS(status, "error in -pixelFilter parameter");  i++;
			argValue = args.asString( i, &status );
			liqglo.m_rFilterX = argValue.asInt();
			LIQCHECKSTATUS(status, "error in -pixelFilter parameter");  i++;
			argValue = args.asString( i, &status );
			liqglo.m_rFilterY = argValue.asInt();
			LIQCHECKSTATUS(status, "error in -pixelFilter parameter");
		} 
		else if((arg == "-gs") || (arg == "-gridSize")) 
		{
			LIQCHECKSTATUS(status, "error in -gridSize parameter");  i++;
			argValue = args.asString( i, &status );
			liqglo.gridSize = argValue.asInt();
			LIQCHECKSTATUS(status, "error in -gridSize parameter");
		} 
		else if((arg == "-txm") || (arg == "-texmem")) 
		{
			LIQCHECKSTATUS(status, "error in -texmem parameter");  i++;
			argValue = args.asString( i, &status );
			liqglo.textureMemory = argValue.asInt();
			LIQCHECKSTATUS(status, "error in -texmem parameter");
		} 
		else if((arg == "-es") || (arg == "-eyeSplits")) 
		{
			LIQCHECKSTATUS(status, "error in -eyeSplits parameter");  i++;
			argValue = args.asString( i, &status );
			liqglo.eyeSplits = argValue.asInt();
			LIQCHECKSTATUS(status, "error in -eyeSplits parameter");
		} 
		else if((arg == "-ar") || (arg == "-aspect")) 
		{
			LIQCHECKSTATUS(status, "error in -aspect parameter");  i++;
			argValue = args.asString( i, &status );
			liqglo.aspectRatio = argValue.asDouble();
			LIQCHECKSTATUS(status, "error in -aspect parameter");
		} 
		else if((arg == "-x") || (arg == "-width")) 
		{
			LIQCHECKSTATUS(status, "error in -width parameter");  i++;
			argValue = args.asString( i, &status );
			width = argValue.asInt();
			LIQCHECKSTATUS(status, "error in -width parameter");
		} 
		else if((arg == "-y") || (arg == "-height")) 
		{
			LIQCHECKSTATUS(status, "error in -height parameter");  i++;
			argValue = args.asString( i, &status );
			height = argValue.asInt();
			LIQCHECKSTATUS(status, "error in -height parameter");
		} 
		else if((arg == "-def") || (arg == "-deferred")) 
		{
			LIQCHECKSTATUS(status, "error in -deferred parameter");
			liqglo.m_deferredGen = true;
		} 
		else if((arg == "-ndf") || (arg == "-noDef")) 
		{
			LIQCHECKSTATUS(status, "error in -noDef parameter");
			liqglo.m_deferredGen = false;
		} 
		else if((arg == "-pad") || (arg == "-padding")) 
		{
			LIQCHECKSTATUS(status, "error in -padding parameter");  i++;
			argValue = args.asString( i, &status );
			liqglo.liqglo_outPadding = argValue.asInt();
			LIQCHECKSTATUS(status, "error in -padding parameter");
		} 
		else if((arg == "-rgo") || (arg == "-ribGenOnly")) 
		{
			LIQCHECKSTATUS(status, "error in -ribGenOnly parameter");
			m_justRib = true;
		} 
		else if((arg == "-rv") || (arg == "-renderView")) 
		{
			LIQCHECKSTATUS(status, "error in -renderView parameter");
			liqglo.m_renderView = true;
		} 
		else if((arg == "-rvl") || (arg == "-renderViewLocal")) 
		{
			LIQCHECKSTATUS(status, "error in -renderViewLocal parameter");
			liqglo.m_renderViewLocal = true;
		} 
		else if((arg == "-rvp") || (arg == "-renderViewPort")) 
		{
			LIQCHECKSTATUS(status, "error in -renderViewPort parameter");  i++;
			argValue = args.asString( i, &status );
			liqglo.m_renderViewPort = argValue.asInt();
		} 
		else if((arg == "-cw") || (arg == "-cropWindow")) 
		{
			LIQCHECKSTATUS(status, "error in -cropWindow parameter");  i++;
			argValue = args.asString( i, &status );
			liqglo.m_cropX1 = argValue.asDouble();
			LIQCHECKSTATUS(status, "error in -cropWindow parameter 1");  i++;
			argValue = args.asString( i, &status );
			liqglo.m_cropX2 = argValue.asDouble();
			LIQCHECKSTATUS(status, "error in -cropWindow parameter 2");  i++;
			argValue = args.asString( i, &status );
			liqglo.m_cropY1 = argValue.asDouble();
			LIQCHECKSTATUS(status, "error in -cropWindow parameter 3");  i++;
			argValue = args.asString( i, &status );
			liqglo.m_cropY2 = argValue.asDouble();
			LIQCHECKSTATUS(status, "error in -cropWindow parameter 4");
			if( liqglo.m_renderView ) 
				liqglo.m_renderViewCrop = true;
		} 
		else if((arg == "-nsfs") || (arg == "-noSingleFrameShadows")) 
		{
			LIQCHECKSTATUS(status, "error in -noSingleFrameShadows parameter");
			liqglo.liqglo_noSingleFrameShadows = true;
		} 
		else if((arg == "-sfso") || (arg == "-singleFrameShadowsOnly")) 
		{
			LIQCHECKSTATUS(status, "error in -singleFrameShadowsOnly parameter");
			liqglo.liqglo_singleFrameShadowsOnly = true;
		} 
		else if((arg == "-shn") || (arg == "-shotName")) 
		{
			LIQCHECKSTATUS(status, "error in -shotName parameter");   i++;
			liqglo.liqglo_shotName = args.asString( i, &status );
		} 
		else if((arg == "-shv") || (arg == "-shotVersion")) 
		{
			LIQCHECKSTATUS(status, "error in -shotVersion parameter");  i++;
			liqglo.liqglo_shotVersion = args.asString( i, &status );
		}
	}
	liquidMessage( "Using project base path '" + string( liqglo.liqglo_projectDir.asChar() ) + "'", messageInfo );
	setSearchPaths();
	return MS::kSuccess;
}

/**
* Read the values from the render globals and set internal values.
*/
void liqRibTranslator::liquidReadGlobals()
{
	//CM_TRACE_FUNC("liqRibTranslator::liquidReadGlobals()");

	//trace log is not created, can't call CM_TRACE_FUNC("liqRibTranslator::liquidReadGlobals()");
	MStatus gStatus;
	MPlug gPlug;
	MFnDependencyNode rGlobalNode( liqglo.rGlobalObj );
	MString varVal;
	int var;
	// Display Channels - Read and store 'em !
	// philippe : channels are stored as structures in a vector
	{
		if( liqglo.liquidRenderer.supports_DISPLAY_CHANNELS ) 
		{
			liqglo.m_channels.clear();
			unsigned int nChannels = liquidGetPlugNumElements( rGlobalNode, "channelName", &gStatus );

			for ( unsigned i( 0 ); i < nChannels; i++ ) 
			{
				StructChannel theChannel;
				gStatus.clear();
				gPlug = rGlobalNode.findPlug( "channelName", &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					gStatus.clear();
					MPlug elementPlug;
					elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
					if( gStatus == MS::kSuccess ) 
					{
						MString val;
						elementPlug.getValue( val );
						theChannel.name = val;
					}
				}
				gStatus.clear();
				gPlug = rGlobalNode.findPlug( "channelType", &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					gStatus.clear();
					MPlug elementPlug;
					elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
					if( gStatus == MS::kSuccess ) 
					{
						int val;
						elementPlug.getValue( val );
						theChannel.type = val;
					}
				}
				gStatus.clear();
				gPlug = rGlobalNode.findPlug( "channelArraySize", &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					gStatus.clear();
					MPlug elementPlug;
					elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
					if( gStatus == MS::kSuccess ) 
					{
						int val;
						elementPlug.getValue( val );
						theChannel.arraySize = val;
					}
				}
				gStatus.clear();
				gPlug = rGlobalNode.findPlug( "channelQuantize", &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					gStatus.clear();
					MPlug elementPlug;
					elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
					if( gStatus == MS::kSuccess ) 
					{
						bool val;
						elementPlug.getValue( val );
						theChannel.quantize = val;
					}
				}
				gStatus.clear();
				gPlug = rGlobalNode.findPlug( "channelBitDepth", &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					gStatus.clear();
					MPlug elementPlug;
					elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
					if( gStatus == MS::kSuccess ) 
					{
						int val;
						elementPlug.getValue( val );
						theChannel.bitDepth = val;
					}
				}
				gStatus.clear();
				gPlug = rGlobalNode.findPlug( "channelDither", &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					gStatus.clear();
					MPlug elementPlug;
					elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
					if( gStatus == MS::kSuccess ) 
					{
						float val;
						elementPlug.getValue( val );
						theChannel.dither = val;
					}
				}
				gStatus.clear();
				gPlug = rGlobalNode.findPlug( "channelFilter", &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					gStatus.clear();
					MPlug elementPlug;
					elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
					if( gStatus == MS::kSuccess ) 
					{
						bool val;
						elementPlug.getValue( val );
						theChannel.filter = val;
					}
				}
				gStatus.clear();
				gPlug = rGlobalNode.findPlug( "channelPixelFilter", &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					gStatus.clear();
					MPlug elementPlug;
					elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
					if( gStatus == MS::kSuccess ) 
					{
						int val;
						elementPlug.getValue( val );
						theChannel.pixelFilter = val;
					}
				}
				gStatus.clear();
				gPlug = rGlobalNode.findPlug( "channelPixelFilterX", &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					gStatus.clear();
					MPlug elementPlug;
					elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
					if( gStatus == MS::kSuccess ) 
					{
						float val;
						elementPlug.getValue( val );
						theChannel.pixelFilterX = val;
					}
				}
				gStatus.clear();
				gPlug = rGlobalNode.findPlug( "channelPixelFilterY", &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					gStatus.clear();
					MPlug elementPlug;
					elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
					if( gStatus == MS::kSuccess ) 
					{
						float val;
						elementPlug.getValue( val );
						theChannel.pixelFilterY = val;
					}
				}
				liqglo.m_channels.push_back( theChannel );
			}
		}
	}
	// Display Driver Globals - Read 'em and store 'em !
	liquidGetPlugValue( rGlobalNode, "ignoreAOVDisplays", liqglo.m_ignoreAOVDisplays, gStatus );
	{
		liqglo.m_displays.clear();
		unsigned int nDisplays = liquidGetPlugNumElements( rGlobalNode, "ddImageName", &gStatus );
		//cout <<"  DD : we have "<<nDisplays<<" displays..."<<endl;
		for ( unsigned int i(0); i<nDisplays; i++ ) 
		{
			StructDisplay theDisplay;
			gStatus.clear();
			gPlug = rGlobalNode.findPlug( "ddImageName", &gStatus );
			if( gStatus == MS::kSuccess ) 
			{
				gStatus.clear();
				MPlug elementPlug;
				elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					MString val;
					elementPlug.getValue( val );
					theDisplay.name = val;
					//cout <<"  DD : name["<<i<<"] = "<<val<<endl;
				}
			}
			gStatus.clear();
			gPlug = rGlobalNode.findPlug( "ddImageType", &gStatus );
			if( gStatus == MS::kSuccess ) 
			{
				gStatus.clear();
				MPlug elementPlug;
				elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					MString val;
					elementPlug.getValue( val );
					theDisplay.type = val;
					//cout <<"  DD : type["<<i<<"] = "<<val<<endl;
				}
			}
			gStatus.clear();
			gPlug = rGlobalNode.findPlug( "ddImageMode", &gStatus );
			if( gStatus == MS::kSuccess ) 
			{
				gStatus.clear();
				MPlug elementPlug;
				elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					MString val;
					elementPlug.getValue( val );
					theDisplay.mode = val;
					//cout <<"  DD : mode["<<i<<"] = "<<val<<endl;
				}
			}
			if( i==0 ) 
				theDisplay.enabled = true;
			else 
			{
				gStatus.clear();
				gPlug = rGlobalNode.findPlug( "ddEnable", &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					gStatus.clear();
					MPlug elementPlug;
					elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
					if( gStatus == MS::kSuccess ) 
					{
						bool val;
						elementPlug.getValue( val );
						theDisplay.enabled = val;
						//cout <<"  DD : enabled["<<i<<"] = "<<val<<endl;
					}
				}
			}
			if( i==0 ) 
				theDisplay.doQuantize = true;
			else 
			{
				gStatus.clear();
				gPlug = rGlobalNode.findPlug( "ddQuantizeEnabled", &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					gStatus.clear();
					MPlug elementPlug;
					elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
					if( gStatus == MS::kSuccess ) 
					{
						bool val;
						elementPlug.getValue( val );
						theDisplay.doQuantize = val;
						//cout <<"  DD : doQuantize["<<i<<"] = "<<val<<endl;
					}
				}
			}
			gStatus.clear();
			gPlug = rGlobalNode.findPlug( "ddBitDepth", &gStatus );
			if( gStatus == MS::kSuccess ) 
			{
				gStatus.clear();
				MPlug elementPlug;
				elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					int val;
					elementPlug.getValue( val );
					theDisplay.bitDepth = val;
					//cout <<"  DD : bitDepth["<<i<<"] = "<<val<<endl;
				}
			}
			gStatus.clear();
			gPlug = rGlobalNode.findPlug( "ddDither", &gStatus );
			if( gStatus == MS::kSuccess ) 
			{
				gStatus.clear();
				MPlug elementPlug;
				elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					float val;
					elementPlug.getValue( val );
					theDisplay.dither = val;
					//cout <<"  DD : dither["<<i<<"] = "<<val<<endl;
				}
			}
			if( i==0 ) 
				theDisplay.doFilter = true;
			else 
			{
				gStatus.clear();
				gPlug = rGlobalNode.findPlug( "ddFilterEnabled", &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					gStatus.clear();
					MPlug elementPlug;
					elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
					if( gStatus == MS::kSuccess ) 
					{
						bool val;
						elementPlug.getValue( val );
						theDisplay.doFilter = val;
						// cout <<"  DD : doFilter["<<i<<"] = "<<val<<endl;
					}
				}
			}
			gStatus.clear();
			gPlug = rGlobalNode.findPlug( "ddPixelFilter", &gStatus );
			if( gStatus == MS::kSuccess ) 
			{
				gStatus.clear();
				MPlug elementPlug;
				elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					int val;
					elementPlug.getValue( val ); 
					// theDisplay.filter = m_pixelFilterNames[val];
					theDisplay.filter = val;
					//cout <<"  DD : filter["<<i<<"] "<<theDisplay.filter<<endl;
					if(i==0) 
						liqglo.m_rFilter  = val;
				}
			}
			gStatus.clear();
			gPlug = rGlobalNode.findPlug( "ddPixelFilterX", &gStatus );
			if( gStatus == MS::kSuccess ) 
			{
				gStatus.clear();
				MPlug elementPlug;
				elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					float val;
					elementPlug.getValue( val );
					theDisplay.filterX = val;
					// cout <<"  DD : filterX["<<i<<"] = "<<val<<endl;
				}
			}
			gStatus.clear();
			gPlug = rGlobalNode.findPlug( "ddPixelFilterY", &gStatus );
			if( gStatus == MS::kSuccess ) 
			{
				gStatus.clear();
				MPlug elementPlug;
				elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					float val;
					elementPlug.getValue( val );
					theDisplay.filterY = val;
					//cout <<"  DD : filterY["<<i<<"] = "<<val<<endl;
				}
			}
			// retrieve the extra parameters for this display
			MStringArray xtraParamsNames;
			MStringArray xtraParamsDatas;
			MIntArray    xtraParamsTypes;

			gStatus.clear();
			gPlug = rGlobalNode.findPlug( "ddXtraParamNames", &gStatus );
			if( gStatus == MS::kSuccess ) 
			{
				gStatus.clear();
				MPlug elementPlug;
				elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					MObject arrayDataObj;
					elementPlug.getValue( arrayDataObj );
					MFnStringArrayData arrayData( arrayDataObj, &gStatus );
					arrayData.copyTo( xtraParamsNames );
				}
			}
			gStatus.clear();
			gPlug = rGlobalNode.findPlug( "ddXtraParamTypes", &gStatus );
			if( gStatus == MS::kSuccess ) 
			{
				gStatus.clear();
				MPlug elementPlug;
				elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					MObject arrayDataObj;
					elementPlug.getValue( arrayDataObj );
					MFnIntArrayData arrayData( arrayDataObj, &gStatus );
					arrayData.copyTo( xtraParamsTypes );
				}
			}
			gStatus.clear();
			gPlug = rGlobalNode.findPlug( "ddXtraParamDatas", &gStatus );
			if( gStatus == MS::kSuccess ) 
			{
				gStatus.clear();
				MPlug elementPlug;
				elementPlug = gPlug.elementByLogicalIndex( i, &gStatus );
				if( gStatus == MS::kSuccess ) 
				{
					MObject arrayDataObj;
					elementPlug.getValue( arrayDataObj );
					MFnStringArrayData arrayData( arrayDataObj, &gStatus );
					arrayData.copyTo( xtraParamsDatas );
				}
			}
			if(i==0) 
			{ // copy filter params from display 0
				liqglo.m_rFilterX = theDisplay.filterX;
				liqglo.m_rFilterY = theDisplay.filterY;
				liqglo.quantValue = theDisplay.bitDepth;
			}
			StructDDParam xtraDDParams;
			xtraDDParams.num   = xtraParamsNames.length();
			xtraDDParams.names = xtraParamsNames;
			xtraDDParams.data  = xtraParamsDatas;
			xtraDDParams.type  = xtraParamsTypes;
			theDisplay.xtraParams = xtraDDParams;
			liqglo.m_displays.push_back( theDisplay );
		}
	}
	liquidGetPlugValue( rGlobalNode, "shotName", liqglo.liqglo_shotName, gStatus ); // no substitution here
	liquidGetPlugValue( rGlobalNode, "shotVersion", liqglo.liqglo_shotVersion, gStatus ); // no substitution here

	liquidGetPlugValue( rGlobalNode, "relativeFileNames", liqglo.liqglo_relativeFileNames, gStatus );
	setOutDirs();
	setSearchPaths();

	if ( liquidGetPlugValue( rGlobalNode, "ribgenCommand", varVal, gStatus ) == MS::kSuccess )
		if ( parseString( varVal ) != "" )
			m_ribgenCommand = varVal;

	liquidGetPlugValue( rGlobalNode, "renderScriptFileName", m_userRenderScriptFileName, gStatus );
	liquidGetPlugValue( rGlobalNode, "preCommand", liqglo.m_preCommand, gStatus );
	if ( liquidGetPlugValue( rGlobalNode, "preJobCommand", varVal, gStatus ) == MS::kSuccess )
		m_preJobCommand = parseString( varVal );
	if ( liquidGetPlugValue( rGlobalNode, "postJobCommand", varVal, gStatus ) == MS::kSuccess )
		m_postJobCommand = parseString( varVal );
	liquidGetPlugValue( rGlobalNode, "postFrameCommand", m_postFrameCommand, gStatus );
	liquidGetPlugValue( rGlobalNode, "preFrameCommand", m_preFrameCommand, gStatus );



	if ( liquidGetPlugValue( rGlobalNode, "renderCamera", varVal, gStatus ) == MS::kSuccess ) 
	{
		liqglo.renderCamera = parseString( varVal );
		liqglo.liqglo_renderCamera = liqglo.renderCamera;
	}
	getCameraParameters(rGlobalNode);

	if ( liquidGetPlugValue( rGlobalNode, "ribName", varVal, gStatus ) == MS::kSuccess ) {
		//Note:  -ribName is set to liqglo.liqglo_sceneName originally. 
		//       Because we replace liqglo.liqglo_sceneName with liquidTransGetSceneName(), and delete liqglo.liqglo_sceneName,
		//       we use liqglo.liqglo_ribName to store the ribName which passed by commandline parameter '-ribName'
		//  [2/17/2012 yaoyansi]
		liquidMessage2(messageWarning,"warrning: ribName is store in liqglo.liqglo_ribName instead of liqglo.liqglo_sceneName.[2/17/2012 yaoyansi]");
		liqglo.liqglo_ribName = parseString( varVal );
	}

	liquidGetPlugValue( rGlobalNode, "beautyRibHasCameraName", liqglo.liqglo_beautyRibHasCameraName, gStatus );

	if ( liquidGetPlugValue( rGlobalNode, "alfredTags", varVal, gStatus ) == MS::kSuccess ) 
		liqglo.m_alfredTags = parseString( varVal );

	if ( liquidGetPlugValue( rGlobalNode, "alfredServices", varVal, gStatus ) == MS::kSuccess ) 
		liqglo.m_alfredServices = parseString( varVal );

	if ( liquidGetPlugValue( rGlobalNode, "dirmaps", varVal, gStatus ) == MS::kSuccess ) 
		liqglo.m_dirmaps = parseString( varVal );


	if ( liquidGetPlugValue( rGlobalNode, "key", varVal, gStatus ) == MS::kSuccess ) 
		liqglo.m_defGenKey = parseString( varVal );

	if ( liquidGetPlugValue( rGlobalNode, "service", varVal, gStatus ) == MS::kSuccess ) 
		liqglo.m_defGenService = parseString( varVal );

	liquidGetPlugValue( rGlobalNode, "preframeMel", m_preFrameMel, gStatus );
	liquidGetPlugValue( rGlobalNode, "postframeMel", m_postFrameMel, gStatus );


	getHinderParameters(rGlobalNode);



	// RAYTRACING OPTIONS:BEGIN
	liquidGetPlugValue( rGlobalNode, "useRayTracing", liqglo.rt_useRayTracing, gStatus );
	liquidGetPlugValue( rGlobalNode, "traceMaxDepth", liqglo.rt_traceMaxDepth, gStatus );
	liquidGetPlugValue( rGlobalNode, "traceSpecularThreshold", liqglo.rt_traceSpecularThreshold, gStatus );
	liquidGetPlugValue( rGlobalNode, "traceBreadthFactor", liqglo.rt_traceBreadthFactor, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "traceDepthFactor", liqglo.rt_traceDepthFactor, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "traceRayContinuation", liqglo.rt_traceRayContinuation, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "traceCacheMemory", liqglo.rt_traceCacheMemory, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "traceDisplacements", liqglo.rt_traceDisplacements, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "traceSampleMotion", liqglo.rt_traceSampleMotion, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "traceBias", liqglo.rt_traceBias, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "traceMaxDiffuseDepth", liqglo.rt_traceMaxDiffuseDepth, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "traceMaxSpecularDepth", liqglo.rt_traceMaxSpecularDepth, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "irradianceMaxError", liqglo.rt_irradianceMaxError, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "irradianceMaxPixelDist", liqglo.rt_irradianceMaxPixelDist, gStatus ); 
	// RAYTRACING OPTIONS:END
	liquidGetPlugValue( rGlobalNode, "outputMayaPolyCreases", liqglo.liqglo_outputMayaPolyCreases, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "useMtorSubdiv", liqglo.liqglo_useMtorSubdiv, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "ribRelativeTransforms", liqglo.liqglo_relativeTransforms, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "shortShaderNames", liqglo.liqglo_shortShaderNames, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "expandAlfred", liqglo.m_alfredExpand, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "createOutputDirectories", createOutputDirectories, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "minCPU", m_minCPU, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "maxCPU", m_maxCPU, gStatus );
	liquidGetPlugValue( rGlobalNode, "showProgress", m_showProgress, gStatus );
	liquidGetPlugValue( rGlobalNode, "expandShaderArrays", liqglo.liqglo_expandShaderArrays, gStatus );
	liquidGetPlugValue( rGlobalNode, "outputComments", liqglo.m_outputComments, gStatus );
	liquidGetPlugValue( rGlobalNode, "shaderDebug", m_shaderDebug, gStatus );
	liquidGetPlugValue( rGlobalNode, "deferredGen", liqglo.m_deferredGen, gStatus );
	liquidGetPlugValue( rGlobalNode, "deferredBlock", liqglo.m_deferredBlockSize, gStatus );
	liquidGetPlugValue( rGlobalNode, "useRenderScript", useRenderScript, gStatus );
	liquidGetPlugValue( rGlobalNode, "remoteRender", liqglo.remoteRender, gStatus );
	liquidGetPlugValue( rGlobalNode, "renderAllCurves", m_renderAllCurves, gStatus );
	liquidGetPlugValue( rGlobalNode, "illuminateByDefault", liqglo.m_illuminateByDefault, gStatus );
	liquidGetPlugValue( rGlobalNode, "liquidSetLightLinking", m_liquidSetLightLinking, gStatus );
	liquidGetPlugValue( rGlobalNode, "ignoreLights", m_ignoreLights, gStatus );
	liquidGetPlugValue( rGlobalNode, "ignoreSurfaces", m_ignoreSurfaces, gStatus );
	liquidGetPlugValue( rGlobalNode, "ignoreDisplacements", m_ignoreDisplacements, gStatus );
	liquidGetPlugValue( rGlobalNode, "ignoreVolumes", m_ignoreVolumes, gStatus );

	liquidGetPlugValue( rGlobalNode, "useNewTranslator", m_useNewTranslator, gStatus );
	liquidGetPlugValue( rGlobalNode, "outputShaderGraph", m_OutputShaderGraph, gStatus );
	liquidGetPlugValue( rGlobalNode, "outputDebugMsgToRib", m_outputDebugMsgToRib, gStatus );
	liquidGetPlugValue( rGlobalNode, "outputShadowPass", m_outputShadowPass, gStatus );
	liquidGetPlugValue( rGlobalNode, "outputHeroPass", m_outputHeroPass, gStatus );

	liquidGetPlugValue( rGlobalNode, "netRManRender", liqglo.useNetRman, gStatus );
	liquidGetPlugValue( rGlobalNode, "ignoreShadows", liqglo.liqglo_doShadows, gStatus );
	liqglo.liqglo_doShadows = !liqglo.liqglo_doShadows;

	liquidGetPlugValue( rGlobalNode, "shapeOnlyInShadowNames", liqglo.liqglo_shapeOnlyInShadowNames, gStatus );
	liquidGetPlugValue( rGlobalNode, "fullShadowRibs", liqglo.fullShadowRib, gStatus );
	liquidGetPlugValue( rGlobalNode, "binaryOutput", liqglo.liqglo_doBinary, gStatus );
	liquidGetPlugValue( rGlobalNode, "lazyCompute", m_lazyCompute, gStatus );
	liquidGetPlugValue( rGlobalNode, "outputShadersInShadows", m_outputShadersInShadows, gStatus );
	// Moritz: added new options for light/shader output in deep shadows
	liquidGetPlugValue( rGlobalNode, "outputShadersInDeepShadows", m_outputShadersInDeepShadows, gStatus );
	liquidGetPlugValue( rGlobalNode, "outputLightsInDeepShadows", m_outputLightsInDeepShadows, gStatus );

	liquidGetPlugValue( rGlobalNode, "outputMeshUVs", liqglo.liqglo_outputMeshUVs, gStatus );
	liquidGetPlugValue( rGlobalNode, "compressedOutput", liqglo.liqglo_doCompression, gStatus );
	liquidGetPlugValue( rGlobalNode, "exportReadArchive", liqglo.m_exportReadArchive, gStatus );
	liquidGetPlugValue( rGlobalNode, "renderJobName", renderJobName, gStatus );
	liquidGetPlugValue( rGlobalNode, "doAnimation", m_animation, gStatus );
	if( m_animation ) 
	{
		MString frameSequence;
		liquidGetPlugValue( rGlobalNode, "frameSequence", frameSequence, gStatus );
		if( gStatus == MS::kSuccess ) 
			liqglo.frameNumbers = generateFrameNumbers( string( frameSequence.asChar() ) );
	}
	liquidGetPlugValue( rGlobalNode, "doPadding", liqglo.liqglo_doExtensionPadding, gStatus );
	if( liqglo.liqglo_doExtensionPadding ) 
		liquidGetPlugValue( rGlobalNode, "padding", liqglo.liqglo_outPadding, gStatus );
	{  
		int gWidth, gHeight;
		liquidGetPlugValue( rGlobalNode, "xResolution", gWidth, gStatus );
		liquidGetPlugValue( rGlobalNode, "yResolution", gHeight, gStatus );
		if( gWidth > 0 ) 
			width = gWidth;
		if( gHeight > 0 ) 
			height = gHeight;
	}


	liquidGetPlugValue( rGlobalNode, "transformationBlur", liqglo.liqglo_doMotion, gStatus );

	liquidGetPlugValue( rGlobalNode, "deformationBlur", liqglo.liqglo_doDef, gStatus );

	liquidGetPlugValue( rGlobalNode, "shutterEfficiency", liqglo.liqglo_shutterEfficiency, gStatus );
	liquidGetPlugValue( rGlobalNode, "motionBlurSamples", liqglo.liqglo_motionSamples, gStatus );
	if( liqglo.liqglo_motionSamples > LIQMAXMOTIONSAMPLES )
		liqglo.liqglo_motionSamples = LIQMAXMOTIONSAMPLES;
	liquidGetPlugValue( rGlobalNode, "relativeMotion", liqglo.liqglo_relativeMotion, gStatus );


	getOtherParameters(rGlobalNode);	
	getLimitsParameters(rGlobalNode);

	liquidGetPlugValue( rGlobalNode, "cleanRib", liqglo.cleanRib, gStatus );
	liquidGetPlugValue( rGlobalNode, "cleanRenderScript", cleanRenderScript, gStatus );
	liquidGetPlugValue( rGlobalNode, "cleanTex", cleanTextures, gStatus );
	liquidGetPlugValue( rGlobalNode, "cleanShad", cleanShadows, gStatus );
	liquidGetPlugValue( rGlobalNode, "justRib", m_justRib, gStatus );


	getStatisticsParameters(rGlobalNode);

	// Philippe : OBSOLETE ?


	// taking into account liquidRibRequest nodes and preposterous mel scripts - Alf
	{
		MStringArray requestArray;
		MString request;

		liquidGetPlugValue( rGlobalNode, "preFrameBegin", request, gStatus );
		if( request != "" )
			requestArray.append( request );
		// add rib request node values
		request = parseLiquidRibRequest( requestArray, "preFrame" );
		if( request != "" )
			liqglo.m_preFrameRIB = parseString( request );

		liquidGetPlugValue( rGlobalNode, "preWorld", request, gStatus );
		if( request != "" )
			requestArray.append( request );
		request = parseLiquidRibRequest( requestArray, "preWorld" );
		if( request != "" )
			liqglo.m_preWorldRIB = parseString( request );

		liquidGetPlugValue( rGlobalNode, "postWorld", request, gStatus );
		if( request != "" )
			requestArray.append( request );
		request = parseLiquidRibRequest( requestArray, "postWorld" );
		if( request != "" )
			liqglo.m_postWorldRIB = parseString( request );

		liquidGetPlugValue( rGlobalNode, "preGeom", request, gStatus );
		if( request != "" )
			requestArray.append( request );
		request = parseLiquidRibRequest( requestArray, "preGeom" );
		if( request != "" )
			m_preGeomRIB = parseString( request );
	}
	liquidGetPlugValue( rGlobalNode, "renderScriptFormat", var, gStatus );
	if( gStatus == MS::kSuccess ) 
		m_renderScriptFormat = ( enum renderScriptFormat ) var;

	liquidGetPlugValue( rGlobalNode, "renderScriptCommand", varVal, gStatus );
	if( varVal != "" ) 
		m_renderScriptCommand = parseString( varVal, false );

	liquidGetPlugValue( rGlobalNode, "currentLayerRifParameters", liqglo.liqglo_rifParams, gStatus );
	
}

bool liqRibTranslator::verifyOutputDirectories()
{
	CM_TRACE_FUNC("liqRibTranslator::verifyOutputDirectories()");
#ifdef _WIN32
	int dirMode = 6; // dummy arg
	int mkdirMode = 0;
#else
	mode_t dirMode,mkdirMode;
	dirMode = R_OK|W_OK|X_OK|F_OK;
	mkdirMode = S_IRWXU|S_IRWXG|S_IRWXO;
#endif

#define DIR_CREATION_WARNING(type, path) \
	liquidMessage( "Had trouble creating " + string( type ) + " directory, '" + path + "'. Defaulting to system temp directory!", messageWarning );

#define DIR_MISSING_WARNING(type, path) \
	liquidMessage( string( type ) + " directory, '" + path + "', does not exist or is not accessible. Defaulting to system temp directory!", messageWarning );

#ifdef _WIN32
	_chdir( liqglo.liqglo_projectDir.asChar() );
#else
	chdir( liqglo.liqglo_projectDir.asChar() );
#endif
	bool problem( false );
	LIQ_ADD_SLASH_IF_NEEDED( liqglo.liqglo_ribDir );
	MString tmp_path( liquidSanitizePath( liquidGetRelativePath( liqglo.liqglo_relativeFileNames, liqglo.liqglo_ribDir, liqglo.liqglo_projectDir ) ) );
	if( !fileFullyAccessible( tmp_path ) ) 
	{
		if( createOutputDirectories ) 
		{
			if( !makeFullPath( tmp_path.asChar(), mkdirMode ) ) 
			{
				DIR_CREATION_WARNING( "RIB", tmp_path.asChar() );
				liqglo.liqglo_ribDir = m_systemTempDirectory;
				problem = true;
			}
		} 
		else 
		{
			DIR_MISSING_WARNING( "RIB", tmp_path.asChar() );
			liqglo.liqglo_ribDir = m_systemTempDirectory;
			problem = true;
		}
	} 
	else 
		liqglo.liqglo_ribDir = tmp_path;

	LIQ_ADD_SLASH_IF_NEEDED( liqglo.liqglo_textureDir );
	tmp_path = liquidSanitizePath( liquidGetRelativePath( liqglo.liqglo_relativeFileNames, liqglo.liqglo_textureDir, liqglo.liqglo_projectDir ) );
	if( !fileFullyAccessible( tmp_path ) ) 
	{
		if( createOutputDirectories ) 
		{
			if( !makeFullPath( tmp_path.asChar(), mkdirMode ) ) 
			{
				DIR_CREATION_WARNING( "Texture", tmp_path.asChar() );
				liqglo.liqglo_textureDir = m_systemTempDirectory;
				problem = true;
			}
		} 
		else 
		{
			DIR_MISSING_WARNING( "Texture", tmp_path.asChar() );
			liqglo.liqglo_textureDir = m_systemTempDirectory;
			problem = true;
		}
	} 
	else 
		liqglo.liqglo_textureDir = tmp_path;

	LIQ_ADD_SLASH_IF_NEEDED( liqglo.m_pixDir );
	tmp_path = liquidSanitizePath( liquidGetRelativePath( liqglo.liqglo_relativeFileNames, liqglo.m_pixDir, liqglo.liqglo_projectDir ) );
	if( !fileFullyAccessible( tmp_path ) ) 
	{
		if( createOutputDirectories ) 
		{
			if( !makeFullPath( tmp_path.asChar(), mkdirMode ) ) 
			{
				DIR_CREATION_WARNING( "Picture", tmp_path.asChar() );
				liqglo.m_pixDir = m_systemTempDirectory;
				problem = true;
			}
		} 
		else 
		{
			DIR_MISSING_WARNING( "Picture", tmp_path.asChar() );
			liqglo.m_pixDir = m_systemTempDirectory;
			problem = true;
		}
	} 
	else 
		liqglo.m_pixDir = tmp_path;

	LIQ_ADD_SLASH_IF_NEEDED( m_tmpDir );
	tmp_path = liquidSanitizePath( liquidGetRelativePath( liqglo.liqglo_relativeFileNames, m_tmpDir, liqglo.liqglo_projectDir ) );
	if( !fileFullyAccessible( tmp_path ) ) 
	{
		if( createOutputDirectories ) 
		{
			if( !makeFullPath( tmp_path.asChar(), mkdirMode ) ) 
			{
				DIR_CREATION_WARNING( "Temp Files", tmp_path.asChar() );
				m_tmpDir = m_systemTempDirectory;
				problem = true;
			}
		} 
		else 
		{
			DIR_MISSING_WARNING( "Temp Files", tmp_path.asChar() );
			m_tmpDir = m_systemTempDirectory;
			problem = true;
		}
	} 
	else 
		m_tmpDir = tmp_path;
	return problem;
}

MString liqRibTranslator::generateRenderScriptName() const
{
	CM_TRACE_FUNC("liqRibTranslator::generateRenderScriptName()");
	MString renderScriptName;
	renderScriptName = m_tmpDir;
	if( m_userRenderScriptFileName != MString( "" ) )
		renderScriptName += m_userRenderScriptFileName;
	else 
	{
		renderScriptName += liquidTransGetSceneName();
#ifndef _WIN32
		struct timeval  t_time;
		struct timezone t_zone;
		size_t tempSize = 0;
		char currentHostName[1024];
		gethostname( currentHostName, tempSize );
		liquidlong hashVal = liquidHash( currentHostName );
		gettimeofday( &t_time, &t_zone );
		srandom( t_time.tv_usec + hashVal );
		short alfRand = random();
		renderScriptName += alfRand;
#endif
	}
	if(m_renderScriptFormat == ALFRED) 
		renderScriptName += ".alf";

	if(m_renderScriptFormat == XML) 
		renderScriptName += ".xml";

	return renderScriptName;
}

MString liqRibTranslator::generateTempMayaSceneName() const
{
	CM_TRACE_FUNC("liqRibTranslator::generateTempMayaSceneName()");
	MString tempDefname = m_tmpDir;
	tempDefname += liquidTransGetSceneName();
#ifndef _WIN32
	struct timeval  t_time;
	struct timezone t_zone;
	size_t tempSize = 0;
	char currentHostName[1024];
	gethostname( currentHostName, tempSize );
	liquidlong hashVal = liquidHash( currentHostName );
	gettimeofday( &t_time, &t_zone );
	srandom( t_time.tv_usec + hashVal );
	short defRand = random();
	tempDefname += defRand;
#endif
	MString currentFileType = MFileIO::fileType();
	if( MString( "mayaAscii" )  == currentFileType ) 
		tempDefname += ".ma";
	if( MString( "mayaBinary" ) == currentFileType ) 
		tempDefname += ".mb";
	return tempDefname;
}

 //MString liqRibTranslator::generateShadowArchiveName( bool renderAllFrames, long renderAtframe, MString geometrySet )
 //{
 //	MString baseShadowName;
 //	if( !liqglo.liqglo_shapeOnlyInShadowNames ) 
 //		baseShadowName += liquidTransGetSceneName() + "_";
 //
 //	baseShadowName += "SHADOWBODY";
 //	if( geometrySet != "" ) 
 //		baseShadowName += "." + sanitizeNodeName( geometrySet.substring(0, 99) );
 //	baseShadowName += LIQ_ANIM_EXT;
 //	baseShadowName += ".rib";
 //
 //	size_t shadowNameLength = baseShadowName.length() + 1;
 //	shadowNameLength += 10;
 //	scoped_ptr< char > baseShadowRibName( new char[ shadowNameLength ] );
 //	sprintf( baseShadowRibName.get(), baseShadowName.asChar(), liqglo.liqglo_doExtensionPadding ? liqglo.liqglo_outPadding : 0, renderAllFrames ? liqglo.liqglo_lframe : renderAtframe );
 //	baseShadowName = baseShadowRibName.get();
 //
 //	return liquidSanitizePath( baseShadowName );
 //}

MString liqRibTranslator::generateFileName( fileGenMode mode, const structJob& job )
{
	CM_TRACE_FUNC(boost::format("liqRibTranslator::generateFileName(%d,%s)")%mode%job.name.asChar());
	MString filename;
	MString debug;
	switch( mode )
	{
	case fgm_shadow_tex:
		debug = "fgm_shadow_tex";
		filename = liqglo.liqglo_textureDir;
		if( !liqglo.liqglo_shapeOnlyInShadowNames )
		{
			filename += liquidTransGetSceneName();
			filename += "_";
		}
		// check if aggregate is on
		if( job.texName != "" )
			filename += sanitizeNodeName( job.texName );
		else
			filename += sanitizeNodeName( job.name );

		filename += job.deepShadows ? "DSH" : "SHD";
		if( job.isPoint && ( job.deepShadows || !job.shadowAggregation ) )
		{
			switch( job.pointDir )
			{
			case pPX:
				filename += "_PX";break;
			case pPY:
				filename += "_PY";break;
			case pPZ:
				filename += "_PZ";break;
			case pNX:
				filename += "_NX";break;
			case pNY:
				filename += "_NY";break;
			case pNZ:
				filename += "_NZ";break;
			}
		}
		// only if aggregate is off
		if( job.shadowObjectSet != "" && job.texName == "" )
			filename += "." + job.shadowObjectSet.substring(0, 99);
		if( m_animation || m_useFrameExt )
			filename += LIQ_ANIM_EXT;
		filename += ".tex";
		break;

	case fgm_shadow_rib:
		debug = "fgm_shadow_rib";
		filename = liqglo.liqglo_ribDir;
		if( !liqglo.liqglo_shapeOnlyInShadowNames )
		{
			filename += liquidTransGetSceneName();
			filename += "_";
		}
		filename += sanitizeNodeName( job.name );
		filename += job.deepShadows ? "DSH" : "SHD";
		if( job.isPoint && ( job.deepShadows || !job.shadowAggregation ) )
		{
			switch( job.pointDir )
			{
			case pPX:
				filename += "_PX";break;
			case pPY:
				filename += "_PY";break;
			case pPZ:
				filename += "_PZ";break;
			case pNX:
				filename += "_NX";break;
			case pNY:
				filename += "_NY";break;
			case pNZ:
				filename += "_NZ";break;
			}
		}
		if( job.shadowObjectSet != "" ) filename += "." + job.shadowObjectSet.substring(0, 99);
		if( m_animation || m_useFrameExt ) filename += LIQ_ANIM_EXT;
		filename += ".rib";
		break;

	case fgm_beauty_rib:
		debug = "fgm_beauty_rib";
		filename = liqglo.liqglo_ribDir;
		filename += liquidTransGetSceneName();
		if( liqglo.liqglo_beautyRibHasCameraName )
		{
			filename += "_";
			filename += sanitizeNodeName( job.name );
		}
		if( m_animation || m_useFrameExt )
			filename += LIQ_ANIM_EXT;
		filename += ".rib";
		break;

	case fgm_image:
		debug = "fgm_image";
		filename = liqglo.m_pixDir;
		filename += liquidTransGetSceneName();
		if( liqglo.liqglo_beautyRibHasCameraName )
		{
			filename += "_";
			filename += sanitizeNodeName( job.name );
		}
		if( m_animation || m_useFrameExt )
			filename += LIQ_ANIM_EXT;
		filename += "." + liqglo.outExt;
		break;

	default:
		liquidMessage( "liqRibTranslator::generateFileName: unknown case", messageError );
	}

	size_t filenameLength = filename.length() + 1;
	filenameLength += 10;
	char *tmp;
	tmp = (char *)alloca(filenameLength);
	long frame = job.renderFrame;
	sprintf(tmp, filename.asChar(), liqglo.liqglo_doExtensionPadding ? liqglo.liqglo_outPadding : 0, frame );
	filename = tmp;

	//cout <<"liqRibTranslator::generateFileName( "<<debug<<" ) -> "<<filename<<endl;

	return liquidSanitizePath( filename );
}

/**
* This method actually does the renderman output.
*/
MStatus liqRibTranslator::doIt( const MArgList& args )
{
	MStatus status;

	// check if we need to switch to a specific render layer
	// we do that here because we need to switch to the chosen layer first
	// to be able to read overriden gloabsl and stuff...
	unsigned int argIndex = args.flagIndex( "lyr", "layer" );
	if(argIndex != MArgList::kInvalidArgIndex) 
		liqglo.liqglo_layer = args.asString( argIndex+1, &status );

	// get the name of the current render layer
	MString originalLayer;
	if( MGlobal::executeCommand( "editRenderLayerGlobals -q -currentRenderLayer;", originalLayer, false, false ) == MS::kFailure ) 
	{
		liquidMessage( "Could not get the current render layer name! ABORTING.", messageError );
		return MS::kFailure;
	}

	// switch to the specified render layer
	if( liqglo.liqglo_layer != "" ) 
	{
		MString cmd;
		cmd = "if( `editRenderLayerGlobals -q -currentRenderLayer` != \"" + liqglo.liqglo_layer + "\" ) editRenderLayerGlobals( \"-currentRenderLayer\", \"" + liqglo.liqglo_layer + "\");";
		if(  MGlobal::executeCommand( cmd, false, false ) == MS::kFailure ) 
		{
			liquidMessage( "Could not switch to render layer '" + string( liqglo.liqglo_layer.asChar() ) + "'! ABORTING.", messageError );
			return MS::kFailure;
		}
	} 
	else 
	{
		// we fill liqglo_layer with current layer name
		// to be able to substitute $LYR in strings.
		liqglo.liqglo_layer = originalLayer;
	}

	if( MS::kSuccess!=liqglo.liquidRenderer.setRenderer() ){
		return MS::kFailure;
	}
	m_renderCommand = liqglo.liquidRenderer.renderCommand;

	status = liquidDoArgs( args );
	if( !status ) 
		return MS::kFailure;

	{
		CM_TRACE_OPEN(getFunctionTraceLogFileName().c_str());
		CM_TRACE_FUNC("liqRibTranslator::doIt()-->if(checkSettings()==true)");
		{//set renderer
			MFnDependencyNode rGlobalNode( liqglo.rGlobalObj );
			MString renderer;
			liquidGetPlugValue( rGlobalNode, "renderer", renderer, status );
			liquid::RendererMgr::getInstancePtr()->createFactory(renderer.asChar());
			liquid::RendererMgr::getInstancePtr()->install();
			liquid::RendererMgr::getInstancePtr()->prologue();
		}

		if( canExport() )
		{
			if(m_useNewTranslator){
				liquidMessage("_doItNew()", messageInfo);
				status = _doItNew(args, originalLayer);// new doIt() process
			}else{
				liquidMessage("_doIt()", messageInfo);
				status = _doIt(args, originalLayer);//original doIt() process
			}
		}

		{//
			liquid::RendererMgr::getInstancePtr()->test();
			liquid::RendererMgr::getInstancePtr()->epilogue();
			liquid::RendererMgr::getInstancePtr()->uninstall();
			liquid::RendererMgr::getInstancePtr()->deleteFactory();
		}
		CM_TRACE_CLOSE();
	}


	return status;
}
//
MStatus liqRibTranslator::_doIt( const MArgList& args , const MString& originalLayer )
{
	//
	liqAssert("test liqAssert");
	liqAssert("tile", "msg", "yes");
	liqAssert("tile", "msg", "yes","no");
	//

	CM_TRACE_FUNC(boost::format("liqRibTranslator::_doIt(args,%s)")%originalLayer.asChar());
	MStatus status;
	MString lastRibName;
	bool hashTableInited = false;

	if( !liqglo.liquidBin && !liqglo.m_deferredGen ) 
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

		if( liqglo.m_deferredGen ) 
		{
			MString currentFileType = MFileIO::fileType();
			MFileIO::exportAll( tempDefname, currentFileType.asChar() );
		}

		if( !liqglo.m_deferredGen && m_justRib ) 
			useRenderScript = false;

		liqRenderScript jobScript;
// 		liqRenderScript::Job preJobInstance;
// 		preJobInstance.title = "liquid pre-job";
// 		preJobInstance.isInstance = true;

		if( useRenderScript ) 
		{
			if( renderJobName == "" ) 
				renderJobName = liquidTransGetSceneName();
			jobScript.title = renderJobName.asChar();

			if( liqglo.useNetRman ) 
			{
				jobScript.minServers = m_minCPU;
				jobScript.maxServers = m_maxCPU;
			} 
			else 
			{
				jobScript.minServers = 1;
				jobScript.maxServers = 1;
			}

			if ( liqglo.m_dirmaps.length() )
				jobScript.dirmaps = liqglo.m_dirmaps.asChar();

			if( m_preJobCommand != MString( "" ) ) 
			{
				liqRenderScript::Job preJob;
				preJob.title = "liquid pre-job";
				preJob.commands.push_back( liqRenderScript::Cmd( m_preJobCommand.asChar(), ( liqglo.remoteRender && !liqglo.useNetRman ) ) );
				jobScript.addJob( preJob );
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

		int currentBlock( 0 );
		unsigned frameIndex( 0 );
		for ( ; frameIndex < liqglo.frameNumbers.size(); frameIndex++ ) 
		{
			liqShaderFactory::instance().clearShaders();

			liqglo.liqglo_lframe = liqglo.frameNumbers[ frameIndex ];

			if( m_showProgress ) 
				printProgress( 1, liqglo.frameNumbers.size(), frameIndex );

			liqRenderScript::Job frameScriptJob;

			liqglo.m_alfShadowRibGen = false;
			liqglo.liqglo_preReadArchive.clear();
			liqglo.liqglo_preRibBox.clear();
			liqglo.liqglo_preReadArchiveShadow.clear();
			liqglo.liqglo_preRibBoxShadow.clear();

			// make sure all the global strings are parsed for this frame

			MString frameRenderCommand    = parseString( liqglo.liquidRenderer.renderCommand + " " + liqglo.liquidRenderer.renderCmdFlags, false );
			MString frameRibgenCommand    = parseString( m_ribgenCommand, false );
			MString framePreCommand       = parseString( liqglo.m_preCommand, false );
			MString framePreFrameCommand  = parseString( m_preFrameCommand, false );
			MString framePostFrameCommand = parseString( m_postFrameCommand, false );
			
			if( useRenderScript ) 
			{
				if( liqglo.m_deferredGen ) 
				{
					liqRenderScript::Job deferredJob;
					if( ( frameIndex % liqglo.m_deferredBlockSize ) == 0 ) 
					{
						if( liqglo.m_deferredBlockSize == 1 ) 
							currentBlock = liqglo.liqglo_lframe;
						else 
							currentBlock++;

						stringstream ribGenExtras;
						//Note:  -ribName is set to liqglo.liqglo_sceneName originally. 
						//       Because we replace liqglo.liqglo_sceneName with liquidTransGetSceneName(), and delete liqglo.liqglo_sceneName,
						//       we use liqglo.liqglo_ribName to store the ribName which passed by commandline parameter '-ribName'
						//  [2/17/2012 yaoyansi]
						assert(0&&"warrning: ribName is store in liqglo.liqglo_ribName instead of liqglo.liqglo_sceneName.[2/17/2012 yaoyansi]");
						// ribGenExtras << " -progress -noDef -nop -noalfred -projectDir " << liqglo_projectDir.asChar() << " -ribName " << liqglo.liqglo_ribName.asChar() << " -mf " << tempDefname.asChar() << " -t ";
						ribGenExtras << " -progress -noDef -projectDir " << liqglo.liqglo_projectDir.asChar() << " -ribName " << liqglo.liqglo_ribName.asChar() << " -fl ";

						unsigned lastGenFrame( ( frameIndex + liqglo.m_deferredBlockSize ) < liqglo.frameNumbers.size() ? frameIndex + liqglo.m_deferredBlockSize : liqglo.frameNumbers.size() );

						//liquidMessage2(messageInfo, ">>> frameIndex = %d m_deferredBlockSize = %d frameNumbers.size = %d lastGenFrame = %d\n",frameIndex,m_deferredBlockSize,frameNumbers.size(),lastGenFrame );

						for( unsigned outputFrame( frameIndex ); outputFrame < lastGenFrame; outputFrame++ )
						{  
							ribGenExtras << liqglo.frameNumbers[ outputFrame ];
							ribGenExtras << (( outputFrame != ( lastGenFrame - 1 ) )? ", " : " ");
							// liquidMessage2(messageInfo, "\t outputFrame = %d\n", outputFrame );
						}
						stringstream titleStream;
						titleStream << liquidTransGetSceneName().asChar() << "FrameRIBGEN" << currentBlock;
						deferredJob.title = titleStream.str();

						stringstream ss;
						ss << framePreCommand.asChar() << " " << frameRibgenCommand.asChar() << ribGenExtras.str() << " " << tempDefname.asChar();
						liqRenderScript::Cmd cmd( ss.str(), liqglo.remoteRender );
						cmd.alfredServices = liqglo.m_defGenService.asChar();
						cmd.alfredTags     = liqglo.m_defGenKey.asChar();
						if( liqglo.m_alfredExpand ) 
							cmd.alfredExpand = true;

						deferredJob.commands.push_back(cmd);
						jobScript.addJob(deferredJob);
					}
				}//if( m_deferredGen )
				if( !m_justRib ) 
				{
					stringstream titleStream;
					titleStream << liquidTransGetSceneName().asChar() << "Frame" << liqglo.liqglo_lframe;
					frameScriptJob.title = titleStream.str();

					if( liqglo.m_deferredGen ) 
					{
						stringstream ss;
						ss << liquidTransGetSceneName().asChar() << "FrameRIBGEN" << currentBlock;
						liqRenderScript::Job instanceJob;
						instanceJob.isInstance = true;
						instanceJob.title = ss.str();
						frameScriptJob.childJobs.push_back(instanceJob);
					}
				}
			}//if( useRenderScript ) 

			LIQDEBUGPRINTF( "-> building jobs\n" );
			// Hmmmmmm not really clean ....
			if( buildJobs() != MS::kSuccess ) 
				break;

			if( !liqglo.m_deferredGen ) 
			{
				if( m_showProgress ) 
					printProgress( 2, liqglo.frameNumbers.size(), frameIndex );

				long lastScannedFrame = -100000;
				long scanTime = liqglo.liqglo_lframe;
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
						float sampleinc( ( liqglo.liqglo_shutterTime * m_blurTime ) / ( liqglo.liqglo_motionSamples - 1 ) );
						for ( unsigned msampleOn( 0 ); msampleOn < liqglo.liqglo_motionSamples; msampleOn++ ) 
						{
							float subframe;
							switch( liqglo.shutterConfig ) 
							{
							case OPEN_ON_FRAME:
							default:
								subframe = scanTime + ( msampleOn * sampleinc );
								break;
							case CENTER_ON_FRAME:
								subframe = ( scanTime - ( liqglo.liqglo_shutterTime * m_blurTime * 0.5 ) ) + msampleOn * sampleinc;
								break;
							case CENTER_BETWEEN_FRAMES:
								subframe = scanTime + ( 0.5 * ( 1 - ( liqglo.liqglo_shutterTime * m_blurTime ) ) ) + ( msampleOn * sampleinc );
								break;
							case CLOSE_ON_NEXT_FRAME:
								subframe = scanTime + ( 1 - ( liqglo.liqglo_shutterTime * m_blurTime ) ) + ( msampleOn * sampleinc );
								break;
							}
							liqglo.liqglo_sampleTimes[ msampleOn ] = subframe;
							liqglo.liqglo_sampleTimesOffsets[ msampleOn ] = msampleOn * sampleinc;
						}
						//cout <<"about to scan... "<<endl;
						// scan the scene
						//
						if( liqglo.doCameraMotion || liqglo.liqglo_doMotion || liqglo.liqglo_doDef ) 
						{
							for ( int msampleOn = 0; msampleOn < liqglo.liqglo_motionSamples; msampleOn++ ) 
								scanScene( liqglo.liqglo_sampleTimes[ msampleOn ] , msampleOn );
						} else {
							liqglo.liqglo_sampleTimes[ 0 ] = scanTime;
							liqglo.liqglo_sampleTimesOffsets[ 0 ] = 0;
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
						liqglo.liqglo_isShadowPass = true;
					else 
						liqglo.liqglo_isShadowPass = false;

					// build the shadow archive name for the job
					{
						bool renderAllFrames( liqglo_currentJob.everyFrame );
						long refFrame( liqglo_currentJob.renderFrame );
						MString geoSet( liqglo_currentJob.shadowObjectSet );
						baseShadowName = generateShadowArchiveName( renderAllFrames, refFrame, geoSet );
						baseShadowName = liquidGetRelativePath( liqglo.liqglo_relativeFileNames, baseShadowName, liqglo.liqglo_ribDir );
					}


					LIQDEBUGPRINTF( "-> setting RiOptions\n" );


					liquid::RendererMgr::getInstancePtr()->
						getRenderer()->setRenderScriptFormatAndCompress(liqglo.liqglo_doBinary, liqglo.liqglo_doCompression);


					// world RiReadArchives and Rib Boxes ************************************************
					//
					if( liqglo_currentJob.isShadow && !liqglo_currentJob.shadowArchiveRibDone && !liqglo.fullShadowRib ) 
					{
						//
						//  create the read-archive shadow files
						//
#ifndef RENDER_PIPE
						liquidMessage( "Beginning RIB output to '" + string( baseShadowName.asChar() ) + "'", messageInfo );
						RiBegin_liq( const_cast< RtToken >( baseShadowName.asChar() ) );
#else
						liqglo.liqglo_ribFP = fopen( baseShadowName.asChar(), "w" );
						if( liqglo.liqglo_ribFP ) {
							LIQDEBUGPRINTF( "-> setting pipe option\n" );
							RtInt ribFD( fileno( liqglo.liqglo_ribFP ) );
							RiOption( "rib", "pipe", &ribFD, RI_NULL );
						}
						else
						{
							liquidMessage( "Error opening RIB -- writing to stdout.\n", messageError );
						}
						liquidMessage( "Beginning RI output directly to renderer", messageInfo );
						RiBegin_liq( RI_NULL );
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
						fclose( liqglo.liqglo_ribFP );
#endif
						liqglo.liqglo_ribFP = NULL;

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

						liqglo.m_alfShadowRibGen = true;
					}//if( liqglo_currentJob.isShadow && !liqglo_currentJob.shadowArchiveRibDone && !fullShadowRib ) 

#ifndef RENDER_PIPE
					liquidMessage( "Beginning RIB output to '" + string( liqglo_currentJob.ribFileName.asChar() ) + "'", messageInfo );
					RiBegin_liq( const_cast< RtToken >( liqglo_currentJob.ribFileName.asChar() ) );

#ifdef DELIGHT
					LIQDEBUGPRINTF( "-> setting binary option\n" );
					{
						RtString format[1] = {"ascii"};
						if( liqglo.liqglo_doBinary ) 
							format[0] = "binary";
						RiOption( "rib", "format", ( RtPointer )&format, RI_NULL);
					}
#endif
#else
					liqglo.liqglo_ribFP = fopen( liqglo_currentJob.ribFileName.asChar(), "w" );
					if( liqglo.liqglo_ribFP ) 
					{
						RtInt ribFD = fileno( liqglo.liqglo_ribFP );
						RiOption( ( RtToken )"rib", ( RtToken )"pipe", &ribFD, RI_NULL );
					} 
					else
					{
						liquidMessage( "Error opening RIB -- writing to stdout.\n", messageError );
					}

					liquidMessage( "Beginning RI output directly to renderer", messageInfo );
					RiBegin_liq( RI_NULL );
#endif
					if( liqglo_currentJob.isShadow && !liqglo.fullShadowRib ) 
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
							printf("Finished RIB generation %s\n", liqglo_currentJob.ribFileName.asChar() );
						}
					}
					RiEnd();
#ifdef RENDER_PIPE
					fclose( liqglo_ribFP );
#endif
					liqglo.liqglo_ribFP = NULL;
					if( m_showProgress ) 
						printProgress( 3, liqglo.frameNumbers.size(), frameIndex );
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
			if( !liqglo.m_deferredGen ) 
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
					ts << "Textures." << liqglo.liqglo_lframe;
					textureJob.title = ts.str();

					while ( iter != txtList.end() ) 
					{
						liqRenderScript::Job textureSubtask;
						stringstream ts;
						ts << textureJob.title << " " << iter->imageName.asChar();
						textureSubtask.title = ts.str();
						if( liqglo.m_deferredGen ) {

						}
						stringstream ss;
						ss << iter->renderName.asChar() << " " << iter->ribFileName.asChar();
						liqRenderScript::Cmd cmd( ss.str(), ( liqglo.remoteRender && !liqglo.useNetRman ) );

						if( liqglo.m_alfredExpand ) 
							cmd.alfredExpand = true;

						cmd.alfredServices = liqglo.m_alfredServices.asChar();
						cmd.alfredTags     = liqglo.m_alfredTags.asChar();
						textureSubtask.commands.push_back( cmd );
						textureSubtask.chaserCommand = ( string( "sho \"" ) + liqglo.liqglo_textureDir.asChar() + " " + iter->imageName.asChar() + "\"" );
						++iter;
						textureJob.childJobs.push_back( textureSubtask );
					}
					frameScriptJob.childJobs.push_back( textureJob );
				}//if( txtList.size() )

				// write out shadows
				if( liqglo.liqglo_doShadows ) 
				{
					LIQDEBUGPRINTF( "-> writing out shadow information to alfred file.\n" );
					vector< structJob >::iterator iter = shadowList.begin();
					if( shadowList.size() ) 
					{
						alf_shadows = true;
						liqRenderScript::Job shadowJob;
						stringstream ts;
						ts << "Shadows." << liqglo.liqglo_lframe;
						shadowJob.title = ts.str();
						while ( iter != shadowList.end() ) 
						{
							alf_shadows = true;
							liqRenderScript::Job shadowSubtask;
							shadowSubtask.title = iter->name.asChar();
							if( alf_textures ) 
							{
								stringstream ss;
								ss << "Textures." << liqglo.liqglo_lframe;
								liqRenderScript::Job instanceJob;
								instanceJob.isInstance = true;
								instanceJob.title = ss.str();
								shadowSubtask.childJobs.push_back(instanceJob);
							}
							if( liqglo.m_deferredGen ) 
							{
								stringstream ss;
								ss << liquidTransGetSceneName().asChar() << "FrameRIBGEN" << currentBlock;
								liqRenderScript::Job instanceJob;
								instanceJob.isInstance = true;
								instanceJob.title = ss.str();
								shadowSubtask.childJobs.push_back(instanceJob);
							}
							stringstream ss;
							if( liqglo.useNetRman ) 
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
							liqRenderScript::Cmd cmd(ss.str(), (liqglo.remoteRender && !liqglo.useNetRman));
							if( liqglo.m_alfredExpand ) 
								cmd.alfredExpand = true;

							cmd.alfredServices = liqglo.m_alfredServices.asChar();
							cmd.alfredTags     = liqglo.m_alfredTags.asChar();
							shadowSubtask.commands.push_back(cmd);

							if(liqglo.cleanRib)  
							{
								stringstream ss;
#ifdef _WIN32
								ss << framePreCommand.asChar() << " " << RM_CMD << " \"" << iter->ribFileName.asChar() << "\"";
#else
								ss << framePreCommand.asChar() << " " << RM_CMD << " " << iter->ribFileName.asChar();
#endif

								shadowSubtask.cleanupCommands.push_back( liqRenderScript::Cmd( ss.str(), liqglo.remoteRender ) );
							}
							shadowSubtask.chaserCommand = ( string( "sho \"" ) + iter->imageName.asChar() + "\"" );
							++iter;
							if( !liqglo.m_alfShadowRibGen && !liqglo.fullShadowRib ) 
								liqglo.m_alfShadowRibGen = true;
							shadowJob.childJobs.push_back( shadowSubtask );
						}
						frameScriptJob.childJobs.push_back( shadowJob );
					}
				}//if( liqglo.liqglo_doShadows ) 
				LIQDEBUGPRINTF( "-> finished writing out shadow information to render script file.\n" );

				// write out make reflection pass
				if( refList.size() ) 
				{
					LIQDEBUGPRINTF( "-> Generating job for ReflectionMap pass\n" );
					vector<structJob>::iterator iter = refList.begin();

					alf_refmaps = true;
					liqRenderScript::Job reflectJob;
					stringstream ts;
					ts << "Reflections." << liqglo.liqglo_lframe;
					reflectJob.title = ts.str();

					while ( iter != refList.end() ) 
					{
						liqRenderScript::Job reflectSubtask;
						stringstream ts;
						ts << reflectJob.title << " " << iter->imageName.asChar();
						reflectSubtask.title = ts.str();
						if( liqglo.m_deferredGen ) {

						}
						if( alf_textures ) 
						{
							stringstream ss;
							ss << "Textures." << liqglo.liqglo_lframe;
							liqRenderScript::Job instanceJob;
							instanceJob.isInstance = true;
							instanceJob.title = ss.str();
							reflectJob.childJobs.push_back( instanceJob );
						}
						if( alf_shadows ) 
						{
							stringstream ss;
							ss << "Shadows." << liqglo.liqglo_lframe;
							liqRenderScript::Job instanceJob;
							instanceJob.isInstance = true;
							instanceJob.title = ss.str();
							reflectJob.childJobs.push_back( instanceJob );
						}

						stringstream ss;
						ss << iter->renderName.asChar() << " " << iter->ribFileName.asChar();
						liqRenderScript::Cmd cmd( ss.str(), (liqglo.remoteRender && !liqglo.useNetRman) );

						if( liqglo.m_alfredExpand ) 
							cmd.alfredExpand = true;

						cmd.alfredServices = liqglo.m_alfredServices.asChar();
						cmd.alfredTags     = liqglo.m_alfredTags.asChar();
						reflectSubtask.commands.push_back( cmd );
						reflectSubtask.chaserCommand = ( string( "sho \"" ) + liqglo.liqglo_textureDir.asChar() + " " + iter->imageName.asChar() + "\"" );
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
					liqRenderScript::Cmd cmd(framePreFrameCommand.asChar(), (liqglo.remoteRender && !liqglo.useNetRman));
					cmd.alfredServices = liqglo.m_alfredServices.asChar();
					cmd.alfredTags     = liqglo.m_alfredTags.asChar();
					frameScriptJob.commands.push_back(cmd);
				}

				if( m_outputHeroPass ) 
				{
					stringstream ss;
					MString ribFileName = frameJob->ribFileName;
					if ( liqglo.m_dirmaps.length() )
					{  
						ribFileName = "\\\"%D(" + ribFileName + ")\\\"";      
						LIQDEBUGPRINTF( "==> Set DirMaps : %s.\n", liqglo.m_dirmaps.asChar() );
					}
					if( liqglo.useNetRman ) 
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
					liqRenderScript::Cmd cmd(ss.str(), (liqglo.remoteRender && !liqglo.useNetRman));
					if( liqglo.m_alfredExpand ) 
						cmd.alfredExpand = true;

					cmd.alfredServices = liqglo.m_alfredServices.asChar();
					cmd.alfredTags     = liqglo.m_alfredTags.asChar();
					frameScriptJob.commands.push_back(cmd);
				}//if( m_outputHeroPass ) 
				LIQDEBUGPRINTF( "-> finished writing out hero information to alfred file.\n" );
				if( m_outputShadowPass ) 
				{
					stringstream ss;
					if( liqglo.useNetRman ) 
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
					liqRenderScript::Cmd cmd(ss.str(), (liqglo.remoteRender && !liqglo.useNetRman));
					if( liqglo.m_alfredExpand ) 
						cmd.alfredExpand = true;

					cmd.alfredServices = liqglo.m_alfredServices.asChar();
					cmd.alfredTags     = liqglo.m_alfredTags.asChar();
					frameScriptJob.commands.push_back(cmd);
				}//if( m_outputShadowPass )

				if( liqglo.cleanRib || ( framePostFrameCommand != MString( "" ) ) ) 
				{
					if( liqglo.cleanRib ) 
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
						if( liqglo.m_alfShadowRibGen ) 
						{
#ifdef _WIN32
							ss << framePreCommand.asChar() << " " << RM_CMD << " \"" << baseShadowName.asChar() << "\"";
#else
							ss << framePreCommand.asChar() << " " << RM_CMD << " " << baseShadowName.asChar();
#endif
						}
						frameScriptJob.cleanupCommands.push_back(liqRenderScript::Cmd(ss.str(), liqglo.remoteRender));
					}
					if( framePostFrameCommand != MString("") ) 
					{
						liqRenderScript::Cmd cmd(framePostFrameCommand.asChar(), (liqglo.remoteRender && !liqglo.useNetRman));
						frameScriptJob.cleanupCommands.push_back(cmd);
					}
				}//if( cleanRib || ( framePostFrameCommand != MString( "" ) ) ) 
				if( m_outputHeroPass ) 
					frameScriptJob.chaserCommand = (string( "sho \"" ) + frameJob->imageName.asChar() + "\"" );
				if( m_outputShadowPass ) 
					frameScriptJob.chaserCommand = (string( "sho \"" ) + shadowPassJob->imageName.asChar() + "\"" );
				if( m_outputShadowPass && !m_outputHeroPass ) 
					lastRibName = liquidGetRelativePath( liqglo.liqglo_relativeFileNames, shadowPassJob->ribFileName, liqglo.liqglo_projectDir );
				else 
					lastRibName = liquidGetRelativePath( liqglo.liqglo_relativeFileNames, frameJob->ribFileName, liqglo.liqglo_projectDir );
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
					stringstream ss;
					ss << RM_CMD << " " << tempDefname.asChar();
					jobScript.cleanupCommands.push_back( liqRenderScript::Cmd( ss.str(), liqglo.remoteRender ) );
				}
				if( cleanRenderScript ) 
				{
					stringstream ss;
					ss << RM_CMD << " " << renderScriptName.asChar();
					jobScript.cleanupCommands.push_back( liqRenderScript::Cmd( ss.str(), liqglo.remoteRender ) );
				}
				if( m_postJobCommand != MString("") ) 
					jobScript.cleanupCommands.push_back( liqRenderScript::Cmd(m_postJobCommand.asChar(), (liqglo.remoteRender && !liqglo.useNetRman) ) );
			}
			if( m_renderScriptFormat == ALFRED ) 
				jobScript.writeALF( liquidGetRelativePath( liqglo.liqglo_relativeFileNames, renderScriptName, liqglo.liqglo_projectDir ).asChar() );
			if( m_renderScriptFormat == XML ) 
				jobScript.writeXML( liquidGetRelativePath( liqglo.liqglo_relativeFileNames, renderScriptName, liqglo.liqglo_projectDir ).asChar() );
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
		MFnDependencyNode rGlobalNode( liqglo.rGlobalObj );
		MPlug nPlug;
		nPlug = rGlobalNode.findPlug( "lastRenderScript" );
		nPlug.setValue( renderScriptName );
		nPlug = rGlobalNode.findPlug( "lastRibFile" );
		nPlug.setValue( lastRibName );
		LIQDEBUGPRINTF( "-> spawning command.\n" );
		if( liqglo.launchRender ) 
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
				printf("2.liqProcessLauncher::execute(%s, \"%s\" ,%s, %d)\n", m_renderScriptCommand.asChar(), renderScriptName.asChar(), liqglo.liqglo_projectDir.asChar(), false);
				liqProcessLauncher::execute( m_renderScriptCommand, "\"" + renderScriptName + "\"", liqglo.liqglo_projectDir, false );
#else
				liqProcessLauncher::execute( m_renderScriptCommand, renderScriptName, liqglo.liqglo_projectDir, false );
#endif
				if( liqglo.m_renderView ) 
				{
					MString local = (liqglo.m_renderViewLocal)? "1":"0";
					stringstream tmp;
					tmp << liqglo.m_renderViewTimeOut;
					//=============
					printf(">> m_renderView: m_renderViewTimeOut = %s\n", tmp.str().c_str() );
					MString timeout( tmp.str().c_str() );
					MString displayCmd = "liquidRenderView "+( (liqglo.renderCamera=="")?"":("-c "+liqglo.renderCamera) ) + " -l " + local + " -port " + liqglo.m_renderViewPort + " -timeout " + timeout ;
					if( liqglo.m_renderViewCrop ) 
						displayCmd = displayCmd + " -doRegion";
					displayCmd = displayCmd + ";liquidSaveRenderViewImage();";
					//============= 
					printf(">> m_renderView: m_displayCmd = %s\n", displayCmd.asChar() );
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
						printf("    - skipping '%s'\n", iter->ribFileName );
						liquidMessage("     - skipping '"+string(iter->ribFileName.asChar())+"'", messageInfo);
						++iter;
						continue;
					}
					liquidMessage( "Making textures '" + string( iter->imageName.asChar() ) + "'", messageInfo );
					printf("[!] Making textures '%s'\n", iter->imageName.asChar() );
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
					printf("\n[!] Rendering shadow maps... \n");
					vector<structJob>::iterator iter = shadowList.begin();
					while ( iter != shadowList.end() ) 
					{
						if( iter->skip ) 
						{
							printf("    - skipping '%s'\n", iter->ribFileName.asChar() );
							liquidMessage( "    - skipping '" + string( iter->ribFileName.asChar() ) + "'", messageInfo );
							++iter;
							continue;
						}
						printf("    + '%s'\n", iter->ribFileName.asChar() );
						liquidMessage( "    + '" + string( iter->ribFileName.asChar() ) + "'", messageInfo );
#ifdef _WIN32
						printf("3.liqProcessLauncher::execute(%s, %s \"%s\", %s, %d)\n", liqglo.liquidRenderer.renderCommand.asChar(), liqglo.liquidRenderer.renderCmdFlags.asChar(), iter->ribFileName.asChar(), liqglo.liqglo_projectDir.asChar(), true);
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
					printf("[!] Rendering hero pass...\n");
					if( liqglo_currentJob.skip ) 
					{
						printf("    - skipping '%s'\n", liqglo_currentJob.ribFileName.asChar() );
						liquidMessage( "    - skipping '" + string( liqglo_currentJob.ribFileName.asChar() ) + "'", messageInfo );
					} 
					else 
					{
						printf("    + '%s'\n", liqglo_currentJob.ribFileName.asChar() );
						liquidMessage( "    + '" + string( liqglo_currentJob.ribFileName.asChar() ) + "'", messageInfo );

#ifdef _WIN32
						printf("4.liqProcessLauncher::execute(%s, %s %s \"%s\" %s, %d)\n", liqglo.liquidRenderer.renderCommand.asChar(), liqglo.liqglo_rifParams.asChar(), liqglo.liquidRenderer.renderCmdFlags.asChar(), liqglo_currentJob.ribFileName.asChar(), liqglo.liqglo_projectDir.asChar(), false);
						liqProcessLauncher::execute( liqglo.liquidRenderer.renderCommand, " "+liqglo.liqglo_rifParams+" "+ liqglo.liquidRenderer.renderCmdFlags + " \"" + liqglo_currentJob.ribFileName + "\"", "\"" + liqglo.liqglo_projectDir + "\"", false );
#else
						liqProcessLauncher::execute( liqglo.liquidRenderer.renderCommand, " "+liqglo.liqglo_rifParams+" "+ liqglo.liquidRenderer.renderCmdFlags + " " + liqglo_currentJob.ribFileName, liqglo.liqglo_projectDir, false );
#endif
						/*  philippe: here we launch the liquidRenderView command which will listen to the liqmaya display driver
						to display buckets in the renderview.
						*/
						if( liqglo.m_renderView ) 
						{
							MString local = (liqglo.m_renderViewLocal)? "1":"0";
							stringstream tmp;
							tmp << liqglo.m_renderViewTimeOut;
							//=============
							printf(">> m_renderView: m_renderViewTimeOut = %s\n", tmp.str().c_str() );
							MString timeout( tmp.str().c_str() );
							MString displayCmd = "liquidRenderView "+( (liqglo.renderCamera=="")?"":("-c "+liqglo.renderCamera) ) + " -l " + local + " -port " + liqglo.m_renderViewPort + " -timeout " + timeout ;
							if( liqglo.m_renderViewCrop ) 
								displayCmd = displayCmd + " -doRegion";
							displayCmd = displayCmd + ";liquidSaveRenderViewImage();";
							//============= 
							printf(">> m_renderView: m_displayCmd = %s\n",  displayCmd.asChar() );
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

/**
* Calculate the port field of view for the camera.
*/
void liqRibTranslator::portFieldOfView( int port_width, int port_height,
									   double& horizontal,
									   double& vertical,
									   MFnCamera& fnCamera )
{
	CM_TRACE_FUNC("liqRibTranslator::portFieldOfView("<<port_width<<","<<port_height<<",&horizontal,&vertical,&fnCamera)");
	// note : works well - api tested
	double left, right, bottom, top;
	double aspect = (double) port_width / port_height;
	computeViewingFrustum(aspect,left,right,bottom,top,fnCamera);

	double neardb = fnCamera.nearClippingPlane();
	horizontal    = atan( ( ( right - left ) * 0.5 ) / neardb ) * 2.0;
	vertical      = atan( ( ( top - bottom ) * 0.5 ) / neardb ) * 2.0;
}

/**
* Calculate the viewing frustrum for the camera.
*/
void liqRibTranslator::computeViewingFrustum ( double     window_aspect,
											  double&    left,
											  double&    right,
											  double&    bottom,
											  double&    top,
											  MFnCamera& cam )
{
	CM_TRACE_FUNC("liqRibTranslator::computeViewingFrustum("<<window_aspect<<","<<",&left,&right,&bottom,&top,&cam)");

	double film_aspect   = cam.aspectRatio();
	double aperture_x    = cam.horizontalFilmAperture();
	double aperture_y    = cam.verticalFilmAperture();
	double offset_x      = cam.horizontalFilmOffset();
	double offset_y      = cam.verticalFilmOffset();
	double focal_to_near = cam.nearClippingPlane() / (cam.focalLength() * MM_TO_INCH);

	focal_to_near *= cam.cameraScale();

	double scale_x = 1.0;
	double scale_y = 1.0;
	double translate_x = 0.0;
	double translate_y = 0.0;

	switch ( cam.filmFit() ) 
	{
	case MFnCamera::kFillFilmFit:
		if( window_aspect < film_aspect ) 
			scale_x = window_aspect / film_aspect;
		else 
			scale_y = film_aspect / window_aspect;
		break;
	case MFnCamera::kHorizontalFilmFit:
		scale_y = film_aspect / window_aspect;
		if( scale_y > 1.0 ) 
			translate_y = cam.filmFitOffset() * ( aperture_y - ( aperture_y * scale_y ) ) / 2.0;
		break;
	case MFnCamera::kVerticalFilmFit:
		scale_x = window_aspect / film_aspect;
		if(scale_x > 1.0 ) 
			translate_x = cam.filmFitOffset() * ( aperture_x - ( aperture_x * scale_x ) ) / 2.0;
		break;
	case MFnCamera::kOverscanFilmFit:
		if( window_aspect < film_aspect ) 
			scale_y = film_aspect / window_aspect;
		else 
			scale_x = window_aspect / film_aspect;
		break;
	case MFnCamera::kInvalid:
		break;
	}

	left   = focal_to_near * (-.5 * aperture_x * scale_x + offset_x + translate_x );
	right  = focal_to_near * ( .5 * aperture_x * scale_x + offset_x + translate_x );
	bottom = focal_to_near * (-.5 * aperture_y * scale_y + offset_y + translate_y );
	top    = focal_to_near * ( .5 * aperture_y * scale_y + offset_y + translate_y );

	// NOTE :
	//      all the code above could be replaced by :
	//
	//      cam.getRenderingFrustum( window_aspect, left, right, bottom, top );
	//
	//      should we keep this for educationnal purposes or use the API call ??
}

/**
* Get information about the given camera.
*/
void liqRibTranslator::getCameraInfo( MFnCamera& cam )
{
	CM_TRACE_FUNC("liqRibTranslator::getCameraInfo("<<",&cam)");

	// Resolution can change if camera film-gate clips image
	// so we must keep camera width/height separate from render
	// globals width/height.
	//
	liqglo.cam_width  = width;
	liqglo.cam_height = height;

	// If we are using a film-gate then we may need to
	// adjust the resolution to simulate the 'letter-boxed'
	// effect.
	if( cam.filmFit() == MFnCamera::kHorizontalFilmFit ) 
	{
		if( !ignoreFilmGate ) 
		{
			double new_height = liqglo.cam_width / ( cam.horizontalFilmAperture() / cam.verticalFilmAperture() );
			if( new_height < liqglo.cam_height ) 
				liqglo.cam_height = ( int )new_height;
		}

		double hfov, vfov;
		portFieldOfView( liqglo.cam_width, liqglo.cam_height, hfov, vfov, cam );
		liqglo.fov_ratio = hfov / vfov;
	}
	else if( cam.filmFit() == MFnCamera::kVerticalFilmFit ) 
	{
		double new_width = liqglo.cam_height / ( cam.verticalFilmAperture() / cam.horizontalFilmAperture() );
		double hfov, vfov;

		// case 1 : film-gate smaller than resolution
		//         film-gate on
		if( ( new_width < liqglo.cam_width ) && ( !ignoreFilmGate ) ) 
		{
			liqglo.cam_width = ( int )new_width;
			liqglo.fov_ratio = 1.0;
		}
		// case 2 : film-gate smaller than resolution
		//         film-gate off
		else if( ( new_width < liqglo.cam_width ) && ( ignoreFilmGate ) ) 
		{
			portFieldOfView( ( int )new_width, liqglo.cam_height, hfov, vfov, cam );
			liqglo.fov_ratio = hfov / vfov;
		}
		// case 3 : film-gate larger than resolution
		//         film-gate on
		else if( !ignoreFilmGate ) 
		{
			portFieldOfView( ( int )new_width, liqglo.cam_height, hfov, vfov, cam );
			liqglo.fov_ratio = hfov / vfov;
		}
		// case 4 : film-gate larger than resolution
		//         film-gate off
		else if( ignoreFilmGate ) 
		{
			portFieldOfView( ( int )new_width, liqglo.cam_height, hfov, vfov, cam );
			liqglo.fov_ratio = hfov / vfov;
		}
	}
	else if( cam.filmFit() == MFnCamera::kOverscanFilmFit ) 
	{
		double new_height = liqglo.cam_width / ( cam.horizontalFilmAperture() / cam.verticalFilmAperture() );
		double new_width = liqglo.cam_height / ( cam.verticalFilmAperture() / cam.horizontalFilmAperture() );

		if( new_width < liqglo.cam_width ) 
		{
			if( !ignoreFilmGate ) {
				liqglo.cam_width = ( int ) new_width;
				liqglo.fov_ratio = 1.0;
			}
			else 
			{
				double hfov, vfov;
				portFieldOfView( ( int )new_width, liqglo.cam_height, hfov, vfov, cam );
				liqglo.fov_ratio = hfov / vfov;
			}
		}
		else {
			if( !ignoreFilmGate )
				liqglo.cam_height = ( int ) new_height;
			double hfov, vfov;
			portFieldOfView( liqglo.cam_width, liqglo.cam_height, hfov, vfov, cam );
			liqglo.fov_ratio = hfov / vfov;
		}
	}
	else if( cam.filmFit() == MFnCamera::kFillFilmFit ) 
	{
		double new_width = liqglo.cam_height / ( cam.verticalFilmAperture() / cam.horizontalFilmAperture() );
		double hfov, vfov;
		if( new_width >= liqglo.cam_width ) 
		{
			portFieldOfView( ( int )new_width, liqglo.cam_height, hfov, vfov, cam );
			liqglo.fov_ratio = hfov / vfov;
		}
		else 
		{
			portFieldOfView( liqglo.cam_width, liqglo.cam_height, hfov, vfov, cam );
			liqglo.fov_ratio = hfov / vfov;
		}
	}
}

/**
* Set up data for the current job.
*/
MStatus liqRibTranslator::buildJobs()
{
	CM_TRACE_FUNC("liqRibTranslator::buildJobs()");

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
				currentShader.buildJobs();
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
	if( liqglo.renderCamera != "" ) 
	{
		MSelectionList camList;
		camList.add( liqglo.renderCamera );
		camList.getDagPath( 0, cameraPath );
		MFnCamera fnCameraNode( cameraPath );
	} 
	else 
	{
		LIQDEBUGPRINTF( "-> getting current view\n" );
		M3dView::active3dView().getCamera( cameraPath );
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

/**
* Write the prologue for the RIB file.
* This includes all RI options but not the camera transformation.
*/
MStatus liqRibTranslator::ribPrologue()
{
	CM_TRACE_FUNC("liqRibTranslator::ribPrologue()");

	if( !liqglo.m_exportReadArchive ) 
	{
		LIQDEBUGPRINTF( "-> beginning to write prologue\n" );
		// general info for traceability
		//
		RiArchiveRecord( RI_COMMENT, "    Generated by Liquid v%s", LIQUIDVERSION );
		RiArchiveRecord( RI_COMMENT, "    Scene : %s", (liqglo.liqglo_projectDir + liquidTransGetSceneName()).asChar() );
#ifndef _WIN32
		uid_t userId = getuid();
		struct passwd *userPwd = getpwuid( userId );
		RiArchiveRecord( RI_COMMENT, "    User  : %s", userPwd->pw_name );
#else
		char* user = getenv("USERNAME");
		if( user )
			RiArchiveRecord( RI_COMMENT, "    User  : %s", user );
#endif
		time_t now;
		time( &now );
		char* theTime = ctime(&now);
		RiArchiveRecord( RI_COMMENT, "    Time  : %s", theTime );
		// set any rib options
		//
		writeStatisticsOptions();

		//limits options
		writeLimitsOptions();

		// set search paths
		//
		if ( liqglo.m_dirmaps.length() )
		{
			using namespace std;
			using namespace boost;

			const string str( liqglo.m_dirmaps.asChar() );
			stringstream ss;
			vector< string > names;
			typedef tokenizer< char_separator< char > > tokenizer;
			char_separator< char > sep("{ }");
			tokenizer tokens(str, sep);
			for ( tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter )
				names.push_back( *tok_iter );
			for ( unsigned i( 0 ); i < names.size(); i+= 3 )
			{
				// names.at(i+2)  - zone
				// names.at(i)    - from
				// names.at(i+1)  - to
				// [\"UNC\" \"/from_path/\" \"//comp/to_path/\"]
				ss << "[\\\"" << names.at(i+2) << "\\\" \\\"" << names.at(i) << "\\\" \\\"" << names.at(i+1) << "\\\"] ";
			}
			printf("%s\n", ss.str().c_str() );
			string dirmapsPath ( ss.str() );
			RtString list = const_cast< char* > ( dirmapsPath.c_str() );
			RiOption( "searchpath", "dirmap", &list, RI_NULL );
		}
		RtString list = const_cast< char* > ( liqglo.liqglo_shaderPath.asChar() );
		RiOption( "searchpath", "shader", &list, RI_NULL );

		MString texturePath = liqglo.liqglo_texturePath + ":" + liquidSanitizeSearchPath( liqglo.liqglo_textureDir );
		list = const_cast< char* > ( texturePath.asChar() );
		RiOption( "searchpath", "texture", &list, RI_NULL );

		MString archivePath = liqglo.liqglo_archivePath + ":" + liquidSanitizeSearchPath( liqglo.liqglo_ribDir );
		list = const_cast< char* > ( archivePath.asChar() );
		RiOption( "searchpath", "archive", &list, RI_NULL );

		list = const_cast< char* > ( liqglo.liqglo_proceduralPath.asChar() );
		RiOption( "searchpath", "procedural", &list, RI_NULL );

		// if rendering to the renderview, add a path to the liqmaya display driver
		if( liqglo.m_renderView ) 
		{
			MString home( getenv( "LIQUIDHOME" ) );
			MString displaySearchPath;
			if( (liqglo.liquidRenderer.renderName == MString("Pixie")) || (liqglo.liquidRenderer.renderName == MString("Air")) || (liqglo.liquidRenderer.renderName == MString("3Delight")) )
				displaySearchPath = ".:@::" + liqglo.liquidRenderer.renderHome + "/displays:" + liquidSanitizePath( home ) + "/displayDrivers/" + liqglo.liquidRenderer.renderName + "/";
			else 
				displaySearchPath = ".:@:" + liqglo.liquidRenderer.renderHome + "/etc:" + liquidSanitizePath( home ) +  "/displayDrivers/" + liqglo.liquidRenderer.renderName + "/";

			list = const_cast< char* > ( displaySearchPath.asChar() );
			RiArchiveRecord( RI_VERBATIM, "Option \"searchpath\" \"display\" [\"%s\"]\n", list );
		}
		//RiOrientation( RI_RH ); // Right-hand coordinates
		if( liqglo_currentJob.isShadow ) 
		{
			RiPixelSamples( liqglo_currentJob.shadowPixelSamples, liqglo_currentJob.shadowPixelSamples );
			RiShadingRate( liqglo_currentJob.shadingRateFactor );
			// Need to use Box filter for deep shadows.
			RiPixelFilter( RiBoxFilter, 1, 1 );
			RtString option;
			if( liqglo_currentJob.deepShadows ) 
				option = "deepshadow";
			else 
				option = "shadow";
			RiOption( "user", "string pass", ( RtPointer )&option, RI_NULL );
		} 
		else 
		{
			RtString hiderName;
			switch( liqglo.liqglo_hider ) 
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
			RiPixelSamples( liqglo.pixelSamples, liqglo.pixelSamples );
			RiShadingRate( liqglo.shadingRate );
			if( liqglo.m_rFilterX > 1 || liqglo.m_rFilterY > 1 ) 
			{
				switch (liqglo.m_rFilter) 
				{
				case pfBoxFilter:
					RiPixelFilter( RiBoxFilter, liqglo.m_rFilterX, liqglo.m_rFilterY );
					break;
				case pfTriangleFilter:
					RiPixelFilter( RiTriangleFilter, liqglo.m_rFilterX, liqglo.m_rFilterY );
					break;
				case pfCatmullRomFilter:
					RiPixelFilter( RiCatmullRomFilter, liqglo.m_rFilterX, liqglo.m_rFilterY );
					break;
				case pfGaussianFilter:
					RiPixelFilter( RiGaussianFilter, liqglo.m_rFilterX, liqglo.m_rFilterY );
					break;
				case pfSincFilter:
					RiPixelFilter( RiSincFilter, liqglo.m_rFilterX, liqglo.m_rFilterY );
					break;
#if defined ( DELIGHT ) || defined ( PRMAN ) || defined ( GENERIC_RIBLIB )
				case pfBlackmanHarrisFilter:
					RiArchiveRecord( RI_VERBATIM, "PixelFilter \"blackman-harris\" %g %g\n", liqglo.m_rFilterX, liqglo.m_rFilterY);
					break;
				case pfMitchellFilter:
					RiArchiveRecord( RI_VERBATIM, "PixelFilter \"mitchell\" %g %g\n", liqglo.m_rFilterX, liqglo.m_rFilterY);
					break;
				case pfSepCatmullRomFilter:
					RiArchiveRecord( RI_VERBATIM, "PixelFilter \"separable-catmull-rom\" %g %g\n", liqglo.m_rFilterX, liqglo.m_rFilterY);
					break;
				case pfBesselFilter:
					RiArchiveRecord( RI_VERBATIM, "PixelFilter \"bessel\" %g %g\n", liqglo.m_rFilterX, liqglo.m_rFilterY);
					break;
#endif
#if defined ( PRMAN ) || defined ( GENERIC_RIBLIB )
				case pfLanczosFilter:
					RiArchiveRecord( RI_VERBATIM, "PixelFilter \"lanczos\" %g %g\n", liqglo.m_rFilterX, liqglo.m_rFilterY);
					break;
				case pfDiskFilter:
					RiArchiveRecord( RI_VERBATIM, "PixelFilter \"disk\" %g %g\n", liqglo.m_rFilterX, liqglo.m_rFilterY);
					break;
#endif
				default:
					RiArchiveRecord( RI_COMMENT, "Unknown Pixel Filter selected" );
					break;
				}
			}
			RtString option( "beauty" );
			RiOption( "user", "string pass", ( RtPointer )&option, RI_NULL );
		}

		// RAYTRACING OPTIONS
		if( liqglo.liquidRenderer.supports_RAYTRACE && liqglo.rt_useRayTracing ) 
		{
			RiArchiveRecord( RI_COMMENT, "Ray Tracing : ON" );
			RiOption( "trace",   "int maxdepth",                ( RtPointer ) &liqglo.rt_traceMaxDepth,            RI_NULL );
#if defined ( DELIGHT ) || defined ( PRMAN ) || defined ( GENERIC_RIBLIB )
			RiOption( "trace",   "float specularthreshold",     ( RtPointer ) &liqglo.rt_traceSpecularThreshold, RI_NULL );
			RiOption( "trace",   "int continuationbydefault",   ( RtPointer ) &liqglo.rt_traceRayContinuation,   RI_NULL );
			RiOption( "limits",  "int geocachememory",          ( RtPointer ) &liqglo.rt_traceCacheMemory,       RI_NULL );
			RiOption( "user",    "float traceBreadthFactor",    ( RtPointer ) &liqglo.rt_traceBreadthFactor,     RI_NULL );
			RiOption( "user",    "float traceDepthFactor",      ( RtPointer ) &liqglo.rt_traceDepthFactor,       RI_NULL );
#endif
		} 
		else 
		{
			if( !liqglo.liquidRenderer.supports_RAYTRACE ) 
				RiArchiveRecord( RI_COMMENT, "Ray Tracing : NOT SUPPORTED" );
			else 
			{
				RiArchiveRecord( RI_COMMENT, "Ray Tracing : OFF" );
				RtInt maxDepth = 0;
				RiOption( "trace",   "int maxdepth",                ( RtPointer ) &maxDepth,                  RI_NULL );
			}
		}

		// CUSTOM OPTIONS
		MFnDependencyNode globalsNode( liqglo.rGlobalObj );
		MPlug prePostplug( globalsNode.findPlug( "preFrameBeginMel" ) );
		MString melcommand( prePostplug.asString() );
		if( liqglo.m_preFrameRIB != "" || melcommand.length() )
		{
			RiArchiveRecord(RI_COMMENT,  " Pre-FrameBegin RIB from liquid globals" );
			MGlobal::executeCommand( melcommand );
			RiArchiveRecord(RI_VERBATIM, ( char* )liqglo.m_preFrameRIB.asChar() );
			RiArchiveRecord(RI_VERBATIM, "\n");
		}
		if( liqglo.m_bakeNonRasterOrient || liqglo.m_bakeNoCullHidden || liqglo.m_bakeNoCullBackface ) 
		{
			RiArchiveRecord( RI_COMMENT, "Bake Attributes" );
			RtInt zero( 0 );
			if( liqglo.m_bakeNonRasterOrient )
				RiAttribute( "dice","int rasterorient", &zero, RI_NULL );
			if( liqglo.m_bakeNoCullBackface )
				RiAttribute( "cull","int backfacing", &zero, RI_NULL );
			if( liqglo.m_bakeNoCullHidden )
				RiAttribute( "cull","int hidden", &zero, RI_NULL );
		}
	}
	ribStatus = kRibBegin;
	return MS::kSuccess;
}

/**
* Write the epilogue for the RIB file.
*/
MStatus liqRibTranslator::ribEpilogue()
{
	CM_TRACE_FUNC("liqRibTranslator::ribEpilogue()");

	if(ribStatus == kRibBegin) 
		ribStatus = kRibOK;
	return (ribStatus == kRibOK ? MS::kSuccess : MS::kFailure);
}

/**
* Scan the DAG at the given frame number and record information about the scene for writing.
*/
MStatus liqRibTranslator::scanSceneNodes( MObject &currentNode, MDagPath &path, float lframe, int sample, int &count, MStatus& returnStatus ) 
{
	CM_TRACE_FUNC("liqRibTranslator::scanSceneNodes(&currentNode, &path,"<<lframe<<","<<sample<<",&count)");

	MFnDagNode dagNode;
	returnStatus = dagNode.setObject( currentNode );
	if(MS::kSuccess != returnStatus)
		return returnStatus;

	LIQ_CHECK_CANCEL_REQUEST;
	// scanScene: check for a rib generator
	MStatus plugStatus;
	MPlug ribGenPlug = dagNode.findPlug( "liquidRibGen", &plugStatus );
	if( plugStatus == MS::kSuccess )
	{
		// scanScene: check the node to make sure it's not using the old ribGen assignment method, this is for backwards
		// compatibility.  If it's a kTypedAttribute that it's more than likely going to be a string!
		if( ribGenPlug.attribute().apiType() == MFn::kTypedAttribute )
		{
			MString ribGenNode;
			ribGenPlug.getValue( ribGenNode );
			MSelectionList ribGenList;
			MStatus ribGenAddStatus = ribGenList.add( ribGenNode );
			if( ribGenAddStatus == MS::kSuccess )
				htable->insert( path, lframe, sample, MRT_RibGen, count++ );
		}
		else
		{
			if( ribGenPlug.isConnected() )
				htable->insert( path, lframe, sample, MRT_RibGen, count++ );
		}

	}
// 	liquidMessage2(messageInfo,"%s, %s,\t\t\t\t %d%d%d %d%d %d%d %d%d%d%d"
// 		,path.fullPathName().asChar(), currentNode.apiTypeStr()
// 		,currentNode.hasFn( MFn::kNurbsSurface )
// 		,currentNode.hasFn( MFn::kMesh )
// 		,currentNode.hasFn( MFn::kParticle )
// 
// 		,currentNode.hasFn( MFn::kLocator )
// 		,currentNode.hasFn( MFn::kSubdiv )
// 
// 		,currentNode.hasFn( MFn::kPfxHair )
// 		,currentNode.hasFn( MFn::kPfxGeometry )
// 
// 		,currentNode.hasFn( MFn::kPfxToon )
// 		,currentNode.hasFn( MFn::kImplicitSphere )
// 		,currentNode.hasFn( MFn::kPluginShape )
// 		,currentNode.hasFn( MFn::kNurbsCurve ) 
	
	if(  currentNode.hasFn( MFn::kNurbsSurface )
		|| currentNode.hasFn( MFn::kMesh )
		|| currentNode.hasFn( MFn::kParticle )
		|| currentNode.hasFn( MFn::kLocator )
		|| currentNode.hasFn( MFn::kSubdiv )
		|| (currentNode.hasFn( MFn::kPfxHair ) && !currentNode.hasFn( MFn::kPfxGeometry )) //pfxHair has both of these two attributes, so we process pfxHair as MFn::kPfxGeometry
		|| currentNode.hasFn( MFn::kPfxToon )
		|| currentNode.hasFn( MFn::kImplicitSphere )
		|| currentNode.hasFn( MFn::kPluginShape ) ) // include plugin shapes as placeholders
	{
		LIQDEBUGPRINTF( "==> inserting obj to htable %s\n", path.fullPathName().asChar() );
		if( ( sample > 0 ) && isObjectMotionBlur( path ))
			htable->insert( path, lframe, sample, MRT_Unknown, count++ );
		else
			htable->insert( path, lframe, 0, MRT_Unknown, count++ );
		LIQDEBUGPRINTF( "==> %s inserted\n", path.fullPathName().asChar() );
	}
	// Alf: treat PFX as three separate entities so a separate shading group can
	// be assigned to each part
	if( currentNode.hasFn( MFn::kPfxGeometry ) )
	{
		LIQDEBUGPRINTF( "==> inserting kPfxGeometry\n" );
		/*
		MStatus status;
		bool hasTube( 0 ), hasLeaf( 0 ), hasPetal( 0 );
		MFnDagNode pfxNode( currentNode );
		MPlug brushPlug( pfxNode.findPlug( "brush" ) );
		MPlugArray brushArray;
		brushPlug.connectedTo( brushArray, 1, 0 );
		MFnDependencyNode brushNode( brushArray[0].node() );
		MPlug brushAttr( brushNode.findPlug( "tubes" ) );
		hasTube = brushAttr.asBool();
		brushAttr = brushNode.findPlug( "leaves" );
		hasLeaf = brushAttr.asBool();
		brushAttr = brushNode.findPlug( "flowers" );
		hasPetal = brushAttr.asBool();


		if( hasTube )
		{
		if( ( sample > 0 ) && isObjectMotionBlur( path ))
		htable->insert( path, lframe, sample, MRT_PfxTube, count++ );
		else
		htable->insert( path, lframe, 0, MRT_PfxTube, count++ );
		}
		if( hasLeaf )
		{
		if( ( sample > 0 ) && isObjectMotionBlur( path ))
		htable->insert( path, lframe, sample, MRT_PfxLeaf, count++ );
		else
		htable->insert( path, lframe, 0, MRT_PfxLeaf, count++ );
		}
		if( hasPetal )
		{
		if( ( sample > 0 ) && isObjectMotionBlur( path ))
		htable->insert( path, lframe, sample, MRT_PfxPetal, count++ );
		else
		htable->insert( path, lframe, 0, MRT_PfxPetal, count++ );
		}
		*/
		MStatus status;
		MRenderLineArray tube, leaf, petal;
		MFnPfxGeometry pfx( path, &status );
		if( status == MS::kSuccess )
			pfx.getLineData( tube, leaf, petal,1,0,0,0,0,0,0,0,0 );

		if( tube.length() )
		{
			if( ( sample > 0 ) && isObjectMotionBlur( path ))
				htable->insert( path, lframe, sample, MRT_PfxTube, count++ );
			else
				htable->insert( path, lframe, 0, MRT_PfxTube, count++ );
		}
		if( leaf.length() )
		{
			if( ( sample > 0 ) && isObjectMotionBlur( path ))
				htable->insert( path, lframe, sample, MRT_PfxLeaf, count++ );
			else
				htable->insert( path, lframe, 0, MRT_PfxLeaf, count++ );
		}
		if( petal.length() )
		{
			if( ( sample > 0 ) && isObjectMotionBlur( path ))
				htable->insert( path, lframe, sample, MRT_PfxPetal, count++ );
			else
				htable->insert( path, lframe, 0, MRT_PfxPetal, count++ );
		}
		tube.deleteArray(); 
		leaf.deleteArray(); 
		petal.deleteArray();
	}
	if( currentNode.hasFn( MFn::kNurbsCurve ) )
	{
		LIQDEBUGPRINTF( "==> inserting kNurbsCurve\n" );

		MStatus plugStatus;
		MPlug renderCurvePlug = dagNode.findPlug( "liquidCurve", &plugStatus );
		if( liqglo.liqglo_renderAllCurves || ( plugStatus == MS::kSuccess ) )
		{
			bool renderCurve( false );
			renderCurvePlug.getValue( renderCurve );
			if( renderCurve )
			{
				if( ( sample > 0 ) && isObjectMotionBlur( path ))
					htable->insert( path, lframe, sample, MRT_NuCurve, count++ );
				else
					htable->insert( path, lframe, 0, MRT_NuCurve, count++ );
			}
		}
	}
	return returnStatus;
}


/**
* Scan the DAG at the given frame number and record information about the scene for writing.
*/
MStatus liqRibTranslator::scanScene(float lframe, int sample )
{
	CM_TRACE_FUNC("liqRibTranslator::scanScene("<<lframe<<","<<sample<<")");

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
					printf("Liquid -> pre-frame script executed successfully.\n");
				else 
					printf("Liquid -> ERROR :pre-frame script failed.\n");
			}
		}

		MStatus returnStatus;
		// scanScene: Scan the scene for lights
		{
			MItDag dagLightIterator( MItDag::kDepthFirst, MFn::kLight, &returnStatus);

			for (; !dagLightIterator.isDone(); dagLightIterator.next()) 
			{
				LIQ_CHECK_CANCEL_REQUEST;
				MDagPath path;
				MObject currentNode;
				currentNode = dagLightIterator.item();
				MFnDagNode dagNode;
				dagLightIterator.getPath( path );
				if(MS::kSuccess != returnStatus) 
					continue;
				if(!currentNode.hasFn(MFn::kDagNode)) 
					continue;
				returnStatus = dagNode.setObject( currentNode );
				if(MS::kSuccess != returnStatus) 
					continue;

				// scanScene: if it's a light then insert it into the hash table
				if( currentNode.hasFn( MFn::kLight ) ) 
				{
					if( currentNode.hasFn( MFn::kAreaLight ) ) 
					{
						// add a coordSys node if necessary
						MStatus status;
						bool coordsysExists = false;
						// get the coordsys name
						MFnDependencyNode areaLightDep( currentNode );
						MString coordsysName = areaLightDep.name()+"CoordSys";
						// get the transform
						MObject transform = path.transform();
						// check the coordsys does not exist yet under the transform
						MFnDagNode transformDag( transform );
						int numChildren = transformDag.childCount();
						if( numChildren > 1 ) 
						{
							for ( unsigned int i=0; i<numChildren; i++ ) 
							{
								MObject childObj = transformDag.child( i, &status );
								if( status == MS::kSuccess && childObj.hasFn( MFn::kLocator ) ) 
								{
									MFnDependencyNode test(childObj);
									if( test.name() == coordsysName ) 
										coordsysExists = true;
								}
							}
						}
						if( !coordsysExists ) 
						{
							// create the coordsys
							MDagModifier coordsysNode;
							MObject coordsysObj  = coordsysNode.createNode( "liquidCoordSys", transform, &status );
							if( status == MS::kSuccess ) 
							{
								// rename node to match light name
								coordsysNode.doIt();
								if( status == MS::kSuccess ) 
								{
									MFnDependencyNode coordsysDep( coordsysObj );
									coordsysDep.setName( coordsysName );
								}
							}
						}
					}

					if( ( sample > 0 ) && isObjectMotionBlur( path )) 
						htable->insert( path, lframe, sample, MRT_Light,	count++ );
					else 
						htable->insert( path, lframe, 0, MRT_Light, count++ );
					continue;
				}
			}
		}
		{
			MItDag dagCoordSysIterator( MItDag::kDepthFirst, MFn::kLocator, &returnStatus);

			for (; !dagCoordSysIterator.isDone(); dagCoordSysIterator.next()) 
			{
				LIQ_CHECK_CANCEL_REQUEST;
				MDagPath path;
				MObject currentNode;
				currentNode = dagCoordSysIterator.item();
				MFnDagNode dagNode;
				dagCoordSysIterator.getPath( path );
				if(MS::kSuccess != returnStatus) 
					continue;
				if(!currentNode.hasFn(MFn::kDagNode)) 
					continue;
				returnStatus = dagNode.setObject( currentNode );
				if(MS::kSuccess != returnStatus) 
					continue;

				// scanScene: if it's a coordinate system then insert it into the hash table
				if( dagNode.typeName() == "liquidCoordSys" ) 
				{
					int coordType = 0;
					MPlug typePlug = dagNode.findPlug( "type", &returnStatus );
					if( MS::kSuccess == returnStatus ) 
						typePlug.getValue( coordType );

					if( ( sample > 0 ) && isObjectMotionBlur( path )) 
					{
						// philippe : should I store a motion-blurred clipping plane ?
						if( coordType == 5 ) 
							htable->insert(path, lframe, sample, MRT_ClipPlane,count++ );
						else 
							htable->insert(path, lframe, sample, MRT_Coord,count++ );
					} 
					else 
					{
						if( coordType == 5 ) 
							htable->insert(path, lframe, 0, MRT_ClipPlane,count++ );
						htable->insert(path, lframe, 0, MRT_Coord,count++ );
					}
					continue;
				}
			}
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
			// scanScene: Now deal with all the particle-instanced objects (where a
			// particle is replaced by an object or group of objects).
			//
			MItInstancer instancerIter;
			while( !instancerIter.isDone() )
			{
				MDagPath path( instancerIter.path() );
				MString instanceStr( ( MString )"|INSTANCE_" +
					instancerIter.instancerId() + (MString)"_" +
					instancerIter.particleId() + (MString)"_" +
					instancerIter.pathId() );
				MMatrix instanceMatrix( instancerIter.matrix() );
				if( ( sample > 0 ) && isObjectMotionBlur( path ) )
					htable->insert( path, lframe, sample, MRT_Unknown,count++, &instanceMatrix, instanceStr, instancerIter.particleId() );
				else
					htable->insert( path, lframe, 0, MRT_Unknown,count++, &instanceMatrix, instanceStr, instancerIter.particleId() );
				instancerIter.next();
			}

		}
		else
		{
			// scanScene: find out the current selection for possible selected object output
			MSelectionList currentSelection;
			MGlobal::getActiveSelectionList( currentSelection );
			MItSelectionList selIterator( currentSelection );
			MItDag dagIterator( MItDag::kDepthFirst, MFn::kInvalid, &returnStatus);
			for( ; !selIterator.isDone(); selIterator.next() )
			{
				MDagPath objectPath;
				selIterator.getDagPath( objectPath );
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
			// scanScene: Now deal with all the particle-instanced objects (where a
			// particle is replaced by an object or group of objects).
			//
			MItInstancer instancerIter;
			while( !instancerIter.isDone() )
			{
				MDagPath path( instancerIter.path() );
				MString instanceStr( ( MString )"|INSTANCE_" +
					instancerIter.instancerId() + (MString)"_" +
					instancerIter.particleId() + (MString)"_" +
					instancerIter.pathId() );

				MMatrix instanceMatrix( instancerIter.matrix() );

				if( ( sample > 0 ) && isObjectMotionBlur( path ))
					htable->insert( path, lframe, sample, MRT_Unknown,count++, &instanceMatrix, instanceStr, instancerIter.particleId() );
				else
					htable->insert( path, lframe, 0, MRT_Unknown,count++, &instanceMatrix, instanceStr, instancerIter.particleId() );
				instancerIter.next();
			}
		}

		vector<structJob>::iterator iter = jobList.begin();
		while ( iter != jobList.end() ) 
		{
			LIQ_CHECK_CANCEL_REQUEST;
			// scanScene: Get the camera/light info for this job at this frame
			MStatus status;

			if( !iter->isShadow ) 
			{
				MDagPath path;
				MFnCamera   fnCamera( iter->path );
				iter->gotJobOptions = false;
				status.clear();
				MPlug cPlug = fnCamera.findPlug( MString( "ribOptions" ), &status );
				if( status == MS::kSuccess ) 
				{
					cPlug.getValue( iter->jobOptions );
					iter->gotJobOptions = true;
				}
				getCameraInfo( fnCamera );
				iter->width = liqglo.cam_width;
				iter->height = liqglo.cam_height;
				// scanScene: Renderman specifies shutter by time open
				// so we need to convert shutterAngle to time.
				// To do this convert shutterAngle to degrees and
				// divide by 360.
				//
				iter->camera[sample].shutter = fnCamera.shutterAngle() * 0.5 / M_PI;
				liqglo.liqglo_shutterTime = iter->camera[sample].shutter;
				iter->camera[sample].orthoWidth     = fnCamera.orthoWidth();
				iter->camera[sample].orthoHeight    = fnCamera.orthoWidth() * ((float)liqglo.cam_height / (float)liqglo.cam_width);
				iter->camera[sample].motionBlur     = fnCamera.isMotionBlur();
				iter->camera[sample].focalLength    = fnCamera.focalLength();
				iter->camera[sample].focalDistance  = fnCamera.focusDistance();
				iter->camera[sample].fStop          = fnCamera.fStop();
				iter->camera[sample].name           = fnCamera.fullPathName();

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
				iter->camera[sample].horizontalFilmOffset = ho;
				iter->camera[sample].verticalFilmOffset   = vo;

				// convert focal length to scene units
				MDistance flenDist(iter->camera[sample].focalLength,MDistance::kMillimeters);
				iter->camera[sample].focalLength = flenDist.as(MDistance::uiUnit());

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
				iter->camera[sample].mat = xform.asMatrixInverse() * camRotMatrix;

				if( fnCamera.isClippingPlanes() ) 
				{
					iter->camera[sample].neardb    = fnCamera.nearClippingPlane();
					iter->camera[sample].fardb    = fnCamera.farClippingPlane();
				} 
				else 
				{
					iter->camera[sample].neardb    = 0.001;    // TODO: these values are duplicated elsewhere in this file
					iter->camera[sample].fardb    = 250000.0; // TODO: these values are duplicated elsewhere in this file
				}
				iter->camera[sample].isOrtho = fnCamera.isOrtho();

				// scanScene: The camera's fov may not match the rendered image in Maya
				// if a film-fit is used. 'fov_ratio' is used to account for
				// this.
				//
				iter->camera[sample].hFOV = fnCamera.horizontalFieldOfView()/liqglo.fov_ratio;
				iter->aspectRatio = liqglo.aspectRatio;

				// scanScene: Determine what information to write out (RGB, alpha, zbuffer)
				//
				iter->imageMode.clear();

				bool isOn;
				MPlug boolPlug;
				boolPlug = fnCamera.findPlug( "image" );

				boolPlug.getValue( isOn );
				if( isOn ) 
				{
					// We are writing RGB info
					//
					iter->imageMode = "rgb";
					iter->format = liqglo.outFormat;
				}
				boolPlug = fnCamera.findPlug( "mask" );
				boolPlug.getValue( isOn );
				if( isOn ) 
				{
					// We are writing alpha channel info
					//
					iter->imageMode += "a";
					iter->format = liqglo.outFormat;
				}
				boolPlug = fnCamera.findPlug( "depth" );
				boolPlug.getValue( isOn );
				if( isOn ) {
					// We are writing z-buffer info
					//
					iter->imageMode = "z";
					iter->format = "zfile";
				}
			} 
			else 
			{
				// scanScene: doing shadow render
				//
				MDagPath path;
				MFnLight   fnLight( iter->path );
				status.clear();

				iter->gotJobOptions = false;
				MPlug cPlug = fnLight.findPlug( MString( "ribOptions" ), &status );
				if( status == MS::kSuccess ) {
					cPlug.getValue( iter->jobOptions );
					iter->gotJobOptions = true;
				}

				// philippe: this block is obsolete as we now get the resolution when building the job list
				//
				/* MPlug lightPlug = fnLight.findPlug( "dmapResolution" );
				float dmapSize;
				lightPlug.getValue( dmapSize );
				iter->height = iter->width = (int)dmapSize; */

				if( iter->hasShadowCam ) 
				{
					// scanScene: the light uses a shadow cam
					//
					MFnCamera fnCamera( iter->shadowCamPath );
					fnCamera.getPath(path);
					MTransformationMatrix xform( path.inclusiveMatrix() );

					// the camera is pointing toward negative Z
					double scale[] = { 1, 1, -1 };
					xform.setScale( scale, MSpace::kTransform );

					iter->camera[sample].mat         = xform.asMatrixInverse();
					iter->camera[sample].neardb      = fnCamera.nearClippingPlane();
					iter->camera[sample].fardb       = fnCamera.farClippingPlane();
					iter->camera[sample].isOrtho     = fnCamera.isOrtho();
					iter->camera[sample].orthoWidth  = fnCamera.orthoWidth();
					iter->camera[sample].orthoHeight = fnCamera.orthoWidth();
					iter->camera[sample].name        = fnCamera.fullPathName();
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

					if( iter->isPoint ) 
					{
						double ninty = M_PI/2;
						if( iter->pointDir == pPX ) { double rotation[] = { 0, -ninty, 0 }; xform.setRotation( rotation, MTransformationMatrix::kXYZ ); }
						if( iter->pointDir == pNX ) { double rotation[] = { 0, ninty, 0 }; xform.setRotation( rotation, MTransformationMatrix::kXYZ ); }
						if( iter->pointDir == pPY ) { double rotation[] = { ninty, 0, 0 }; xform.setRotation( rotation, MTransformationMatrix::kXYZ ); }
						if( iter->pointDir == pNY ) { double rotation[] = { -ninty, 0, 0 }; xform.setRotation( rotation, MTransformationMatrix::kXYZ ); }
						if( iter->pointDir == pPZ ) { double rotation[] = { 0, M_PI, 0 }; xform.setRotation( rotation, MTransformationMatrix::kXYZ ); }
						if( iter->pointDir == pNZ ) { double rotation[] = { 0, 0, 0 }; xform.setRotation( rotation, MTransformationMatrix::kXYZ ); }
					}
					iter->camera[sample].mat = xform.asMatrixInverse();

					MPlug shaderConnection( fnLight.findPlug( "liquidLightShaderNode", &status ) );
					if( status == MS::kSuccess && shaderConnection.isConnected() ) 
					{
						MPlugArray LightShaderPlugArray;
						shaderConnection.connectedTo( LightShaderPlugArray, true, true );
						MFnDependencyNode fnLightShaderNode( LightShaderPlugArray[0].node() );
						fnLightShaderNode.findPlug( "nearClipPlane" ).getValue( iter->camera[sample].neardb );
						fnLightShaderNode.findPlug( "farClipPlane" ).getValue( iter->camera[sample].fardb );
					} 
					else 
					{
						iter->camera[sample].neardb   = 0.001;    // TODO: these values are duplicated elsewhere in this file
						iter->camera[sample].fardb    = 250000.0; // TODO: these values are duplicated elsewhere in this file
						MPlug nearPlug = fnLight.findPlug( "nearClipPlane", &status );
						if( status == MS::kSuccess ) 
							nearPlug.getValue( iter->camera[sample].neardb );
						MPlug farPlug = fnLight.findPlug( "farClipPlane", &status );
						if( status == MS::kSuccess ) 
							farPlug.getValue( iter->camera[sample].fardb );
					}

					if( fnLight.dagPath().hasFn( MFn::kDirectionalLight ) ) 
					{
						iter->camera[sample].isOrtho = true;
						fnLight.findPlug( "dmapWidthFocus" ).getValue( iter->camera[sample].orthoWidth );
						fnLight.findPlug( "dmapWidthFocus" ).getValue( iter->camera[sample].orthoHeight );
					} 
					else 
					{
						iter->camera[sample].isOrtho = false;
						iter->camera[sample].orthoWidth = 0.0;
					}
				}

				if( iter->deepShadows )
				{
					iter->camera[sample].shutter = liqglo.liqglo_shutterTime;
					iter->camera[sample].motionBlur = true;
				}
				else
				{
					iter->camera[sample].shutter = 0;
					iter->camera[sample].motionBlur = false;
				}
				iter->camera[sample].focalLength = 0;
				iter->camera[sample].focalDistance = 0;
				iter->camera[sample].fStop = 0;
				iter->camera[sample].name  = fnLight.fullPathName();
				//doCameraMotion = 0;

				iter->aspectRatio = 1.0;

				// The camera's fov may not match the rendered image in Maya
				// if a film-fit is used. 'fov_ratio' is used to account for
				// this.
				//
				if( iter->hasShadowCam ) 
				{
					MFnCamera fnCamera( iter->shadowCamPath );
					float camFov = fnCamera.horizontalFieldOfView();
					iter->camera[sample].hFOV = camFov;
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
						iter->camera[sample].hFOV = angle;
					} 
					else 
						iter->camera[sample].hFOV = 95;
				}

				// Determine what information to write out ( depth map or deep shadow )
				//
				iter->imageMode.clear();
				if( iter->deepShadows )
				{
					iter->imageMode    += liqglo.liquidRenderer.dshImageMode;        //"deepopacity";
					iter->format        =  liqglo.liquidRenderer.dshDisplayName;    //"deepshad";
				}
				else
				{
					iter->imageMode += "z";
					iter->format = "shadow";
				}
			}
			++iter;
		}
		// post-frame script execution
		if( m_postFrameMel != "" ) 
		{
			MString postFrameMel( parseString( m_postFrameMel, false ) );
			if( fileExists( postFrameMel  ) ) 
				MGlobal::sourceFile( postFrameMel );
			else 
				if( MS::kSuccess == MGlobal::executeCommand( postFrameMel, false, false ) ) 
					printf("Liquid -> post-frame script executed successfully.\n");
				else 
					printf("Liquid -> ERROR :post-frame script failed.\n");
		}
		return MS::kSuccess;
	}
	return MS::kFailure;
}

/**
* This method takes care of the blocking together of objects and their children in the DAG.
* This method compares two DAG paths and figures out how many attribute levels to push and/or pop.
* The intention seems clear but this method is not currently used -- anyone cares to comment? --Moritz.
*/
void liqRibTranslator::doAttributeBlocking( const MDagPath& newPath, const MDagPath& previousPath )
{
	CM_TRACE_FUNC("liqRibTranslator::doAttributeBlocking("<<MFnDagNode(newPath).fullPathName()<<","<<previousPath.fullPathName()<<")");

	int newDepth = newPath.length();
	int prevDepth = 0;
	MFnDagNode dagFn( newPath );
	MDagPath npath = newPath;
	MDagPath ppath = previousPath;

	if( previousPath.isValid() ) 
	{
		// Recursive base case
		// If the paths are the same, then we don't have to write
		// any start/end attribute blocks.  So, just return
		//
		if( newPath == previousPath ) 
			return;
		prevDepth = previousPath.length();
		// End attribute block if necessary
		//
		if( newDepth <= prevDepth ) 
		{
			// Write an attribute block end
			//
			RiAttributeEnd();
			attributeDepth--;
			if( prevDepth > 1 ) 
				ppath.pop();
		}
	}
	if( ( newDepth >= prevDepth ) && ( newDepth > 1 ) )
		npath.pop();
	// Recurse and process parents
	//
	if( ( prevDepth > 1 ) || ( newDepth > 1 ) ) 
		doAttributeBlocking( npath, ppath ); // Recurse
	// Write open for new attribute block if necessary
	//
	if( newDepth >= prevDepth ) 
	{
		MString name( dagFn.name() );

		RiAttributeBegin();
		RiAttribute( "identifier", "name", &getLiquidRibName( name.asChar() ), RI_NULL );

		if( newPath.hasFn( MFn::kTransform ) ) 
		{
			// We have a transform, so write out the info
			//
			RtMatrix ribMatrix;
			MObject transform = newPath.node();
			MFnTransform transFn( transform );
			MTransformationMatrix localTransformMatrix = transFn.transformation();
			MMatrix localMatrix = localTransformMatrix.asMatrix();
			localMatrix.get( ribMatrix );
			RiConcatTransform( ribMatrix );
		}
		attributeDepth++;
	}
}

/**
* Write out the frame prologue.
* This includes all pass-dependant options like shading interpolation, hider,
* display driver and the camera transformation.
*/
MStatus liqRibTranslator::framePrologue( long lframe )
{
	CM_TRACE_FUNC("liqRibTranslator::framePrologue("<<lframe<<")");

	LIQDEBUGPRINTF( "-> Beginning Frame Prologue\n" );
	ribStatus = kRibFrame;

	if( !liqglo.m_exportReadArchive )
	{
		RiFrameBegin( lframe );

		if( !liqglo_currentJob.isShadow )
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
		}
		if( liqglo_currentJob.isShadow &&
			( !liqglo_currentJob.deepShadows ||
			liqglo_currentJob.shadowPixelSamples == 1 ) )
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
		if( liqglo_currentJob.isShadow && liqglo_currentJob.isMidPointShadow && !liqglo_currentJob.deepShadows )
		{
			RtString midPoint = "midpoint";
			RtFloat midRatio = liqglo_currentJob.midPointRatio;

			RiHider( "hidden", "depthfilter", &midPoint, RI_NULL );

			if ( liqglo_currentJob.midPointRatio != 0 )
				RiHider( "hidden", "midpointratio", &midRatio, RI_NULL ); // Output to rib jami
		}

		LIQDEBUGPRINTF( "-> Setting Display Options\n" );
		if( liqglo_currentJob.isShadow )
		{
			//MString relativeShadowName( liquidSanitizePath( liquidGetRelativePath( liqglo_relativeFileNames, liqglo_currentJob.imageName, liqglo_projectDir ) ) );
			if( !liqglo_currentJob.isMinMaxShadow )
			{
				if( liqglo_currentJob.deepShadows )
				{
					// RiDeclare( "volumeinterpretation", "string" );
					RtString viContinuous = "continuous";
					RtString viDiscrete   = "discrete";

					if( liqglo.liquidRenderer.renderName == MString("3Delight") )
					{
						liqRIBMsg("Display 1");
						RiDisplay( const_cast< char* >( liqglo_currentJob.imageName.asChar()),
							const_cast< char* >( liqglo_currentJob.format.asChar() ),
							(RtToken)liqglo_currentJob.imageMode.asChar(),
							"string volumeinterpretation",
							( liqglo_currentJob.shadowVolumeInterpretation == 1 ? &viContinuous : &viDiscrete ),
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

						MString deepFileImageName = "+" + liqglo_currentJob.imageName;

						liqRIBMsg("Display 3");
						RiDisplay( const_cast< char* >( deepFileImageName.asChar() ),
							const_cast< char* >( liqglo_currentJob.format.asChar() ),
							(RtToken)liqglo_currentJob.imageMode.asChar(),
							"string volumeinterpretation",
							( liqglo_currentJob.shadowVolumeInterpretation == 1 ? &viContinuous : &viDiscrete ),
							RI_NULL );
					}
				}
				else
				{
					liqRIBMsg("Display 4");
					RtInt aggregate( liqglo_currentJob.shadowAggregation );
					RiDisplay( const_cast< char* >( liqglo_currentJob.imageName.asChar() ),
						const_cast< char* >( liqglo_currentJob.format.asChar() ),
						(RtToken)liqglo_currentJob.imageMode.asChar(),
						"int aggregate", &aggregate,
						RI_NULL );
				}
			}
			else
			{
				liqRIBMsg("Display 5");
				RiArchiveRecord( RI_COMMENT, "Display Driver:" );
				RtInt minmax = 1;
				RiDisplay( const_cast< char* >( (liqglo_currentJob.imageName+(int)liqglo.liqglo_lframe).asChar() ),//const_cast< char* >( parseString(liqglo_currentJob.imageName).asChar() ),
					const_cast< char* >(liqglo_currentJob.format.asChar()),
					(RtToken)liqglo_currentJob.imageMode.asChar(),
					"minmax", &minmax,
					RI_NULL );
			}
		}
		else
		{
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
				}
			}
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
					RiArchiveRecord( RI_VERBATIM, "Display \"%s\" \"%s\" \"%s\" \"int merge\" [0] \"int mayaDisplayPort\" [%s] \"string host\" [\"%s\"]\n", const_cast< char* >( imageName.asChar() ), formatType.asChar(), imageMode.asChar(), port.asChar(), host.asChar() );

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
			}
		}

		LIQDEBUGPRINTF( "-> Setting Resolution\n" );
		// philippe : Rotated Camera Case
		if( liqglo_currentJob.isShadow == false && liqglo.liqglo_rotateCamera  == true ) 
			RiFormat( liqglo_currentJob.height, liqglo_currentJob.width, liqglo_currentJob.aspectRatio );
		else 
			RiFormat( liqglo_currentJob.width, liqglo_currentJob.height, liqglo_currentJob.aspectRatio );

		if( liqglo_currentJob.camera[0].isOrtho )
		{
			RtFloat frameWidth, frameHeight;
			// the whole frame width has to be scaled according to the UI Unit
			frameWidth  = liqglo_currentJob.camera[0].orthoWidth  * 0.5 ;
			frameHeight = liqglo_currentJob.camera[0].orthoHeight * 0.5 ;
			RiProjection( "orthographic", RI_NULL );

			// if we are describing a shadow map camera,
			// we need to set the screenwindow to the default,
			// as shadow maps are always square.
			if( liqglo_currentJob.isShadow == true )
				RiScreenWindow( -frameWidth, frameWidth, -frameHeight, frameHeight );
			else
				RiScreenWindow( -frameWidth, frameWidth, -frameHeight, frameHeight );
		} 
		else 
		{
			RtFloat fieldOfView = liqglo_currentJob.camera[0].hFOV * 180.0 / M_PI ;
			if( liqglo_currentJob.isShadow && liqglo_currentJob.isPoint ) 
				fieldOfView = liqglo_currentJob.camera[0].hFOV;

			RiProjection( "perspective", RI_FOV, &fieldOfView, RI_NULL );

			// if we are describing a shadow map camera,
			// we need to set the screenwindow to the default,
			// as shadow maps are always square.
			if( liqglo_currentJob.isShadow == false )
			{
				double ratio = (double)liqglo_currentJob.width / (double)liqglo_currentJob.height;
				double left, right, bottom, top;
				if( ratio <= 0 ) 
				{
					left    = -1 + liqglo_currentJob.camera[0].horizontalFilmOffset;
					right   =  1 + liqglo_currentJob.camera[0].horizontalFilmOffset;
					bottom  = -1 / ratio + liqglo_currentJob.camera[0].verticalFilmOffset;
					top     =  1 / ratio + liqglo_currentJob.camera[0].verticalFilmOffset;
				} 
				else 
				{
					left    = -ratio + liqglo_currentJob.camera[0].horizontalFilmOffset;
					right   =  ratio + liqglo_currentJob.camera[0].horizontalFilmOffset;
					bottom  = -1 + liqglo_currentJob.camera[0].verticalFilmOffset;
					top     =  1 + liqglo_currentJob.camera[0].verticalFilmOffset;
				}
				RiScreenWindow( left, right, bottom, top );
			} else 
				RiScreenWindow( -1.0, 1.0, -1.0, 1.0 );
		}

		RiClipping( liqglo_currentJob.camera[0].neardb, liqglo_currentJob.camera[0].fardb );
		if( liqglo.doDof && !liqglo_currentJob.isShadow ) 
			RiDepthOfField( liqglo_currentJob.camera[0].fStop, liqglo_currentJob.camera[0].focalLength, liqglo_currentJob.camera[0].focalDistance );

		// Set up for camera motion blur
		/* doCameraMotion = liqglo_currentJob.camera[0].motionBlur && liqglo_doMotion; */
		float frameOffset = 0;
		if( liqglo.doCameraMotion || liqglo.liqglo_doMotion || liqglo.liqglo_doDef ) 
		{
			switch( liqglo.shutterConfig ) 
			{
			case OPEN_ON_FRAME:
			default:
				if(liqglo.liqglo_relativeMotion)
					RiShutter( 0, liqglo_currentJob.camera[0].shutter );
				else
					RiShutter( lframe, lframe + liqglo_currentJob.camera[0].shutter );
				frameOffset = lframe;
				break;
			case CENTER_ON_FRAME:
				if(liqglo.liqglo_relativeMotion)
					RiShutter(  - ( liqglo_currentJob.camera[0].shutter * 0.5 ),  ( liqglo_currentJob.camera[0].shutter * 0.5 ) );
				else
					RiShutter( ( lframe - ( liqglo_currentJob.camera[0].shutter * 0.5 ) ), ( lframe + ( liqglo_currentJob.camera[0].shutter * 0.5 ) ) );
				frameOffset = lframe - ( liqglo_currentJob.camera[0].shutter * 0.5 );
				break;
			case CENTER_BETWEEN_FRAMES:
				if(liqglo.liqglo_relativeMotion)
					RiShutter( + ( 0.5 * ( 1 - liqglo_currentJob.camera[0].shutter ) ), + liqglo_currentJob.camera[0].shutter + ( 0.5 * ( 1 - liqglo_currentJob.camera[0].shutter ) ) );
				else
					RiShutter( lframe + ( 0.5 * ( 1 - liqglo_currentJob.camera[0].shutter ) ), lframe + liqglo_currentJob.camera[0].shutter + ( 0.5 * ( 1 -liqglo_currentJob.camera[0].shutter ) ) );
				frameOffset = lframe + ( 0.5 * ( 1 - liqglo_currentJob.camera[0].shutter ) );
				break;
			case CLOSE_ON_NEXT_FRAME:
				if(liqglo.liqglo_relativeMotion)
					RiShutter( + ( 1 - liqglo_currentJob.camera[0].shutter ),  1 );
				else
					RiShutter( lframe + ( 1 - liqglo_currentJob.camera[0].shutter ), lframe + 1 );
				frameOffset = lframe + ( 1 - liqglo_currentJob.camera[0].shutter );
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
		if( liqglo_currentJob.gotJobOptions ) 
			RiArchiveRecord( RI_COMMENT, "jobOptions: \n%s", liqglo_currentJob.jobOptions.asChar() );

		if( ( liqglo.liqglo_preRibBox.length() > 0 ) && !liqglo_currentJob.isShadow ) 
			for ( unsigned ii(0); ii < liqglo.liqglo_preRibBox.length(); ii++ ) 
				RiArchiveRecord( RI_COMMENT, "Additional Rib:\n%s", liqglo.liqglo_preRibBox[ii].asChar() );

		if( ( liqglo.liqglo_preReadArchive.length() > 0 ) && !liqglo_currentJob.isShadow ) 
			for ( unsigned ii(0); ii < liqglo.liqglo_preReadArchive.length(); ii++ ) 
				RiArchiveRecord( RI_COMMENT, "Read Archive Data: \nReadArchive \"%s\"", liqglo.liqglo_preReadArchive[ii].asChar() );

		if( ( liqglo.liqglo_preRibBoxShadow.length() > 0 ) && !liqglo_currentJob.isShadow ) 
			for ( unsigned ii(0); ii < liqglo.liqglo_preRibBoxShadow.length(); ii++ ) 
				RiArchiveRecord( RI_COMMENT, "Additional Rib:\n%s", liqglo.liqglo_preRibBoxShadow[ii].asChar() );

		if( ( liqglo.liqglo_preReadArchiveShadow.length() > 0 ) && liqglo_currentJob.isShadow ) 
			for ( unsigned ii(0); ii < liqglo.liqglo_preReadArchiveShadow.length(); ii++ ) 
				RiArchiveRecord( RI_COMMENT, "Read Archive Data: \nReadArchive \"%s\"", liqglo.liqglo_preReadArchiveShadow[ii].asChar() );

		// if we motion-blur the cam, open the motion block
		//
		if( liqglo.doCameraMotion && ( !liqglo_currentJob.isShadow || liqglo_currentJob.deepShadows) ) 
			if(liqglo.liqglo_relativeMotion)
				RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimesOffsets );
			else
				RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimes );

		// write the camera transform
		//
		RtMatrix cameraMatrix;
		liqglo_currentJob.camera[0].mat.get( cameraMatrix );
		RiTransform( cameraMatrix );

		// if we motion-blur the cam, write the subsequent motion samples and close the motion block
		//
		if( liqglo.doCameraMotion && ( !liqglo_currentJob.isShadow || liqglo_currentJob.deepShadows ) ) 
		{
			int mm = 1;
			while ( mm < liqglo.liqglo_motionSamples ) 
			{
				liqglo_currentJob.camera[mm].mat.get( cameraMatrix );
				RiTransform( cameraMatrix );
				++mm;
			}
			RiMotionEnd();
		}

	}
	return MS::kSuccess;
}

/**
* Write out the frame epilogue.
* This basically calls RiFrameEnd().
*/
MStatus liqRibTranslator::frameEpilogue( long )
{
	CM_TRACE_FUNC("liqRibTranslator::frameEpilogue()");

	if(ribStatus == kRibFrame) 
	{
		ribStatus = kRibBegin;
		if( !liqglo.m_exportReadArchive ) 
			RiFrameEnd();
	}
	return (ribStatus == kRibBegin ? MS::kSuccess : MS::kFailure);
}

/**
* Write out the body of the frame.
* This is a dump of the DAG to RIB with flattened transforms (MtoR-style).
*/
MStatus liqRibTranslator::objectBlock()
{
	CM_TRACE_FUNC("liqRibTranslator::objectBlock()");

	MStatus returnStatus = MS::kSuccess;
	MStatus status;
	attributeDepth = 0;

	LIQDEBUGPRINTF( "-> objectBlock\n" );

	if( m_ignoreSurfaces ) 
		RiSurface( "matte", RI_NULL );

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

	// retrieve the shadow set object
	MObject shadowSetObj;
	if( liqglo_currentJob.isShadow && liqglo_currentJob.shadowObjectSet != "" ) 
	{
		MObject tmp;
		tmp = getNodeByName( liqglo_currentJob.shadowObjectSet, &status );
		if( status == MS::kSuccess ) 
			shadowSetObj = tmp;
		else 
		{
			MString warn;
			warn += "Liquid : set " + liqglo_currentJob.shadowObjectSet + " in shadow " + liqglo_currentJob.name + " does not exist !";
			MGlobal:: displayWarning( warn );
			printf("%s\n", warn.asChar());
		}
		status.clear();
	}
	MFnSet shadowSet( shadowSetObj, &status );

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
		if( ( !liqglo_currentJob.isShadow ) && ( ribNode->object(0)->ignore ) ) 
			continue;
		if( ( liqglo_currentJob.isShadow ) && ( ribNode->object(0)->ignoreShadow ) ) 
			continue;
		// test against the set
		if( ( liqglo_currentJob.isShadow ) && ( liqglo_currentJob.shadowObjectSet != "" ) && ( !shadowSetObj.isNull() ) && ( !shadowSet.isMember( transform, &status ) ) ) 
		{
			//cout <<"SET FILTER : object "<<ribNode->name.asChar()<<" is NOT in "<<liqglo_currentJob.shadowObjectSet.asChar()<<endl;
			continue;
		}

		if( liqglo.m_outputComments ) 
			RiArchiveRecord( RI_COMMENT, "Name: %s", ribNode->name.asChar(), RI_NULL );

		RiAttributeBegin();
		RiAttribute( "identifier", "name", &getLiquidRibName( ribNode->name.asChar() ), RI_NULL );

		// Alf: preTransformMel
		MFnDagNode fnTransform( transform );
		MPlug prePostPlug = fnTransform.findPlug( "liqPreTransformMel" );
		m_preTransformMel = prePostPlug.asString();

		if( m_preTransformMel != "" )
			MGlobal::executeCommand( m_preTransformMel );

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
		if( !liqglo_currentJob.isShadow || liqglo_currentJob.deepShadows && m_outputLightsInDeepShadows && !m_ignoreLights )
		{
			MObjectArray linkLights;

			// light linking mode - Alf
			// inclusive - lights are off by default and objects list included lights
			// exclusive - lights are on by default and objects list ignored lights
			// liquid Light sets - ignores the maya light linker
			if( m_liquidSetLightLinking )
				ribNode->getSetLights( linkLights );
			else
				ribNode->getLinkLights( linkLights, liqglo.m_illuminateByDefault );

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
						if( liqglo.m_illuminateByDefault )
							RiIlluminate( ln->object(0)->lightHandle(), RI_FALSE );
						else
							RiIlluminate( ln->object(0)->lightHandle(), RI_TRUE );
					}
				}
			}
		}

		if( liqglo.liqglo_doMotion &&
			ribNode->motion.transformationBlur &&
			( ribNode->object( 1 ) ) &&
			//( ribNode->object(0)->type != MRT_Locator ) && // Why the fuck do we not allow motion blur for locators?
			( !liqglo_currentJob.isShadow || liqglo_currentJob.deepShadows ) )
		{
			LIQDEBUGPRINTF( "-> writing matrix motion blur data\n" );
			// Moritz: replaced RiMotionBegin call with ..V version to allow for more than five motion samples
			if(liqglo.liqglo_relativeMotion)
				RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimesOffsets );
			else
				RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimes );
		}
		RtMatrix ribMatrix;
		matrix = ribNode->object( 0 )->matrix( path.instanceNumber() );
		matrix.get( ribMatrix );

		if( liqglo.liqglo_relativeTransforms ) 
			RiConcatTransform( ribMatrix ); else RiTransform( ribMatrix );

		// Output the world matrices for the motionblur
		// This will override the current transformation setting
		if( liqglo.liqglo_doMotion &&
			ribNode->motion.transformationBlur &&
			( ribNode->object( 1 ) ) &&
			//( ribNode->object( 0 )->type != MRT_Locator ) && // Why the fuck do we not allow motion blur for locators?
			( !liqglo_currentJob.isShadow || liqglo_currentJob.deepShadows ) )
		{
			path = ribNode->path();
			RtMatrix ribMatrix;
			for( unsigned mm( 1 ); mm < liqglo.liqglo_motionSamples; mm++ ) {
				matrix = ribNode->object( mm )->matrix( path.instanceNumber() );
				matrix.get( ribMatrix );
				if( liqglo.liqglo_relativeTransforms ) RiConcatTransform( ribMatrix ); else RiTransform( ribMatrix );
			}
			RiMotionEnd();
		}

		// Alf: postTransformMel
		prePostPlug = fnTransform.findPlug( "liqPostTransformMel" );
		m_postTransformMel = prePostPlug.asString();
		if( m_postTransformMel != "" )
			MGlobal::executeCommand( m_postTransformMel );

		bool hasSurfaceShader( false );
		typedef enum {
			liqRegularShaderNode = 0,     // A regular Liquid node, keep it 0 to evaluate to false in conditions
			liqCustomPxShaderNode = 1,     // A custom MPxNode inheriting from liqCustomNode
			liqRibBoxShader = 2          // A rib box attached to the shader
		} liqDetailShaderKind;

		liqDetailShaderKind hasCustomSurfaceShader( liqRegularShaderNode );
		MString shaderRibBox( "" );
		bool hasDisplacementShader( false );
		bool hasVolumeShader( false );

		MPlug rmanShaderPlug;
		// Check for surface shader
		status.clear();
		MFnDagNode fnDagNode( path );
		rmanShaderPlug = fnDagNode.findPlug( MString( "liquidSurfaceShaderNode" ), &status );
		if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
		{ 
			status.clear(); 
			rmanShaderPlug = ribNode->assignedShadingGroup.findPlug( MString( "liquidSurfaceShaderNode" ), &status ); 
		}
		if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
		{ 
			status.clear(); 
			rmanShaderPlug = ribNode->assignedShader.findPlug( MString( "liquidSurfaceShaderNode" ), &status ); 
		}
		if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
		{ 
			status.clear(); 
			rmanShaderPlug = ribNode->assignedShadingGroup.findPlug( MString( "surfaceShader" ), &status ); 
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
					ribNode->assignedShader.setObject( rmShaderNodeObj );
					hasSurfaceShader = true;
				} 
				else 
				{ // Is it a custom shading node ?
					MPxNode *mpxNode = shaderDepNode.userNode();
					liqCustomNode *customNode = NULL;
					if( mpxNode && ( customNode = dynamic_cast<liqCustomNode*>(mpxNode) ) ) 
					{ // customNode will be null if can't be casted to a liqCustomNode
						ribNode->assignedShader.setObject( rmShaderNodeObj );
						hasSurfaceShader = true;
						hasCustomSurfaceShader = liqCustomPxShaderNode;
					} 
					else 
					{ // Try to find a liqRIBBox attribute
						MPlug ribbPlug = shaderDepNode.findPlug( MString( "liqRIBBox" ), &status );
						if( status == MS::kSuccess ) 
						{
							ribbPlug.getValue( shaderRibBox );
							if( shaderRibBox.substring(0,2) == "*H*" ) 
							{
								MString parseThis = shaderRibBox.substring(3, shaderRibBox.length() - 1 );
								shaderRibBox = parseThis;
							} 
							else if( shaderRibBox.substring(0,3) == "*SH*" ) 
							{
								MString parseThis = shaderRibBox.substring(3, shaderRibBox.length() - 1 );
								shaderRibBox = parseThis;
							}
							hasSurfaceShader = true;
							hasCustomSurfaceShader = liqRibBoxShader;
						}
						// else {
						//liquidMessage( "Do noy know how to handle " + string( shaderDepNode.typeName().asChar() ), messageError );
						//}
					}
				}
			}
		}
		// Check for displacement shader
		status.clear();
		rmanShaderPlug = fnDagNode.findPlug( MString( "liquidDispShaderNode" ), &status );
		if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
		{ 
			status.clear(); 
			rmanShaderPlug = ribNode->assignedShadingGroup.findPlug( MString( "liquidDispShaderNode" ), &status ); 
		}
		if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
		{ 
			status.clear(); 
			rmanShaderPlug = ribNode->assignedDisp.findPlug( MString( "liquidDispShaderNode" ), &status ); 
		}
		if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
		{ 
			status.clear(); 
			rmanShaderPlug = ribNode->assignedShadingGroup.findPlug( MString( "displacementShader" ), &status ); 
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
					ribNode->assignedDisp.setObject( rmShaderNodeObj );
					hasDisplacementShader = true;
				}
			}
		}
		// Check for volume shader
		status.clear();
		rmanShaderPlug = fnDagNode.findPlug( MString( "liquidVolumeShaderNode" ), &status );
		if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
		{ 
			status.clear(); 
			rmanShaderPlug = ribNode->assignedShadingGroup.findPlug( MString( "liquidVolumeShaderNode" ), &status ); 
		}
		if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
		{ 
			status.clear(); 
			rmanShaderPlug = ribNode->assignedVolume.findPlug( MString( "liquidVolumeShaderNode" ), &status ); 
		}
		if( ( status != MS::kSuccess ) || ( !rmanShaderPlug.isConnected() ) ) 
		{ 
			status.clear(); 
			rmanShaderPlug = ribNode->assignedShadingGroup.findPlug( MString( "volumeShader" ), &status ); 
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
					ribNode->assignedVolume.setObject( rmShaderNodeObj );
					hasVolumeShader = true;
				}
			}
		}
		// displacement bounds
		float surfaceDisplacementBounds = 0.0;
		MString surfaceDisplacementBoundsSpace = "shader";
		MString tmpSpace = "";
		status.clear();
		if( !ribNode->assignedShader.object().isNull() ) 
		{
			MPlug sDBPlug = ribNode->assignedShader.findPlug( MString( "displacementBound" ), &status );
			if( status == MS::kSuccess ) 
				sDBPlug.getValue( surfaceDisplacementBounds );
			MPlug sDBSPlug = ribNode->assignedShader.findPlug( MString( "displacementBoundSpace" ), &status );
			if( status == MS::kSuccess ) 
				sDBSPlug.getValue( tmpSpace );
			if( tmpSpace != "" ) 
				surfaceDisplacementBoundsSpace = tmpSpace;
		}
		float dispDisplacementBounds = 0.0;
		MString dispDisplacementBoundsSpace = "shader";
		tmpSpace = "";
		status.clear();
		if( !ribNode->assignedDisp.object().isNull() ) 
		{
			MPlug dDBPlug = ribNode->assignedDisp.findPlug( MString( "displacementBound" ), &status );
			if( status == MS::kSuccess ) 
				dDBPlug.getValue( dispDisplacementBounds );
			MPlug sDBSPlug = ribNode->assignedDisp.findPlug( MString( "displacementBoundSpace" ), &status );
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
		LIQDEBUGPRINTF( "-> writing node attributes\n" );
		// if the node's shading rate == -1,
		// it means it hasn't been overriden by a liqShadingRate attribute.
		// No need to output it then.
		if( ribNode->shading.shadingRate > 0 )
			RiShadingRate ( ribNode->shading.shadingRate );
		if( !liqglo_currentJob.isShadow ) 
		{
			RtInt off( 0 );
			RtInt on( 1 );
			if( !ribNode->shading.diceRasterOrient ) 
				RiAttribute( "dice", (RtToken) "rasterorient", &off, RI_NULL );
			if( ribNode->shading.doubleShaded ) 
				RiAttribute( "sides", (RtToken) "doubleshaded", &on, RI_NULL );
			if( liqglo.liquidRenderer.supports_RAYTRACE ) 
			{
				if( ribNode->trace.sampleMotion ) 
					RiAttribute( "trace", (RtToken) "samplemotion", &on, RI_NULL );
				if( ribNode->trace.displacements ) 
					RiAttribute( "trace", (RtToken) "displacements", &on, RI_NULL );
				if( ribNode->trace.bias != 0.01f ) 
				{
					RtFloat bias( ribNode->trace.bias );
					RiAttribute( "trace", (RtToken) "bias", &bias, RI_NULL );
				}
				if( ribNode->trace.maxDiffuseDepth != 1 ) 
				{
					RtInt mddepth( ribNode->trace.maxDiffuseDepth );
					RiAttribute( "trace", (RtToken) "maxdiffusedepth", &mddepth, RI_NULL );
				}
				if( ribNode->trace.maxSpecularDepth != 2 ) 
				{
					RtInt msdepth( ribNode->trace.maxSpecularDepth );
					RiAttribute( "trace", (RtToken) "maxspeculardepth", &msdepth, RI_NULL );
				}
			}
			if( !ribNode->visibility.camera ) 
				RiAttribute( "visibility", (RtToken) "camera", &off, RI_NULL );

			// old-style raytracing visibility support
			// philippe: if raytracing is off in the globals, trace visibility is turned off for all objects, transmission is set to TRANSPARENT for all objects
			if( liqglo.liquidRenderer.supports_RAYTRACE && !liqglo.liquidRenderer.supports_ADVANCED_VISIBILITY ) 
			{
				if( liqglo.rt_useRayTracing && ribNode->visibility.trace ) {
					RtInt on( 1 );
					RiAttribute( "visibility", (RtToken) "trace", &on, RI_NULL );
				}
				if( liqglo.rt_useRayTracing && ribNode->visibility.transmission != liqRibNode::visibility::TRANSMISSION_TRANSPARENT ) 
				{
					RtString trans;
					switch( ribNode->visibility.transmission ) 
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
				if( liqglo.rt_useRayTracing && ribNode->visibility.diffuse ) 
					RiAttribute( "visibility", (RtToken) "int diffuse", &on, RI_NULL );

				if( liqglo.rt_useRayTracing && ribNode->visibility.specular ) 
					RiAttribute( "visibility", (RtToken) "int specular", &on, RI_NULL );

				if( liqglo.rt_useRayTracing && ribNode->visibility.newtransmission ) 
					RiAttribute( "visibility", (RtToken) "int transmission", &on, RI_NULL );

				if( liqglo.rt_useRayTracing && ribNode->visibility.camera ) 
					RiAttribute( "visibility", (RtToken) "int camera", &on, RI_NULL );

				if( liqglo.rt_useRayTracing && ribNode->visibility.photon ) 
					RiAttribute( "visibility", (RtToken) "int photon", &on, RI_NULL );

				if( liqglo.rt_useRayTracing && ribNode->visibility.midpoint ) 
					RiAttribute( "visibility", (RtToken) "int midpoint", &on, RI_NULL );

				if( liqglo.rt_useRayTracing && ribNode->hitmode.diffuse != liqRibNode::hitmode::DIFFUSE_HITMODE_PRIMITIVE ) 
				{
					switch( ribNode->hitmode.diffuse ) 
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

				if( liqglo.rt_useRayTracing && ribNode->hitmode.specular != liqRibNode::hitmode::SPECULAR_HITMODE_SHADER ) 
				{
					switch( ribNode->hitmode.specular ) 
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

				if( liqglo.rt_useRayTracing && ribNode->hitmode.transmission != liqRibNode::hitmode::TRANSMISSION_HITMODE_SHADER ) 
				{
					switch( ribNode->hitmode.transmission ) 
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

				if( ribNode->hitmode.camera != liqRibNode::hitmode::CAMERA_HITMODE_SHADER ) 
				{
					switch( ribNode->hitmode.camera ) 
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
				if( ribNode->irradiance.shadingRate != 1.0f ) 
				{
					RtFloat rate = ribNode->irradiance.shadingRate;
					RiAttribute( "irradiance", (RtToken) "shadingrate", &rate, RI_NULL );
				}

				if( ribNode->irradiance.nSamples != 64 ) 
				{
					RtInt samples = ribNode->irradiance.nSamples;
					RiAttribute( "irradiance", (RtToken) "nsamples", &samples, RI_NULL );
				}

				if( ribNode->irradiance.maxError != 0.5f ) 
				{
					RtFloat merror = ribNode->irradiance.maxError;
					RiAttribute( "irradiance", (RtToken) "float maxerror", &merror, RI_NULL );
				}

				if( ribNode->irradiance.maxPixelDist != 30.0f ) 
				{
					RtFloat mpd = ribNode->irradiance.maxPixelDist;
					RiAttribute( "irradiance", (RtToken) "float maxpixeldist", &mpd, RI_NULL );
				}

				if( ribNode->irradiance.handle != "" ) 
				{
					RtString handle = const_cast< char* >( ribNode->irradiance.handle.asChar() );
					RiAttribute( "irradiance", (RtToken) "handle", &handle, RI_NULL );
				}

				if( ribNode->irradiance.fileMode != liqRibNode::irradiance::FILEMODE_NONE ) 
				{
					RtString mode;
					switch( ribNode->irradiance.fileMode ) 
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

				if( ribNode->photon.globalMap != "" ) 
				{
					RtString map = const_cast< char* >( ribNode->photon.globalMap.asChar() );
					RiAttribute( "photon", (RtToken) "globalmap", &map, RI_NULL );
				}

				if( ribNode->photon.causticMap != "" ) 
				{
					RtString map = const_cast< char* >( ribNode->photon.causticMap.asChar() );
					RiAttribute( "photon", (RtToken) "causticmap", &map, RI_NULL );
				}

				if( ribNode->photon.shadingModel != liqRibNode::photon::SHADINGMODEL_MATTE ) 
				{
					RtString model;
					switch( ribNode->photon.shadingModel  ) {
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

				if( ribNode->photon.estimator != 100 ) 
				{
					RtInt estimator = ribNode->photon.estimator;
					RiAttribute( "photon", (RtToken) "estimator", &estimator, RI_NULL );
				}

			}

			// 3Delight sss group
			if( ribNode->delightSSS.doScatter && liqglo.liquidRenderer.renderName == MString("3Delight") )
			{
#ifdef GENERIC_RIBLIB         
				useAdvancedVisibilityAttributes = true;
#endif			  
				RtString groupName = const_cast< char* >( ribNode->delightSSS.groupName.asChar() );
				RiAttribute( "visibility", (RtToken) "string subsurface", &groupName, RI_NULL );

				RtColor scattering, absorption;
				scattering[0] = ribNode->delightSSS.scattering.r;
				scattering[1] = ribNode->delightSSS.scattering.g;
				scattering[2] = ribNode->delightSSS.scattering.b;

				absorption[0] = ribNode->delightSSS.absorption.r;
				absorption[1] = ribNode->delightSSS.absorption.g;
				absorption[2] = ribNode->delightSSS.absorption.b;

				if ( scattering[0] && scattering[1] && scattering[2] )
					RiAttribute( "subsurface",
					(RtToken) "scattering", &scattering,
					(RtToken) "absorption", &absorption,
					RI_NULL );

				RtFloat refractionindex = ribNode->delightSSS.refraction;
				RtFloat shadingrate = ribNode->delightSSS.shadingRate;
				RtFloat scale = ribNode->delightSSS.scale;

				RiAttribute( "subsurface",
					(RtToken) "refractionindex", &refractionindex,
					(RtToken) "shadingrate", &shadingrate,
					(RtToken) "scale", &scale, 
					RI_NULL );

				RtColor meanfreepath, reflectance;
				meanfreepath[0] = ribNode->delightSSS.meanfreepath.r;
				meanfreepath[1] = ribNode->delightSSS.meanfreepath.g;
				meanfreepath[2] = ribNode->delightSSS.meanfreepath.b;

				reflectance[0] = ribNode->delightSSS.reflectance.r;
				reflectance[1] = ribNode->delightSSS.reflectance.g;
				reflectance[2] = ribNode->delightSSS.reflectance.b;

				if ( reflectance[0] && reflectance[1] && reflectance[2] )
					RiAttribute( "subsurface",
					(RtToken) "meanfreepath", &meanfreepath,
					(RtToken) "reflectance", &reflectance, 
					RI_NULL );

				if ( ribNode->delightSSS.referencecamera != "" )
				{
					RtString referenceCamera = const_cast< char* >( ribNode->delightSSS.referencecamera.asChar() );
					RiAttribute( "subsurface", (RtToken) "string referencecamera", &referenceCamera, RI_NULL );
				}
			}

			//strategy
			{
				if(ribNode->strategy.strategy_!="grids"){
					RtString strategy = const_cast<char*>(ribNode->strategy.strategy_.asChar());
					RiAttribute("shade",(RtToken)"string strategy", &strategy, RI_NULL);
				}

				if(ribNode->strategy.volumeIntersectionStrategy!="exclusive"){
					RtString volumeIntersectionStrategy = const_cast<char*>(ribNode->strategy.volumeIntersectionStrategy.asChar());
					RiAttribute("shade",(RtToken)"string volumeintersectionstrategy", &volumeIntersectionStrategy, RI_NULL);
				}

				if(ribNode->strategy.volumeIntersectionPriority >0.0001){
					RtFloat volumeIntersectionPriority = ribNode->strategy.volumeIntersectionPriority;
					RiAttribute("shade",(RtToken)"float volumeintersectionpriority", &volumeIntersectionPriority, RI_NULL);
				}
			}

			//trim curve 
			{
				RtString sense = "inside";

				switch(ribNode->trimcurve.sense){
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
				if( ribNode->stitch.enable != true ){
					RtInt enable = (ribNode->stitch.enable)? 1: 0;
					RiAttribute("stitch",(RtToken)"int enable", &enable, RI_NULL);	
				}
				if( ribNode->stitch.traceenable != false ){
					RtInt traceenable = (ribNode->stitch.traceenable)? 1: 0;
					RiAttribute("stitch",(RtToken)"int traceenable", &traceenable, RI_NULL);	
				}
				if( ribNode->stitch.newgroup != false ){
					RtInt newgroup = (ribNode->stitch.newgroup)? 1: 0;
					RiAttribute("stitch",(RtToken)"int newgroup", &newgroup, RI_NULL);	
				}	
			}//stitch

			//stochastic
			{
				if( ribNode->stochastic.sigma != 0 ){
					RtInt sigma = ribNode->stochastic.sigma;
					RiAttribute("stochastic",(RtToken)"int sigma", &sigma, RI_NULL);	
				}
				if( ribNode->stochastic.pointfalloff != 0 ){
					RtInt pointfalloff = ribNode->stochastic.pointfalloff;
					RiAttribute("stochastic",(RtToken)"int pointfalloff", &pointfalloff, RI_NULL);	
				}
			}//stochastic

			//dice
			{
				if( ribNode->dice.binary != 0 ){
					RtInt binary = ribNode->dice.binary;
					RiAttribute("dice",(RtToken)"int binary", &binary, RI_NULL);
				}
				if( ribNode->dice.hair != 0 ){
					RtInt hair = ribNode->dice.hair;
					RiAttribute("dice",(RtToken)"int hair", &hair, RI_NULL);
				}
				//strategy
				RtString strategy = "planarprojection";
				switch(ribNode->dice.strategy){
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
				switch(ribNode->dice.referencecamera){
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
				if( ribNode->derivatives.centered != 1 ){
					RtInt centered = ribNode->derivatives.centered;
					RiAttribute("derivatives",(RtToken)"int centered", &centered, RI_NULL);
				}
				if( ribNode->derivatives.extrapolate != 1 ){
					RtInt extrapolate = ribNode->derivatives.extrapolate;
					RiAttribute("derivatives",(RtToken)"int extrapolate", &extrapolate, RI_NULL);
				}
			}//derivatives

			//procedural
			{
				if( ribNode->procedural.attribute.length()>0 ){
					RtString attribute = const_cast<char*>(ribNode->procedural.attribute.asChar());
					RiAttribute("procedural",(RtToken)"string attribute", &attribute, RI_NULL);
				}
			}//procedural

			if( ribNode->motion.deformationBlur || ribNode->motion.transformationBlur && ribNode->motion.factor != 1.0f ) 
				RiGeometricApproximation( "motionfactor", ribNode->motion.factor );

			ribNode->writeUserAttributes();
		}

		bool writeShaders( true );

		if( liqglo_currentJob.isShadow &&
			( ( !liqglo_currentJob.deepShadows && !m_outputShadersInShadows ) || ( liqglo_currentJob.deepShadows && !m_outputShadersInDeepShadows ) )
			)
			writeShaders = false;
		
		liqRIBMsg("[6] writeShaders=%d=%d && ((!%d&&!%d)||(%d&&!%d) ", writeShaders, 
			liqglo_currentJob.isShadow, 
			liqglo_currentJob.deepShadows, m_outputShadersInShadows, liqglo_currentJob.deepShadows, m_outputShadersInDeepShadows );
		if( writeShaders ) 
		{
			liqRIBMsg("[5] hasVolumeShader=%d, m_ignoreVolumes=%d", hasVolumeShader, m_ignoreVolumes );
			if( hasVolumeShader && !m_ignoreVolumes ) 
			{
				//liqShader& currentShader( liqGetShader( ribNode->assignedVolume.object() ) );
				liqShader& currentShader = liqShaderFactory::instance().getShader( ribNode->assignedVolume.object() );
				liqRIBMsg("[1] liqglo_currentJob.isShadow=%d, currentShader.outputInShadow=%d", liqglo_currentJob.isShadow, currentShader.outputInShadow );
				// per shader shadow pass override
				if( !liqglo_currentJob.isShadow || currentShader.outputInShadow )
				{
					currentShader.write( );
				}
			}
			if( hasSurfaceShader && !m_ignoreSurfaces )
			{
				if( hasCustomSurfaceShader )
				{
					if( hasCustomSurfaceShader == liqCustomPxShaderNode )
					{  // Just call the write method of the custom shader
						MFnDependencyNode customShaderDepNode( ribNode->assignedShader.object() );
						MPxNode *mpxNode = customShaderDepNode.userNode();
						liqCustomNode *customNode( NULL );
						if( mpxNode && ( customNode = dynamic_cast<liqCustomNode*>( mpxNode ) ) )
							customNode->liquidWrite();
						else
							;// Should never happen in theory ... but what is the way to report a problem ???
					}
					else//hasCustomSurfaceShader==liqRibBoxShader
					{ 
						// Default : just write the contents of the rib box
						RiArchiveRecord( RI_VERBATIM, ( char* )shaderRibBox.asChar() );
						RiArchiveRecord( RI_VERBATIM, "\n" );
					}
				}
				else//hasCustomSurfaceShader==liqRegularShaderNode
				{
					//liqShader& currentShader( liqGetShader( ribNode->assignedShader.object() ) );
					liqShader& currentShader = liqShaderFactory::instance().getShader( ribNode->assignedShader.object() );

					// Output color overrides or color
					if(ribNode->shading.color.r != -1.0)
					{
						RtColor rColor;
						rColor[0] = ribNode->shading.color[0];
						rColor[1] = ribNode->shading.color[1];
						rColor[2] = ribNode->shading.color[2];
						RiColor( rColor );
					}
					else
						RiColor( currentShader.rmColor );

					if(ribNode->shading.opacity.r != -1.0)
					{
						RtColor rOpacity;
						rOpacity[0] = ribNode->shading.opacity[0];
						rOpacity[1] = ribNode->shading.opacity[1];
						rOpacity[2] = ribNode->shading.opacity[2];
						RiOpacity( rOpacity );
					}
					else
						RiOpacity( currentShader.rmOpacity );
					liqRIBMsg("[2] liqglo_currentJob.isShadow=%d, currentShader.outputInShadow=%d", liqglo_currentJob.isShadow, currentShader.outputInShadow );
					// per shader shadow pass override
					if( !liqglo_currentJob.isShadow || currentShader.outputInShadow )
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
			} 
			else //if( hasSurfaceShader && !m_ignoreSurfaces )
			{
				RtColor rColor,rOpacity;
				if( m_shaderDebug ) 
				{
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
				} 
				else 
				{
					if(ribNode->shading.color.r != -1.0) 
					{
						rColor[0] = ribNode->shading.color[0];
						rColor[1] = ribNode->shading.color[1];
						rColor[2] = ribNode->shading.color[2];
						RiColor( rColor );
					} 
					else if( ( ribNode->color.r != -1.0 ) ) 
					{
						rColor[0] = ribNode->color[0];
						rColor[1] = ribNode->color[1];
						rColor[2] = ribNode->color[2];
						RiColor( rColor );
					}
					if(ribNode->shading.opacity.r != -1.0) 
					{
						rOpacity[0] = ribNode->shading.opacity[0];
						rOpacity[1] = ribNode->shading.opacity[1];
						rOpacity[2] = ribNode->shading.opacity[2];
						RiOpacity( rOpacity );
					} 
					else if( ( ribNode->opacity.r != -1.0 ) ) 
					{
						rOpacity[0] = ribNode->opacity[0];
						rOpacity[1] = ribNode->opacity[1];
						rOpacity[2] = ribNode->opacity[2];
						RiOpacity( rOpacity );
					}
				}

				if( !m_ignoreSurfaces ) 
				{
					MObject shadingGroup = ribNode->assignedShadingGroup.object();
					MObject shader = ribNode->findShader( shadingGroup );
					//
					// here we check for regular shader nodes first
					// and assign default shader to shader-less nodes.
					//
					if( m_shaderDebug ) {
						liqRIBMsg("shader debug is turned on, so the surface is constant.");
						RiSurface( "constant", RI_NULL );
						LIQDEBUGPRINTF("add more constant parameters here. take /RMS-1.0.1-Maya2008/lib/shaders/src/mtorBlinn.sl as an example.(?)");
					}
// 					else if( shader.apiType() == MFn::kLambert ){ 
// 						RiSurface( "matte", RI_NULL );
// 						LIQDEBUGPRINTF("add more lambert parameters here. take //RMS-1.0.1-Maya2008/lib/shaders/src/mtorLambert.sl as an example.");
// 					}else if( shader.apiType() == MFn::kPhong ) {
// 						RiSurface( "plastic", RI_NULL );
// 						LIQDEBUGPRINTF("add more phong parameters here. take /RMS-1.0.1-Maya2008/lib/shaders/src/mtorPhong.sl as an example.");
// 					}
					else if( path.hasFn( MFn::kPfxHair ) ) 
					{
						// get some of the hair system parameters
						RtFloat translucence = 0, specularPower = 0;
						RtColor specularColor;
						//cout <<"getting pfxHair shading params..."<<endl;
						MObject hairSystemObj;
						MFnDependencyNode pfxHairNode( path.node() );
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
						RiSurface(  "liquidpfxhair",
							"float specularpower", &specularPower,
							"float translucence",  &translucence,
							"color specularcolor", &specularColor,
							RI_NULL );
					} 
					else if( path.hasFn( MFn::kPfxToon ) ) {
						RiSurface( "liquidpfxtoon", RI_NULL );
					}else if( path.hasFn( MFn::kPfxGeometry ) ){
						RiSurface( "liquidpfx", RI_NULL );
					}else {
						//RiSurface( "plastic", RI_NULL );
						MFnDependencyNode shaderFn(shader);
						RiSurface( const_cast<char*>(shaderFn.name().asChar()), RI_NULL );
					}
				}
			}//if( hasSurfaceShader && !m_ignoreSurfaces )else
		} //if( writeShaders ) 
		else if( liqglo_currentJob.deepShadows ) 
		{
			liqRIBMsg("[7] liqglo_currentJob[.deepShadows=%d, .isShadow=%d ], hasSurfaceShader=%d, hasCustomSurfaceShader=%d",
				liqglo_currentJob.deepShadows, liqglo_currentJob.isShadow, hasSurfaceShader, hasCustomSurfaceShader );

			// if the current job is a deep shadow,
			// we still want to output primitive color and opacity and surface shader
			// In case of custom shaders, what should we do ? Stephane.
			if( hasSurfaceShader && ! hasCustomSurfaceShader ) 
			{
				//liqShader & currentShader = liqGetShader( ribNode->assignedShader.object());
				liqShader &currentShader = liqShaderFactory::instance().getShader( ribNode->assignedShader.object() );

				// Output color overrides or color
				if(ribNode->shading.color.r != -1.0) 
				{
					RtColor rColor;
					rColor[0] = ribNode->shading.color[0];
					rColor[1] = ribNode->shading.color[1];
					rColor[2] = ribNode->shading.color[2];
					RiColor( rColor );
				} 
				else 
					RiColor( currentShader.rmColor );

				if(ribNode->shading.opacity.r != -1.0) 
				{
					RtColor rOpacity;
					rOpacity[0] = ribNode->shading.opacity[0];
					rOpacity[1] = ribNode->shading.opacity[1];
					rOpacity[2] = ribNode->shading.opacity[2];
					RiOpacity( rOpacity );
				} 
				else 
					RiOpacity( currentShader.rmOpacity );
				
				liqRIBMsg("[8] currentShader[.name=%s, .filename=%s, .outputInShadow=%d]", currentShader.getName().c_str(), currentShader.getShaderFileName().c_str(), currentShader.outputInShadow );
				if(currentShader.outputInShadow){
					currentShader.write();
				}

			} 
			else 
			{
				RtColor rColor,rOpacity;

				if(ribNode->shading.color.r != -1.0) 
				{
					rColor[0] = ribNode->shading.color[0];
					rColor[1] = ribNode->shading.color[1];
					rColor[2] = ribNode->shading.color[2];
					RiColor( rColor );
				} 
				else if( ( ribNode->color.r != -1.0 ) ) 
				{
					rColor[0] = ribNode->color[0];
					rColor[1] = ribNode->color[1];
					rColor[2] = ribNode->color[2];
					RiColor( rColor );
				}
				if(ribNode->shading.opacity.r != -1.0) 
				{
					rOpacity[0] = ribNode->shading.opacity[0];
					rOpacity[1] = ribNode->shading.opacity[1];
					rOpacity[2] = ribNode->shading.opacity[2];
					RiOpacity( rOpacity );
				} 
				else if( ( ribNode->opacity.r != -1.0 ) ) 
				{
					rOpacity[0] = ribNode->opacity[0];
					rOpacity[1] = ribNode->opacity[1];
					rOpacity[2] = ribNode->opacity[2];
					RiOpacity( rOpacity );
				}
				if( path.hasFn( MFn::kPfxHair ) ) 
				{
					// get some of the hair system parameters
					float translucence = 0, specularPower = 0;
					float specularColor[3];
					//cout <<"getting pfxHair shading params..."<<endl;
					MObject hairSystemObj;
					MFnDependencyNode pfxHairNode( path.node() );
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
							//cout <<"specularColor = "<<specularColor<<endl;
						}
						status.clear();
						paramPlug = hairSystemNode.findPlug( "specularPower", &status );
						if( status == MS::kSuccess ) 
							paramPlug.getValue( specularPower );
					}
					RiSurface(  "liquidPfxHair",
						"float specularPower", &specularPower,
						"float translucence",  &translucence,
						"color specularColor", &specularColor,
						RI_NULL );
				}
			}
		} 
		else 
			RiSurface( "null", RI_NULL );

		liqRIBMsg("[4] hasDisplacementShader=%d, m_ignoreDisplacements=%d", hasDisplacementShader, m_ignoreDisplacements );
		if( hasDisplacementShader && !m_ignoreDisplacements ) 
		{
			//liqShader & currentShader = liqGetShader( ribNode->assignedDisp.object() );
			liqShader &currentShader = liqShaderFactory::instance().getShader( ribNode->assignedDisp.object() );
			
			liqRIBMsg("[3] liqglo_currentJob.isShadow=%d, currentShader.outputInShadow=%d", liqglo_currentJob.isShadow, currentShader.outputInShadow );
			// per shader shadow pass override
			if( !liqglo_currentJob.isShadow || currentShader.outputInShadow )
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
		// Alf: preShapeMel
		prePostPlug = fnTransform.findPlug( "liqPreShapeMel" );
		m_preShapeMel = prePostPlug.asString();
		if( m_preShapeMel != "" )
			MGlobal::executeCommand( m_preShapeMel );

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

			bool doMotion ( liqglo.liqglo_doDef && ribNode->motion.deformationBlur &&
				( ribNode->object(1) ) &&
				( ribNode->object(0)->type != MRT_RibGen ) &&
				//( ribNode->object(0)->type != MRT_Locator ) &&
				( !liqglo_currentJob.isShadow || liqglo_currentJob.deepShadows ) );

			if( doMotion )
			{
				// For each grain, open a new motion block...
				for( unsigned i( 0 ); i < ribNode->object( 0 )->granularity(); i++ ) //granularity() is always 1.
				{
					if( ribNode->object( 0 )->isNextObjectGrainAnimated() ) //isNextObjectGrainAnimated() is always true.
					{
						if(liqglo.liqglo_relativeMotion)
							RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimesOffsets );
						else
							RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimes );

						for ( unsigned msampleOn( 0 ); msampleOn < liqglo.liqglo_motionSamples; msampleOn++ ){ 
							MString geometryRibFile( liquidGetRelativePath( false, getLiquidRibName( ribNode->name.asChar() ), liqglo.liqglo_ribDir ) +"."+(int)liqglo.liqglo_lframe+".m"+(int)msampleOn+".rib" );
							ribNode->object( msampleOn )->writeObject(geometryRibFile, liqglo_currentJob, false);
						}

						RiMotionEnd();
					} 
					else {
						RiArchiveRecord( RI_COMMENT, "the the next object grain is not animated" );

						MString geometryRibFile( liquidGetRelativePath( false, getLiquidRibName( ribNode->name.asChar() ), liqglo.liqglo_ribDir ) +"."+(int)liqglo.liqglo_lframe+".rib" );
						ribNode->object( 0 )->writeObject(geometryRibFile, liqglo_currentJob, false);
					}
				}
			} 
			else {
				if(    ribNode->rib.hasGenerator()
					|| ribNode->rib.hasReadArchive()  
					|| ribNode->rib.hasDelayedReadArchive() 
					)
				{
					//if ribNode is tagged as readArchive or delayedReadArchive, we do not output its geometry data.
					//return;
				}else{
					//ribNode->object( 0 )->writeObject();
					_writeObject(ribNode, liqglo_currentJob, false, 0);
				}

			}

			// Alf: postShapeMel
			prePostPlug = fnTransform.findPlug( "liqPostShapeMel" );
			m_postShapeMel = prePostPlug.asString();
			if( m_postShapeMel != "" )
				MGlobal::executeCommand( m_postShapeMel );

		} // else RiArchiveRecord( RI_COMMENT, " Shapes Ignored !!" );
		RiAttributeEnd();
	}
	while ( attributeDepth > 0 ) 
	{
		RiAttributeEnd();
		attributeDepth--;
	}
	return returnStatus;
}

/**
* Write the world prologue.
* This includes the pre- and post-world begin RIB boxes and the definition of
* any default coordinate systems.
*/
MStatus liqRibTranslator::worldPrologue()
{
	CM_TRACE_FUNC("liqRibTranslator::worldPrologue()");

	MStatus returnStatus = MS::kSuccess;
	LIQDEBUGPRINTF( "-> Writing world prologue.\n" );
	// if this is a readArchive that we are exporting then ingore this header information
	if( !liqglo.m_exportReadArchive )
	{
		MFnDependencyNode globalsNode( liqglo.rGlobalObj );
		MPlug prePostplug( globalsNode.findPlug( "preWorldMel" ) );
		MString melcommand( prePostplug.asString() );
		// put in pre-worldbegin statements
		if(liqglo.m_preWorldRIB != "" || melcommand.length() )
		{
			RiArchiveRecord(RI_COMMENT,  " Pre-WorldBegin RIB from liquid globals");
			MGlobal::executeCommand( melcommand );
			RiArchiveRecord(RI_VERBATIM, ( char* )liqglo.m_preWorldRIB.asChar());
			RiArchiveRecord(RI_VERBATIM, "\n");
		}
		// output the arbitrary clipping planes here /////////////
		//
		{
			for ( RNMAP::iterator rniter( htable->RibNodeMap.begin() ); rniter != htable->RibNodeMap.end(); rniter++ ) 
			{
				LIQ_CHECK_CANCEL_REQUEST;
				liqRibNodePtr   ribNode = (*rniter).second;
				if( ribNode->object(0)->ignore || ribNode->object(0)->type != MRT_ClipPlane ) 
					continue;
				RiTransformBegin();
				if( liqglo.m_outputComments )
					RiArchiveRecord( RI_COMMENT, "Clipping Plane: %s", ribNode->name.asChar(), RI_NULL );
				RtMatrix ribMatrix;
				MMatrix matrix;
				MDagPath path;

				matrix = ribNode->object(0)->matrix( path.instanceNumber() );
				matrix.get( ribMatrix );
				RiConcatTransform( ribMatrix );

				ribNode->object(0)->writeObject("", liqglo_currentJob, false);
				ribNode->object(0)->written = 1;

				RiTransformEnd();
			}
		}
		RiWorldBegin();
		// set attributes from the globals
		if( liqglo.rt_useRayTracing )
		{
			RiArchiveRecord(RI_COMMENT,  " Ray-Tracing Attributes from liquid globals");
			RtInt on( 1 );
			RiAttribute("visibility", "int trace", &on, RI_NULL );
			if( liqglo.rt_traceDisplacements )
				RiAttribute("trace", "int displacements", &on, RI_NULL );
			if( liqglo.rt_traceSampleMotion )
				RiAttribute("trace", "int samplemotion", &on, RI_NULL );
			if( liqglo.rt_traceBias != 0 )
				RiAttribute("trace", "float bias", &liqglo.rt_traceBias, RI_NULL );
			RiAttribute("trace", "int maxdiffusedepth", &liqglo.rt_traceMaxDiffuseDepth, RI_NULL);
			RiAttribute("trace", "int maxspeculardepth", &liqglo.rt_traceMaxSpecularDepth, RI_NULL);
			if( liqglo.rt_irradianceMaxError != -1.0 )
				RiAttribute( "irradiance", (RtToken) "float maxerror", &liqglo.rt_irradianceMaxError, RI_NULL );
			if( liqglo.rt_irradianceMaxPixelDist != -1.0 )
				RiAttribute( "irradiance", (RtToken) "float maxpixeldist", &liqglo.rt_irradianceMaxPixelDist, RI_NULL );
		}
		// put in post-worldbegin statements
		prePostplug = globalsNode.findPlug( "postWorldMel" );
		melcommand = prePostplug.asString();
		if(liqglo.m_postWorldRIB != "" || melcommand.length() )
		{
			RiArchiveRecord( RI_COMMENT,  " Post-WorldBegin RIB from liquid globals" );
			MGlobal::executeCommand( melcommand );
			RiArchiveRecord( RI_VERBATIM, ( char* )liqglo.m_postWorldRIB.asChar() );
			RiArchiveRecord( RI_VERBATIM, "\n");
		}
		RiTransformBegin();
		RiCoordinateSystem( "worldspace" );
		RiTransformEnd();

		RiTransformBegin();
		RiRotate( -90., 1., 0., 0. );
		RiCoordinateSystem( "_environment" );
		RiTransformEnd();
	}
	RiReverseOrientation();
	return returnStatus;
}

/**
* Write the world epilogue.
* This basically calls RiWorldEnd().
*/
MStatus liqRibTranslator::worldEpilogue()
{
	CM_TRACE_FUNC("liqRibTranslator::worldEpilogue()");

	return liquid::RendererMgr::getInstancePtr()->getRenderer()->worldEpilogue();
}

/**
* Write all coordinate systems.
* This writes all user-defined coordinate systems as well as those required
* for environment/reflection map lookup and texture projection.
*/
MStatus liqRibTranslator::coordSysBlock()
{
	CM_TRACE_FUNC("liqRibTranslator::coordSysBlock()");

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

		ribNode->object(0)->writeObject("", liqglo_currentJob, false);
		ribNode->object(0)->written = 1;
		RiAttributeEnd();
	}
	return returnStatus;
}

/**
* Write all lights.
* This writes all lightsource shaders with their attributes and switches them
* on afterwards.
*/
MStatus liqRibTranslator::lightBlock()
{
	CM_TRACE_FUNC("liqRibTranslator::lightBlock()");

	MStatus returnStatus = MS::kSuccess;
	LIQDEBUGPRINTF( "-> Writing lights.\n" );
	// If this is a readArchive that we are exporting then ignore this header information
	if( !liqglo.m_exportReadArchive )
	{
		RNMAP::iterator rniter;
		int nbLight = 0;
		for ( rniter = htable->RibNodeMap.begin(); rniter != htable->RibNodeMap.end(); rniter++ )
		{
			RtInt on( 1 );
			LIQ_CHECK_CANCEL_REQUEST;
			liqRibNodePtr   ribNode = (*rniter).second;

			if( ribNode->object(0)->ignore || ribNode->object(0)->type != MRT_Light )
				continue;
			// We need to enclose lights in attribute blocks because of the
			// new added attribute support
			RiAttributeBegin();

			// All this stuff below should be handled by a new attribute class
			LIQDEBUGPRINTF( "-> RibNodeName " );
			RtString RibNodeName = getLiquidRibName( ribNode->name.asChar() );
			LIQDEBUGPRINTF( "= %s.\n", (char *)RibNodeName  );
			RiAttribute( "identifier", "name", &RibNodeName, RI_NULL );
			if( ribNode->trace.sampleMotion )
				RiAttribute( "trace", (RtToken) "samplemotion", &on, RI_NULL );
			if( ribNode->trace.displacements )
				RiAttribute( "trace", (RtToken) "displacements", &on, RI_NULL );
			if( ribNode->trace.bias != 0.01f )
			{
				RtFloat bias = ribNode->trace.bias;
				RiAttribute( "trace", (RtToken) "bias", &bias, RI_NULL );
			}
			if( ribNode->trace.maxDiffuseDepth != 1 )
			{
				RtInt mddepth = ribNode->trace.maxDiffuseDepth;
				RiAttribute( "trace", (RtToken) "maxdiffusedepth", &mddepth, RI_NULL );
			}
			if( ribNode->trace.maxSpecularDepth != 2 )
			{
				RtInt msdepth = ribNode->trace.maxSpecularDepth;
				RiAttribute( "trace", (RtToken) "maxspeculardepth", &msdepth, RI_NULL );
			}
			ribNode->object(0)->writeObject("", liqglo_currentJob, false);
			ribNode->object(0)->written = 1;
			// The next line pops the light...
			RiAttributeEnd();
			// ...so we have to switch it on again explicitly
			// if exclusive Lightlinking is set
			if( liqglo.m_illuminateByDefault )
				RiIlluminate( ribNode->object(0)->lightHandle(), 1 );
			else
				RiIlluminate( ribNode->object(0)->lightHandle(), 0 );
			nbLight++;
		}
	}
	return returnStatus;
}

void liqRibTranslator::setOutDirs()
{
//	CM_TRACE_FUNC("liqRibTranslator::setOutDirs()");

	MStatus gStatus;
	MPlug gPlug;
	MFnDependencyNode rGlobalNode( liqglo.rGlobalObj );
	{
		MString varVal;
		gPlug = rGlobalNode.findPlug( "ribDirectory", &gStatus );
		if( gStatus == MS::kSuccess ) 
			gPlug.getValue( varVal );
		gStatus.clear();
		if( varVal != "" ) 
			liqglo.liqglo_ribDir = removeEscapes( parseString( varVal, false ) );
	}
	{
		MString varVal;
		gPlug = rGlobalNode.findPlug( "textureDirectory", &gStatus );
		if( gStatus == MS::kSuccess ) 
			gPlug.getValue( varVal );
		gStatus.clear();
		if( varVal != "" ) 
			liqglo.liqglo_textureDir = removeEscapes( parseString( varVal, false ) );
	}
	{
		MString varVal;
		gPlug = rGlobalNode.findPlug( "pictureDirectory", &gStatus );
		if( gStatus == MS::kSuccess ) 
			gPlug.getValue( varVal );
		gStatus.clear();
		if( varVal != "" ) 
			liqglo.m_pixDir = removeEscapes( parseString( varVal, false ) );
	}
}


void liqRibTranslator::setSearchPaths()
{
//	CM_TRACE_FUNC("liqRibTranslator::setSearchPaths()");

	//trace log is not created, can't call CM_TRACE_FUNC()
	liqglo.liqglo_shaderPath = "&:@:.:~:rmanshader";
	liqglo.liqglo_texturePath = "&:@:.:~"; // :rmantex
	liqglo.liqglo_archivePath = "&:@:.:~"; // :rib
	liqglo.liqglo_proceduralPath = "&:@:.:~";

	MString tmphome( getenv( "LIQUIDHOME" ) );
	tmphome = liquidSanitizeSearchPath( tmphome );

	if( tmphome != "" ) 
	{
		liqglo.liqglo_shaderPath += ":" + tmphome + "/lib/shaders";
		liqglo.liqglo_texturePath += ":" + tmphome + "/lib/textures";
		liqglo.liqglo_archivePath += ":" + tmphome + "/lib/rib";
		liqglo.liqglo_proceduralPath += ":" + tmphome + "/lib/plugins";
	}

	liqglo.liqglo_shaderPath += ":" + liqglo.liqglo_projectDir;
	liqglo.liqglo_texturePath += ":" + liqglo.liqglo_projectDir;
	liqglo.liqglo_archivePath += ":" + liqglo.liqglo_projectDir;
	liqglo.liqglo_proceduralPath += ":" + liqglo.liqglo_projectDir;

	MStatus gStatus;
	MPlug gPlug;
	MFnDependencyNode rGlobalNode( liqglo.rGlobalObj );

	{
		MString varVal;
		gPlug = rGlobalNode.findPlug( "shaderPath", &gStatus );
		if( gStatus == MS::kSuccess ) 
			gPlug.getValue( varVal );
		gStatus.clear();
		if( varVal != "" ) 
		{
			tmphome += "/shaders";
			if( varVal.index( ':' ) == 0 )
				liqglo.liqglo_shaderPath += ":" + removeEscapes( parseString( varVal, false ) );
			else if( varVal.rindex( ':' ) == 0 )
				liqglo.liqglo_shaderPath = removeEscapes( parseString( varVal, false ) ) + liqglo.liqglo_shaderPath;
			else
				liqglo.liqglo_shaderPath = removeEscapes( parseString( varVal, false ) ) + ":" + tmphome;
		}
	}
	{
		MString varVal;
		gPlug = rGlobalNode.findPlug( "texturePath", &gStatus );
		if( gStatus == MS::kSuccess ) 
			gPlug.getValue( varVal );
		gStatus.clear();
		if( varVal != "" ) 
		{
			if( varVal.index( ':' ) == 0 )
				liqglo.liqglo_texturePath += ":" + removeEscapes( parseString( varVal, false ) );
			else if( varVal.rindex( ':' ) == 0 )
				liqglo.liqglo_texturePath = removeEscapes( parseString( varVal, false ) ) + liqglo.liqglo_texturePath;
			else
				liqglo.liqglo_texturePath = removeEscapes( parseString( varVal, false ) );
		}
	}
	{
		MString varVal;
		gPlug = rGlobalNode.findPlug( "archivePath", &gStatus );
		if( gStatus == MS::kSuccess ) 
			gPlug.getValue( varVal );
		gStatus.clear();
		if( varVal != "" ) 
		{
			if( varVal.index( ':' ) == 0 )
				liqglo.liqglo_archivePath += ":" + removeEscapes( parseString( varVal, false ) );
			else if( varVal.rindex( ':' ) == 0 )
				liqglo.liqglo_archivePath = removeEscapes( parseString( varVal, false ) ) + liqglo.liqglo_archivePath;
			else
				liqglo.liqglo_archivePath = removeEscapes( parseString( varVal, false ) );
		}
	}
	{
		MString varVal;
		gPlug = rGlobalNode.findPlug( "proceduralPath", &gStatus );
		if( gStatus == MS::kSuccess ) 
			gPlug.getValue( varVal );
		gStatus.clear();
		if( varVal != "" ) 
		{
			if( varVal.index( ':' ) == 0 )
				liqglo.liqglo_proceduralPath += ":" + removeEscapes( parseString( varVal, false ) );
			else if( varVal.rindex( ':' ) == 0 )
				liqglo.liqglo_proceduralPath = removeEscapes( parseString( varVal, false ) ) + liqglo.liqglo_proceduralPath;
			else
				liqglo.liqglo_proceduralPath = removeEscapes( parseString( varVal, false ) );
		}
	}
}

bool liqRibTranslator::renderFrameSort( const structJob& a, const structJob& b )
{
	CM_TRACE_FUNC("liqRibTranslator::renderFrameSort("<<a.name<<","<<b.name<<")");

	long v1 = ( a.isShadow )? a.renderFrame : 100000000;
	long v2 = ( b.isShadow )? b.renderFrame : 100000000;
	return v1 < v2;
}

void liqRibTranslator::_writeObject(
	const liqRibNodePtr& ribNode, 
	const structJob &currentJob,
	const bool bGeometryMotionBlur,
	const unsigned int msampleOn
	)
{
	CM_TRACE_FUNC("liqRibTranslator::_writeObject("<<ribNode->name<<","<<currentJob.name<<","<<bGeometryMotionBlur<<","<<msampleOn<<")");

// 	MString frame; 
// 	frame.set(liqglo.liqglo_lframe);

	MString MotionPostfix;
	unsigned int sample;
	if( bGeometryMotionBlur ){
		MString MSampleOn;
		MSampleOn.set((int)msampleOn);
		MotionPostfix = ".m"+MSampleOn;
		sample        = msampleOn;
	}else{
		MotionPostfix = "";
		sample        = 0;
	}
    
	MString geometryRibFile( 
				liquidGetRelativePath( 
					false, 
					getLiquidRibName( ribNode->name.asChar() ), 
					liqglo.liqglo_ribDir 
				) +"."+(int)liqglo.liqglo_lframe+MotionPostfix+".rib" 
			);
	ribNode->object( sample )->writeObject(geometryRibFile, currentJob, false);
}
//
bool liqRibTranslator::canExport()
{
	//CM_TRACE_FUNC("liqRibTranslator::canExport()");
	//
	if( liqglo.m_displays[0].name.length()==0 )
	{
		assert(0&&"liqglo.m_displays[ 0 ].name is empty. Please set the output image and render the scene again.");
		liquidMessage2(messageError,"liqglo.m_displays[ 0 ].name is empty. Please set the output image and render the scene again.");
		return false;
	}
	//check liquid required project directories.
	int checkDirecoties=0;
	IfMErrorWarn(MGlobal::executeCommand( "liquidCheckProjectDirectories()", checkDirecoties));
	if(0==checkDirecoties){
		liquidMessage2(messageError,"liquidCheckProjectDirectories() fails, see script editor for more details.");
		return false;
	}
	//
	return liquid::RendererMgr::getInstancePtr()->getRenderer()->canExport();
}

std::string liqRibTranslator::getFunctionTraceLogFileName() const
{
	//CM_TRACE_FUNC("liqRibTranslator::getFunctionTraceLogFileName()");

	std::stringstream sslogFileName;
	{
		//fullpath name
#ifndef _DEBUG
		liquidMessage2(messageError, "liqglo.liqglo_lframe is not initilized in Release mode. so when the program goes here liqglo.liqglo_lframe is random value, I set it to 0 manully. You can ingore this error.");
		liqglo.liqglo_lframe = 0;
#endif
		MString imageName( liqglo.liqglo_projectDir+liqglo.m_pixDir );
		imageName += parseString( liqglo.m_displays[ 0 ].name, false );


		sslogFileName << boost::format("%s.log")%imageName.asChar();
	}
	return sslogFileName.str();
}