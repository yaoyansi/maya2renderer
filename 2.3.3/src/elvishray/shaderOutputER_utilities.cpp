#include "shaderOutputER.h"
#include <liqlog.h>
#include "../common/mayacheck.h"
#include "er_GlobalNodeHelper.h"
//#include "../shadergraph/shadermgr.h"

namespace ER
{
/// General utilities ///
// @node	maya shader node name
void Visitor::visitArrayMapper(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitBump2d(const char* node)
{
	std::vector<MString> deferedCmd;
	{
		//add bumpNormal
		MString attr("bumpNormal");
		MString cmd;
		cmd ="addAttr -hidden true -k true -longName \""+attr+"\" -at \"double3\" \""+MString(node)+"\";\n";
		cmd+="addAttr -hidden true -k true -longName (\""+attr+"a\") -at \"double\" -parent \""+attr+"\" \""+MString(node)+"\";\n";
		cmd+="addAttr -hidden true -k true -longName (\""+attr+"b\") -at \"double\" -parent \""+attr+"\" \""+MString(node)+"\";\n";
		cmd+="addAttr -hidden true -k true -longName (\""+attr+"c\") -at \"double\" -parent \""+attr+"\" \""+MString(node)+"\";\n";
		cmd+="setAttr (\""+MString(node)+".bumpNormal\") -type \"double3\" -1 -1 -1;\n";
		liquidMessage2(messageInfo,"cmd:%s", cmd.asChar());
		IfMErrorMsgWarn(MGlobal::executeCommand(cmd), cmd);
		//deferedCmd.push_back("myDeleteAttr(\""+MString(node)+"\",\""+attr+"\", 1)");
		
		//
		MStringArray srcNode;
		IfMErrorWarn(MGlobal::executeCommand("listConnections -source true "+MString(node)+".bumpValue", srcNode));
		assert(srcNode.length()==1);
		//connect file.outColor to bumpNormal
		cmd="connectAttr -f "+srcNode[0]+".outColor "+MString(node)+".bumpNormal";
		IfMErrorMsgWarn(MGlobal::executeCommand(cmd), cmd);
		//deferedCmd.push_back("disconnectAttr "+srcNode[0]+".outColor "+MString(node)+".bumpNormal");

		//set bumpInterp to ObjectSpaceNormals(2) if it is not.
		elvishray::GlobalNodeHelper h(node);
		std::size_t bumpInterp = h.getInt("bumpInterp");

		if( 2 != bumpInterp ){//ObjectSpaceNormals
			//backup the current bumpInterp value
			MString bumpInterpStr;
			bumpInterpStr.set(bumpInterp);
			//deferedCmd.push_back("setAttr "+MString(node)+".bumpInterp "+bumpInterpStr );

			bumpInterpStr.set(2);
			cmd="setAttr "+MString(node)+".bumpInterp "+bumpInterpStr;
			IfMErrorMsgWarn(MGlobal::executeCommand(cmd), cmd);
		}
	}

	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("ei_shader_param_string(\"desc\", \"maya_bump2d\");");
	//input
	o.addRSLVariable("scalar",  "bumpValue",		"bumpValue",	node);
	o.addRSLVariable("scalar",  "bumpDepth",		"bumpDepth",	node);
	o.addRSLVariable("index",	"bumpInterp",		"bumpInterp",	node);
	o.addRSLVariable("scalar",  "bumpFilter",		"bumpFilter",	node);
	o.addRSLVariable("scalar",  "bumpFilterOffset",	"bumpFilterOffset",	node);
	o.addRSLVariable("normal",  "normalCamera",		"normalCamera",	node);
	if(doesPlugExist(node, "bumpNormal")){
		o.addRSLVariable("normal",  "bumpNormal",	"bumpNormal",	node);
	}
	//output
	o.addRSLVariable("normal",  "outNormal",		"outNormal",	node);

	o.endRSL();

	{
		//recover bumpInterp
		//disconnect  file.outColor with bumpNormal
		//delete bumpNormal
 		std::vector<MString>::reverse_iterator i = deferedCmd.rbegin();
 		std::vector<MString>::reverse_iterator re = deferedCmd.rend();
 		for(; i!=re; ++i)
 		{
 			liquidMessage2(messageInfo,"deferedCmd:%s", i->asChar());
 			IfMErrorMsgWarn(MGlobal::executeCommand(*i), *i);
 		}
	}
}
// @node	maya shader node name
void Visitor::visitBump3d(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitCondition(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitDistanceBetween(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitHeightField(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitLightInfo(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitMultiplyDivide(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
	void Visitor::visitPlace2dTexture(const char* node)
	{
		OutputHelper o(file);

		o.beginRSL(node);

		o.addToRSL("ei_shader_param_string(\"desc\", \"maya_place2dTexture\");");
		o.addRSLVariable("vector",  "repeatUV",	"repeatUV",	node);
		o.addRSLVariable("vector",  "outUV",	"outUV",	node);

		o.endRSL();
	}
// @node	maya shader node name
void Visitor::visitPlace3dTexture(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitPlusMinusAverage(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitProjection(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitReverse(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSamplerInfo(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSetRange(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitStencil(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitStudioClearCoat(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitUVChooser(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitVectorProduct(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// color utilities ///
// @node	maya shader node name
void Visitor::visitBlendColors(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitClamp(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitContrast(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitGammaCorrect(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitHsvToRgb(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitLuminance(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitRemapColor(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitrRemapHsv(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitRemapValue(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitRgbToHsv(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSmear(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSurfaceLuminance(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// switch utilities ///
// @node	maya shader node name
void Visitor::visitDoubleShadingSwitch(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitQuadShadingSwitch(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSingleShadingSwitch(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitTripleShadingSwitch(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// particle utilities ///	
// @node	maya shader node name
void Visitor::visitParticleSamplerInfo(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// image planes ///
// @node	maya shader node name
void Visitor::visitImagePlane(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// glow ///
// @node	maya shader node name
void Visitor::visitOpticalFX(const char* node)
{
	OutputHelper o(file);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
}//namespace ER