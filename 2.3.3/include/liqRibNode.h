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

#ifndef liqRibNode_H
#define liqRibNode_H

/* ______________________________________________________________________
**
** Liquid Rib Node Header File
** ______________________________________________________________________
*/

// Standard headers
#include <map>
// Boost headers
#include <boost/shared_ptr.hpp>
// Maya headers
#include <maya/MColor.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MDagPath.h>
#include <maya/MObjectArray.h>
// Liquid headers
#include <liquid.h>
#include <liqRibData.h>
#include <liqRibObj.h>
//#include <liqTokenPointer.h>
//#include <liqRibNode.h>

//enum transmissions {TRANS, OPAQUE, OS, SHADER};

class liqRibNode;
typedef boost::shared_ptr< liqRibNode > liqRibNodePtr;

enum AttributeState{
	//not exist
	AS_NotEXist = -1,
	//exist
		AS_NotConnected =-4,
		//connected
			AS_ConnectedAsDes = -2,
			AS_ConnectedAsSrc = -3,

	AS_Num
};

class liqRibNode {
  public:


    explicit liqRibNode( liqRibNodePtr instanceOfNode = liqRibNodePtr(),
                const MString instanceOfNodeStr = "" );
    virtual ~liqRibNode();

    void set( const MDagPath &, int, ObjectType objType, int particleId = -1 );


    liqRibNodePtr      next;
    MString            name;

    AnimType           matXForm;
    AnimType           bodyXForm;

    liqRibObjPtr       object( unsigned );
  //liqRibObj *        no;

    MDagPath&          path();
	const MDagPath&    path() const;
	MObject			   getTransformNode() const;
	MString			   getTransformNodeFullPath() const;
	unsigned int	   getChildrenCountOfTransformNode() const;
    MStringArray       getChildrenMsgOfTransformNode() const;

    MColor             color;
    MColor             opacity;
    bool               mayaMatteMode;
    bool               doubleSided;
    bool               reversedNormals;
    MString            shaderName;
    MString            dispName;
    MString            volumeName;
    MFnDependencyNode  assignedShadingGroup;
    MFnDependencyNode  assignedShader;
    MFnDependencyNode  assignedDisp;
    MFnDependencyNode  assignedVolume;

    void     writeUserAttributes();
    MObject  findShadingGroup( const MDagPath& path, ObjectType type );
    MObject  findShader( MObject& group );
    MObject  findDisp( MObject& group );
    MObject  findVolume( MObject& group );
//  void     getIgnoredLights( MObject& group, MObjectArray& lights );
    void     getLinkLights( MObjectArray& lights, bool exclusive );
    void     getSetLights( MObjectArray& lights );
    bool     getMatteMode( MObject& shader );
    bool     hasRibGen();
    void     doRibGen();
    RtBound  bound;
    RtBound  shadowBound;
    bool     doDef;    /* Used for per-object deformation blur */
    bool     doMotion;  /* Used for per-object transformation blur */

    bool     belongsToCsgOperation;

    MString  getInstanceStr() { return instanceStr; };
    bool     hasNObjects( unsigned n );
    bool     colorOverridden() { return overrideColor; };


    struct shading {
      float    shadingRate;
      bool     diceRasterOrient;
      MColor   color;
      MColor   opacity;
      bool     matte;
      bool     doubleShaded;
    } shading;


    struct trace {
      bool      sampleMotion;
      bool      displacements;
      float     bias;
      int       maxDiffuseDepth;
      int       maxSpecularDepth;
    } trace;



    struct visibility {
      bool      camera;
      bool      trace;
      bool      diffuse;
      bool      specular;
      bool      photon;
      bool      midpoint;
      bool      newtransmission;
      bool      subsurface;
      enum {
        TRANSMISSION_TRANSPARENT = 0,
        TRANSMISSION_OPAQUE      = 1,
        TRANSMISSION_OS          = 2,
        TRANSMISSION_SHADER      = 3
      } transmission;
    } visibility;

    struct hitmode {
      enum {
        CAMERA_HITMODE_PRIMITIVE  = 0,
        CAMERA_HITMODE_SHADER     = 1
      } camera;
      enum {
        DIFFUSE_HITMODE_PRIMITIVE  = 0,
        DIFFUSE_HITMODE_SHADER     = 1
      } diffuse;
      enum {
        SPECULAR_HITMODE_PRIMITIVE  = 0,
        SPECULAR_HITMODE_SHADER     = 1
      } specular;
      enum {
        TRANSMISSION_HITMODE_PRIMITIVE  = 0,
        TRANSMISSION_HITMODE_SHADER     = 1
      } transmission;
    } hitmode;

    struct irradiance {
      float     shadingRate;
      int       nSamples;
      float     maxError;
      float     maxPixelDist;
      MString   handle;
      enum {
        FILEMODE_NONE = 0,
        FILEMODE_READ = 1,
        FILEMODE_WRITE = 2,
        FILEMODE_READ_WRITE = 3
      } fileMode;
    } irradiance;

    struct photon {
      MString   globalMap;
      MString   causticMap;
      enum {
        SHADINGMODEL_MATTE = 0,
        SHADINGMODEL_GLASS = 1,
        SHADINGMODEL_WATER = 2,
        SHADINGMODEL_CHROME = 3,
        SHADINGMODEL_TRANSPARENT = 4,
        SHADINGMODEL_DIALECTRIC = 5
      } shadingModel;
      int estimator;
    } photon;

    struct motion {
      bool    transformationBlur;
      bool    deformationBlur;
      int     samples;
      float   factor;
    } motion;

    struct rib {
      MString box;
      MString generator;
      MString readArchive;
      MString delayedReadArchive;
	  bool hasBox(){
		  return ( box!="" && box!="-" );
	  }
	  bool hasGenerator(){
		  return ( generator!="" && generator!="-" );
	  }
	  bool hasReadArchive(){
		  return ( readArchive!="" && readArchive!="-" );
	  }
	  bool hasDelayedReadArchive(){
		  return ( delayedReadArchive!="" && delayedReadArchive!="-" );
	  }
    } rib;

    struct shadowRib {
      MString box;
      MString generator;
      MString readArchive;
      MString delayedReadArchive;
    } shadowRib;

    struct grouping {
		std::string membership;
    } grouping;

	struct delightSSS {
		bool doScatter;
		float  shadingRate;
    MString groupName;
    MColor  scattering;
    MColor  absorption;
    float  refraction;
    float  scale;
    MColor  meanfreepath;
    MColor  reflectance;
    MString referencecamera;
    } delightSSS;

    struct subdivMesh {
      bool  render;
      bool  interpBounday;
      bool  edgeCreasing;
    } subdivMesh;

    struct curve {
      bool  render;
      float constantwidth;
    } curve;

	struct strategy{
		MString strategy_;
		MString volumeIntersectionStrategy;
		float   volumeIntersectionPriority;
	} strategy;

	struct trimcurve{
		enum{
			INSIDE  = 0,
			OUTSIDE = 1
		} sense;
	} trimcurve;

	struct stitch{
		bool enable;
		bool traceenable;
		bool newgroup;
	} stitch;

	struct stochastic{
		int sigma;
		int pointfalloff;
	} stochastic;

	struct dice{
		bool binary;
		bool hair;
		//bool rasterorient;// see shading.diceRasterOrient
		enum {
			PLANAR_PROJECTION    = 0,
			SPHERICAL_PROJECTION = 1
		} strategy;
		enum {
			WORLD_CAMERA = 0,
			FRAME_CAMERA = 1
		} referencecamera;
	} dice;

	struct derivatives{
		bool centered;
		bool extrapolate;
	} derivatives;

	struct procedural{
		MString attribute;
	} procedural;

    bool    instanceInheritPPColor;
    bool    invisible;
    bool    ignoreShapes;

	std::map<const std::string, liqTokenPointer > tokenPointerMap;


private:

    MDagPath    DagPath;
	std::vector< liqRibObjPtr > objects;
    liqRibNodePtr instance;
    MString     instanceStr;
    MString     ribGenName;
    bool        hasRibGenAttr;
    bool        overrideColor;
    void        parseVectorAttributes( const MFnDependencyNode&, const MStringArray&, const ParameterType& );
	AttributeState     getColor( MObject& shader, MColor& color );
	AttributeState     getOpacity( MObject& shader, MColor& opacity );


private:
	liqRibNode(const liqRibNode&);
	liqRibNode& operator=(const liqRibNode&);
};

#endif
