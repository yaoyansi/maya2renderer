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

#if _USE_SHAVE_

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
#include "renderman/rm_helper.h"
#include "renderermgr.h"
#include "./common/mayacheck.h"

using namespace boost;

#pragma comment(lib,"libShaveAPI.lib")


void displayGeomInfo(MString name, shaveAPI::SceneGeom& geom);
void displayHairInfo(shaveAPI::HairInfo* hairInfo, bool instances);

/** Ccreate a RIB compatible representation of a Maya nurbs surface.
 */
liqRibShaveData::liqRibShaveData( MObject obj )
{
	CM_TRACE_FUNC("liqRibShaveData::liqRibShaveData("<<MFnDagNode(obj).fullPathName()<<")");

	LIQDEBUGPRINTF( "-> creating shave hair\n" );
	MStatus status;
	MFnDagNode fnDagPath(obj, &status);
	IfErrorWarn(status);
	IfErrorWarn(fnDagPath.getPath(objDagPath));

	liquidMessage2( messageInfo, "-> shavehair path %s\n", this->getFullPathName() );

	test();
}


void liqRibShaveData::write(const MString &ribFileName, const structJob &currentJob, const bool bReference)
{
	CM_TRACE_FUNC("liqRibShaveData::write("<<ribFileName<<",job="<<currentJob.name<<","<<bReference<<")");
	
	liquid::RendererMgr::getInstancePtr()->
		getRenderer()->write(this, ribFileName, currentJob, bReference);
	//assert(liqglo.m_ribFileOpen&&"liqRibShaveData");

	//if( !bReference ){//write data at first time
	//	assert(m_ribFileFullPath.length()==0);
	//	m_ribFileFullPath = ribFileName;

	//	//1)make a reference
	//	RiReadArchive( const_cast< RtToken >( m_ribFileFullPath.asChar() ), NULL, RI_NULL );

	//	//2)call shave command to write the rib file(not support motion blur)
	//	MGlobal::executeCommand(
	//		"shaveWriteRib -hairNode \""+objDagPath.partialPathName()+"\" \""+m_ribFileFullPath+"\";"
	//	);
	//}else{
	//	//write the reference
	//	assert(m_ribFileFullPath == ribFileName);
	//	RiReadArchive( const_cast< RtToken >( m_ribFileFullPath.asChar() ), NULL, RI_NULL );
	//}
}
/** Write the RIB for this surface.
 */
// void liqRibShaveData::_write(const structJob &currentJob)
// {
//   LIQDEBUGPRINTF( "-> writing shave surface\n" );
// 
//   LIQDEBUGPRINTF( "-> writing shave surface trims\n" );
//   liqRIBMsg("This is a shave object data:\n" );
//  
//    MString nodeName(objDagPath.partialPathName());
//    liqRIBMsg( "node name = %s", nodeName.asChar() );
//  
//    MString frame; 
//    frame.set(liqglo.liqglo_lframe);
//    MString prefix("shv_");
//    MString shv_RibFile( liquidGetRelativePath( false, getLiquidRibName( (prefix+nodeName).asChar() ), liqglo.liqglo_ribDir ) +"."+frame+".rib" );
// 
//   //1)make a reference
//   RiReadArchive( const_cast< RtToken >( shv_RibFile.asChar() ), NULL, RI_NULL );
// 
//   //call shave command to write the rib file(not support motion blur)
//    MGlobal::executeCommand(
//  	  "shaveWriteRib -hairNode \""+nodeName+"\" \""+shv_RibFile+"\";"
//  	  );
//  
//   LIQDEBUGPRINTF( "-> done writing shave surface\n" );
// }

// unsigned liqRibShaveData::granularity() const 
// {
// 	CM_TRACE_FUNC("liqRibShaveData::granularity()");
// 
// //   if ( hasTrims && !tokenPointerArray.empty() ) 
// //   {
// //     return 2;
// //   } else if ( !tokenPointerArray.empty() ) {
// //     return 1;
// //   } else {
// //     return 0;
// //   }
// 	assert(0&&"liqRibShaveData::granularity() is not implemented.");
// 	return 0;
// }

// bool liqRibShaveData::writeNextGrain()
// {
// 	CM_TRACE_FUNC("liqRibShaveData::writeNextGrain()");
// 
// 	assert(0&&"liqRibShaveData::writeNextGrain() is not implemented.");
// 
//   return false;
// }

/** Compare this surface to the other for the purpose of determining
 *  if it is animated.
 */
bool liqRibShaveData::compare( const liqRibData & otherObj ) const
{
	CM_TRACE_FUNC("liqRibShaveData::compare("<<otherObj.getFullPathName()<<")");

  LIQDEBUGPRINTF( "-> comparing shave hair\n" );
  if ( otherObj.type() != this->type() ) 
	  return false;

  const liqRibShaveData & other = (liqRibShaveData&)otherObj;
  if(other.objDagPath.fullPathName() != this->objDagPath.fullPathName())
	  return false;

  assert(0&&"liqRibShaveData::compare() is not implemented.");


  // TODO: Check trims as well
  return true;
}

/** Return the geometry type.
 */
ObjectType liqRibShaveData::type() const
{
	CM_TRACE_FUNC("liqRibShaveData::type()");

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

#endif//_USE_SHAVE_