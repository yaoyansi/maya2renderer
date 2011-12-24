/* $Revision: #1 $  (Pixar - RenderMan Division)  $Date: 2007/07/06 $ */
/*
** Copyright (c) 2000-2006 PIXAR.  All rights reserved.  This program or
** documentation contains proprietary confidential information and trade
** secrets of PIXAR.  Reverse engineering of object code is prohibited.
** Use of copyright notice is precautionary and does not imply
** publication.
**
**                      RESTRICTED RIGHTS NOTICE
**
** Use, duplication, or disclosure by the Government is subject to the
** following restrictions:  For civilian agencies, subparagraphs (a) through
** (d) of the Commercial Computer Software--Restricted Rights clause at
** 52.227-19 of the FAR; and, for units of the Department of Defense, DoD
** Supplement to the FAR, clause 52.227-7013 (c)(1)(ii), Rights in
** Technical Data and Computer Software.
**
** Pixar Animation Studios
** 1200 Park Ave.
** Emeryville, CA  94608
*/
/*
 *	RenderMan Interface Standard Include File
 */

#ifndef RI_H
#define RI_H

#ifndef DLLIMPORT
#if defined(_WIN32) || defined(_WINDOWS)
#ifdef DLL 
#define DLLIMPORT __declspec(dllimport)
#else
#define DLLIMPORT
#endif /* DLL */
#else
#define DLLIMPORT
#endif 
#endif

#ifdef  __cplusplus
extern "C" {
#endif

	/* Definitions of Abstract Types used in RI */

typedef short	 RtBoolean;
typedef float	 RtFloat;
typedef int	 RtInt;
typedef char	*RtToken;

typedef RtFloat	 RtColor[3];
typedef RtFloat	 RtPoint[3];
typedef RtFloat	 RtVector[3];
typedef RtFloat	 RtNormal[3];
typedef RtFloat	 RtHpoint[4];
typedef RtFloat	 RtMatrix[4][4];
typedef RtFloat	 RtBasis[4][4];
typedef RtFloat	 RtBound[6];
typedef RtFloat  RtInterval[2];
typedef void    *RtVolumeHandle;
typedef char	*RtString;

typedef void	*RtPointer;
/* ANSI spec says we can't do 'typedef void RtVoid' here */
#define RtVoid	void
typedef	RtFloat	(*RtFilterFunc)(RtFloat, RtFloat, RtFloat, RtFloat);
typedef RtVoid  (*RtErrorHandler)(RtInt, RtInt, char *);

typedef RtVoid (*RtProcSubdivFunc)(RtPointer, RtFloat);
typedef RtVoid (*RtProcFreeFunc)(RtPointer);
typedef RtVoid (*RtArchiveCallback)(RtToken, char *, ...);

typedef RtPointer RtObjectHandle;
typedef RtPointer RtLightHandle;
typedef RtPointer RtContextHandle;
typedef RtString  RtArchiveHandle;
typedef RtString  RtShaderHandle;
    
	/* Extern Declarations for Predefined RI Data Structures */

#define RI_FALSE	0
#define RI_TRUE		(! RI_FALSE)
#define RI_INFINITY	1.0e38
#define RI_EPSILON	1.0e-10
#define RI_NULL		((RtToken)0)

DLLIMPORT extern RtToken	RI_FRAMEBUFFER, RI_FILE;
DLLIMPORT extern RtToken	RI_RGB, RI_RGBA, RI_RGBZ, RI_RGBAZ, RI_A, RI_Z, RI_AZ;
DLLIMPORT extern RtToken  	RI_DEEPSHADOWERROR;
DLLIMPORT extern RtToken 	RI_ADDCOVERAGE;
DLLIMPORT extern RtToken	RI_I;
DLLIMPORT extern RtToken	RI_RGBI, RI_RGBAI, RI_RGBZI, RI_RGBAZI, RI_AI, RI_ZI, RI_AZI;
DLLIMPORT extern RtToken	RI_PERSPECTIVE, RI_ORTHOGRAPHIC;
DLLIMPORT extern RtToken	RI_HIDDEN, RI_PAINT, RI_DEPTHFILTER, RI_PHOTON;
DLLIMPORT extern RtToken	RI_CONSTANT, RI_SMOOTH;
DLLIMPORT extern RtToken  	RI_ORIGIN;
DLLIMPORT extern RtToken  	RI_FLATNESS, RI_MOTIONFACTOR, RI_FOCUSFACTOR, RI_OLDMOTIONFACTOR, 
				RI_TRIMDEVIATION, RI_FOV;
DLLIMPORT extern RtToken	RI_AMBIENTLIGHT, RI_POINTLIGHT, RI_DISTANTLIGHT, RI_SPOTLIGHT;
DLLIMPORT extern RtToken	RI_INTENSITY, RI_LIGHTCOLOR, RI_FROM, RI_TO, RI_CONEANGLE,
				RI_CONEDELTAANGLE, RI_BEAMDISTRIBUTION;
DLLIMPORT extern RtToken	_RI_SHADERINSTANCEID;
DLLIMPORT extern RtToken	RI_MATTE, RI_METAL, RI_SHINYMETAL;
DLLIMPORT extern RtToken	RI_PLASTIC, RI_PAINTEDPLASTIC;
DLLIMPORT extern RtToken	RI_KA, RI_KD, RI_KS, RI_ROUGHNESS, RI_SPECULARCOLOR;
DLLIMPORT extern RtToken	RI_KR, RI_TEXTURENAME;
DLLIMPORT extern RtToken	RI_DEPTHCUE, RI_FOG, RI_BUMPY;
DLLIMPORT extern RtToken	RI_MINDISTANCE, RI_MAXDISTANCE, RI_BACKGROUND, RI_DISTANCE;
DLLIMPORT extern RtToken	RI_AMPLITUDE;

DLLIMPORT extern RtToken	RI_RASTER, RI_SCREEN, RI_CAMERA, RI_FRAME, RI_WORLD, RI_OBJECT;
DLLIMPORT extern RtToken        RI_FRAMECAMERA, RI_WORLDCAMERA;
DLLIMPORT extern RtToken	RI_INSIDE, RI_OUTSIDE, RI_LH, RI_RH;
DLLIMPORT extern RtToken	RI_P, RI_PZ, RI_PW, RI_N, RI_NG, RI_NP, RI_CS, RI_OS, RI_CI, RI_OI,
		RI_S, RI_T, RI_ST;
DLLIMPORT extern RtToken	RI_MAXSPECULARDEPTH, RI_MAXDIFFUSEDEPTH;/*ray*/
DLLIMPORT extern RtToken	RI_IMPORTANCETHRESHOLD; /* for ray tracing */
DLLIMPORT extern RtToken	RI_DISPLACEMENTS, RI_BIAS, RI_SAMPLEMOTION; /* for ray tracing*/
DLLIMPORT extern RtToken	RI_ATMOSPHERES; /* for ray tracing*/
DLLIMPORT extern RtToken	RI_DPDU, RI_DPDV; /* for ray tracing */
DLLIMPORT extern RtToken	RI_ESTIMATOR; /* for globillum and caustics */
DLLIMPORT extern RtToken	RI_SHADINGMODEL; /* for photon tracing */
DLLIMPORT extern RtToken	RI_GLOBALMAP; /* for global illum */
DLLIMPORT extern RtToken	RI_CAUSTICMAP; /* for caustics */
DLLIMPORT extern RtToken	RI_MAXERROR, RI_MAXPIXELDIST; /* irrad cache */
DLLIMPORT extern RtToken	RI_FORCEDSAMPLING; /* irrad cache */
DLLIMPORT extern RtToken	RI_FILENAME; /* for ptcloud filename attrib. */
DLLIMPORT extern RtToken	RI_HANDLE, RI_FILEMODE; /* irradiance cache */
DLLIMPORT extern RtToken	RI_BACKFACING, RI_FRUSTUM; /* cull */
DLLIMPORT extern RtToken	RI_BILINEAR, RI_BICUBIC;
DLLIMPORT extern RtToken	RI_LINEAR, RI_CUBIC;
DLLIMPORT extern RtToken	RI_PRIMITIVE, RI_INTERSECTION, RI_UNION, RI_DIFFERENCE;
DLLIMPORT extern RtToken	RI_PERIODIC, RI_NONPERIODIC, RI_CLAMP, RI_BLACK;
DLLIMPORT extern RtToken	RI_IGNORE, RI_PRINT, RI_ABORT, RI_HANDLER;
DLLIMPORT extern RtToken	RI_COMMENT, RI_STRUCTURE, RI_VERBATIM;
DLLIMPORT extern RtToken	RI_ID, RI_IDENTIFIER, RI_NAME, RI_SHADINGGROUP;
DLLIMPORT extern RtToken	RI_WIDTH, RI_CONSTANTWIDTH;


DLLIMPORT extern RtToken 	RI_MINWIDTH, RI_CLAMPWIDTH;


/* Added for 4.0 compile
DLLIMPORT extern RtToken	RI_DEVIATION, RI_RASTER, RI_TESSELATION;
DLLIMPORT extern RtToken  RI_TRIMCURVE, RI_PARAMETRIC;
*/

DLLIMPORT extern RtToken 	RI_QUANTIZE, RI_DITHER, RI_FILTER, RI_FILTERWIDTH;
DLLIMPORT extern RtToken	RI_REMAP;
DLLIMPORT extern RtToken 	RI_REPELFILE, RI_REPELPARAMS;
DLLIMPORT extern RtToken 	RI_HANDLEID;
DLLIMPORT extern RtToken	RI_THRESHOLD;
DLLIMPORT extern RtBasis	RiBezierBasis, RiBSplineBasis, RiCatmullRomBasis,
		RiHermiteBasis, RiPowerBasis;
DLLIMPORT extern RtToken	RI_CATMARK, RI_LOOP;
    
#define RI_BEZIERSTEP		((RtInt)3)
#define RI_BSPLINESTEP		((RtInt)1)
#define RI_CATMULLROMSTEP	((RtInt)1)
#define RI_HERMITESTEP		((RtInt)2)
#define RI_POWERSTEP		((RtInt)4)

DLLIMPORT extern RtInt	RiLastError;


	/* Declarations of All the RenderMan Interface Subroutines */


DLLIMPORT extern RtFloat	RiGaussianFilter(RtFloat x, RtFloat y,
			RtFloat xwidth, RtFloat ywidth);
DLLIMPORT extern RtFloat	RiBoxFilter(RtFloat x, RtFloat y,
			RtFloat xwidth, RtFloat ywidth);
DLLIMPORT extern RtFloat	RiTriangleFilter(RtFloat x, RtFloat y,
			RtFloat xwidth, RtFloat ywidth);
DLLIMPORT extern RtFloat	RiCatmullRomFilter(RtFloat x, RtFloat y,
			RtFloat xwidth, RtFloat ywidth);
DLLIMPORT extern RtFloat	RiSeparableCatmullRomFilter(RtFloat x, RtFloat y,
			RtFloat xwidth, RtFloat ywidth);
DLLIMPORT extern RtFloat	RiBlackmanHarrisFilter(RtFloat x, RtFloat y,
			RtFloat xwidth, RtFloat ywidth);
DLLIMPORT extern RtFloat	RiLanczosFilter(RtFloat x, RtFloat y,
			RtFloat xwidth, RtFloat ywidth);
DLLIMPORT extern RtFloat	RiMitchellFilter(RtFloat x, RtFloat y,
			RtFloat xwidth, RtFloat ywidth);
DLLIMPORT extern RtFloat	RiSincFilter(RtFloat x, RtFloat y,
			RtFloat xwidth, RtFloat ywidth);
DLLIMPORT extern RtFloat	RiBesselFilter(RtFloat x, RtFloat y,
			RtFloat xwidth, RtFloat ywidth);
DLLIMPORT extern RtFloat	RiDiskFilter(RtFloat x, RtFloat y,
			RtFloat xwidth, RtFloat ywidth);
DLLIMPORT extern RtVoid	RiErrorIgnore(RtInt code, RtInt severity, char *msg);
DLLIMPORT extern RtVoid	RiErrorPrint(RtInt code, RtInt severity, char *msg);
DLLIMPORT extern RtVoid	RiErrorPrintOnce(RtInt code, RtInt severity, char *msg);
DLLIMPORT extern RtVoid	RiErrorCondAbort(RtInt code, RtInt severity, char *msg);
DLLIMPORT extern RtVoid	RiErrorAbort(RtInt code, RtInt severity, char *msg);
DLLIMPORT extern RtVoid   RiErrorCleanup(void);
DLLIMPORT extern RtVoid	RiProcDelayedReadArchive(RtPointer data, RtFloat detail);
DLLIMPORT extern RtVoid	RiProcRunProgram(RtPointer data, RtFloat detail);
DLLIMPORT extern RtVoid	RiProcDynamicLoad(RtPointer data, RtFloat detail);

DLLIMPORT extern RtContextHandle RiGetContext(void);
DLLIMPORT extern RtVoid RiContext(RtContextHandle);

DLLIMPORT extern RtToken
	RiDeclare(char *name, char *declaration);

DLLIMPORT extern RtVoid
	RiBegin(RtToken name),
	RiEnd(void),
	RiFrameBegin(RtInt frame),
	RiFrameEnd(void),
	RiWorldBegin(void),
	RiWorldEnd(void);

DLLIMPORT extern RtVoid
	RiFormat(RtInt xres, RtInt yres, RtFloat aspect),
	RiFrameAspectRatio(RtFloat aspect),
	RiScreenWindow(RtFloat left, RtFloat right, RtFloat bot, RtFloat top),
	RiCropWindow(RtFloat xmin, RtFloat xmax, RtFloat ymin, RtFloat ymax),
	RiProjection(RtToken name, ...),
	RiProjectionV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiClipping(RtFloat hither, RtFloat yon),
	RiClippingPlane(RtFloat Nx, RtFloat Ny, RtFloat Nz, RtFloat Px, 
                        RtFloat Py, RtFloat Pz),	
	RiDepthOfField(RtFloat fstop, RtFloat focallength, RtFloat focaldistance),
	RiShutter(RtFloat min, RtFloat max);

DLLIMPORT extern RtVoid
	RiPixelVariance(RtFloat variation),
	RiPixelSamples(RtFloat xsamples, RtFloat ysamples),
	RiPixelFilter(RtFilterFunc filterfunc, RtFloat xwidth, RtFloat ywidth),
	RiExposure(RtFloat gain, RtFloat gamma),
	RiImager(RtToken name, ...),
	RiImagerV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiQuantize(RtToken type, RtInt one, RtInt min, RtInt max, RtFloat ampl),
	RiDisplay(char *name, RtToken type, RtToken mode, ...),
	RiDisplayV(char *name, RtToken type, RtToken mode,
			RtInt n, RtToken tokens[], RtPointer parms[]);

/* OBSOLETE call: see RiPixelVariance */
DLLIMPORT extern RtVoid
	RiPixelFidelity(RtFloat variation);

DLLIMPORT extern RtVoid
	RiHider(RtToken type, ...),
	RiHiderV(RtToken type, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiColorSamples(RtInt n, RtFloat nRGB[], RtFloat RGBn[]),
	RiRelativeDetail(RtFloat relativedetail),
	RiOption(RtToken name, ...),
	RiOptionV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern RtVoid
	RiAttributeBegin(void),
	RiAttributeEnd(void),
	RiColor(RtColor color),
	RiOpacity(RtColor color),
	RiTextureCoordinates(RtFloat s1, RtFloat t1, RtFloat s2, RtFloat t2,
				RtFloat s3, RtFloat t3, RtFloat s4, RtFloat t4);

DLLIMPORT extern RtLightHandle
	RiLightSource(RtToken name, ...),
	RiLightSourceV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiAreaLightSource(RtToken name, ...),
	RiAreaLightSourceV(RtToken name,
				RtInt n, RtToken tokens[], RtPointer parms[]);
DLLIMPORT extern RtVoid
	RiIlluminate(RtLightHandle light, RtBoolean onoff),
	RiShader(RtToken name, RtToken handle, ...),
	RiShaderV(RtToken name, RtToken handle, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiSurface(RtToken name, ...),
	RiSurfaceV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiAtmosphere(RtToken name, ...),
	RiAtmosphereV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiInterior(RtToken name, ...),
	RiInteriorV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiExterior(RtToken name, ...),
	RiExteriorV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiShadingRate(RtFloat size),
	RiShadingInterpolation(RtToken type),
	RiMatte(RtBoolean onoff);

DLLIMPORT extern RtVoid
	RiBound(RtBound bound),
	RiDetail(RtBound bound),
	RiDetailRange(RtFloat minvis, RtFloat lowtran, RtFloat uptran,
			RtFloat maxvis),
	RiGeometricApproximation(RtToken type, RtFloat value),
	RiOrientation(RtToken orientation),
	RiReverseOrientation(void),
	RiSides(RtInt sides);

DLLIMPORT extern RtVoid
	RiIdentity(void),
	RiTransform(RtMatrix transform),
	RiConcatTransform(RtMatrix transform),
	RiPerspective(RtFloat fov),
	RiTranslate(RtFloat dx, RtFloat dy, RtFloat dz),
	RiRotate(RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz),
	RiScale(RtFloat sx, RtFloat sy, RtFloat sz),
	RiSkew(RtFloat angle, RtFloat dx1, RtFloat dy1, RtFloat dz1,
		RtFloat dx2, RtFloat dy2, RtFloat dz2),
	RiDeformation(RtToken name, ...),
	RiDeformationV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiDisplacement(RtToken name, ...),
	RiDisplacementV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiCoordinateSystem(RtToken space),
	RiScopedCoordinateSystem(RtToken space),
	RiCoordSysTransform(RtToken space);
DLLIMPORT extern RtPoint
	*RiTransformPoints(RtToken fromspace, RtToken tospace, RtInt n,
			   RtPoint points[]);
DLLIMPORT extern RtVoid
	RiTransformBegin(void),
	RiTransformEnd(void);

DLLIMPORT extern RtVoid
	RiAttribute(RtToken name, ...),
	RiAttributeV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern RtVoid
	RiPolygon(RtInt nverts, ...),
	RiPolygonV(RtInt nverts, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiGeneralPolygon(RtInt nloops, RtInt nverts[], ...),
	RiGeneralPolygonV(RtInt nloops, RtInt nverts[],
				RtInt n, RtToken tokens[], RtPointer parms[]),
	RiPointsPolygons(RtInt npolys, RtInt nverts[], RtInt verts[], ...),
	RiPointsPolygonsV(RtInt npolys, RtInt nverts[], RtInt verts[],
				RtInt n, RtToken tokens[], RtPointer parms[]),
	RiPointsGeneralPolygons(RtInt npolys, RtInt nloops[], RtInt nverts[],
				RtInt verts[], ...),
	RiPointsGeneralPolygonsV(RtInt npolys, RtInt nloops[], RtInt nverts[],
			RtInt verts[], RtInt n, RtToken tokens[], RtPointer parms[]),
	RiBasis(RtBasis ubasis, RtInt ustep, RtBasis vbasis, RtInt vstep),
	RiPatch(RtToken type, ...),
	RiPatchV(RtToken type, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiPatchMesh(RtToken type, RtInt nu, RtToken uwrap,
			RtInt nv, RtToken vwrap, ...),
	RiPatchMeshV(RtToken type, RtInt nu, RtToken uwrap,
			RtInt nv, RtToken vwrap,
			RtInt n, RtToken tokens[], RtPointer parms[]),
	RiNuPatch(RtInt nu, RtInt uorder, RtFloat uknot[], RtFloat umin, RtFloat umax,
			RtInt nv, RtInt vorder, RtFloat vknot[], RtFloat vmin,
			RtFloat vmax, ...),
	RiNuPatchV(RtInt nu, RtInt uorder, RtFloat uknot[], RtFloat umin,
			RtFloat umax, RtInt nv, RtInt vorder, RtFloat vknot[],
			RtFloat vmin, RtFloat vmax,
			RtInt n, RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern RtVoid
	RiSphere(RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat tmax, ...),
	RiSphereV(RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat tmax,
			RtInt n, RtToken tokens[], RtPointer parms[]),
	RiCone(RtFloat height, RtFloat radius, RtFloat tmax, ...),
	RiConeV(RtFloat height, RtFloat radius, RtFloat tmax,
			RtInt n, RtToken tokens[], RtPointer parms[]),
	RiCylinder(RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat tmax, ...),
	RiCylinderV(RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat tmax,
			RtInt n, RtToken tokens[], RtPointer parms[]),
	RiHyperboloid(RtPoint point1, RtPoint point2, RtFloat tmax, ...),
	RiHyperboloidV(RtPoint point1, RtPoint point2, RtFloat tmax,
			RtInt n, RtToken tokens[], RtPointer parms[]),
	RiParaboloid(RtFloat rmax, RtFloat zmin, RtFloat zmax, RtFloat tmax, ...),
	RiParaboloidV(RtFloat rmax, RtFloat zmin, RtFloat zmax, RtFloat tmax,
			RtInt n, RtToken tokens[], RtPointer parms[]),
	RiDisk(RtFloat height, RtFloat radius, RtFloat tmax, ...),
	RiDiskV(RtFloat height, RtFloat radius, RtFloat tmax,
			RtInt n, RtToken tokens[], RtPointer parms[]),
	RiTorus(RtFloat majrad, RtFloat minrad, RtFloat phimin, RtFloat phimax,
			RtFloat tmax, ...),
	RiTorusV(RtFloat majrad, RtFloat minrad, RtFloat phimin, RtFloat phimax,
			RtFloat tmax, RtInt n, RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern RtVoid RiBlobby(RtInt nleaf, RtInt ncode, RtInt code[], 
		       RtInt nflt, RtFloat flt[],
		       RtInt nstr, RtToken str[], ...);
DLLIMPORT extern RtVoid RiBlobbyV(RtInt nleaf, RtInt ncode, RtInt  code[], 
			RtInt nflt, RtFloat flt[],
			RtInt nstr, RtToken str[],
			RtInt n , RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern RtVoid
	RiCurves(RtToken type, RtInt ncurves,
		 RtInt nvertices[], RtToken wrap, ...),
	RiCurvesV(RtToken type, RtInt ncurves, RtInt nvertices[], RtToken wrap,
		  RtInt n, RtToken tokens[], RtPointer parms[]),
	RiPoints(RtInt nverts,...),
	RiPointsV(RtInt nverts, RtInt n, RtToken tokens[], RtPointer parms[]),

	RiSubdivisionMesh(RtToken mask, RtInt nf, RtInt nverts[],
			  RtInt verts[],
			  RtInt ntags, RtToken tags[], RtInt numargs[],
			  RtInt intargs[], RtFloat floatargs[], ...),
	RiSubdivisionMeshV(RtToken mask, RtInt nf, RtInt nverts[],
			   RtInt verts[], RtInt ntags, RtToken tags[],
			   RtInt nargs[], RtInt intargs[],
			   RtFloat floatargs[], RtInt n,
			   RtToken tokens[], RtPointer *parms),
	RiHierarchicalSubdivisionMesh(RtToken mask, RtInt nf, RtInt nverts[],
			  RtInt verts[],
			  RtInt ntags, RtToken tags[], RtInt numargs[],
			  RtInt intargs[], RtFloat floatargs[], RtToken stringargs[], ...),
	RiHierarchicalSubdivisionMeshV(RtToken mask, RtInt nf, RtInt nverts[],
			   RtInt verts[], RtInt ntags, RtToken tags[],
			   RtInt nargs[], RtInt intargs[],
			   RtFloat floatargs[], RtToken stringargs[], RtInt n,
			   RtToken tokens[], RtPointer *parms);

DLLIMPORT extern RtVoid
	RiTrimCurve(RtInt nloops, RtInt ncurves[], RtInt order[], RtFloat knot[],
			RtFloat min[], RtFloat max[], RtInt n[],
			RtFloat u[], RtFloat v[], RtFloat w[]),
	RiProcedural(RtPointer data, RtBound bound,
			RtVoid (*subdivfunc)(RtPointer, RtFloat),
			RtVoid (*freefunc)(RtPointer)),
	RiGeometry(RtToken type, ...),
	RiGeometryV(RtToken type, RtInt n, RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern RtVoid
	RiSolidBegin(RtToken operation),
	RiSolidEnd(void);
DLLIMPORT extern RtObjectHandle
	RiObjectBegin(void);
DLLIMPORT extern RtVoid
	RiObjectEnd(void),
	RiObjectInstance(RtObjectHandle handle),
	RiMotionBegin(RtInt n, ...),
	RiMotionBeginV(RtInt n, RtFloat times[]),
	RiMotionEnd(void);

DLLIMPORT extern RtVoid
	RiResource(RtToken handle, RtToken type, ...),
	RiResourceV(RtToken handle, RtToken type,
		RtInt n, RtToken tokens[], RtPointer parms[]),
	RiResourceBegin(void),
	RiResourceEnd(void);
    

DLLIMPORT extern RtVoid
	RiMakeTexture(char *pic, char *tex, RtToken swrap, RtToken twrap,
		RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, ...),
	RiMakeTextureV(char *pic, char *tex, RtToken swrap, RtToken twrap,
		RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth,
		RtInt n, RtToken tokens[], RtPointer parms[]),
	RiMakeBump(char *pic, char *tex, RtToken swrap, RtToken twrap,
		RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, ...),
	RiMakeBumpV(char *pic, char *tex, RtToken swrap, RtToken twrap,
		RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth,
		RtInt n, RtToken tokens[], RtPointer parms[]),
	RiMakeLatLongEnvironment(char *pic, char *tex, RtFilterFunc filterfunc,
		RtFloat swidth, RtFloat twidth, ...),
	RiMakeLatLongEnvironmentV(char *pic, char *tex, RtFilterFunc filterfunc,
		RtFloat swidth, RtFloat twidth,
		RtInt n, RtToken tokens[], RtPointer parms[]),
	RiMakeCubeFaceEnvironment(char *px, char *nx, char *py, char *ny,
		char *pz, char *nz, char *tex, RtFloat fov,
		RtFilterFunc filterfunc, RtFloat swidth, RtFloat ywidth, ...),
	RiMakeCubeFaceEnvironmentV(char *px, char *nx, char *py, char *ny,
		char *pz, char *nz, char *tex, RtFloat fov,
		RtFilterFunc filterfunc, RtFloat swidth, RtFloat ywidth,
		RtInt n, RtToken tokens[], RtPointer parms[]),
	RiMakeShadow(char *pic, char *tex, ...),
	RiMakeShadowV(char *pic, char *tex,
		      RtInt n, RtToken tokens[], RtPointer parms[]),
        RiMakeBrickMap(int nptcs, char **ptcs, char *bkm, ...),
	RiMakeBrickMapV(int nptcs, char **ptcs, char *bkm,
			RtInt n, RtToken tokens[], RtPointer parms[]),
	RiSystem(char *cmdstring);

DLLIMPORT extern RtVoid
	RiErrorHandler(RtErrorHandler handler);

DLLIMPORT extern RtVoid
	RiSynchronize(RtToken);

DLLIMPORT extern RtVoid
	RiArchiveRecord(RtToken type, char *format, ...),
	RiReadArchive(RtToken name, RtVoid (*callback)(RtToken,char*,...), ...),
	RiReadArchiveV(RtToken name, RtVoid (*callback)(RtToken,char*,...),
		RtInt n, RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern RtArchiveHandle
	RiArchiveBegin(RtToken name, ...),
    	RiArchiveBeginV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);

DLLIMPORT extern RtVoid
	RiArchiveEnd(void);

DLLIMPORT extern RtVoid
	RiIfBegin(char *expr, ...),
	RiIfBeginV(char *expr, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiElseIf(char *expr, ...),
	RiElseIfV(char *expr, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiElse(void),
	RiIfEnd(void);


/* OBSOLETE call: see RiErrorHandler */
DLLIMPORT extern RtVoid
	RiErrorMode(RtToken mode, RtErrorHandler handler);

DLLIMPORT extern RtVoid
	RiDisplayChannel(RtToken channel, ...),
	RiDisplayChannelV(RtToken channel, RtInt n, RtToken tokens[], RtPointer parms[]);


DLLIMPORT extern RtVoid
    	RiCamera(RtToken name, ...),
    	RiCameraV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);
    
#ifdef  __cplusplus
}
#endif


/*
	Error Codes

	 1 - 10		System and File Errors
	11 - 20		Program Limitations
	21 - 40		State Errors
	41 - 60		Parameter and Protocol Errors
	61 - 80		Execution Errors
*/


#define RIE_NOERROR	((RtInt)0)

#define RIE_NOMEM	((RtInt)1)	/* Out of memory */
#define RIE_SYSTEM	((RtInt)2)	/* Miscellaneous system error */
#define RIE_NOFILE	((RtInt)3)	/* File nonexistent */
#define RIE_BADFILE	((RtInt)4)	/* Bad file format */
#define RIE_VERSION	((RtInt)5)	/* File version mismatch */
#define RIE_DISKFULL	((RtInt)6)	/* Target disk is full */

#define RIE_INCAPABLE	((RtInt)11)	/* Optional RI feature */
#define RIE_UNIMPLEMENT	((RtInt)12)	/* Unimplemented feature */
#define RIE_LIMIT	((RtInt)13)	/* Arbitrary program limit */
#define RIE_BUG		((RtInt)14)	/* Probably a bug in renderer */

#define RIE_NOTSTARTED	((RtInt)23)	/* RiBegin not called */
#define RIE_NESTING	((RtInt)24)	/* Bad begin-end nesting */
#define RIE_NOTOPTIONS	((RtInt)25)	/* Invalid state for options */
#define RIE_NOTATTRIBS	((RtInt)26)	/* Invalid state for attribs */
#define RIE_NOTPRIMS	((RtInt)27)	/* Invalid state for primitives */
#define RIE_ILLSTATE	((RtInt)28)	/* Other invalid state */
#define RIE_BADMOTION	((RtInt)29)	/* Badly formed motion block */
#define RIE_BADSOLID	((RtInt)30)	/* Badly formed solid block */

#define RIE_BADTOKEN	((RtInt)41)	/* Invalid token for request */
#define RIE_RANGE	((RtInt)42)	/* Parameter out of range */
#define RIE_CONSISTENCY	((RtInt)43)	/* Parameters inconsistent */
#define RIE_BADHANDLE	((RtInt)44)	/* Bad object/light handle */
#define RIE_NOSHADER	((RtInt)45)	/* Can't load requested shader */
#define RIE_MISSINGDATA	((RtInt)46)	/* Required parameters not provided */
#define RIE_SYNTAX	((RtInt)47)	/* Declare type syntax error */

#define RIE_SKIPPING	((RtInt)51)	/* Inactive 'If' branch, no rendering */

#define RIE_MATH	((RtInt)61)	/* Zerodivide, noninvert matrix, etc. */

	/* Error severity levels */

#define RIE_INFO	((RtInt)0)	/* Rendering stats and other info */
#define RIE_WARNING	((RtInt)1)	/* Something seems wrong, maybe okay */
#define RIE_ERROR	((RtInt)2)	/* Problem. Results may be wrong */
#define RIE_SEVERE	((RtInt)3)	/* So bad you should probably abort */

#endif /* RI_H */

#ifdef RI_H_STANDARD_FACE
#include <RiStandardFace.h>
#endif

