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


class liqRibLightData;
class liqRenderScript;

typedef enum {
	liqRegularShaderNode = 0,     // A regular Liquid node, keep it 0 to evaluate to false in conditions
	liqCustomPxShaderNode = 1,     // A custom MPxNode inheriting from liqCustomNode
	liqRibBoxShader = 2          // A rib box attached to the shader
} liqDetailShaderKind;

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
//	MObject rGlobalObj;

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

	MStatus buildJobs();
#ifdef Refactoring 
public: 
#endif
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
#ifdef Refactoring 
public: 
#endif
	std::vector<structJob>  jobList;
	std::vector<structJob>  shadowList;

	std::vector<structJob>  refList;  // reflections list
	std::vector<structJob>  envList;  // environments list
#ifdef Refactoring 
public: 
#endif
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







	bool        cleanShadows;                // UN-USED GLOBAL
	bool        cleanTextures;               // UN-USED GLOBAL


	// bool        renderAllCameras;   // Render all cameras, or only active ones     UN-USED GLOBAL
	bool        ignoreFilmGate;


	MString     baseShadowName;
	bool        createOutputDirectories;

	static MString magic;

	// Data used to construct output file names


//	MString       extension;
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


#ifdef Refactoring 
public: 
#endif
	// Hash table for scene
	boost::shared_ptr< liqRibHT > htable;

	// Depth in attribute blocking
	// NOTE : used in liqRibTranslator::doAttributeBlocking,
	// but this method isn't called anywhere.
	int attributeDepth;

private :

	// Old global values
	int           m_errorMode;
//	M3dView       m_activeView;

	MString       m_tmpDir;
	bool          m_noDirCheck;
	bool          m_animation;
	bool          m_useFrameExt;
	// bool          m_shadowRibGen;                // UN-USED GLOBAL
	double        m_blurTime;
#ifdef Refactoring 
public: 
#endif
	static MComputation  m_escHandler;

	bool          m_justRib;
	liquidlong    m_minCPU;
	liquidlong    m_maxCPU;



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

	bool m_renderAllCurves;
	bool m_liquidSetLightLinking;
	bool m_ignoreLights;
	bool m_ignoreSurfaces;
	bool m_ignoreDisplacements;
	bool m_ignoreVolumes;
	bool m_useNewTranslator;
	bool m_OutputShaderGraph;
	bool m_outputDebugMsgToRib;
	bool m_outputShadowPass;
	bool m_outputHeroPass;

	bool m_lazyCompute;
	bool m_outputShadersInShadows;
	bool m_outputShadersInDeepShadows;
	bool m_outputLightsInDeepShadows;
//	liquidlong m_deferredBlockSize; //moved to liqGlobal

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




	MString m_preGeomRIB;




	// MStringArray  m_pixelFilterNames;










	//vector<liqShader> m_shaders;

	//liqShader & liqGetShader( MObject shaderObj );
	MStatus liqShaderParseVectorAttr ( liqShader & currentShader, MFnDependencyNode & shaderNode, const char * argName, ParameterType pType );
	//void freeShaders( void );

//	void scanExpressions( liqRibLightData *light );

	void _writeObject( 
		const liqRibNodePtr& ribNode,
		const structJob &currentJob,
		const bool bGeometryMotionBlur,
		const unsigned int msampleOn
	);
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
	void doTextures(const std::vector<structJob> &txtList_);
	void doShadows(const std::vector<structJob> &shadowList_);
	void postActions(const MString& originalLayer__);
	MStatus buildShadowJobs__();
	MStatus scanScene__(float lframe, int sample );
	void dealwithParticleInstancedObjects(
		const float lframe__, const int sample__,
		int &count__ );
	void getCameraData( std::vector<structJob>::iterator &iter__ , const int sample__);
	void getLightData( std::vector<structJob>::iterator &iter__ , const int sample__);


	MTime originalTime;

public:
	MStatus ribPrologue__(const structJob &currentJob);
 	MStatus ribEpilogue__(const structJob &currentJob);
 	MStatus framePrologue__( long , const structJob &currentJob);
	MStatus worldPrologue__(const structJob &currentJob);
	MStatus lightBlock__(const structJob &currentJob);
	MStatus coordSysBlock__(const structJob &currentJob);
	MStatus objectBlock__(const structJob &currentJob);
	MStatus worldEpilogue__();
	MStatus frameEpilogue__( long );

	MStatus preGeometryMel();
	MStatus postGeometryMel();
	MObject getShadowSetObject(const structJob &currentJob);
	MStatus preTransformMel(const MObject &transform__);
	MStatus postTransformMel(const MObject &transform__);
	MStatus tRiIlluminate(const structJob &currentJob__, const liqRibNodePtr ribNode__);
	MStatus MaxtrixMotionBlur(const liqRibNodePtr ribNode__, MDagPath &path__, const bool bMotionBlur);

	MStatus preShapeMel(const MObject &transform__);
	MStatus postShapeMel(const MObject &transform__);
	MStatus checkSurfaceShader(
		const MDagPath &path__, 
		const liqRibNodePtr &ribNode__,
		bool &hasSurfaceShader__, 
		liqDetailShaderKind &hasCustomSurfaceShader__,
		MString &shaderRibBox__
		);
	MStatus checkDisplacementShader(
		const MDagPath &path__, 
		const liqRibNodePtr &ribNode__,
		bool &hasDisplacementShader__ 
		//liqDetailShaderKind &hasCustomSurfaceShader__,
		//MString &shaderRibBox__
		);
	MStatus checkVolumeShader(
		const MDagPath &path__, 
		const liqRibNodePtr &ribNode__,
		bool &hasDisplacementShader__ 
		//liqDetailShaderKind &hasCustomSurfaceShader__,
		//MString &shaderRibBox__
		);
	MStatus displacementBounds(const liqRibNodePtr &ribNode__);
	MStatus objectNonShadowAttribute(const liqRibNodePtr &ribNode__);
	MStatus objectShadowAttribute(const liqRibNodePtr &ribNode__);
// 	MStatus writeShader(
// 		const bool writeShaders__, 
// 		const liqRibNodePtr &ribNode__,
// 		const bool hasVolumeShader__,
// 		const bool hasSurfaceShader__,
// 		const bool hasCustomSurfaceShader__,
// 		//const bool hasDisplacementShader__,
// 		const MString &shaderRibBox__,
// 		const MDagPath &path__,
// 		const structJob &currentJob
// 		);
	MStatus writeShader_(
		const bool writeShaders__, 
		const liqRibNodePtr &ribNode__,
		const bool hasVolumeShader__,
		const bool hasSurfaceShader__,
		const bool hasCustomSurfaceShader__,
		//const bool hasDisplacementShader__,
		const MString &shaderRibBox__,
		const MDagPath &path__,
		const structJob &currentJob
		);
	MStatus writeShader_forShadow(
		/*const */bool writeShaders__, 
		const liqRibNodePtr &ribNode__,
		const bool hasVolumeShader__,
		const bool hasSurfaceShader__,
		const bool hasCustomSurfaceShader__,
		//const bool hasDisplacementShader__,
		const MString &shaderRibBox__,
		const MDagPath &path__,
		const structJob &currentJob
		);
	//
	void F1(
		const liqRibNodePtr &ribNode__, liqShader &currentShader
		);
	void F2(
		const bool m_shaderDebug, const liqRibNodePtr &ribNode__
		);
	void getPfxHairData(const MDagPath &path__,
		RtFloat &translucence, RtFloat &specularPower, RtColor &specularColor
		);
	//
	MStatus _doItNewWithoutRenderScript(const MArgList& args , const MString& originalLayer );
	MStatus _doItNewWithRenderScript(const MArgList& args , const MString& originalLayer );
	void oneObjectBlock(
		const liqRibNodePtr &ribNode,
		const structJob&currentJob
		);
	void writeShadingGroup(const MString& meshname);

private:
	liqRibTranslator(const liqRibTranslator&);
	liqRibTranslator& operator=(const liqRibTranslator&);

//singletion pattern
private:
	static liqRibTranslator *mInstance;
public:
	static liqRibTranslator* getInstancePtr();

};



#endif
