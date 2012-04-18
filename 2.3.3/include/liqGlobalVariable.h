#ifndef _liqGlobalVariable_H
#define _liqGlobalVariable_H

#include <vector>

#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MIntArray.h>

#include "ri_interface.h"

#include <liquid.h>
#include <liqRenderer.h>

enum ShutterConfig {
	OPEN_ON_FRAME         = 0,
	CENTER_ON_FRAME       = 1,
	CENTER_BETWEEN_FRAMES = 2,
	CLOSE_ON_NEXT_FRAME   = 3
};

// Display Driver Variables
typedef struct StructDDParam {
	liquidlong    num;
	MStringArray  names;
	MStringArray  data;
	MIntArray     type;
} StructDDParam;

typedef struct StructDisplay {
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
	StructDDParam   xtraParams;
} StructDisplay;

typedef struct StructChannel {
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
} StructChannel;



struct liqGlobalVariable
{
	// this get's set if we are running the commandline version of liquid
	bool liquidBin;


	// Kept global for liquidRigGenData and liquidRibParticleData
	FILE        *liqglo_ribFP;
	long         liqglo_lframe;
//	structJob    liqglo_currentJob;
	bool         liqglo_doMotion;                         // Motion blur for transformations
	bool         liqglo_doDef;                            // Motion blur for deforming objects
	bool         liqglo_doCompression;                    // output compressed ribs
	bool         liqglo_doBinary;                         // output binary ribs
	bool         liqglo_relativeMotion;                   // Use relative motion blocks
	RtFloat      liqglo_sampleTimes[LIQMAXMOTIONSAMPLES]; // current sample times
	RtFloat      liqglo_sampleTimesOffsets[LIQMAXMOTIONSAMPLES]; // current sample times (as offsets from frame)
	int          liqglo_motionSamples;                    // used to assign more than two motion blur samples!
	float        liqglo_shutterTime;
	float        liqglo_shutterEfficiency;
	bool         liqglo_doShadows;                        // Kept global for liquidRigLightData
	bool         liqglo_shapeOnlyInShadowNames;
	MString      liqglo_ribName;
	bool         liqglo_beautyRibHasCameraName;           // if true, usual behaviour, otherwise, no camera name in beauty rib
	bool         liqglo_isShadowPass;                     // true if we are rendering a shadow pass
	bool         liqglo_expandShaderArrays;
	bool         liqglo_shortShaderNames;                 // true if we don't want to output path names with shaders
	bool         liqglo_relativeFileNames;                // true if we only want to output project relative names
	//MStringArray liqglo_DDimageName;
	double       liqglo_FPS;                              // Frame-rate (for particle streak length)
	bool         liqglo_outputMeshUVs;                    // true if we are writing uvs for subdivs/polys (in addition to "st")
	bool         liqglo_noSingleFrameShadows;             // allows you to skip single-frame shadows when you chunk a render
	bool         liqglo_singleFrameShadowsOnly;           // allows you to skip single-frame shadows when you chunk a render
	MString      liqglo_renderCamera;                     // a global copy for liqRibPfxToonData
	bool         liqglo_relativeTransforms;               // wether we do Transform or ConcatTransform (relative)

	// Kept global for liquidGlobalHelper
	MString      liqglo_projectDir;
	MString      liqglo_ribDir;
	MString      liqglo_textureDir;
	MString      liqglo_shaderPath;               // Shader searchpath
	MString      liqglo_texturePath;             // Texture searchpath
	MString      liqglo_archivePath;
	MString      liqglo_proceduralPath;

	// Kept global for liqRibNode.cpp
	MStringArray liqglo_preGenerateArchive;
	MStringArray liqglo_preReadArchive;
	MStringArray liqglo_preRibBox;
	MStringArray liqglo_preReadArchiveShadow;
	MStringArray liqglo_preRibBoxShadow;
	MString      liqglo_currentNodeName;
	MString      liqglo_currentNodeShortName;

	bool         liqglo_useMtorSubdiv;  // use mtor subdiv attributes
	bool         liqglo_outputMayaPolyCreases;
	bool         liqglo_renderAllCurves;
	HiderType    liqglo_hider;

	// Kept global for raytracing
	bool         rt_useRayTracing;
	RtFloat      rt_traceBreadthFactor;
	RtFloat      rt_traceDepthFactor;
	int          rt_traceMaxDepth;
	RtFloat      rt_traceSpecularThreshold;
	int         rt_traceRayContinuation;
	int          rt_traceCacheMemory;
	bool         rt_traceDisplacements;
	bool         rt_traceSampleMotion;
	RtFloat      rt_traceBias;
	int          rt_traceMaxDiffuseDepth;
	int          rt_traceMaxSpecularDepth;
	RtFloat      rt_irradianceMaxError;
	RtFloat      rt_irradianceMaxPixelDist;

	// Additionnal globals for organized people
	MString      liqglo_shotName;
	MString      liqglo_shotVersion;
	MString      liqglo_layer;
	bool         liqglo_doExtensionPadding;
	int          liqglo_outPadding;

	// renderer properties
	liqRenderer liquidRenderer;

	MString		liqglo_rifParams;

	liquidlong m_deferredBlockSize;
    std::vector<int> frameNumbers;
	bool remoteRender;
	MString m_defGenKey;
	MString m_defGenService;
	bool m_alfredExpand;
	bool useNetRman;
	MString m_alfredTags;
	MString m_alfredServices;
	MString m_preCommand;
	bool m_deferredGen;
	bool m_alfShadowRibGen;
	bool fullShadowRib;
	bool cleanRib;              // clean the rib files up
	MString m_dirmaps;
#if 0
#ifdef _WIN32
	// Hmmmmmmmm what's this ?
	int RiNColorSamples;
#endif
	// these are little storage variables to keep track of the current graphics state and will eventually be wrapped in
	// a specific class
#endif

	MString tempDefname;
	MString renderCamera;
	bool m_exportReadArchive;
	MObject rGlobalObj;
	MString m_preWorldRIB;
	MString m_postWorldRIB;
	bool m_outputComments;
	bool m_illuminateByDefault;

	//option   ribPrologue
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
	//limits options
	liquidlong  bucketSize[2];
	liquidlong  gridSize;
	liquidlong  textureMemory;
	liquidlong  eyeSplits;
	MVector    othreshold;
	MVector    zthreshold;
	//statistics
	int           m_statistics;
	MString       m_statisticsFile;
	//other
	liquidlong  pixelSamples;
	float       shadingRate;
	liquidlong    m_rFilter;
	float         m_rFilterX, m_rFilterY;

	bool          m_renderView;
	bool	  m_bakeNonRasterOrient;
	bool	  m_bakeNoCullBackface;
	bool	  m_bakeNoCullHidden;

	MString       outFormat;
	MString       outExt;
		MString       m_pixDir;

	MString m_preFrameRIB;

	bool doDof;                 // do camera depth of field
	bool doCameraMotion;        // Motion blur for moving cameras
	bool liqglo_rotateCamera;   // rotates the camera for sideways renderings
	enum ShutterConfig shutterConfig;
	double      fov_ratio;
	int         cam_width;
	int			cam_height;
	float       aspectRatio;
	liquidlong  quantValue;
	float		m_rgain;
	float		m_rgamma;
	double        m_cropX1;
	double        m_cropX2;
	double        m_cropY1;
	double        m_cropY2;
	std::vector<StructDisplay> m_displays;
	std::vector<StructChannel> m_channels;
	bool          m_ignoreAOVDisplays;
	bool          m_renderViewCrop;
	bool          m_renderViewLocal;
	liquidlong    m_renderViewPort;
	liquidlong    m_renderViewTimeOut;
	bool launchRender;

	//debug
	bool m_logFunctionCall;//enable logFunctionCall

	bool m_ribFileOpen;//is the rib file open? for renderman only.
	bool m_writeDataIntoMainRibFile;
};

extern struct liqGlobalVariable liqglo;
extern liquidVerbosityType liqglo_verbosity;

void initHinderParameters();
void getHinderParameters(const MFnDependencyNode& rGlobalNode);
MString getHiderOptions( MString rendername, MString hidername );

void initLimitsParameters();
void getLimitsParameters(const MFnDependencyNode& rGlobalNode);
void writeLimitsOptions();

void initStatisticsParameters();
void getStatisticsParameters(const MFnDependencyNode& rGlobalNode);
void writeStatisticsOptions();

void initOtherParameters();
void getOtherParameters(const MFnDependencyNode& rGlobalNode);

void initCameraParameters();
void getCameraParameters(const MFnDependencyNode& rGlobalNode);

 

#endif//_liqGlobalVariable_H