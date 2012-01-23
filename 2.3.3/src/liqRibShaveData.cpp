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
** The RenderMan (R) Interface Procedures and Protocol are: Copyright 1988,
** 1989, Pixar All Rights Reserved
**
**
** RenderMan (R) is a registered trademark of Pixar
**
*/

/* ______________________________________________________________________
**
** Liquid Rib Surface Data Source
** ______________________________________________________________________
*/
#include <liqRibShaveData.h>
// Boost headers
#include <boost/scoped_array.hpp>
#include <boost/shared_array.hpp>
// RenderMan headers
//extern "C" {
#include "ri_interface.h"
//}

// Maya headers
#include<maya/MPlug.h>
#include<maya/MFnNurbsCurve.h>
#include<maya/MDoubleArray.h>
#include<maya/MItSurfaceCV.h>
#include<maya/MFnNurbsSurface.h>
#include<maya/shaveAPI.h>
#include<maya/shaveItHair.h>
#include<maya/MGlobal.h>
// Liquid headers
#include <liqGlobalHelpers.h>
#include <liqRenderer.h>
#include <liqGlobalVariable.h>
#include <liqRibTranslator.h>

using namespace boost;

#pragma comment(lib,"libShaveAPI.lib")


void displayGeomInfo(MString name, shaveAPI::SceneGeom& geom);
void displayHairInfo(shaveAPI::HairInfo* hairInfo, bool instances);

/** Ccreate a RIB compatible representation of a Maya nurbs surface.
 */
liqRibShaveData::liqRibShaveData( MObject surface )
:   hasTrims( false ),
    grain( 0 ),
    uknot(),
    vknot(),
    CVs(),
    ncurves(),
    order(),
    numCVs(),
    knot(),
    minKnot(),
    maxKnot(),
    u(),
    v(),
    w()

{
  LIQDEBUGPRINTF( "-> creating shave surface\n" );
//  if ( debugMode ) {
    MFnDependencyNode myDep( surface );
    MString name = myDep.name();
    liquidMessage2( messageInfo, "-> surface path %s\n", name.asChar() );
//  }

	test();

  // Hmmmmm Was global but never changed ...
  bool normalizeNurbsUV( true );

  MStatus status( MS::kSuccess );
  MFnNurbsSurface nurbs( surface, &status );
  if ( MS::kSuccess == status ) 
  {
    // Extract the order and number of CVs in the surface

    MDoubleArray uKnots, vKnots;

    if ( liqglo.liquidRenderer.requires_SWAPPED_UVS ) 
    {
      LIQDEBUGPRINTF( "-> swapping uvs\n" );

      uorder = nurbs.degreeV() + 1; // uv order is switched
      vorder = nurbs.degreeU() + 1; // uv order is switched
      nu = nurbs.numCVsInV();       // uv order is switched
      nv = nurbs.numCVsInU();       // uv order is switched

      // Read the knot information

      nurbs.getKnotsInU( vKnots ); // uv order is switched
      nurbs.getKnotsInV( uKnots ); // uv order is switched
      
      double uMin_d, uMax_d, vMin_d, vMax_d;
      nurbs.getKnotDomain(uMin_d, uMax_d, vMin_d, vMax_d);
      umin = ( RtFloat )vMin_d; // uv order is switched
      umax = ( RtFloat )vMax_d; // uv order is switched
      vmin = ( RtFloat )uMin_d; // uv order is switched
      vmax = ( RtFloat )uMax_d; // uv order is switched
    } 
    else 
    {
      LIQDEBUGPRINTF( "-> not swapping uvs\n" );

      uorder = nurbs.degreeU() + 1;
      vorder = nurbs.degreeV() + 1;
      nu = nurbs.numCVsInU();
      nv = nurbs.numCVsInV();

      // Read the knot information

      nurbs.getKnotsInU( uKnots );
      nurbs.getKnotsInV( vKnots );

      double uMin_d, uMax_d, vMin_d, vMax_d;
      nurbs.getKnotDomain( uMin_d, uMax_d, vMin_d, vMax_d );
      umin = ( RtFloat )uMin_d;
      umax = ( RtFloat )uMax_d;
      vmin = ( RtFloat )vMin_d;
      vmax = ( RtFloat )vMax_d;
      
          	
    	// Reverse v knots values for matching Maya texture coordinates
      for ( unsigned k = 0; k < vKnots.length(); k++ )
    	{	
    		 vKnots[ k ] = vmax - vKnots[ k ] + vmin;
    		 //LIQDEBUGPRINTF( "vKnots[%d]  = %f\n", k, vKnots[ k ] );
    	}
    	
    }

    float uKnotMult = 1;
    float vKnotMult = 1;

    // this was added to simulate MTOR's parameterization handling
    // it, by default, normalizes the U and V coordinates.

    bool noNormalizeNurbs = false;
    
    liquidGetPlugValue( nurbs, "noNormalizeNurbs", noNormalizeNurbs, status );
    
    normalizeNurbsUV = !noNormalizeNurbs;
    
    if ( normalizeNurbsUV ) 
    {
      uKnotMult = 1 / ( umax - umin );
      vKnotMult = 1 / ( vmax - vmin );
    }

    // Allocate CV and knot storage
    CVs   = shared_array< RtFloat >( new RtFloat[ nu * nv * 4 ] );
    uknot = shared_array< RtFloat >( new RtFloat[ uKnots.length() + 2 ] );
    vknot = shared_array< RtFloat >( new RtFloat[ vKnots.length() + 2 ] );

    unsigned k;
    if ( normalizeNurbsUV ) 
    {
      for ( k = 0; k < uKnots.length(); k++ ) 
        uknot[ k + 1 ] = ( ( RtFloat )uKnots[ k ] - umin ) * uKnotMult;
    } 
    else 
      for ( k = 0; k < uKnots.length(); k++ ) 
        uknot[ k + 1 ] = ( RtFloat )uKnots[ k ];

    // Maya doesn't store the first and last knots, so we double them up
    // manually
    //
    uknot[ 0 ]   = uknot[ 1 ];
    uknot[ k+1 ] = uknot[ k ];

    
    if ( liqglo.liquidRenderer.requires_SWAPPED_UVS )
    {
			if ( normalizeNurbsUV ) 
			{
				for ( k = 0; k < vKnots.length(); k++ ) 
					vknot[ k + 1 ] = ( ( RtFloat )vKnots[ k ] - vmin ) * vKnotMult;
			} 
			else 
				for ( k = 0; k < vKnots.length(); k++ ) 
					vknot[ k + 1 ] = ( RtFloat )vKnots[ k ];
		}
		else
		{
			if ( normalizeNurbsUV ) 
			{
				for ( k = 0; k < vKnots.length(); k++ ) 
					vknot[ k + 1 ] = ( ( RtFloat )vKnots[ vKnots.length() - 1 - k ] - vmin ) * vKnotMult;
			} 
			else 
				for ( k = 0; k < vKnots.length(); k++ ) 
					vknot[ k + 1 ] = ( RtFloat )vKnots[ vKnots.length() - 1 - k ];	
		}
    // Maya doesn't store the first and last knots, so we double them up
    // manually
    //
    vknot[ 0 ] = vknot[ 1 ];
    vknot[ k + 1 ] = vknot[ k ];
    
    

    // Read CV information
    //
    MItSurfaceCV cvs( surface, liqglo.liquidRenderer.requires_SWAPPED_UVS == false );
    
    
    if ( liqglo.liquidRenderer.requires_SWAPPED_UVS )
    {
			RtFloat* cvPtr( CVs.get() );
    	while( !cvs.isDone() ) 
			{
				while( !cvs.isRowDone() ) 
				{
					MPoint pt( cvs.position( MSpace::kObject ) );
					*cvPtr++ = ( RtFloat )pt.x;
					*cvPtr++ = ( RtFloat )pt.y; 
					*cvPtr++ = ( RtFloat )pt.z;
					*cvPtr++ = ( RtFloat )pt.w;
					cvs.next();
				}
				cvs.nextRow();
			}
		}
		else
    {
    	// Reverse v knots order for matching Maya texture coordinates	
    	
    	    	
    	// store rows in reversed order
    	RtFloat* cvPtr( CVs.get() );
    	cvPtr += nu * ( nv - 1 ) * 4; // set pointer to last row in array
    	
    	while( !cvs.isDone() ) 
			{
				while( !cvs.isRowDone() ) 
				{
					MPoint pt( cvs.position( MSpace::kObject ) );
					*cvPtr++ = ( RtFloat )pt.x;
					*cvPtr++ = ( RtFloat )pt.y; 
					*cvPtr++ = ( RtFloat )pt.z;
					*cvPtr++ = ( RtFloat )pt.w;
					cvs.next();
				}
				cvs.nextRow();
				cvPtr -= (nu * 4 * 2); // skip two rows
			}
    	
    }

    // Store trim information
    //
    if ( nurbs.isTrimmedSurface() ) 
    {
      hasTrims = true;
      LIQDEBUGPRINTF( "-> storing trim information\n" );

      unsigned numRegions, numBoundaries, numEdges, numCurves;

      // Get the number of loops
      //
      numRegions = nurbs.numRegions();
      nloops = 0;
      for ( unsigned r( 0 ); r < numRegions; r++ ) 
      {
        numBoundaries = nurbs.numBoundaries( r );
        nloops += numBoundaries;
      }

      // Get the number of trim curves in each loop and gather curve
      // information
      //
      for ( unsigned r( 0 ); r < (unsigned) nloops; r++ ) 
      {
        numBoundaries = nurbs.numBoundaries( r );
        for ( unsigned b( 0 ); b < numBoundaries; b++ ) 
        {
          numCurves = 0;
          numEdges = nurbs.numEdges( r, b );
          for ( unsigned e( 0 ); e < numEdges; e++ ) 
          {
            MObjectArray curves( nurbs.edge( r, b, e, true ) );
            numCurves += curves.length();

            // Gather extra stats for each curve
            //
            for ( unsigned c( 0 ); c < curves.length(); c++ ) 
            {
              // Read the # of CVs in and the order of each curve
              //
              MFnNurbsCurve curveFn(curves[ c ]);
              order.push_back( curveFn.degree() + 1 );
              numCVs.push_back( curveFn.numCVs() );

              // Read the CVs for each curve
              //
              MPoint pnt;
              for ( unsigned i( 0 ); i < curveFn.numCVs(); ++i ) 
              {
                curveFn.getCV( i, pnt );
                //cvArray.push_back( pnt );
                if ( liqglo.liquidRenderer.requires_SWAPPED_UVS ) 
                {
                	if ( normalizeNurbsUV )
                 {	
										u.push_back( ( pnt.y - umin ) * uKnotMult );
										v.push_back( ( pnt.x - vmin ) * vKnotMult );
									} 
									else
									{
										u.push_back( pnt.y );
										v.push_back( pnt.x );	
									}	
                } 
                else 
                {
									if ( normalizeNurbsUV )
                 {		
                 	 u.push_back( ( pnt.x - umin ) * uKnotMult );
                 	 v.push_back( ( vmax - pnt.y - vmin + vmin) * vKnotMult );
                 }
                 else
                 {
                 		u.push_back( pnt.x );
                 		v.push_back( vmax - pnt.y + vmin ); 
                 }
                }
                w.push_back( pnt.w );
              }

              // Read the knot array for each curve
              //
              MDoubleArray knotsTmpArray;
              curveFn.getKnots( knotsTmpArray );
              knot.push_back( knotsTmpArray[ 0 ] );
              for ( unsigned i( 0 ); i < knotsTmpArray.length(); ++i ) 
                knot.push_back( (float)knotsTmpArray[ i ] );
              
              knot.push_back( knotsTmpArray[ knotsTmpArray.length() - 1 ] );

              // Read the knot domain for each curve
              //
              double start, end;
              curveFn.getKnotDomain( start, end );
              minKnot.push_back( start );
              maxKnot.push_back( end );
            }
          }
          ncurves.push_back( numCurves );
        }
      }
    }
    
    if ( normalizeNurbsUV )
    {
			 umin = 0; 
			 umax = 1;
			 vmin = 0; 
			 vmax = 1;
    }

    // now place our tokens and parameters into our tokenlist

    liqTokenPointer tokenPointerPair;
    tokenPointerPair.set( "Pw", rHpoint, nu * nv );
    tokenPointerPair.setDetailType( rVertex );
    tokenPointerPair.setTokenFloats( CVs );
    tokenPointerArray.push_back( tokenPointerPair );

    addAdditionalSurfaceParameters( surface );
  }
}



/** Write the RIB for this surface.
 */
void liqRibShaveData::_write(const structJob &currentJob)
{
  LIQDEBUGPRINTF( "-> writing shave surface\n" );

  LIQDEBUGPRINTF( "-> writing shave surface trims\n" );
  liqRIBMsg("This is a shave object data:\n" );
 
  MString nodeName(objDagPath.partialPathName());
  liqRIBMsg( "node name = %s", nodeName.asChar() );

  MString frame; 
  frame.set(liqglo.liqglo_lframe);
  MString prefix("shv_");
  MString shv_RibFile( liquidGetRelativePath( false, getLiquidRibName( (prefix+nodeName).asChar() ), liqglo.liqglo_ribDir ) +"."+frame+".rib" );

  //1)make a reference
  RiReadArchive( const_cast< RtToken >( shv_RibFile.asChar() ), NULL, RI_NULL );

  //call shave command to write the rib file(not support motion blur)
   MGlobal::executeCommand(
 	  "shaveWriteRib -hairNode \""+nodeName+"\" \""+shv_RibFile+"\";"
 	  );
 
  LIQDEBUGPRINTF( "-> done writing shave surface\n" );
}

unsigned liqRibShaveData::granularity() const 
{
  if ( hasTrims && !tokenPointerArray.empty() ) 
  {
    return 2;
  } else if ( !tokenPointerArray.empty() ) {
    return 1;
  } else {
    return 0;
  }
}

bool liqRibShaveData::writeNextGrain()
{
  if ( hasTrims && ( 0 == grain ) ) 
  {
    RiTrimCurve( nloops,
                 const_cast< RtInt* >( &ncurves[ 0 ] ),
                 const_cast< RtInt* >( &order[ 0 ] ),
                 const_cast< RtFloat* >( &knot[ 0 ] ),
                 const_cast< RtFloat* >( &minKnot[ 0 ] ),
                 const_cast< RtFloat* >( &maxKnot[ 0 ] ),
                 const_cast< RtInt* >( &numCVs[ 0 ] ),
                 const_cast< RtFloat* >( &u[ 0 ] ),
                 const_cast< RtFloat* >( &v[ 0 ] ),
                 const_cast< RtFloat* >( &w[ 0 ] ) );
    ++grain;
    return true;
  } else if ( !tokenPointerArray.empty() ) {
    unsigned numTokens( tokenPointerArray.size() );
    scoped_array< RtToken > tokenArray( new RtToken[ numTokens ] );
    scoped_array< RtPointer > pointerArray( new RtPointer[ numTokens ] );
    assignTokenArraysV( tokenPointerArray, tokenArray.get(), pointerArray.get() );

    RiNuPatchV( nu,
                uorder,
                uknot.get(),
                umin,
                umax,
                nv,
                vorder,
                vknot.get(),
                vmin,
                vmax,
                numTokens,
                tokenArray.get(),
                pointerArray.get() );

    grain = 0;
  }

  return false;
}

/** Compare this surface to the other for the purpose of determining
 *  if it is animated.
 */
bool liqRibShaveData::compare( const liqRibData & otherObj ) const
{
  LIQDEBUGPRINTF( "-> comparing shave surface\n" );
  if ( otherObj.type() != MRT_Shave ) 
	  return false;

  const liqRibShaveData & other = (liqRibShaveData&)otherObj;

  if ( ( nu != other.nu ) ||
       ( nv != other.nv ) ||
       ( uorder != other.uorder ) ||
       ( vorder != other.vorder ) ||
       !equiv( umin, other.umin ) ||
       !equiv( umax, other.umax ) ||
       !equiv( vmin, other.vmin ) ||
       !equiv( vmax, other.vmax ) )
  {
    return false;
  }

  // Check Knots
  unsigned i;
  unsigned last( nu + uorder );
  for ( i = 0; i < last; ++i ) 
  {
    if ( !equiv( uknot[ i ], other.uknot[ i ] ) )
      return false;
  }
  last = nv + vorder;
  for ( i = 0; i < last; ++i ) 
  {
    if ( !equiv( vknot[ i ], other.vknot[ i ] ) )
      return false;
  }

  // Check CVs
  last = nu * nv * 4;
  for ( i = 0; i < last; ++i ) 
  {
    if ( !equiv( CVs[ i ], other.CVs[ i ] ) )
      return false;
  }

  // TODO: Check trims as well
  return true;
}

/** Return the geometry type.
 */
ObjectType liqRibShaveData::type() const
{
  LIQDEBUGPRINTF( "-> returning shave type\n" );
  return MRT_Shave;
}


MStatus liqRibShaveData::test()
{
	MStatus  status;
	char     msg[256]={0};

	//--------------------------------------------------------------------
	MGlobal::displayInfo("Test 1: export all shaveHairShapes...\n");

	shaveAPI::HairInfo hairInfo;

	status = shaveAPI::exportAllHair(&hairInfo);

	if (status == MS::kNotFound)
	{
		MGlobal::displayInfo(
			"  exportAllHair says there are no shaveHairShapes in the scene.\n"
			);
	}
	else if (!status)
	{
		MGlobal::displayError(
			MString("  we got back the following unexpected error: ")
			+ status.errorString()
			);
	}
	else
	{
		MGlobal::displayInfo("  Scene contains...");
		displayHairInfo(&hairInfo, false);
	}
	hairInfo.clear();

	//--------------------------------------------------------------------
	MGlobal::displayInfo("Test 2: export renderable shaveHairShapes...\n");

	status = shaveAPI::exportAllHair(&hairInfo, true);

	if (status == MS::kNotFound)
	{
		MGlobal::displayInfo(
			"  exportAllHair says there are no renderable shaveHairShapes"
			" in the scene.\n"
			);

		status = MS::kSuccess;
	}
	else
	{
		MGlobal::displayInfo("  Renderable shaveHairShapes contain...\n");
		displayHairInfo(&hairInfo, false);
	}
	hairInfo.clear();

	//--------------------------------------------------------------------
	MGlobal::displayInfo("Test 3: iterate through non-instanced hairs...\n");

	status = shaveItHair::init(false, true);

	if (status == MS::kNotFound)
	{
		MGlobal::displayInfo(
			"  shaveItHair::init says there are no renderable, non-instanced"
			" shaveHairShapes in the scene.\n"
			);
	}
	else
	{
		int  hairNum = 0;

		while (shaveItHair::nextHair(&hairInfo))
		{
			sprintf(msg, "  Hair %d contains...\n", hairNum);
			MGlobal::displayInfo(msg);
			displayHairInfo(&hairInfo, false);
			hairInfo.clear();

			if (++hairNum >= 3) break;
		}
	}
	hairInfo.clear();

	//--------------------------------------------------------------------
	MGlobal::displayInfo("Test 4: iterate through instanced hairs...\n");

	status = shaveItHair::init(true, true);

	if (status == MS::kNotFound)
	{
		MGlobal::displayInfo(
			"  shaveItHair::init says there are no renderable, instanced"
			" shaveHairShapes in the scene.\n"
			);
	}
	else
	{
		int  hairNum = 0;

		while (shaveItHair::nextHair(&hairInfo))
		{
			sprintf(msg, "  Hair %d contains...\n", hairNum);
			MGlobal::displayInfo(msg);
			displayHairInfo(&hairInfo, true);
			hairInfo.clear();

			if (++hairNum >= 3) break;
		}
	}
	hairInfo.clear();

	//--------------------------------------------------------------------
	MGlobal::displayInfo("Test 5: get occlusion geometry...\n");

	shaveAPI::SceneGeom   hairOcclusions;
	shaveAPI::SceneGeom   shadowOcclusions;

	status = shaveAPI::exportOcclusions(&hairOcclusions, &shadowOcclusions);

	if ((status != MS::kSuccess) && (status != MS::kUnknownParameter))
	{
		MGlobal::displayError(
			MString("  we got back the following unexpected error: ")
			+ status.errorString()
			);
	}
	else
	{
		if (status == MS::kUnknownParameter)
		{
			MGlobal::displayWarning(
				"  motion blur is on but no renderable camera could be found,"
				" so geometry velocities will all be zero."
				);
		}

		displayGeomInfo("Hair occlusions", hairOcclusions);
		displayGeomInfo("Shadow occlusions", shadowOcclusions);
	}

	//
	// Free up all the memory allocated to 'hairInfo'.
	//
	// This call is provided just as an example.  In this particular case
	// it is unnecessary because 'hairInfo' will go out of scope at the end
	// of the function and be destroyed, along with all of its storage.
	//
	// However, if you were planning on doing some other processing in this
	// function, then it might make sense to clear 'hairInfo's storage
	// first so that that memory was available for other uses.
	//
	//hairInfo.clear();

	return MS::kSuccess;
}


void displayGeomInfo(
									  MString name, shaveAPI::SceneGeom& geom
									  )
{
	MGlobal::displayInfo(MString("  ") + name + " consists of...");

	char msg[1024]={0};

	sprintf(
		msg,
		"  %d faces\n  %d vertices\n  %d face vertices\n",
		geom.numFaces,
		geom.numVertices,
		geom.numFaceVertices
		);

	MGlobal::displayInfo(msg);

	//
	// Dump out some details for the first three faces, if there are that
	// many.
	//
	int face;
	int i;

	for (face = 0; (face < 3) && (face < geom.numFaces); face++)
	{
		sprintf(msg, "  face %d", face);
		MGlobal::displayInfo(msg);

		for (i = geom.faceStartIndices[face];
			i < geom.faceEndIndices[face];
			i++)
		{
			int vert = geom.faceVertices[i];

			sprintf(
				msg,
				"    vertex %d: position (%f, %f, %f)  velocity (%f, %f, %f)",
				i-geom.faceStartIndices[face],
				geom.vertices[vert].x,
				geom.vertices[vert].y,
				geom.vertices[vert].z,
				geom.velocities[vert].x,
				geom.velocities[vert].y,
				geom.velocities[vert].z
				);

			MGlobal::displayInfo(msg);
		}
	}
}


void displayHairInfo(
									  shaveAPI::HairInfo* hairInfo, bool instances
									  )
{
	MString  strandName = (instances ? "face" : "strand");
	char     buff[1024];

	sprintf(buff, "  %d %s", hairInfo->numHairs, strandName.asChar());
	MGlobal::displayInfo(buff);

	sprintf(buff, "  %d vertices", hairInfo->numVertices);
	MGlobal::displayInfo(buff);

	sprintf(buff, "  %d %s vertices", hairInfo->numHairVertices, strandName.asChar());
	MGlobal::displayInfo(buff);

	//
	// Dump out some details for the first three strands, if there are that
	// many.
	//
	int strand;
	int i;

	for (strand = 0; (strand < 3) && (strand < hairInfo->numHairs); strand++)
	{
		sprintf(
			buff,
			"  %s %d: root colour (%f, %f, %f)  tip colour (%f, %f, %f)  surface normal (%f, %f, %f) \n",
			strandName.asChar(),
			strand,
			hairInfo->rootColors[strand].r,
			hairInfo->rootColors[strand].g,
			hairInfo->rootColors[strand].b,
			hairInfo->tipColors[strand].r,
			hairInfo->tipColors[strand].g,
			hairInfo->tipColors[strand].b,
			hairInfo->surfaceNormals[strand].x,
			hairInfo->surfaceNormals[strand].y,
			hairInfo->surfaceNormals[strand].z
			);
		MGlobal::displayInfo(buff);
		//
		sprintf(buff, "hairInfo->hairStartIndices[%d]=%d, hairInfo->hairEndIndices[%d]=%d",
			strand, hairInfo->hairStartIndices[strand], strand, hairInfo->hairEndIndices[strand]);
		MGlobal::displayInfo(buff);
		//
		for (i = hairInfo->hairStartIndices[strand];
			i < hairInfo->hairEndIndices[strand];
			i++)
		{
			int vert = hairInfo->hairVertices[i];
			sprintf(buff, "i=%d, vert=%d", i, vert);
			MGlobal::displayInfo(buff);

			sprintf(
				buff,
				"    vertex %d: position (%f, %f, %f)  velocity (%f, %f, %f)   texture coords (%f, %f, %f)",
				hairInfo->hairStartIndices[strand], //(i - hairInfo->hairStartIndices[strand]),
				hairInfo->vertices[vert].x,
				hairInfo->vertices[vert].y,
				hairInfo->vertices[vert].z,
				hairInfo->velocities[vert].x,
				hairInfo->velocities[vert].y,
				hairInfo->velocities[vert].z,
				hairInfo->uvws[vert].x,
				hairInfo->uvws[vert].y,
				hairInfo->uvws[vert].z
				);
			MGlobal::displayInfo(buff);
		}
	}
}

