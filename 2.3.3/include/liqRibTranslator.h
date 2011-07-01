/*
**
** The contents of this file are subject to the Mozilla Public License Version
** 1.1 (the "License"); you may not use this file except in compliance with
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
** Copyright 1988, 1989, Pixar
** All Rights Reserved
**
**
** RenderMan (R) is a registered trademark of Pixar
*/

#ifndef liqRibTranslator_H
#define liqRibTranslator_H

/* ______________________________________________________________________
**
** Liquid Rib Translator Header File
** ______________________________________________________________________
*/
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>

#include <maya/M3dView.h>
#include <maya/MComputation.h>
#include <maya/MPxCommand.h>
#include <maya/MFnCamera.h>
#include <maya/MArgList.h>
#include <maya/MIntArray.h>
#include <maya/MStringArray.h>
#include <maya/MTime.h>

#include <liquid.h>
#include <liqRibHT.h>
#include <liqShader.h>
#include <liqRenderScript.h>
#include <liqGlobalVariable.h>

enum TempControlBreak//for my refactoring only [3/4/2011 yys]
{
	TCB_OK     = 0,
	TCB_Break  = 1,
	TCB_Continue = 2,
	TCB_MS_Success = 3,
	TCB_MS_Failure = 4,
};

#define PROCESS_TEMP_CONTROL_BREAK(tcb) \
	if(TCB_Break == tcb)\
		break;\
	else if(TCB_Continue == tcb)\
		continue;\
	else if(TCB_MS_Success == tcb)\
		return MS::kSuccess;\
	else if(TCB_MS_Failure == tcb)\
		return MS::kFailure;\
	else if(TCB_OK == tcb){/* go ahead */}

class liqRibLightData;
class liqRenderScript;

class liqRibTranslator : public MPxCommand {
public:
	liqRibTranslator();
	virtual ~liqRibTranslator();

	static void * creator();
	static MSyntax syntax();

	MStatus doIt(const MArgList& args );
	
	MStatus _doItNew(const MArgList& args, const MString& originalLayer );
	MStatus _doIt(const MArgList& args, const MString& originalLayer );

	friend class liqJobList;

private: // Methods
	MObject rGlobalObj;

	MStatus scanSceneNodes( MObject&, MDagPath &, float, int, int &, MStatus& ); 
	MStatus scanScene(float, int );

	void portFieldOfView( int width, int height, double& horizontal, double& vertical, MFnCamera& fnCamera );
	void computeViewingFrustum( double window_aspect, double& left, double& right, double& bottom, double& top, MFnCamera& cam );
	void getCameraInfo( MFnCamera &cam );
	void setSearchPaths();
	void setOutDirs();

	// rib output functions
	MStatus liquidDoArgs( MArgList args );
	bool liquidInitGlobals();
	void liquidReadGlobals();
	bool verifyOutputDirectories();
	MString getHiderOptions( MString rendername, MString hidername );

	MStatus buildJobs();
	MStatus ribPrologue();
	MStatus ribEpilogue();
	MStatus framePrologue( long );
	MStatus worldPrologue();
	MStatus lightBlock();
	MStatus coordSysBlock();
	MStatus objectBlock();
	MStatus worldEpilogue();
	MStatus frameEpilogue( long );
	void doAttributeBlocking( const MDagPath & newPath,  const MDagPath & previousPath );
	void printProgress ( unsigned stat, unsigned frames, unsigned where );

	MString generateRenderScriptName()  const;
	MString generateTempMayaSceneName() const;
	MString generateFileName( fileGenMode mode, const structJob& job );
	MString generateShadowArchiveName( bool renderAllFrames, long renderAtframe, MString geometrySet );
	static bool renderFrameSort( const structJob& a, const structJob& b );

private: // Data
	enum MRibStatus {
		kRibOK,
		kRibBegin,
		kRibFrame,
		kRibWorld,
		kRibError
	};
	MRibStatus ribStatus;

	// Render Globals and RIB Export Options
	std::vector<structJob>  jobList;
	std::vector<structJob>  shadowList;

	std::vector<structJob>  refList;  // reflections list
	std::vector<structJob>  envList;  // environments list
	std::vector<structJob>  txtList;  // make textures list

	// MDagPathArray shadowLightArray;            //  UN-USED GLOBAL
	// MDagPath activeCamera;                     //  UN-USED GLOBAL

	// const MString m_default_tmp_dir;           //  UN-USED GLOBAL
	MString m_systemTempDirectory;

	liquidlong width, height, depth;

	//std::vector< int > frameNumbers; //moved to global

	// alfred stuff
	bool useRenderScript;
	bool cleanRenderScript;


	MString renderJobName;


	MString m_userRenderScriptFileName;
	MString m_renderScriptCommand;

	renderScriptFormat m_renderScriptFormat;





	bool doDof;                 // do camera depth of field
	bool doCameraMotion;        // Motion blur for moving cameras
	bool liqglo_rotateCamera;   // rotates the camera for sideways renderings
	enum shutterConfig {
		OPEN_ON_FRAME         = 0,
		CENTER_ON_FRAME       = 1,
		CENTER_BETWEEN_FRAMES = 2,
		CLOSE_ON_NEXT_FRAME   = 3
	} shutterConfig;

	bool        cleanShadows;                // UN-USED GLOBAL
	bool        cleanTextures;               // UN-USED GLOBAL
	liquidlong  pixelSamples;
	float       shadingRate;
	liquidlong  bucketSize[2];
	liquidlong  gridSize;
	liquidlong  textureMemory;
	liquidlong  eyeSplits;
	MVector    othreshold;
	MVector    zthreshold;
	// bool        renderAllCameras;   // Render all cameras, or only active ones     UN-USED GLOBAL
	bool        ignoreFilmGate;
	double      fov_ratio;
	int         cam_width,
		cam_height;
	float       aspectRatio;
	liquidlong  quantValue;
	MString     renderCamera;
	MString     baseShadowName;
	bool        createOutputDirectories;

	static MString magic;

	// Data used to construct output file names
	MString       outFormat;
	MString       outExt;
	MString       extension;
	MString       imageName;

	MString       m_beautyRibFile;
	struct MStringCmp
	{
		bool operator() (const MString &a, const MString &b) const
		{
			return strcmp( a.asChar(), b.asChar() ) < 0;
		}
	};
	//std::map<const MString, MString, MStringCmp> m_shadowRibFile;

	// MString     outFormatString;                 // UN-USED GLOBAL
	// liquidlong  outFormatControl;                // UN-USED GLOBAL

	// Data used for choosing output method
	// MString riboutput;                           // UN-USED GLOBAL
	bool launchRender;

	// Hash table for scene
	boost::shared_ptr< liqRibHT > htable;

	// Depth in attribute blocking
	// NOTE : used in liqRibTranslator::doAttributeBlocking,
	// but this method isn't called anywhere.
	int attributeDepth;

private :

	// Old global values
	int           m_errorMode;
	M3dView       m_activeView;
	MString       m_pixDir;
	MString       m_tmpDir;
	bool          m_noDirCheck;
	bool          m_animation;
	bool          m_useFrameExt;
	// bool          m_shadowRibGen;                // UN-USED GLOBAL
	double        m_blurTime;
	MComputation  m_escHandler;
	float         m_rgain,
		m_rgamma;
	bool          m_justRib;
	liquidlong    m_minCPU;
	liquidlong    m_maxCPU;

	double        m_cropX1,
		m_cropX2,
		m_cropY1,
		m_cropY2;

#ifdef _WIN32
	int RiNColorSamples;
#endif

	// these are little storage variables to keep track of the current graphics state and will eventually be wrapped in
	// a specific class
	struct globals{
		struct feedback{
			bool showProgress;
			bool outputDetailedComments;
			bool shaderDebugging;
		} feedback;

		struct shadowMaps{
			bool noShadowRibs;
			bool fullShadowRibs;
			bool lazyCompute;
		} shadowMaps;

		struct depthShadows{
			bool opacityThreshold;
			bool outputAllShaders;
		} depthShadows;

		struct deepShadows{
			bool outputAllShaders;
			bool outputLights;
		} deepShadows;

		struct rib{
			bool readArchiveable;

			struct output{
				bool allCurves;
				bool meshUVs;
			} output;

			struct shaders{
				bool noSurfaces;
				bool noLights;
				bool noDisplacements;
				bool noVolumes;
				bool expandArrays;
			} shaders;

			struct paths{
				bool projectRelative;
				bool shaders;
			} paths;

			struct format{
				bool binary;
				bool gZip;
			} format;

			struct box{
				MString preWorld;
				MString postWorld;
				MString preObject;
			} box;

		} rib;

	} globals;


	bool m_showProgress;
	bool m_currentMatteMode;
	bool m_renderSelected;
	bool m_exportReadArchive;
	bool m_renderAllCurves;
	bool m_illuminateByDefault;
	bool m_liquidSetLightLinking;
	bool m_ignoreLights;
	bool m_ignoreSurfaces;
	bool m_ignoreDisplacements;
	bool m_ignoreVolumes;
	bool m_useNewTranslator;
	bool m_outputShadowPass;
	bool m_outputHeroPass;

	bool m_lazyCompute;
	bool m_outputShadersInShadows;
	bool m_outputShadersInDeepShadows;
	bool m_outputLightsInDeepShadows;
//	liquidlong m_deferredBlockSize; //moved to liqGlobal
	bool m_outputComments;
	bool m_shaderDebug;

	long m_currentLiquidJobNumber;



	MString m_preFrameMel;
	MString m_postFrameMel;

	MString m_renderCommand;
	MString m_ribgenCommand;


	MString m_preJobCommand;
	MString m_postJobCommand;
	MString m_preFrameCommand;
	MString m_postFrameCommand;

	MString m_preTransformMel;
	MString m_postTransformMel;
	MString m_preShapeMel;
	MString m_postShapeMel;

	MString m_shaderPath;

	bool	  m_bakeNonRasterOrient;
	bool	  m_bakeNoCullBackface;
	bool	  m_bakeNoCullHidden;

	MString m_preFrameRIB;
	MString m_preWorldRIB;
	MString m_postWorldRIB;

	MString m_preGeomRIB;

	// Display Driver Variables
	typedef struct structDDParam {
		liquidlong    num;
		MStringArray  names;
		MStringArray  data;
		MIntArray     type;
	} structDDParam;

	bool          m_ignoreAOVDisplays;

	typedef struct structDisplay {
		MString         name;
		MString         type;
		MString         mode;
		bool            enabled;
		bool            doQuantize;
		int             bitDepth;
		float           dither;
		bool            doFilter;
		int             filter;
		float           filterX;
		float           filterY;
		structDDParam   xtraParams;
	} structDisplay;
	std::vector<structDisplay> m_displays;

	typedef struct structChannel {
		MString     name;
		int         type;
		int         arraySize;
		bool        quantize;
		int         bitDepth;
		float       dither;
		bool        filter;
		int         pixelFilter;
		float       pixelFilterX;
		float       pixelFilterY;
	} structChannel;
	std::vector<structChannel> m_channels;

	// MStringArray  m_pixelFilterNames;
	liquidlong    m_rFilter;
	float         m_rFilterX, m_rFilterY;

	bool          m_renderView;
	bool          m_renderViewCrop;
	bool          m_renderViewLocal;
	liquidlong    m_renderViewPort;
	liquidlong    m_renderViewTimeOut;

	int           m_statistics;
	MString       m_statisticsFile;

	int           m_hiddenJitter;
	// PRMAN 13 BEGIN
	float         m_hiddenAperture[4];
	float         m_hiddenShutterOpening[2];
	// PRMAN 13 END
	float         m_hiddenOcclusionBound;
	bool          m_hiddenMpCache;
	int           m_hiddenMpMemory;
	MString       m_hiddenMpCacheDir;
	bool          m_hiddenSampleMotion;
	int           m_hiddenSubPixel;
	bool          m_hiddenExtremeMotionDof;
	int           m_hiddenMaxVPDepth;
	// PRMAN 13 BEGIN
	bool          m_hiddenSigma;
	float         m_hiddenSigmaBlur;
	// PRMAN 13 END
	int           m_raytraceFalseColor;
	int           m_photonEmit;
	int           m_photonSampleSpectrum;

	MString       m_depthMaskZFile;
	bool          m_depthMaskReverseSign;
	float         m_depthMaskDepthBias;

	//vector<liqShader> m_shaders;

	//liqShader & liqGetShader( MObject shaderObj );
	MStatus liqShaderParseVectorAttr ( liqShader & currentShader, MFnDependencyNode & shaderNode, const char * argName, ParameterType pType );
	//void freeShaders( void );

	void scanExpressions( liqShader & currentShader );
	void scanExpressions( liqRibLightData *light );
	void processExpression( liqTokenPointer *token, liqRibLightData *light = NULL );

	void _writeObject( const liqRibNodePtr& ribNode);
	void _RiOption_format_compress(bool bBinary, bool bCompress);
	void makeReflectionPass(
		std::vector<structJob> &refList__, 
		liqRenderScript::Job &reflectJob__,
		bool &alf_textures__,
		bool &alf_shadows__,
		bool &alf_refmaps__
	);
	void makeShadowPass(
		std::vector<structJob> &shadowList__, 
		liqRenderScript::Job &shadowJob__,
		bool &alf_textures__,
		bool &alf_shadows__,
		bool &alf_refmaps__,
		const MString &framePreCommand__,
		const MString &frameRenderCommand__,
		const int currentBlock__
		);

	void calaculateSamplingTime(const long scanTime__);

	MStatus buildJobs__();

	TempControlBreak processOneFrame(
		const unsigned int frameIndex,
		struct liqGlobalVariable &liqglo__
		);
	void doRenderView();
	void doTextures();
	void doShadows();
	void postActions(const MString& originalLayer__);
	MStatus buildShadowJobs__();
	MStatus scanScene__(float lframe, int sample );

	MTime originalTime;

private:
	liqRibTranslator(const liqRibTranslator&);
	liqRibTranslator& operator=(const liqRibTranslator&);
};



#endif
