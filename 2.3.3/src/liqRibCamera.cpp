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
//
void tRibCameraMgr::framePrologue_camera(long lframe, const structJob &currentJob)
{
	LIQDEBUGPRINTF( "-> Setting Resolution\n" );
	// philippe : Rotated Camera Case
	if( /*liqglo.liqglo_*/currentJob.isShadow == false && liqglo.liqglo_rotateCamera  == true ) 
		RiFormat( /*liqglo.liqglo_*/currentJob.height, /*liqglo.liqglo_*/currentJob.width, /*liqglo.liqglo_*/currentJob.aspectRatio );
	else 
		RiFormat( /*liqglo.liqglo_*/currentJob.width, /*liqglo.liqglo_*/currentJob.height, /*liqglo.liqglo_*/currentJob.aspectRatio );

	if( /*liqglo.liqglo_*/currentJob.camera[0].isOrtho )
	{
		RtFloat frameWidth, frameHeight;
		// the whole frame width has to be scaled according to the UI Unit
		frameWidth  = /*liqglo.liqglo_*/currentJob.camera[0].orthoWidth  * 0.5 ;
		frameHeight = /*liqglo.liqglo_*/currentJob.camera[0].orthoHeight * 0.5 ;
		RiProjection( "orthographic", RI_NULL );

		// if we are describing a shadow map camera,
		// we need to set the screenwindow to the default,
		// as shadow maps are always square.
		if( /*liqglo.liqglo_*/currentJob.isShadow == true )
			RiScreenWindow( -frameWidth, frameWidth, -frameHeight, frameHeight );
		else
			RiScreenWindow( -frameWidth, frameWidth, -frameHeight, frameHeight );
	} 
	else 
	{
		RtFloat fieldOfView = /*liqglo.liqglo_*/currentJob.camera[0].hFOV * 180.0 / M_PI ;
		if( /*liqglo.liqglo_*/currentJob.isShadow && /*liqglo.liqglo_*/currentJob.isPoint ) 
			fieldOfView = /*liqglo.liqglo_*/currentJob.camera[0].hFOV;

		RiProjection( "perspective", RI_FOV, &fieldOfView, RI_NULL );

		// if we are describing a shadow map camera,
		// we need to set the screenwindow to the default,
		// as shadow maps are always square.
		if( /*liqglo.liqglo_*/currentJob.isShadow == false )
		{
			double ratio = (double)/*liqglo.liqglo_*/currentJob.width / (double)/*liqglo.liqglo_*/currentJob.height;
			double left, right, bottom, top;
			if( ratio <= 0 ) 
			{
				left    = -1 + currentJob.camera[0].horizontalFilmOffset;
				right   =  1 + currentJob.camera[0].horizontalFilmOffset;
				bottom  = -1 / ratio + currentJob.camera[0].verticalFilmOffset;
				top     =  1 / ratio + currentJob.camera[0].verticalFilmOffset;
			} 
			else 
			{
				left    = -ratio + currentJob.camera[0].horizontalFilmOffset;
				right   =  ratio + currentJob.camera[0].horizontalFilmOffset;
				bottom  = -1 + currentJob.camera[0].verticalFilmOffset;
				top     =  1 + currentJob.camera[0].verticalFilmOffset;
			}
			RiScreenWindow( left, right, bottom, top );
		} else 
			RiScreenWindow( -1.0, 1.0, -1.0, 1.0 );
	}

	RiClipping( currentJob.camera[0].neardb, currentJob.camera[0].fardb );
	if( liqglo.doDof && !currentJob.isShadow ) 
		RiDepthOfField( currentJob.camera[0].fStop, currentJob.camera[0].focalLength, currentJob.camera[0].focalDistance );

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
				RiShutter( 0, currentJob.camera[0].shutter );
			else
				RiShutter( lframe, lframe + currentJob.camera[0].shutter );
			frameOffset = lframe;
			break;
		case CENTER_ON_FRAME:
			if(liqglo.liqglo_relativeMotion)
				RiShutter(  - ( currentJob.camera[0].shutter * 0.5 ),  ( currentJob.camera[0].shutter * 0.5 ) );
			else
				RiShutter( ( lframe - ( currentJob.camera[0].shutter * 0.5 ) ), ( lframe + ( currentJob.camera[0].shutter * 0.5 ) ) );
			frameOffset = lframe - ( currentJob.camera[0].shutter * 0.5 );
			break;
		case CENTER_BETWEEN_FRAMES:
			if(liqglo.liqglo_relativeMotion)
				RiShutter( + ( 0.5 * ( 1 - currentJob.camera[0].shutter ) ), + currentJob.camera[0].shutter + ( 0.5 * ( 1 - currentJob.camera[0].shutter ) ) );
			else
				RiShutter( lframe + ( 0.5 * ( 1 - currentJob.camera[0].shutter ) ), lframe + currentJob.camera[0].shutter + ( 0.5 * ( 1 -currentJob.camera[0].shutter ) ) );
			frameOffset = lframe + ( 0.5 * ( 1 - currentJob.camera[0].shutter ) );
			break;
		case CLOSE_ON_NEXT_FRAME:
			if(liqglo.liqglo_relativeMotion)
				RiShutter( + ( 1 - currentJob.camera[0].shutter ),  1 );
			else
				RiShutter( lframe + ( 1 - currentJob.camera[0].shutter ), lframe + 1 );
			frameOffset = lframe + ( 1 - currentJob.camera[0].shutter );
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
	if( currentJob.gotJobOptions ) 
		RiArchiveRecord( RI_COMMENT, "jobOptions: \n%s", currentJob.jobOptions.asChar() );

	if( ( liqglo.liqglo_preRibBox.length() > 0 ) && !currentJob.isShadow ) 
		for ( unsigned ii(0); ii < liqglo.liqglo_preRibBox.length(); ii++ ) 
			RiArchiveRecord( RI_COMMENT, "Additional Rib:\n%s", liqglo.liqglo_preRibBox[ii].asChar() );

	if( ( liqglo.liqglo_preReadArchive.length() > 0 ) && !currentJob.isShadow ) 
		for ( unsigned ii(0); ii < liqglo.liqglo_preReadArchive.length(); ii++ ) 
			RiArchiveRecord( RI_COMMENT, "Read Archive Data: \nReadArchive \"%s\"", liqglo.liqglo_preReadArchive[ii].asChar() );

	if( ( liqglo.liqglo_preRibBoxShadow.length() > 0 ) && !currentJob.isShadow ) 
		for ( unsigned ii(0); ii < liqglo.liqglo_preRibBoxShadow.length(); ii++ ) 
			RiArchiveRecord( RI_COMMENT, "Additional Rib:\n%s", liqglo.liqglo_preRibBoxShadow[ii].asChar() );

	if( ( liqglo.liqglo_preReadArchiveShadow.length() > 0 ) && currentJob.isShadow ) 
		for ( unsigned ii(0); ii < liqglo.liqglo_preReadArchiveShadow.length(); ii++ ) 
			RiArchiveRecord( RI_COMMENT, "Read Archive Data: \nReadArchive \"%s\"", liqglo.liqglo_preReadArchiveShadow[ii].asChar() );

	// if we motion-blur the cam, open the motion block
	//
	if( liqglo.doCameraMotion && ( !currentJob.isShadow || currentJob.deepShadows) ) 
		if(liqglo.liqglo_relativeMotion)
			RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimesOffsets );
		else
			RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimes );

	// write the camera transform
	//
	RtMatrix cameraMatrix;
	currentJob.camera[0].mat.get( cameraMatrix );
	RiTransform( cameraMatrix );

	// if we motion-blur the cam, write the subsequent motion samples and close the motion block
	//
	if( liqglo.doCameraMotion && ( !currentJob.isShadow || currentJob.deepShadows ) ) 
	{
		int mm = 1;
		while ( mm < liqglo.liqglo_motionSamples ) 
		{
			currentJob.camera[mm].mat.get( cameraMatrix );
			RiTransform( cameraMatrix );
			++mm;
		}
		RiMotionEnd();
	}


}