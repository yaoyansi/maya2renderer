#ifndef _liqGlobalVariable_H
#define _liqGlobalVariable_H

#include <vector>

#include <maya/MString.h>
#include <maya/MStringArray.h>

#include "ri_interface.h"

#include <liquid.h>
#include <liqRenderer.h>

struct liqGlobalVariable
{
	// this get's set if we are running the commandline version of liquid
	bool liquidBin;


	// Kept global for liquidRigGenData and liquidRibParticleData
	FILE        *liqglo_ribFP;
	long         liqglo_lframe;
	structJob    liqglo_currentJob;
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
	MString      liqglo_sceneName;
	bool         liqglo_beautyRibHasCameraName;           // if true, usual behaviour, otherwise, no camera name in beauty rib
	bool         liqglo_isShadowPass;                     // true if we are rendering a shadow pass
	bool         liqglo_expandShaderArrays;
	bool         liqglo_shortShaderNames;                 // true if we don't want to output path names with shaders
	bool         liqglo_relativeFileNames;                // true if we only want to output project relative names
	MStringArray liqglo_DDimageName;
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
#if 0
#ifdef _WIN32
	// Hmmmmmmmm what's this ?
	int RiNColorSamples;
#endif
	// these are little storage variables to keep track of the current graphics state and will eventually be wrapped in
	// a specific class
#endif

	MString tempDefname;
};

extern struct liqGlobalVariable liqglo;
extern liquidVerbosityType liqglo_verbosity;

#endif//_liqGlobalVariable_H