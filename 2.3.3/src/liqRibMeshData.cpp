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

/* ______________________________________________________________________
**
** Liquid Rib Mesh Data Source
** ______________________________________________________________________
*/


// Renderman Headers
//extern "C" {
#include "ri_interface.h"
//}

// Maya headers
#include <maya/MPlug.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MGlobal.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MIntArray.h>
#include <maya/MFnMesh.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MMatrix.h>
#include <maya/MFloatPointArray.h>

// Liquid headers
#include <liquid.h>
#include <liqGlobalHelpers.h>
#include <liqRibMeshData.h>

// Standard/Boost headers
#include <vector>
#include <iostream>
#include <boost/scoped_array.hpp>
#include <boost/shared_array.hpp>

using namespace boost;
using namespace std;

extern int debugMode;
extern bool liqglo_outputMeshUVs;

/** Create a RIB compatible representation of a Maya polygon mesh.
 */
liqRibMeshData::liqRibMeshData( MObject mesh )
: numFaces( 0 ),
  numPoints ( 0 ),
  numNormals ( 0 ),
  nverts(),
  verts(),
  vertexParam(),
  normalParam()
{
  areaLight = false;
  LIQDEBUGPRINTF( "-> creating mesh\n" );
  MFnMesh fnMesh( mesh );
  objDagPath = fnMesh.dagPath();
  MStatus astatus;
  
  name = fnMesh.name();
  areaLight =( liquidGetPlugValue( fnMesh, "areaIntensity", areaIntensity, astatus ) == MS::kSuccess )? true : false ; 

  if ( areaLight ) 
  {
    MDagPath meshDagPath;
    meshDagPath = fnMesh.dagPath();
    MTransformationMatrix worldMatrix = meshDagPath.inclusiveMatrix();
    MMatrix worldMatrixM = worldMatrix.asMatrix();
    worldMatrixM.get( transformationMatrix );
  }

  numPoints = fnMesh.numVertices();
  numNormals = fnMesh.numNormals();

  // UV sets -------------------
  //
  const unsigned numSTs( fnMesh.numUVs() );
  const unsigned numUVSets( fnMesh.numUVSets() );
  MString currentUVSetName;
  MStringArray extraUVSetNames;
  fnMesh.getCurrentUVSetName( currentUVSetName );
  {
    MStringArray UVSetNames;
    fnMesh.getUVSetNames( UVSetNames );

    for ( unsigned i( 0 ); i<numUVSets; i++ ) 
      if ( UVSetNames[i] != currentUVSetName ) 
        extraUVSetNames.append( UVSetNames[i] );
  }

  numFaces = fnMesh.numPolygons();
  const unsigned numFaceVertices( fnMesh.numFaceVertices() );

	if ( numPoints < 1 )
	{
//		MGlobal::displayInfo( MString( "fnMesh: " ) + fnMesh.name() );
//		cerr << "Liquid : Could not export degenerate mesh '"<< fnMesh.fullPathName( &astatus ).asChar() << "'" << endl << flush;
		return;
	}

  unsigned face = 0;
  unsigned faceVertex = 0;
  unsigned count;
  unsigned vertex;
  unsigned normal;
  float S;
  float T;
  MPoint point;
  liqTokenPointer pointsPointerPair;
  liqTokenPointer normalsPointerPair;
  liqTokenPointer pFaceVertexSPointer;
  liqTokenPointer pFaceVertexTPointer;

  // Allocate memory and tokens
  numFaces = numFaces;
  nverts = shared_array< RtInt >( new RtInt[ numFaces ] );
  verts = shared_array< RtInt >( new RtInt[ numFaceVertices ] );

  pointsPointerPair.set( "P", rPoint, numPoints );
  pointsPointerPair.setDetailType( rVertex );

  if ( numNormals == numPoints ) 
  {
    normalsPointerPair.set( "N", rNormal, numPoints );
    normalsPointerPair.setDetailType( rVertex );
  } 
  else 
  {
    normalsPointerPair.set( "N", rNormal, numFaceVertices );
    normalsPointerPair.setDetailType( rFaceVarying );
  }

  std::vector<liqTokenPointer> UVSetsArray;
  UVSetsArray.reserve( 1 + extraUVSetNames.length() );

  if ( numSTs > 0 ) 
  {
    liqTokenPointer pFaceVertexPointerPair;

    pFaceVertexPointerPair.set( "st", rFloat, numFaceVertices, 2 );
    pFaceVertexPointerPair.setDetailType( rFaceVarying );

    UVSetsArray.push_back( pFaceVertexPointerPair );

    for ( unsigned j( 0 ); j<extraUVSetNames.length(); j++) 
    {
      liqTokenPointer pFaceVertexPointerPair;

      pFaceVertexPointerPair.set( extraUVSetNames[j].asChar(), rFloat, numFaceVertices, 2 );
      pFaceVertexPointerPair.setDetailType( rFaceVarying );

      UVSetsArray.push_back( pFaceVertexPointerPair );
    }

    if( liqglo_outputMeshUVs ) 
    {
      // Match MTOR, which also outputs face-varying STs as well for some reason - Paul
      // not anymore - Philippe
      pFaceVertexSPointer.set( "u", rFloat, numFaceVertices );
      pFaceVertexSPointer.setDetailType( rFaceVarying );

      pFaceVertexTPointer.set( "v", rFloat, numFaceVertices );
      pFaceVertexTPointer.setDetailType( rFaceVarying );
    }
  }

  vertexParam = pointsPointerPair.getTokenFloatArray();
  normalParam = normalsPointerPair.getTokenFloatArray();

  // Read the mesh from Maya
  MFloatVectorArray normals;
  fnMesh.getNormals( normals );

  for ( MItMeshPolygon polyIt ( mesh ); polyIt.isDone() == false; polyIt.next() ) 
  {
    count = polyIt.polygonVertexCount();
    nverts[face] = count;
    unsigned i = count;
	  
    // printf("poly count = %d\n", count );
    
    while( i )
    {
      --i;
      vertex = polyIt.vertexIndex( i );
      verts[faceVertex] = vertex;
      point = polyIt.point( i, MSpace::kObject );
      pointsPointerPair.setTokenFloat( vertex, point.x, point.y, point.z );
      normal = polyIt.normalIndex( i );

      if( numNormals == numPoints ) 
        normalsPointerPair.setTokenFloat( vertex, normals[normal].x, normals[normal].y, normals[normal].z );
      else 
        normalsPointerPair.setTokenFloat( faceVertex, normals[normal].x, normals[normal].y, normals[normal].z );

      if ( UVSetsArray.size() ) 
      {
        fnMesh.getPolygonUV( face, i, S, T );

        UVSetsArray[0].setTokenFloat( faceVertex, 0, S );
        UVSetsArray[0].setTokenFloat( faceVertex, 1, 1 - T );

        for ( unsigned j( 1 ); j <= extraUVSetNames.length(); j++ ) 
        {
          fnMesh.getPolygonUV( face, i, S, T, &extraUVSetNames[j] );

          UVSetsArray[j].setTokenFloat( faceVertex, 0, S );
          UVSetsArray[j].setTokenFloat( faceVertex, 1, 1 - T );
        }

        if( liqglo_outputMeshUVs ) 
        {
          // Match MTOR, which always outputs face-varying STs as well for some reason - Paul
          pFaceVertexSPointer.setTokenFloat( faceVertex, S );
          pFaceVertexTPointer.setTokenFloat( faceVertex, 1 - T );
        }
      }
      // printf( "[%d] faceVertex = %d  vertex = %d\n", i, faceVertex, vertex );

      ++faceVertex;
    }
    ++face;
  }
  // Add tokens to array and clean up after
  tokenPointerArray.push_back( pointsPointerPair );
  tokenPointerArray.push_back( normalsPointerPair );

  if( UVSetsArray.size() ) 
    tokenPointerArray.insert( tokenPointerArray.end(), UVSetsArray.begin(), UVSetsArray.end() );
  
  if( liqglo_outputMeshUVs ) 
  {
    tokenPointerArray.push_back( pFaceVertexSPointer );
    tokenPointerArray.push_back( pFaceVertexTPointer );
  }

  addAdditionalSurfaceParameters( mesh );
}

/**      Print data about this mesh.
 */
void liqRibMeshData::printMesh()
{
	int i;
    scoped_array< RtInt > nloops( new RtInt[ numFaces ] );
	unsigned numTokens( tokenPointerArray.size() );

	LIQDEBUGPRINTF("numFace %d \n", numFaces);
	LIQDEBUGPRINTF("nloops (%d) [ ", numFaces);
	for(i=0; i<numFaces; i++)
	{
		LIQDEBUGPRINTF(" %d", nloops[i]);
	}
	LIQDEBUGPRINTF("]\n");

	int nvertsSize = nverts.use_count();
	RtInt *nvertsPtr = nverts.get();
	LIQDEBUGPRINTF("nverts (%d) [ ", nvertsSize);
	for(i=0; i<nvertsSize; i++)
	{
		LIQDEBUGPRINTF(" %d", nvertsPtr[i]);
	}
	LIQDEBUGPRINTF("]\n");


	int vertsSize = verts.use_count();
	RtInt *vertsPtr = verts.get();
	LIQDEBUGPRINTF("nverts (%d) [ ", vertsSize);
	for(i=0; i<vertsSize; i++)
	{
		LIQDEBUGPRINTF(" %d", vertsPtr[i]);
	}
	LIQDEBUGPRINTF("]\n");

	LIQDEBUGPRINTF("numTokens (%d)\n", numTokens);
	LIQDEBUGPRINTF("\n");
	// print tokens & pointers
}


/**      Write the RIB for this mesh.
 */
void liqRibMeshData::write()
{
  if ( numPoints > 1 ) 
  {
    LIQDEBUGPRINTF( "-> writing mesh\n" );
    RtLightHandle handle = INVALID_LIGHT_INDEX;
    if ( areaLight ) 
    { // What happens if we're inside a motion block????? This whole approach of Liquid is flawed...
      LIQDEBUGPRINTF( "-> mesh is area light\n" );
      //	RiAttributeBegin();
      RtString ribname = const_cast< char* >( name.asChar() );
      RiAttribute( "identifier", "name", &ribname, RI_NULL );
      RtMatrix tmp;
      memcpy( tmp, transformationMatrix, sizeof( RtMatrix ) );
      RiTransform( tmp );

      handle = RiAreaLightSource( "arealight", "intensity", &areaIntensity, RI_NULL );
    }

    // Each loop has one polygon, so we just want an array of 1's of
    // the correct size. Stack version.
    //vector< RtInt > nloops( numFaces, 1 );
    // Alternatively (heap version):
    scoped_array< RtInt > nloops( new RtInt[ numFaces ] );
    fill( nloops.get(), nloops.get() + numFaces, ( RtInt )1 );

    unsigned numTokens( tokenPointerArray.size() );
    scoped_array< RtToken > tokenArray( new RtToken[ numTokens ] );
    scoped_array< RtPointer > pointerArray( new RtPointer[ numTokens ] );
    assignTokenArraysV( tokenPointerArray, tokenArray.get(), pointerArray.get() );

    RiPointsGeneralPolygonsV( numFaces,
                              &nloops[ 0 ],
                              nverts.get(),
                              verts.get(),
                              numTokens,
                              tokenArray.get(),
                              pointerArray.get() );

    if ( areaLight ) 
    {
      // RiAttributeEnd();
      RiIlluminate( handle, 1 );
    }
  } 
  else 
  {
//    liquidMessage( "Could not export degenerate mesh", messageError );
  }
}

/** Compare this mesh to the other for the purpose of determining
 *  if it's animated.
 */
bool liqRibMeshData::compare( const liqRibData & otherObj ) const
{
  unsigned numFaceVertices( 0 );

  LIQDEBUGPRINTF( "-> comparing mesh\n" );
  if ( otherObj.type() != MRT_Mesh ) 
    return false;
  const liqRibMeshData& other = (liqRibMeshData&)otherObj;

  if ( numFaces != other.numFaces )     return false;
  if ( numPoints != other.numPoints )   return false;
  if ( numNormals != other.numNormals ) return false;

  for ( unsigned i( 0 ); i < numFaces; ++i ) 
  {
    if ( nverts[i] != other.nverts[i] ) 
      return false;
    numFaceVertices += nverts[i];
  }

  for ( unsigned i( 0 ); i < numFaceVertices; ++i ) 
    if ( verts[i] != other.verts[i] ) 
      return false;

  for ( unsigned i( 0 ); i < numPoints; ++i ) 
  {
    const unsigned a( i * 3 );
    const unsigned b( a + 1 );
    const unsigned c( a + 2 );
    if (  !equiv( vertexParam[a], other.vertexParam[a] ) ||
          !equiv( vertexParam[b], other.vertexParam[b] ) ||
          !equiv( vertexParam[c], other.vertexParam[c] ) )
    {
      return false;
    }
  }

  for ( unsigned i( 0 ); i < numNormals; ++i ) 
  {
    const unsigned a = i * 3;
    const unsigned b = a + 1;
    const unsigned c = a + 2;
    if (  !equiv( normalParam[a], other.normalParam[a] ) ||
          !equiv( normalParam[b], other.normalParam[b] ) ||
          !equiv( normalParam[c], other.normalParam[c] ) )
    {
      return false;
    }
  }
  return true;
}


/** Return the geometry type.
 */
ObjectType liqRibMeshData::type() const
{
  LIQDEBUGPRINTF( "-> returning mesh type\n" );
  return ( areaLight )? MRT_Light : MRT_Mesh;
}

