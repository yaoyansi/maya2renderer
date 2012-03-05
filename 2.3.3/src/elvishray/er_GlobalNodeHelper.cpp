
#include"er_GlobalNodeHelper.h"
#include "../common/prerequest_std.h"
#include "../common/mayacheck.h"
#include <liqGlobalHelpers.h>
#include <liqlog.h>

namespace elvishray
{


GlobalNodeHelper::GlobalNodeHelper()
:liqGlobalNodeHelper()
{
	assert(0&&"m_GlobalNodeName is empty.");
}

GlobalNodeHelper::GlobalNodeHelper(const char* globalNodeName)
{
	getDependNodeByName(m_GlobalNode, globalNodeName);
}

GlobalNodeHelper::~GlobalNodeHelper()
{

}

bool GlobalNodeHelper::getBool(const MString& attrName)
{
	MStatus status;
	bool value;
	liquidGetPlugValue(m_GlobalNode, attrName.asChar(), value, status);
	IfMErrorMsgWarn(status,"elvishray::GlobalNodeHelper::getBool("+attrName+")");
	return value;
}
int GlobalNodeHelper::getInt(const MString& attrName)
{
	MStatus status;
	int value;
	liquidGetPlugValue(m_GlobalNode, attrName.asChar(), value, status);
	IfMErrorMsgWarn(status,"elvishray::GlobalNodeHelper::getInt("+attrName+")");
	return value;
}
MString GlobalNodeHelper::getString(const MString& attrName)
{
	MStatus status;
	MString value;
	liquidGetPlugValue(m_GlobalNode, attrName.asChar(), value, status);
	IfMErrorMsgWarn(status,"elvishray::GlobalNodeHelper::getString("+attrName+")");
	return value;
}
float GlobalNodeHelper::getFloat(const MString& attrName)
{
	MStatus status;
	float value;
	liquidGetPlugValue(m_GlobalNode, attrName.asChar(), value, status);
	IfMErrorMsgWarn(status,"elvishray::GlobalNodeHelper::getFloat("+attrName+")");
	return value;
}
double GlobalNodeHelper::getDouble(const MString& attrName)
{
	MStatus status;
	double value;
	liquidGetPlugValue(m_GlobalNode, attrName.asChar(), value, status);
	IfMErrorMsgWarn(status,"elvishray::GlobalNodeHelper::getDouble("+attrName+")");
	return value;
}
// MFloatVector GlobalNodeHelper::getVector3(const MString& attrName )
// {
//  	MStatus status;
//  	MFloatVector value(-1.0f, -1.0f, -1.0f);
// // 	liquidGetPlugValue(m_GlobalNode, attrName.asChar(), value, status);
// // 	IfMErrorMsgWarn(status,"elvishray::GlobalNodeHelper::getVector("+attrName+")"
// 	MStringArray a(getStringArray(attrName));
// 	switch(a.length())
// 	{
// 		case 1: 
// 			value.x = a[0].asFloat();	
// 			break;
// 		case 2: 
// 			value.x = a[0].asFloat(); 
// 			value.y = a[1].asFloat();	
// 			break;
// 		case 3: 
// 			value.x = a[0].asFloat();
// 			value.y = a[1].asFloat();
// 			value.z = a[2].asFloat();	
// 			break;
// 		default:
// 			liquidMessage2(messageError, "GlobalNodeHelper::getVector3(%s), sub-element length=%d", attrName.asChar(), a.length());
// 	}
// 	return value;
// }
MFloatPoint GlobalNodeHelper::getVector(const MString& attrName )
{
 	MStatus status;
 	MFloatPoint value(-1.0f, -1.0f, -1.0f, -1.0f);
// 	liquidGetPlugValue(m_GlobalNode, attrName.asChar(), value, status);
// 	IfMErrorMsgWarn(status,"elvishray::GlobalNodeHelper::getVector("+attrName+")"
	MStringArray a(getStringArray(attrName));
	switch(a.length())
	{
		case 4: value.w = a[3].asFloat();
		case 3: value.z = a[2].asFloat();
		case 2: value.y = a[1].asFloat();
		case 1: value.x = a[0].asFloat(); break;
		default:
			liquidMessage2(messageError, "GlobalNodeHelper::getVector(%s), sub-element length=%d", attrName.asChar(), a.length());
	}
	return value;
}
MStringArray GlobalNodeHelper::getStringArray(const MString& attrName )
{
	MStatus status;

	MString strValue;
	liquidGetPlugValue(m_GlobalNode, attrName.asChar(), strValue, status);
	IfMErrorMsgWarn(status,"elvishray::GlobalNodeHelper::getStringArray("+attrName+")");
	
	MStringArray value;
	status = strValue.split('|', value);
	IfMErrorMsgWarn(status,"elvishray::GlobalNodeHelper::getStringArray --> split["+strValue+"] error.");

	return value;
}

}