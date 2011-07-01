
void CqRibRequestHandler::handleFrameBegin(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqInt number = parser.getInt();

	// Call through to the C binding.
	RiFrameBegin(toRiType(number));
}

void CqRibRequestHandler::handleFrameEnd(IqRibParser& parser)
{

	// Call through to the C binding.
	RiFrameEnd();
}

void CqRibRequestHandler::handleWorldBegin(IqRibParser& parser)
{

	// Call through to the C binding.
	RiWorldBegin();
}

void CqRibRequestHandler::handleWorldEnd(IqRibParser& parser)
{

	// Call through to the C binding.
	RiWorldEnd();
}

void CqRibRequestHandler::handleIfBegin(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string condition = parser.getString();

	// Call through to the C binding.
	RiIfBegin(toRiType(condition));
}

void CqRibRequestHandler::handleElseIf(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string condition = parser.getString();

	// Call through to the C binding.
	RiElseIf(toRiType(condition));
}

void CqRibRequestHandler::handleElse(IqRibParser& parser)
{

	// Call through to the C binding.
	RiElse();
}

void CqRibRequestHandler::handleIfEnd(IqRibParser& parser)
{

	// Call through to the C binding.
	RiIfEnd();
}

void CqRibRequestHandler::handleFormat(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqInt xresolution = parser.getInt();
	TqInt yresolution = parser.getInt();
	TqFloat pixelaspectratio = parser.getFloat();

	// Call through to the C binding.
	RiFormat(toRiType(xresolution), toRiType(yresolution), toRiType(pixelaspectratio));
}

void CqRibRequestHandler::handleFrameAspectRatio(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqFloat frameratio = parser.getFloat();

	// Call through to the C binding.
	RiFrameAspectRatio(toRiType(frameratio));
}

void CqRibRequestHandler::handleScreenWindow(IqRibParser& parser)
{

	// Collect all args as an array
	const IqRibParser::TqFloatArray& allArgs = parser.getFloatArray(4);

	// Collect arguments from parser.
	TqFloat left = allArgs[0];
	TqFloat right = allArgs[1];
	TqFloat bottom = allArgs[2];
	TqFloat top = allArgs[3];

	// Call through to the C binding.
	RiScreenWindow(toRiType(left), toRiType(right), toRiType(bottom), toRiType(top));
}

void CqRibRequestHandler::handleCropWindow(IqRibParser& parser)
{

	// Collect all args as an array
	const IqRibParser::TqFloatArray& allArgs = parser.getFloatArray(4);

	// Collect arguments from parser.
	TqFloat xmin = allArgs[0];
	TqFloat xmax = allArgs[1];
	TqFloat ymin = allArgs[2];
	TqFloat ymax = allArgs[3];

	// Call through to the C binding.
	RiCropWindow(toRiType(xmin), toRiType(xmax), toRiType(ymin), toRiType(ymax));
}

void CqRibRequestHandler::handleProjection(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string name = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiProjectionV(toRiType(name), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleClipping(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqFloat cnear = parser.getFloat();
	TqFloat cfar = parser.getFloat();

	// Call through to the C binding.
	RiClipping(toRiType(cnear), toRiType(cfar));
}

void CqRibRequestHandler::handleClippingPlane(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqFloat x = parser.getFloat();
	TqFloat y = parser.getFloat();
	TqFloat z = parser.getFloat();
	TqFloat nx = parser.getFloat();
	TqFloat ny = parser.getFloat();
	TqFloat nz = parser.getFloat();

	// Call through to the C binding.
	RiClippingPlane(toRiType(x), toRiType(y), toRiType(z), toRiType(nx), toRiType(ny), toRiType(nz));
}

void CqRibRequestHandler::handleShutter(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqFloat opentime = parser.getFloat();
	TqFloat closetime = parser.getFloat();

	// Call through to the C binding.
	RiShutter(toRiType(opentime), toRiType(closetime));
}

void CqRibRequestHandler::handlePixelVariance(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqFloat variance = parser.getFloat();

	// Call through to the C binding.
	RiPixelVariance(toRiType(variance));
}

void CqRibRequestHandler::handlePixelSamples(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqFloat xsamples = parser.getFloat();
	TqFloat ysamples = parser.getFloat();

	// Call through to the C binding.
	RiPixelSamples(toRiType(xsamples), toRiType(ysamples));
}

void CqRibRequestHandler::handlePixelFilter(IqRibParser& parser)
{

	// Collect arguments from parser.
	CqFilterFuncString function = parser.getString();
	TqFloat xwidth = parser.getFloat();
	TqFloat ywidth = parser.getFloat();

	// Call through to the C binding.
	RiPixelFilter(toRiType(function), toRiType(xwidth), toRiType(ywidth));
}

void CqRibRequestHandler::handleExposure(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqFloat gain = parser.getFloat();
	TqFloat gamma = parser.getFloat();

	// Call through to the C binding.
	RiExposure(toRiType(gain), toRiType(gamma));
}

void CqRibRequestHandler::handleImager(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string name = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiImagerV(toRiType(name), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleQuantize(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string type = parser.getString();
	TqInt one = parser.getInt();
	TqInt min = parser.getInt();
	TqInt max = parser.getInt();
	TqFloat ditheramplitude = parser.getFloat();

	// Call through to the C binding.
	RiQuantize(toRiType(type), toRiType(one), toRiType(min), toRiType(max), toRiType(ditheramplitude));
}

void CqRibRequestHandler::handleDisplay(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string name = parser.getString();
	std::string type = parser.getString();
	std::string mode = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiDisplayV(toRiType(name), toRiType(type), toRiType(mode), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleHider(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string name = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiHiderV(toRiType(name), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleRelativeDetail(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqFloat relativedetail = parser.getFloat();

	// Call through to the C binding.
	RiRelativeDetail(toRiType(relativedetail));
}

void CqRibRequestHandler::handleOption(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string name = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiOptionV(toRiType(name), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleAttributeBegin(IqRibParser& parser)
{

	// Call through to the C binding.
	RiAttributeBegin();
}

void CqRibRequestHandler::handleAttributeEnd(IqRibParser& parser)
{

	// Call through to the C binding.
	RiAttributeEnd();
}

void CqRibRequestHandler::handleColor(IqRibParser& parser)
{

	// Collect arguments from parser.
	const IqRibParser::TqFloatArray& Cq = parser.getFloatArray(m_numColorComps);

	// Call through to the C binding.
	RiColor(toRiType(Cq));
}

void CqRibRequestHandler::handleOpacity(IqRibParser& parser)
{

	// Collect arguments from parser.
	const IqRibParser::TqFloatArray& Os = parser.getFloatArray(m_numColorComps);

	// Call through to the C binding.
	RiOpacity(toRiType(Os));
}

void CqRibRequestHandler::handleTextureCoordinates(IqRibParser& parser)
{

	// Collect all args as an array
	const IqRibParser::TqFloatArray& allArgs = parser.getFloatArray(8);

	// Collect arguments from parser.
	TqFloat s1 = allArgs[0];
	TqFloat t1 = allArgs[1];
	TqFloat s2 = allArgs[2];
	TqFloat t2 = allArgs[3];
	TqFloat s3 = allArgs[4];
	TqFloat t3 = allArgs[5];
	TqFloat s4 = allArgs[6];
	TqFloat t4 = allArgs[7];

	// Call through to the C binding.
	RiTextureCoordinates(toRiType(s1), toRiType(t1), toRiType(s2), toRiType(t2), toRiType(s3), toRiType(t3), toRiType(s4), toRiType(t4));
}

void CqRibRequestHandler::handleSurface(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string name = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiSurfaceV(toRiType(name), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleDisplacement(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string name = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiDisplacementV(toRiType(name), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleAtmosphere(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string name = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiAtmosphereV(toRiType(name), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleInterior(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string name = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiInteriorV(toRiType(name), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleExterior(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string name = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiExteriorV(toRiType(name), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleShaderLayer(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string type = parser.getString();
	std::string name = parser.getString();
	std::string layername = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiShaderLayerV(toRiType(type), toRiType(name), toRiType(layername), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleConnectShaderLayers(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string type = parser.getString();
	std::string layer1 = parser.getString();
	std::string variable1 = parser.getString();
	std::string layer2 = parser.getString();
	std::string variable2 = parser.getString();

	// Call through to the C binding.
	RiConnectShaderLayers(toRiType(type), toRiType(layer1), toRiType(variable1), toRiType(layer2), toRiType(variable2));
}

void CqRibRequestHandler::handleShadingRate(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqFloat size = parser.getFloat();

	// Call through to the C binding.
	RiShadingRate(toRiType(size));
}

void CqRibRequestHandler::handleShadingInterpolation(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string type = parser.getString();

	// Call through to the C binding.
	RiShadingInterpolation(toRiType(type));
}

void CqRibRequestHandler::handleMatte(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqInt onoff = parser.getInt();

	// Call through to the C binding.
	RiMatte(toRiType(onoff));
}

void CqRibRequestHandler::handleBound(IqRibParser& parser)
{

	// Collect arguments from parser.
	const IqRibParser::TqFloatArray& bound = parser.getFloatArray(6);

	// Call through to the C binding.
	RiBound(toRiType(bound));
}

void CqRibRequestHandler::handleDetail(IqRibParser& parser)
{

	// Collect arguments from parser.
	const IqRibParser::TqFloatArray& bound = parser.getFloatArray(6);

	// Call through to the C binding.
	RiDetail(toRiType(bound));
}

void CqRibRequestHandler::handleDetailRange(IqRibParser& parser)
{

	// Collect all args as an array
	const IqRibParser::TqFloatArray& allArgs = parser.getFloatArray(4);

	// Collect arguments from parser.
	TqFloat offlow = allArgs[0];
	TqFloat onlow = allArgs[1];
	TqFloat onhigh = allArgs[2];
	TqFloat offhigh = allArgs[3];

	// Call through to the C binding.
	RiDetailRange(toRiType(offlow), toRiType(onlow), toRiType(onhigh), toRiType(offhigh));
}

void CqRibRequestHandler::handleGeometricApproximation(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string type = parser.getString();
	TqFloat value = parser.getFloat();

	// Call through to the C binding.
	RiGeometricApproximation(toRiType(type), toRiType(value));
}

void CqRibRequestHandler::handleOrientation(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string orientation = parser.getString();

	// Call through to the C binding.
	RiOrientation(toRiType(orientation));
}

void CqRibRequestHandler::handleReverseOrientation(IqRibParser& parser)
{

	// Call through to the C binding.
	RiReverseOrientation();
}

void CqRibRequestHandler::handleSides(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqInt nsides = parser.getInt();

	// Call through to the C binding.
	RiSides(toRiType(nsides));
}

void CqRibRequestHandler::handleIdentity(IqRibParser& parser)
{

	// Call through to the C binding.
	RiIdentity();
}

void CqRibRequestHandler::handleTransform(IqRibParser& parser)
{

	// Collect arguments from parser.
	SqRtMatrixHolder transform = parser.getFloatArray();

	// Call through to the C binding.
	RiTransform(toRiType(transform));
}

void CqRibRequestHandler::handleConcatTransform(IqRibParser& parser)
{

	// Collect arguments from parser.
	SqRtMatrixHolder transform = parser.getFloatArray();

	// Call through to the C binding.
	RiConcatTransform(toRiType(transform));
}

void CqRibRequestHandler::handlePerspective(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqFloat fov = parser.getFloat();

	// Call through to the C binding.
	RiPerspective(toRiType(fov));
}

void CqRibRequestHandler::handleTranslate(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqFloat dx = parser.getFloat();
	TqFloat dy = parser.getFloat();
	TqFloat dz = parser.getFloat();

	// Call through to the C binding.
	RiTranslate(toRiType(dx), toRiType(dy), toRiType(dz));
}

void CqRibRequestHandler::handleRotate(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqFloat angle = parser.getFloat();
	TqFloat dx = parser.getFloat();
	TqFloat dy = parser.getFloat();
	TqFloat dz = parser.getFloat();

	// Call through to the C binding.
	RiRotate(toRiType(angle), toRiType(dx), toRiType(dy), toRiType(dz));
}

void CqRibRequestHandler::handleScale(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqFloat sx = parser.getFloat();
	TqFloat sy = parser.getFloat();
	TqFloat sz = parser.getFloat();

	// Call through to the C binding.
	RiScale(toRiType(sx), toRiType(sy), toRiType(sz));
}

void CqRibRequestHandler::handleSkew(IqRibParser& parser)
{

	// Collect all args as an array
	const IqRibParser::TqFloatArray& allArgs = parser.getFloatArray(7);

	// Collect arguments from parser.
	TqFloat angle = allArgs[0];
	TqFloat dx1 = allArgs[1];
	TqFloat dy1 = allArgs[2];
	TqFloat dz1 = allArgs[3];
	TqFloat dx2 = allArgs[4];
	TqFloat dy2 = allArgs[5];
	TqFloat dz2 = allArgs[6];

	// Call through to the C binding.
	RiSkew(toRiType(angle), toRiType(dx1), toRiType(dy1), toRiType(dz1), toRiType(dx2), toRiType(dy2), toRiType(dz2));
}

void CqRibRequestHandler::handleCoordinateSystem(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string space = parser.getString();

	// Call through to the C binding.
	RiCoordinateSystem(toRiType(space));
}

void CqRibRequestHandler::handleCoordSysTransform(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string space = parser.getString();

	// Call through to the C binding.
	RiCoordSysTransform(toRiType(space));
}

void CqRibRequestHandler::handleTransformBegin(IqRibParser& parser)
{

	// Call through to the C binding.
	RiTransformBegin();
}

void CqRibRequestHandler::handleTransformEnd(IqRibParser& parser)
{

	// Call through to the C binding.
	RiTransformEnd();
}

void CqRibRequestHandler::handleResource(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string handle = parser.getString();
	std::string type = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiResourceV(toRiType(handle), toRiType(type), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleResourceBegin(IqRibParser& parser)
{

	// Call through to the C binding.
	RiResourceBegin();
}

void CqRibRequestHandler::handleResourceEnd(IqRibParser& parser)
{

	// Call through to the C binding.
	RiResourceEnd();
}

void CqRibRequestHandler::handleAttribute(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string name = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiAttributeV(toRiType(name), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handlePolygon(IqRibParser& parser)
{

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	TqInt nvertices = paramList.countP();

	// Call through to the C binding.
	RiPolygonV(toRiType(nvertices), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleGeneralPolygon(IqRibParser& parser)
{

	// Collect arguments from parser.
	const IqRibParser::TqIntArray& nverts = parser.getIntArray();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	TqInt nloops = nverts.size();

	// Call through to the C binding.
	RiGeneralPolygonV(toRiType(nloops), toRiType(nverts), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handlePointsPolygons(IqRibParser& parser)
{

	// Collect arguments from parser.
	const IqRibParser::TqIntArray& nverts = parser.getIntArray();
	const IqRibParser::TqIntArray& verts = parser.getIntArray();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	TqInt npolys = nverts.size();

	// Call through to the C binding.
	RiPointsPolygonsV(toRiType(npolys), toRiType(nverts), toRiType(verts), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handlePointsGeneralPolygons(IqRibParser& parser)
{

	// Collect arguments from parser.
	const IqRibParser::TqIntArray& nloops = parser.getIntArray();
	const IqRibParser::TqIntArray& nverts = parser.getIntArray();
	const IqRibParser::TqIntArray& verts = parser.getIntArray();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	TqInt npolys = nloops.size();

	// Call through to the C binding.
	RiPointsGeneralPolygonsV(toRiType(npolys), toRiType(nloops), toRiType(nverts), toRiType(verts), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handlePatch(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string type = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiPatchV(toRiType(type), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handlePatchMesh(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string type = parser.getString();
	TqInt nu = parser.getInt();
	std::string uwrap = parser.getString();
	TqInt nv = parser.getInt();
	std::string vwrap = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiPatchMeshV(toRiType(type), toRiType(nu), toRiType(uwrap), toRiType(nv), toRiType(vwrap), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleNuPatch(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqInt nu = parser.getInt();
	TqInt uorder = parser.getInt();
	const IqRibParser::TqFloatArray& uknot = parser.getFloatArray();
	TqFloat umin = parser.getFloat();
	TqFloat umax = parser.getFloat();
	TqInt nv = parser.getInt();
	TqInt vorder = parser.getInt();
	const IqRibParser::TqFloatArray& vknot = parser.getFloatArray();
	TqFloat vmin = parser.getFloat();
	TqFloat vmax = parser.getFloat();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiNuPatchV(toRiType(nu), toRiType(uorder), toRiType(uknot), toRiType(umin), toRiType(umax), toRiType(nv), toRiType(vorder), toRiType(vknot), toRiType(vmin), toRiType(vmax), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleTrimCurve(IqRibParser& parser)
{

	// Collect arguments from parser.
	const IqRibParser::TqIntArray& ncurves = parser.getIntArray();
	const IqRibParser::TqIntArray& order = parser.getIntArray();
	const IqRibParser::TqFloatArray& knot = parser.getFloatArray();
	const IqRibParser::TqFloatArray& min = parser.getFloatArray();
	const IqRibParser::TqFloatArray& max = parser.getFloatArray();
	const IqRibParser::TqIntArray& n = parser.getIntArray();
	const IqRibParser::TqFloatArray& u = parser.getFloatArray();
	const IqRibParser::TqFloatArray& v = parser.getFloatArray();
	const IqRibParser::TqFloatArray& w = parser.getFloatArray();

	TqInt nloops = ncurves.size();

	// Call through to the C binding.
	RiTrimCurve(toRiType(nloops), toRiType(ncurves), toRiType(order), toRiType(knot), toRiType(min), toRiType(max), toRiType(n), toRiType(u), toRiType(v), toRiType(w));
}

void CqRibRequestHandler::handleSphere(IqRibParser& parser)
{

	// Collect all args as an array
	const IqRibParser::TqFloatArray& allArgs = parser.getFloatArray(4);

	// Collect arguments from parser.
	TqFloat radius = allArgs[0];
	TqFloat zmin = allArgs[1];
	TqFloat zmax = allArgs[2];
	TqFloat thetamax = allArgs[3];

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiSphereV(toRiType(radius), toRiType(zmin), toRiType(zmax), toRiType(thetamax), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleCone(IqRibParser& parser)
{

	// Collect all args as an array
	const IqRibParser::TqFloatArray& allArgs = parser.getFloatArray(3);

	// Collect arguments from parser.
	TqFloat height = allArgs[0];
	TqFloat radius = allArgs[1];
	TqFloat thetamax = allArgs[2];

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiConeV(toRiType(height), toRiType(radius), toRiType(thetamax), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleCylinder(IqRibParser& parser)
{

	// Collect all args as an array
	const IqRibParser::TqFloatArray& allArgs = parser.getFloatArray(4);

	// Collect arguments from parser.
	TqFloat radius = allArgs[0];
	TqFloat zmin = allArgs[1];
	TqFloat zmax = allArgs[2];
	TqFloat thetamax = allArgs[3];

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiCylinderV(toRiType(radius), toRiType(zmin), toRiType(zmax), toRiType(thetamax), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleParaboloid(IqRibParser& parser)
{

	// Collect all args as an array
	const IqRibParser::TqFloatArray& allArgs = parser.getFloatArray(4);

	// Collect arguments from parser.
	TqFloat rmax = allArgs[0];
	TqFloat zmin = allArgs[1];
	TqFloat zmax = allArgs[2];
	TqFloat thetamax = allArgs[3];

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiParaboloidV(toRiType(rmax), toRiType(zmin), toRiType(zmax), toRiType(thetamax), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleDisk(IqRibParser& parser)
{

	// Collect all args as an array
	const IqRibParser::TqFloatArray& allArgs = parser.getFloatArray(3);

	// Collect arguments from parser.
	TqFloat height = allArgs[0];
	TqFloat radius = allArgs[1];
	TqFloat thetamax = allArgs[2];

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiDiskV(toRiType(height), toRiType(radius), toRiType(thetamax), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleTorus(IqRibParser& parser)
{

	// Collect all args as an array
	const IqRibParser::TqFloatArray& allArgs = parser.getFloatArray(5);

	// Collect arguments from parser.
	TqFloat majorrad = allArgs[0];
	TqFloat minorrad = allArgs[1];
	TqFloat phimin = allArgs[2];
	TqFloat phimax = allArgs[3];
	TqFloat thetamax = allArgs[4];

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiTorusV(toRiType(majorrad), toRiType(minorrad), toRiType(phimin), toRiType(phimax), toRiType(thetamax), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handlePoints(IqRibParser& parser)
{

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	TqInt npoints = paramList.countP();

	// Call through to the C binding.
	RiPointsV(toRiType(npoints), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleCurves(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string type = parser.getString();
	const IqRibParser::TqIntArray& nvertices = parser.getIntArray();
	std::string wrap = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	TqInt ncurves = nvertices.size();

	// Call through to the C binding.
	RiCurvesV(toRiType(type), toRiType(ncurves), toRiType(nvertices), toRiType(wrap), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleBlobby(IqRibParser& parser)
{

	// Collect arguments from parser.
	TqInt nleaf = parser.getInt();
	const IqRibParser::TqIntArray& code = parser.getIntArray();
	const IqRibParser::TqFloatArray& flt = parser.getFloatArray();
	SqRtTokenArrayHolder str = parser.getStringArray();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	TqInt ncode = code.size();
	TqInt nflt = flt.size();
	TqInt nstr = str.size();

	// Call through to the C binding.
	RiBlobbyV(toRiType(nleaf), toRiType(ncode), toRiType(code), toRiType(nflt), toRiType(flt), toRiType(nstr), toRiType(str), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleGeometry(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string type = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiGeometryV(toRiType(type), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleSolidBegin(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string type = parser.getString();

	// Call through to the C binding.
	RiSolidBegin(toRiType(type));
}

void CqRibRequestHandler::handleSolidEnd(IqRibParser& parser)
{

	// Call through to the C binding.
	RiSolidEnd();
}

void CqRibRequestHandler::handleObjectEnd(IqRibParser& parser)
{

	// Call through to the C binding.
	RiObjectEnd();
}

void CqRibRequestHandler::handleMotionEnd(IqRibParser& parser)
{

	// Call through to the C binding.
	RiMotionEnd();
}

void CqRibRequestHandler::handleMakeTexture(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string imagefile = parser.getString();
	std::string texturefile = parser.getString();
	std::string swrap = parser.getString();
	std::string twrap = parser.getString();
	CqFilterFuncString filterfunc = parser.getString();
	TqFloat swidth = parser.getFloat();
	TqFloat twidth = parser.getFloat();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiMakeTextureV(toRiType(imagefile), toRiType(texturefile), toRiType(swrap), toRiType(twrap), toRiType(filterfunc), toRiType(swidth), toRiType(twidth), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleMakeLatLongEnvironment(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string imagefile = parser.getString();
	std::string reflfile = parser.getString();
	CqFilterFuncString filterfunc = parser.getString();
	TqFloat swidth = parser.getFloat();
	TqFloat twidth = parser.getFloat();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiMakeLatLongEnvironmentV(toRiType(imagefile), toRiType(reflfile), toRiType(filterfunc), toRiType(swidth), toRiType(twidth), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleMakeCubeFaceEnvironment(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string px = parser.getString();
	std::string nx = parser.getString();
	std::string py = parser.getString();
	std::string ny = parser.getString();
	std::string pz = parser.getString();
	std::string nz = parser.getString();
	std::string reflfile = parser.getString();
	TqFloat fov = parser.getFloat();
	CqFilterFuncString filterfunc = parser.getString();
	TqFloat swidth = parser.getFloat();
	TqFloat twidth = parser.getFloat();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiMakeCubeFaceEnvironmentV(toRiType(px), toRiType(nx), toRiType(py), toRiType(ny), toRiType(pz), toRiType(nz), toRiType(reflfile), toRiType(fov), toRiType(filterfunc), toRiType(swidth), toRiType(twidth), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleMakeShadow(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string picfile = parser.getString();
	std::string shadowfile = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	// Call through to the C binding.
	RiMakeShadowV(toRiType(picfile), toRiType(shadowfile), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleMakeOcclusion(IqRibParser& parser)
{

	// Collect arguments from parser.
	SqRtTokenArrayHolder picfiles = parser.getStringArray();
	std::string shadowfile = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	TqInt npics = picfiles.size();

	// Call through to the C binding.
	RiMakeOcclusionV(toRiType(npics), toRiType(picfiles), toRiType(shadowfile), paramList.count(), paramList.tokens(), paramList.values());
}

void CqRibRequestHandler::handleErrorHandler(IqRibParser& parser)
{

	// Collect arguments from parser.
	CqErrorHandlerString handler = parser.getString();

	// Call through to the C binding.
	RiErrorHandler(toRiType(handler));
}

void CqRibRequestHandler::handleReadArchive(IqRibParser& parser)
{

	// Collect arguments from parser.
	std::string name = parser.getString();

	// Extract the parameter list
	CqParamListHandler paramList(m_tokenDict);
	parser.getParamList(paramList);

	RtArchiveCallback callback = RiArchiveRecord;

	// Call through to the C binding.
	RiReadArchiveV(toRiType(name), toRiType(callback), paramList.count(), paramList.tokens(), paramList.values());
}
