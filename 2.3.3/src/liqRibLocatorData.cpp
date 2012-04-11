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
#include <liqRibLocatorData.h>
// Renderman Headers
//extern "C" {
#include "ri_interface.h"
//}

// Maya's Headers
#include <maya/MPoint.h>
#include <maya/MBoundingBox.h>
#include <maya/MPlug.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnDagNode.h>
#include <maya/MStringArray.h>

#include <liquid.h>
#include <liqGlobalHelpers.h>
#include "renderman/rm_helper.h"
#include "renderermgr.h"

/** Create a RIB compatible representation of a Maya locator.
 */
liqRibLocatorData::liqRibLocatorData( MObject /*locator*/ )
{
  LIQDEBUGPRINTF( "-> creating locator\n" );
}
void liqRibLocatorData::write(const MString &ribFileName, const structJob &currentJob, const bool bReference)
{
	CM_TRACE_FUNC("liqRibLocatorData::write("<<ribFileName<<",job="<<currentJob.name<<","<<bReference<<")");

	liquid::RendererMgr::getInstancePtr()->
		getRenderer()->write(this, ribFileName, currentJob, bReference);
// 	if( !bReference ){//write data at first time
// 		assert(m_ribFileFullPath.length()==0);
// 		m_ribFileFullPath = ribFileName;
// 
// 		renderman::Helper o;
// 		o.RiBeginRef(m_ribFileFullPath.asChar());
// 		_write(currentJob);
// 		o.RiEndRef();
// 
// 	}else{
// 		//write the reference
// 		assert(m_ribFileFullPath == ribFileName);
// 		RiReadArchive( const_cast< RtToken >( m_ribFileFullPath.asChar() ), NULL, RI_NULL );
// 	}
}
/** Write the RIB for this locator.
 */
//void liqRibLocatorData::_write(const structJob &currentJob)
//{
//  RiTranslate( 0., 0., 0. );
//  LIQDEBUGPRINTF( "-> writing locator" );
//}

/** Compare this locator to the other for the purpose of determining
 *  if its animated.
 */
bool liqRibLocatorData::compare( const liqRibData & otherObj ) const
{
	CM_TRACE_FUNC("liqRibLocatorData::compare("<<otherObj.getFullPathName()<<")");

  LIQDEBUGPRINTF( "-> comparing locator\n" );
  if ( otherObj.type() != MRT_Locator ) return false;
  return true;
}

/** Return the geometry type.
 */
ObjectType liqRibLocatorData::type() const
{
  LIQDEBUGPRINTF( "-> returning locator type\n" );
  return MRT_Locator;
}
