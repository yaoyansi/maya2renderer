#include <liqRibCamera.h>

#include <string>

#include <maya/MSelectionList.h>
#include <maya/M3dView.h>
#include <maya/MDagPath.h>
#include <maya/MString.h>

#include <liqGlobalVariable.h>
#include <liqRibTranslator.h>

tRibCameraMgr::tRibCameraMgr()
{

}
//
tRibCameraMgr::~tRibCameraMgr()
{

}
//
void tRibCameraMgr::gatherDataForJob(
	struct liqGlobalVariable &liqglo___, 
	structJob &thisJob___,
	std::vector<structJob>  &jobList__,
	const bool m_outputShadowPass_,
	const bool m_outputHeroPass_
	)
{
	// Determine which cameras to render
	// it will either traverse the dag and find all the renderable cameras or
	// grab the current view and render that as a camera - both get added to the
	// end of the renderable camera array
	MDagPath cameraPath;
	if( liqglo___.renderCamera != "" ) 
	{
		MSelectionList camList;
		camList.add( liqglo___.renderCamera );
		camList.getDagPath( 0, cameraPath );
		MFnCamera fnCameraNode( cameraPath );
	} 
	else 
	{
		LIQDEBUGPRINTF( "-> getting current view\n" );
		M3dView::active3dView().getCamera( cameraPath );
	}


	MFnCamera fnCameraNode( cameraPath );
	thisJob___.renderFrame   = liqglo.liqglo_lframe;
	thisJob___.everyFrame    = true;
	thisJob___.isPoint       = false;
	thisJob___.path          = cameraPath;
	thisJob___.name          = fnCameraNode.name();
	thisJob___.isShadow      = false;
	thisJob___.skip          = false;
	//for shadow pass
	thisJob___.name         += "SHADOWPASS";
	thisJob___.isShadowPass  = true;
	if( m_outputShadowPass_ ) 
		jobList__.push_back( thisJob___ );
	//for hero pass
	thisJob___.name          = fnCameraNode.name();
	thisJob___.isShadowPass  = false;
	if( m_outputHeroPass_ ) 
		jobList__.push_back( thisJob___ );

	liqglo.liqglo_shutterTime    = fnCameraNode.shutterAngle() * 0.5 / M_PI;

}