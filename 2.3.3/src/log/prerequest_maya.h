#ifndef _PREREQUEST_MAYA_H_
#define _PREREQUEST_MAYA_H_

#ifdef _USE_OPENGL_
#include "prerequest_ogl.h"
#endif

#include <maya/MFnNumericAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MDGMessage.h>

#include <maya/MPxNode.h>
#include <maya/MTypeId.h> 
#include <maya/MTime.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MFloatPointArray.h>
#include <maya/MPxCommand.h>
#include <maya/MDGModifier.h>
#include <maya/MItSelectionList.h>
#include <maya/MPxLocatorNode.h>
#include <maya/MString.h>
#include <maya/MVector.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/M3dView.h>
#include <maya/MDistance.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnMessageAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MPxManipContainer.h>
#include <maya/MPointArray.h>
#include <maya/MFnDagNode.h>
#include <maya/MColor.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MFnTransform.h>
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>
#include <maya/MAnimControl.h>
#include <maya/MEulerRotation.h>
#include <maya/MQuaternion.h>
#include <maya/MFnNurbsSurfaceData.h>
#include <maya/MFnNurbsSurface.h>
#include <maya/MAngle.h>
#include <maya/MMatrix.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MItDag.h>
#include <maya/MFnMesh.h>
#include <maya/MTypes.h>
#include <maya/MStatus.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MSyntax.h>
#include <maya/MArgDatabase.h>
#include <maya/MFloatMatrix.h>
#include <maya/MFnMeshData.h>
#include <maya/MConditionMessage.h>
#include <maya/MPxData.h>
#include <maya/MPxHwShaderNode.h>
#include <maya/MImage.h>
#include <maya/MPxDragAndDropBehavior.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MFloatArray.h>
#include <maya/MIOStream.h>
#include <maya/MPxEmitterNode.h>
#include <maya/MFnMatrixData.h>
#include <maya/MFnArrayAttrsData.h>
#include <maya/MFnVectorArrayData.h>
#include <maya/MFnPointArrayData.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MRenderView.h>
#include <maya/MFnCamera.h>
#include <maya/MFileObject.h>


#endif//_PREREQUEST_MAYA_H_