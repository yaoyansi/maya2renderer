/*
**
** The contents of this file are subject to the Mozilla Public License Version 1.1 (the
** "License"); you may not use this file except in compliance with the License. You may
** obtain a copy of the License at http://www.mozilla.org/MPL/
**
** Software distributed under the License is distributed on an "AS IS" basis, WITHOUT
** WARRANTY OF ANY KIND, either express or implied. See the License for the specific
** language governing rights and limitations under the License.
**
** The Original Code is the Liquid Rendering Toolkit.
**
** The Initial Developer of the Original Code is Colin Doncaster. Portions created by
** Colin Doncaster are Copyright (C) 2002. All Rights Reserved.
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

// Renderman Headers
//extern "C" {
  #include "ri_interface.h"
//}

#include <maya/MFnDependencyNode.h>

#include <liquid.h>
#include <liqRibCoordData.h>
#include <liqGlobalVariable.h>
#include "renderman/rm_helper.h"

/** Create a RIB compatible representation of a Maya coordinate system.
 */
liqRibCoordData::liqRibCoordData( MObject coord )
{
  LIQDEBUGPRINTF("-> creating coord\n");
  MFnDependencyNode fnNode( coord );
  this->name = fnNode.name();
  //cout <<"created coord "<<this->name.asChar()<<endl;
}

void liqRibCoordData::write(const MString &ribFileName, const structJob &currentJob, const bool bReference)
{
	CM_TRACE_FUNC("liqRibCoordData::write("<<ribFileName<<","<<currentJob.name<<","<<bReference<<")");

	assert(liqglo.m_ribFileOpen&&"liqRibCoordData.cpp");

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

/** Write the RIB for this coordinate system.
 */
void liqRibCoordData::_write(const structJob &currentJob)
{
	CM_TRACE_FUNC("liqRibCoordData::_write("<<currentJob.name<<")");

  LIQDEBUGPRINTF("-> writing coord"); 
  RiCoordinateSystem( const_cast<char *> ( name.asChar() ) );
}

/** Compare this coordinate system to otherObj.
 *  The purpose is usually to determe if the coordinate system is animated.
 */
bool liqRibCoordData::compare( const liqRibData & otherObj ) const
{
	CM_TRACE_FUNC("liqRibCoordData::compare("<<otherObj.getFullPathName()<<")");

  LIQDEBUGPRINTF("-> comparing coord\n");
  return ( otherObj.type() != MRT_Coord )? false : true;
}

/** Return the geometry type.
 */
ObjectType liqRibCoordData::type() const
{
  LIQDEBUGPRINTF("-> returning coord type\n"); 
  return MRT_Coord;
}

