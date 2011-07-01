
#include <liqGlobalVariable.h>
#include <sstream>

struct liqGlobalVariable liqglo;
liquidVerbosityType liqglo_verbosity( verbosityAll );
int  debugMode;

void initHinderParameters()
{

	liqglo.m_hiddenJitter = 1;
	// PRMAN 13 BEGIN
	liqglo.m_hiddenAperture[0] = 0.0;
	liqglo.m_hiddenAperture[1] = 0.0;
	liqglo.m_hiddenAperture[2] = 0.0;
	liqglo.m_hiddenAperture[3] = 0.0;
	liqglo.m_hiddenShutterOpening[0] = 0.0;
	liqglo.m_hiddenShutterOpening[0] = 1.0;
	// PRMAN 13 END
	liqglo.m_hiddenOcclusionBound = 0;
	liqglo.m_hiddenMpCache = true;
	liqglo.m_hiddenMpMemory = 6144;
	liqglo.m_hiddenMpCacheDir = ".";
	liqglo.m_hiddenSampleMotion = true;
	liqglo.m_hiddenSubPixel = 1;
	liqglo.m_hiddenExtremeMotionDof = false;
	liqglo.m_hiddenMaxVPDepth = -1;
	// PRMAN 13 BEGIN
	liqglo.m_hiddenSigma = false;
	liqglo.m_hiddenSigmaBlur = 1.0;
	// PRMAN 13 END

	liqglo.m_raytraceFalseColor = 0;
	liqglo.m_photonEmit = 0;
	liqglo.m_photonSampleSpectrum = 0;

	liqglo.m_depthMaskZFile = "";
	liqglo.m_depthMaskReverseSign = false;
	liqglo.m_depthMaskDepthBias = 0.01;

}
//
void getHinderParameters(const MFnDependencyNode& rGlobalNode)
{
	MStatus gStatus;
	MString varVal;
	// RENDER OPTIONS:BEGIN
	int var;
	if ( liquidGetPlugValue( rGlobalNode, "hider", var, gStatus ) == MS::kSuccess ) 
	{
		liqglo.liqglo_hider = (enum HiderType) var;
	}
	liquidGetPlugValue( rGlobalNode, "jitter", liqglo.m_hiddenJitter, gStatus );
	// PRMAN 13 BEGIN
	liquidGetPlugValue( rGlobalNode, "hiddenApertureNSides", liqglo.m_hiddenAperture[0], gStatus );
	liquidGetPlugValue( rGlobalNode, "hiddenApertureAngle", liqglo.m_hiddenAperture[1], gStatus );
	liquidGetPlugValue( rGlobalNode, "hiddenApertureRoundness", liqglo.m_hiddenAperture[2], gStatus );
	liquidGetPlugValue( rGlobalNode, "hiddenApertureDensity", liqglo.m_hiddenAperture[3], gStatus );   
	liquidGetPlugValue( rGlobalNode, "hiddenShutterOpeningOpen", liqglo.m_hiddenShutterOpening[0], gStatus );     
	liquidGetPlugValue( rGlobalNode, "hiddenShutterOpeningClose", liqglo.m_hiddenShutterOpening[1], gStatus );   
	// PRMAN 13 END
	liquidGetPlugValue( rGlobalNode, "hiddenOcclusionBound", liqglo.m_hiddenOcclusionBound, gStatus );  
	liquidGetPlugValue( rGlobalNode, "hiddenMpCache", liqglo.m_hiddenMpCache, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "hiddenMpMemory", liqglo.m_hiddenMpMemory, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "hiddenMpCacheDir", liqglo.m_hiddenMpCacheDir, gStatus );   
	liquidGetPlugValue( rGlobalNode, "hiddenSampleMotion", liqglo.m_hiddenSampleMotion, gStatus );     
	liquidGetPlugValue( rGlobalNode, "hiddenSubPixel", liqglo.m_hiddenSubPixel, gStatus );  
	liquidGetPlugValue( rGlobalNode, "hiddenExtremeMotionDof", liqglo.m_hiddenExtremeMotionDof, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "hiddenMaxVPDepth", liqglo.m_hiddenMaxVPDepth, gStatus ); 
	// PRMAN 13 BEGIN  
	liquidGetPlugValue( rGlobalNode, "hiddenSigmaHiding", liqglo.m_hiddenSigma, gStatus );   
	liquidGetPlugValue( rGlobalNode, "hiddenSigmaBlur", liqglo.m_hiddenSigmaBlur, gStatus );   
	// PRMAN 13 END  
	liquidGetPlugValue( rGlobalNode, "raytraceFalseColor", liqglo.m_raytraceFalseColor, gStatus );     
	liquidGetPlugValue( rGlobalNode, "photonEmit", liqglo.m_photonEmit, gStatus );   
	liquidGetPlugValue( rGlobalNode, "photonSampleSpectrum", liqglo.m_photonSampleSpectrum, gStatus );  
	if ( liquidGetPlugValue( rGlobalNode, "depthMaskZFile", varVal, gStatus ) == MS::kSuccess )   
		liqglo.m_depthMaskZFile = parseString( varVal, false );  
	liquidGetPlugValue( rGlobalNode, "depthMaskReverseSign", liqglo.m_depthMaskReverseSign, gStatus ); 
	liquidGetPlugValue( rGlobalNode, "depthMaskDepthBias", liqglo.m_depthMaskDepthBias, gStatus ); 
	// RENDER OPTIONS:END
}

MString getHiderOptions( MString rendername, MString hidername )
{
	MString options;
	// PRMAN
	if( rendername == "PRMan" ) 
	{
		if( hidername == "hidden" ) 
		{
			{
				std::stringstream tmp;
				tmp << "\"int jitter\" [" << liqglo.m_hiddenJitter << "] " /*<< ends*/;
				options += tmp.str().c_str();
			}
			// PRMAN 13 BEGIN
			if( liqglo.m_hiddenAperture[0] != 0.0 ||
				liqglo.m_hiddenAperture[1] != 0.0 ||
				liqglo.m_hiddenAperture[2] != 0.0 ||
				liqglo.m_hiddenAperture[3] != 0.0 ) 
			{
				char tmp[255];
				sprintf( tmp, "\"float aperture[4]\" [%f %f %f %f] ", 
					liqglo.m_hiddenAperture[0], 
					liqglo.m_hiddenAperture[1], 
					liqglo.m_hiddenAperture[2], 
					liqglo.m_hiddenAperture[3] );
				options += tmp;
			}
			if( liqglo.m_hiddenShutterOpening[0] != 0.0 && liqglo.m_hiddenShutterOpening[1] != 1.0) 
			{
				char tmp[255];
				sprintf( tmp, "\"float[2] shutteropening\" [%f %f] ", 
					liqglo.m_hiddenShutterOpening[0], liqglo.m_hiddenShutterOpening[1] );
				options += tmp;
			}
			// PRMAN 13 END
			if( liqglo.m_hiddenOcclusionBound != 0.0 ) 
			{
				char tmp[128];
				sprintf( tmp, "\"occlusionbound\" [%f] ", liqglo.m_hiddenOcclusionBound );
				options += tmp;
			}
			if( liqglo.m_hiddenMpCache != true ) 
				options += "\"int mpcache\" [0] ";
			if( liqglo.m_hiddenMpMemory != 6144 ) 
			{
				char tmp[128];
				sprintf( tmp, "\"mpcache\" [%d] ", liqglo.m_hiddenMpMemory );
				options += tmp;
			}
			if( liqglo.m_hiddenMpCacheDir != "" ) 
			{
				char tmp[1024];
				sprintf( tmp, "\"mpcachedir\" [\"%s\"] ", liqglo.m_hiddenMpCacheDir.asChar() );
				options += tmp;
			}
			if( liqglo.m_hiddenSampleMotion != true ) 
				options += "\"int samplemotion\" [0] ";
			if( liqglo.m_hiddenSubPixel != 1 ) 
			{
				char tmp[128];
				sprintf( tmp, "\"subpixel\" [%d] ", liqglo.m_hiddenSubPixel );
				options += tmp;
			}
			if( liqglo.m_hiddenExtremeMotionDof != false ) 
				options += "\"extrememotiondof\" [1] ";
			if( liqglo.m_hiddenMaxVPDepth != -1 ) 
			{
				char tmp[128];
				sprintf( tmp, "\"maxvpdepth\" [%d] ", liqglo.m_hiddenMaxVPDepth );
				options += tmp;
			}
			// PRMAN 13 BEGIN
			if( liqglo.m_hiddenSigma != false ) 
			{
				options += "\"int sigma\" [1] ";
				char tmp[128];
				sprintf( tmp, "\"sigmablur\" [%f] ", liqglo.m_hiddenSigmaBlur );
				options += tmp;
			}
			// PRMAN 13 END
		} 
		else if( hidername == "photon" ) 
		{
			if( liqglo.m_photonEmit != 0 ) 
			{
				char tmp[128];
				sprintf( tmp, " \"int emit\" [%d] ", liqglo.m_photonEmit );
				options += tmp;
			}
		} 
		else if( hidername == "depthmask" ) 
		{
			{
				char tmp[1024];
				sprintf( tmp, "\"zfile\" [\"%s\"] ", liqglo.m_depthMaskZFile.asChar() );
				options += tmp;
			}
			{
				char tmp[128];
				sprintf( tmp, "\"reversesign\" [\"%d\"] ", liqglo.m_depthMaskReverseSign );
				options += tmp;
			}
			{
				char tmp[128];
				sprintf( tmp, "\"depthbias\" [%f] ", liqglo.m_depthMaskDepthBias );
				options += tmp;
			}
		}
	}
	// 3DELIGHT
	if( rendername == "3Delight" ) 
	{
		if( hidername == "hidden" ) 
		{
			{
				char tmp[128];
				sprintf( tmp, "\"jitter\" [%d] ", liqglo.m_hiddenJitter );
				options += tmp;
			}
			if( liqglo.m_hiddenSampleMotion != true ) 
				options += "\"int samplemotion\" [0] ";
			if( liqglo.m_hiddenExtremeMotionDof != false ) 
				options += "\"int extrememotiondof\" [1] ";
		}
	}
	// PIXIE
	if( rendername == "Pixie" ) 
	{
		if( hidername == "hidden" ) 
		{
			char tmp[128];
			sprintf( tmp, "\"float jitter\" [%d] ", liqglo.m_hiddenJitter );
			options += tmp;
		} 
		else if( hidername == "raytrace" ) 
			if( liqglo.m_raytraceFalseColor != 0 ) 
				options += "\"int falsecolor\" [1] ";
			else if( hidername == "photon" ) 
			{
				if( liqglo.m_photonEmit != 0 ) 
				{
					char tmp[128];
					sprintf( tmp, " \"int emit\" [%d] ", liqglo.m_photonEmit );
					options += tmp;
				}
				if( liqglo.m_photonSampleSpectrum ) 
				{
					char tmp[128];
					sprintf( tmp, " \"int samplespectrum\" [1] ");
					options += tmp;
				}
			}
	}

	// AQSIS
	if( rendername == "Aqsis" ) 
	{
		// no known options
	}

	// AIR
	if( rendername == "Air" ) 
	{
		// no known options
	}
	return options;
}


//
void initLimitsParameters()
{
	liqglo.bucketSize[0] = 16;
	liqglo.bucketSize[1] = 16;
	liqglo.gridSize = 256;
	liqglo.textureMemory = 2048;
	liqglo.eyeSplits = 10;
	liqglo.othreshold[0] = 0.996; liqglo.othreshold[1] = 0.996; liqglo.othreshold[2] = 0.996;
	liqglo.zthreshold[0] = 0.996; liqglo.zthreshold[1] = 0.996; liqglo.zthreshold[2] = 0.996;
}
void getLimitsParameters(const MFnDependencyNode& rGlobalNode)
{
	MStatus gStatus;
	MString varVal;
	// RENDER OPTIONS:BEGIN
	int var;
	liquidGetPlugValue( rGlobalNode, "limitsBucketXSize", liqglo.bucketSize[0], gStatus );
	liquidGetPlugValue( rGlobalNode, "limitsBucketYSize", liqglo.bucketSize[1], gStatus );
	liquidGetPlugValue( rGlobalNode, "limitsGridSize", liqglo.gridSize, gStatus );
	liquidGetPlugValue( rGlobalNode, "limitsTextureMemory", liqglo.textureMemory, gStatus );
	liquidGetPlugValue( rGlobalNode, "limitsEyeSplits", liqglo.eyeSplits, gStatus );

	liquidGetPlugValue( rGlobalNode, "limitsOThreshold", liqglo.othreshold, gStatus );
	liquidGetPlugValue( rGlobalNode, "limitsZThreshold", liqglo.zthreshold, gStatus );
}
void writeLimitsOptions()
{
	if( liqglo.bucketSize != 0 )    
		RiOption( "limits", "bucketsize", ( RtPointer ) &liqglo.bucketSize, RI_NULL );
	if( liqglo.gridSize != 0 )      
		RiOption( "limits", "gridsize", ( RtPointer ) &liqglo.gridSize, RI_NULL );
	if( liqglo.textureMemory != 0 ) 
		RiOption( "limits", "texturememory", ( RtPointer) &liqglo.textureMemory, RI_NULL );
	if( liqglo.liquidRenderer.supports_EYESPLITS ) 
		RiOption( "limits", "eyesplits", ( RtPointer ) &liqglo.eyeSplits, RI_NULL );

	if(liqglo.liquidRenderer.renderName == MString("PRMan") || liqglo.liquidRenderer.renderName == MString("3Delight") )
	{
		RtColor othresholdC = {liqglo.othreshold[0], liqglo.othreshold[1], liqglo.othreshold[2]};
		RiOption( "limits", "othreshold", &othresholdC, RI_NULL );
		RtColor zthresholdC = {liqglo.zthreshold[0], liqglo.zthreshold[1], liqglo.zthreshold[2]};
		RiOption( "limits", "zthreshold", &zthresholdC, RI_NULL );
	}
}
//
//
void initStatisticsParameters()
{
	liqglo.m_statistics        = 0;
	liqglo.m_statisticsFile    = "";
}
void getStatisticsParameters(const MFnDependencyNode& rGlobalNode)
{
	MStatus gStatus;
	MString varVal;
	// RENDER OPTIONS:BEGIN
	int var;
	liquidGetPlugValue( rGlobalNode, "statistics", liqglo.m_statistics, gStatus );
	liquidGetPlugValue( rGlobalNode, "statisticsFile", varVal, gStatus );
	if( varVal != "" ) 
		liqglo.m_statisticsFile = parseString( varVal, false );
}
void writeStatisticsOptions()
{
		if( liqglo.m_statistics != 0 )  
		{
			if( liqglo.m_statistics < 4 ) 
				RiOption( "statistics", "endofframe", ( RtPointer ) &liqglo.m_statistics, RI_NULL );
			else 
			{
				//cout <<"xml stats "<<endl;
				int stats = 1;
				RiOption( "statistics", "int endofframe", ( RtPointer ) &stats, RI_NULL );
				RiArchiveRecord( RI_VERBATIM, "Option \"statistics\" \"xmlfilename\" [\"%s\"]\n", const_cast< char* > ( liqglo.m_statisticsFile.asChar() ) );
			}
		}
}
//
void initOtherParameters()
{
	liqglo.m_rFilterX = 1;
	liqglo.m_rFilterY = 1;
	liqglo.m_rFilter = pfBoxFilter;

	liqglo.pixelSamples = 1;
	liqglo.shadingRate = 1.0;
	liqglo.m_renderView        = false;
	liqglo.m_bakeNonRasterOrient    = false;
	liqglo.m_bakeNoCullBackface    = false;
	liqglo.m_bakeNoCullHidden    = false;
	liqglo.outFormat = "it";

	liqglo.m_preFrameRIB.clear();

}
void getOtherParameters(const MFnDependencyNode& rGlobalNode)
{
	MStatus gStatus;
	MString varVal;
	liquidGetPlugValue( rGlobalNode, "pixelSamples", liqglo.pixelSamples, gStatus );
	liquidGetPlugValue( rGlobalNode, "shadingRate", liqglo.shadingRate, gStatus );

	if ( liquidGetPlugValue( rGlobalNode, "imageDriver", varVal, gStatus )== MS::kSuccess )
		liqglo.outFormat = parseString( varVal, false );
	if ( liquidGetPlugValue( rGlobalNode, "bakeRasterOrient", liqglo.m_bakeNonRasterOrient, gStatus )== MS::kSuccess )
		liqglo.m_bakeNonRasterOrient = !liqglo.m_bakeNonRasterOrient;
	if ( liquidGetPlugValue( rGlobalNode, "bakeCullBackface", liqglo.m_bakeNoCullBackface, gStatus )== MS::kSuccess )
		liqglo.m_bakeNoCullBackface = !liqglo.m_bakeNoCullBackface;
	if ( liquidGetPlugValue( rGlobalNode, "bakeCullHidden", liqglo.m_bakeNoCullHidden, gStatus )== MS::kSuccess )
		liqglo.m_bakeNoCullHidden = !liqglo.m_bakeNoCullHidden;
}
 