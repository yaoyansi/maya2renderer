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
** Liquid Rib Locator Data Source
** ______________________________________________________________________
*/
#include <liqRibImplicitSphereData.h>
// Boost headers
#include <boost/scoped_array.hpp>

// Renderman Headers
//extern "C" {
#include "ri_interface.h"
//}

// Maya headers
//#include <maya/MPoint.h>
//#include <maya/MBoundingBox.h>
#include <maya/MPlug.h>
#include <maya/MFnDagNode.h>
//#include <maya/MFnDagNode.h>
//#include <maya/MStringArray.h>

// Liquid headers
#include <liquid.h>
#include <liqGlobalHelpers.h>
#include <liqGlobalVariable.h>
#include "renderman/rm_helper.h"

using namespace std;
using namespace boost;


/** Create a RIB compatible representation of a Maya locator.
 */
liqRibImplicitSphereData::liqRibImplicitSphereData( MObject daSphere )
{
  LIQDEBUGPRINTF( "-> creating implicit sphere\n" );
  MStatus status( MS::kSuccess );
  MFnDagNode sphere( daSphere );
  MPlug radiusPlug( sphere.findPlug( "radius", &status ) );

  if( MS::kSuccess == status ) {
    radiusPlug.getValue( radius );
  } else {
    radius = 1.;
  }

  addAdditionalSurfaceParameters( daSphere );
}
void liqRibImplicitSphereData::write(const MString &ribFileName, const structJob &currentJob, const bool bReference)
{
	assert(liqglo.m_ribFileOpen&&"liqRibImplicitSphereData.cpp");

	if( !bReference ){//write data at first time
		assert(m_ribFileFullPath.length()==0);
		m_ribFileFullPath = ribFileName;

		renderman::Helper o;
		o.RiBeginRef(m_ribFileFullPath.asChar());
		_write(currentJob);
		o.RiEndRef();

	}else{
		//write the reference
		assert(m_ribFileFullPath == ribFileName);
		RiReadArchive( const_cast< RtToken >( m_ribFileFullPath.asChar() ), NULL, RI_NULL );
	}
}
/** Write the RIB for this locator.
 */
void liqRibImplicitSphereData::_write(const structJob &currentJob)
{
  unsigned numTokens( tokenPointerArray.size() );
  scoped_array< RtToken > tokenArray( new RtToken[ numTokens ] );
  scoped_array< RtPointer > pointerArray( new RtPointer[ numTokens ] );
  assignTokenArraysV( tokenPointerArray, tokenArray.get(), pointerArray.get() );

  RiSphereV( radius, -radius, radius, 360, numTokens, tokenArray.get(), pointerArray.get() );
  LIQDEBUGPRINTF( "-> writing locator" );
}

/** Compare this locator to the other for the purpose of determining
 *  if its animated.
 */
bool liqRibImplicitSphereData::compare( const liqRibData& otherObj ) const
{
  LIQDEBUGPRINTF( "-> comparing locator\n" );
  if( otherObj.type() == MRT_ImplicitSphere ) 
  {
    return ( ( liqRibImplicitSphereData* )&otherObj )->radius == radius;
    //return true;
  } 
  else 
	  return false;
}

/** Return the geometry type.
 */
ObjectType liqRibImplicitSphereData::type() const
{
  LIQDEBUGPRINTF( "-> returning locator type\n" );
  return MRT_ImplicitSphere;
}
