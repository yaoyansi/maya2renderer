
#define VALIDATE_RIDECLARE \
{ \
	if(!ValidateState(9, Outside, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiDeclare [" << GetStateAsString() << "]" << std::endl; \
		return(0); \
	} \
}

#define VALIDATE_RIBEGIN \
{ \
	if(!ValidateState(1, Outside) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiBegin [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIEND \
{ \
	if(!ValidateState(1, BeginEnd) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiEnd [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIGETCONTEXT
#define VALIDATE_RICONTEXT
#define VALIDATE_RIFRAMEBEGIN \
{ \
	if(!ValidateState(1, BeginEnd) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiFrameBegin [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIFRAMEEND \
{ \
	if(!ValidateState(1, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiFrameEnd [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIWORLDBEGIN \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiWorldBegin [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIWORLDEND \
{ \
	if(!ValidateState(1, World) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiWorldEnd [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIIFBEGIN
#define VALIDATE_RIELSEIF
#define VALIDATE_RIELSE
#define VALIDATE_RIIFEND
#define VALIDATE_RIFORMAT \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiFormat [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIFRAMEASPECTRATIO \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiFrameAspectRatio [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RISCREENWINDOW \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiScreenWindow [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RICROPWINDOW \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiCropWindow [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIPROJECTION \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiProjection [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RICLIPPING \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiClipping [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RICLIPPINGPLANE
#define VALIDATE_RIDEPTHOFFIELD \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiDepthOfField [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RISHUTTER \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiShutter [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIPIXELVARIANCE \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiPixelVariance [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIPIXELSAMPLES \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiPixelSamples [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIPIXELFILTER \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiPixelFilter [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIEXPOSURE \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiExposure [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIIMAGER \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiImager [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIQUANTIZE \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiQuantize [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIDISPLAY \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiDisplay [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIGAUSSIANFILTER
#define VALIDATE_RIBOXFILTER
#define VALIDATE_RIMITCHELLFILTER
#define VALIDATE_RITRIANGLEFILTER
#define VALIDATE_RICATMULLROMFILTER
#define VALIDATE_RISINCFILTER
#define VALIDATE_RIDISKFILTER
#define VALIDATE_RIBESSELFILTER
#define VALIDATE_RIHIDER \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiHider [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RICOLORSAMPLES \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiColorSamples [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIRELATIVEDETAIL \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiRelativeDetail [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIOPTION \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiOption [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIATTRIBUTEBEGIN \
{ \
	if(!ValidateState(5, World, Attribute, Transform, Solid, Object) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiAttributeBegin [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIATTRIBUTEEND \
{ \
	if(!ValidateState(1, Attribute) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiAttributeEnd [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RICOLOR \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiColor [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIOPACITY \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiOpacity [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RITEXTURECOORDINATES \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiTextureCoordinates [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RILIGHTSOURCE \
{ \
	if(!ValidateState(7, BeginEnd, Frame, World, Attribute, Transform, Solid, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiLightSource [" << GetStateAsString() << "]" << std::endl; \
		return(0); \
	} \
}

#define VALIDATE_RIAREALIGHTSOURCE \
{ \
	if(!ValidateState(7, BeginEnd, Frame, World, Attribute, Transform, Solid, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiAreaLightSource [" << GetStateAsString() << "]" << std::endl; \
		return(0); \
	} \
}

#define VALIDATE_RIILLUMINATE \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiIlluminate [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RISURFACE \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiSurface [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIDEFORMATION \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiDeformation [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIDISPLACEMENT \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiDisplacement [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIATMOSPHERE \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiAtmosphere [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIINTERIOR \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiInterior [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIEXTERIOR \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiExterior [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RISHADERLAYER \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiShaderLayer [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RICONNECTSHADERLAYERS
#define VALIDATE_RISHADINGRATE \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiShadingRate [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RISHADINGINTERPOLATION \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiShadingInterpolation [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIMATTE \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiMatte [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIBOUND \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiBound [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIDETAIL \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiDetail [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIDETAILRANGE \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiDetailRange [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIGEOMETRICAPPROXIMATION \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiGeometricApproximation [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIORIENTATION \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiOrientation [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIREVERSEORIENTATION \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiReverseOrientation [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RISIDES \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiSides [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIIDENTITY \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiIdentity [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RITRANSFORM \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiTransform [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RICONCATTRANSFORM \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiConcatTransform [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIPERSPECTIVE \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiPerspective [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RITRANSLATE \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiTranslate [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIROTATE \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiRotate [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RISCALE \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiScale [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RISKEW \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiSkew [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RICOORDINATESYSTEM \
{ \
	if(!ValidateState(7, BeginEnd, Frame, World, Attribute, Transform, Solid, Object) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiCoordinateSystem [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RICOORDSYSTRANSFORM \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiCoordSysTransform [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RITRANSFORMPOINTS \
{ \
	if(!ValidateState(7, BeginEnd, Frame, World, Attribute, Transform, Solid, Object) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiTransformPoints [" << GetStateAsString() << "]" << std::endl; \
		return(0); \
	} \
}

#define VALIDATE_RITRANSFORMBEGIN \
{ \
	if(!ValidateState(7, BeginEnd, Frame, World, Attribute, Transform, Solid, Object) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiTransformBegin [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RITRANSFORMEND \
{ \
	if(!ValidateState(1, Transform) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiTransformEnd [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIRESOURCE
#define VALIDATE_RIRESOURCEBEGIN
#define VALIDATE_RIRESOURCEEND
#define VALIDATE_RIATTRIBUTE \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiAttribute [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIPOLYGON \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiPolygon [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIGENERALPOLYGON \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiGeneralPolygon [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIPOINTSPOLYGONS \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiPointsPolygons [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIPOINTSGENERALPOLYGONS \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiPointsGeneralPolygons [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIBASIS \
{ \
	if(!ValidateState(8, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiBasis [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIPATCH \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiPatch [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIPATCHMESH \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiPatchMesh [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RINUPATCH \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiNuPatch [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RITRIMCURVE \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiTrimCurve [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RISUBDIVISIONMESH \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiSubdivisionMesh [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RISPHERE \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiSphere [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RICONE \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiCone [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RICYLINDER \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiCylinder [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIHYPERBOLOID \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiHyperboloid [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIPARABOLOID \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiParaboloid [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIDISK \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiDisk [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RITORUS \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiTorus [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIPOINTS \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiPoints [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RICURVES \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiCurves [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIBLOBBY \
{ \
	if(!ValidateState(6, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiBlobby [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIPROCEDURAL \
{ \
	if(!ValidateState(5, World, Attribute, Transform, Solid, Object) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiProcedural [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIPROCFREE
#define VALIDATE_RIPROCDELAYEDREADARCHIVE
#define VALIDATE_RIPROCRUNPROGRAM
#define VALIDATE_RIPROCDYNAMICLOAD
#define VALIDATE_RIGEOMETRY \
{ \
	if(!ValidateState(5, World, Attribute, Transform, Solid, Object) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiGeometry [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RISOLIDBEGIN \
{ \
	if(!ValidateState(5, World, Attribute, Transform, Solid, Object) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiSolidBegin [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RISOLIDEND \
{ \
	if(!ValidateState(1, Solid) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiSolidEnd [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIOBJECTBEGIN \
{ \
	if(!ValidateState(6, BeginEnd, Frame, World, Attribute, Transform, Solid) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiObjectBegin [" << GetStateAsString() << "]" << std::endl; \
		return(0); \
	} \
}

#define VALIDATE_RIOBJECTEND \
{ \
	if(!ValidateState(1, Object) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiObjectEnd [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIOBJECTINSTANCE \
{ \
	if(!ValidateState(5, World, Attribute, Transform, Solid, Object) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiObjectInstance [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIMOTIONBEGIN \
{ \
	if(!ValidateState(7, BeginEnd, Frame, World, Attribute, Transform, Solid, Object) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiMotionBegin [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIMOTIONBEGINV \
{ \
	if(!ValidateState(7, BeginEnd, Frame, World, Attribute, Transform, Solid, Object) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiMotionBeginV [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIMOTIONEND \
{ \
	if(!ValidateState(1, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiMotionEnd [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIMAKETEXTURE \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiMakeTexture [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIMAKEBUMP \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiMakeBump [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIMAKELATLONGENVIRONMENT \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiMakeLatLongEnvironment [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIMAKECUBEFACEENVIRONMENT \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiMakeCubeFaceEnvironment [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIMAKESHADOW \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiMakeShadow [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIMAKEOCCLUSION \
{ \
	if(!ValidateState(2, BeginEnd, Frame) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiMakeOcclusion [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIERRORHANDLER \
{ \
	if(!ValidateState(9, Outside, BeginEnd, Frame, World, Attribute, Transform, Solid, Object, Motion) ) \
	{ \
		Aqsis::log() << error << "Invalid state for RiErrorHandler [" << GetStateAsString() << "]" << std::endl; \
		return; \
	} \
}

#define VALIDATE_RIERRORIGNORE
#define VALIDATE_RIERRORPRINT
#define VALIDATE_RIERRORABORT
#define VALIDATE_RIARCHIVERECORD
#define VALIDATE_RIREADARCHIVE
