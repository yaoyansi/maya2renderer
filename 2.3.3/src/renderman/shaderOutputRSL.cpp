#include "shaderOutputRSL.h"
#include <liqlog.h>
#include <liqShader.h>
#include <liqShaderFactory.h>
#include "../common/mayacheck.h"
#include "../shadergraph/convertShadingNetwork.h"
#include "../shadergraph/shadermgr.h"
#include "ri_interface.h"
#include "rm_helper.h"

namespace RSL
{
	MObject getMObjectByName(const MString& name)
	{
		MSelectionList sList;
		MGlobal::getSelectionListByName(name, sList);
		assert(1==sList.length());
		
		MObject mobj;
		sList.getDependNode(0, mobj);
		return mobj;
	}
	void connectMStringArray(MString& des, const MStringArray& src)
	{
		des.clear();
		for(std::size_t i=0; i<src.length(); ++i){
			des += src[ i ] + ",";
		}
	}
//////////////////////////////////////////////////////////////////////////
OutputHelper::OutputHelper(std::ofstream& RSLfile)
:RSLfileRef(RSLfile)
{
	assert(RSLfileRef.is_open());
}
//
OutputHelper::~OutputHelper()
{

}
//
void OutputHelper::addRSLVariable(MString rslType, const MString& rslName,
					const MString& mayaName, const MString& mayaNode)
{
	MString cmd;

	// If the user specified that the type was an array of floats
	// (eg "float2"), extract the size and set the type to float.
	int rslTypeSize = 1;

	MString matchedStr;
	IfMErrorWarn(MGlobal::executeCommand("match(\"float[0-9]+$\",\""+rslType+"\")", matchedStr));
	if(matchedStr != "")
	{
		IfMErrorWarn(MGlobal::executeCommand("match(\"[0-9]+$\",\""+rslType+"\")", matchedStr));
		rslTypeSize = matchedStr.asInt();
		rslType = "float";
	}

	// Create the plug's name, and check for convertible connections.
	MString plug(mayaNode+"."+mayaName);
	int connected = liquidmaya::ShaderMgr::getSingletonPtr()->convertibleConnection(plug.asChar());

	// If there are no convertible connections, then we have to
	// write out the variable into the shader's body.
	if( connected == 0 )
	{
		//rslTypeSize(int) --> rslTypeSizeStr(string)
		MString rslTypeSizeStr;
		rslTypeSizeStr.set(rslTypeSize);
		// Write out the description of the variable.
		rslShaderBody += (" " + rslType + " " + rslName);
		rslShaderBody += ( rslTypeSize != 1 )?
							 ( "[" + rslTypeSizeStr + "] = " )
							:( " = " + rslType + " " );

		// Write out the value of the variable.
		if(   rslType=="color"
			||rslType=="point"
			||rslType=="normal"
			||rslType=="vector")
		{
			MDoubleArray val; val.setLength(3);
			IfMErrorWarn(MGlobal::executeCommand("getAttr \""+plug+"\"", val));
			//val(double) --> valStr(string)
			MStringArray valStr; valStr.setLength(3);
			valStr[0].set(val[0]);
			valStr[1].set(val[1]);
			valStr[2].set(val[2]);
			rslShaderBody +="("+valStr[0]+","+valStr[1]+","+valStr[2]+")";
		}else if(rslType=="string"){
			MString val;
			IfMErrorWarn(MGlobal::executeCommand("getAttr \""+plug+"\"", val));
			rslShaderBody +="\""+val+"\"";
		}else if(rslType=="float"){
			if(rslTypeSize == 1){
				double val;
				IfMErrorWarn(MGlobal::executeCommand("getAttr \""+plug+"\"", val));
				//val(double) --> valStr(string)
				MString valStr;
				valStr.set(val);
				rslShaderBody += valStr;
			}else{
				rslShaderBody += "{ ";
				MDoubleArray val; val.setLength(rslTypeSize);
				IfMErrorWarn(MGlobal::executeCommand("getAttr \""+plug+"\"", val));
				for(int i=0; i<rslTypeSize; ++i){
					if( i != 0 ){
						rslShaderBody += ", ";
					}
					//val[i](double) --> valStr(string)
					MString valStr;
					valStr.set(val[i]);
					rslShaderBody += valStr;
				}
				rslShaderBody += " }";
			}
		}
		rslShaderBody += ";\n";
	}//if( $connected == 0 )
	// Otherwise, we have a convertible connection, so we'll be
	// adding the variable to the block's header.
	else{
		rslShaderHeader += " ";

		// Note if it's connected as an output.
		if(connected == 2){
			rslShaderHeader += "output ";
		}

		// Write out the description.
		rslShaderHeader += ( rslType + " " + rslName );
		if( rslTypeSize != 1 )
		{
			rslShaderHeader += "[]";
		}
		rslShaderHeader += ";\n";

		//
		if(connected == 1)
		{
			MStringArray srcPlug;
			IfMErrorWarn(MGlobal::executeCommand("listConnections -source true -plugs true \""+plug+"\"", srcPlug));
			assert(srcPlug.length()==1);
			rslShaderBody +="//"+plug+" <-- "+srcPlug[0]+"\n";
		}

	}//else
}
//
void OutputHelper::addToRSL(const MString& code)
{
	rslShaderBody += (" "+code+"\n");
}
//
void OutputHelper::beginRSL (const MString& name)
{
	CM_TRACE_FUNC("OutputHelper::beginRSL("<<name<<")");

	// "Open" the header and body.
	//
	rslShaderHeader  = ( "//shader name: " + name + "\n" );
	rslShaderHeader += ( "void " + renderman::getShaderName(name) + " (\n" );
	rslShaderBody = "{\n";
}
//
void OutputHelper::endRSL ()
{
	CM_TRACE_FUNC("OutputHelper::endRSL()");

	// "Close" the header and body.
	//
	rslShaderHeader += ")\n";
	rslShaderBody += "}\n";

	RSLfileRef << rslShaderHeader + rslShaderBody + "\n" ;
}
//////////////////////////////////////////////////////////////////////////
Visitor::Visitor()
{

}
//
Visitor::~Visitor()
{

}
//
void Visitor::initShaderData(const MString& startingNode, const MString &mayaplug)
{
	CM_TRACE_FUNC("Visitor::initShaderData("<<startingNode<<","<<mayaplug<<")");

	shaderType = getRSLShaderType(mayaplug);

	shaderData.setLength(3);
	shaderData[SHADER_METHOD_VARIAVLES_I] = "";// shader method variables
	shaderData[SHADER_METHOD_BODY_I]      = "";// shader method body
	shaderData[SHADER_NAME_I]             = startingNode;// shader name

}
void Visitor::preOutput(const char* shaderNodeName)
{
	CM_TRACE_FUNC("Visitor::preOutput("<<shaderNodeName<<")");

	this->shaderNodeName = shaderNodeName;
}
void Visitor::outputBegin(const char* shaderNodeName)
{
	CM_TRACE_FUNC("Visitor::outputBegin("<<shaderNodeName<<"), open shader file");
	RSLfile.open( renderman::getShaderFilePath_SRC(shaderNodeName).asChar() );
}
void Visitor::outputUpstreamShader(const char* shaderNodeName)
{
	CM_TRACE_FUNC("Visitor::outputUpstreamShader("<<shaderNodeName<<")");

	MString nodetype;
	IfMErrorWarn(MGlobal::executeCommand( ("nodeType \""+MString(shaderNodeName)+"\""), nodetype));

	_outputUpstreamShader(shaderNodeName, nodetype.asChar());
}
void Visitor::outputShaderMethod()
{
	CM_TRACE_FUNC("Visitor::outputShaderMethod()");

	RSLfile << "//surface shader name: " << shaderData[SHADER_NAME_I] << "\n";
	RSLfile << shaderType<<" " << renderman::getShaderName(shaderData[SHADER_NAME_I]) << "()\n{\n";
	RSLfile << shaderData[SHADER_METHOD_VARIAVLES_I];
	RSLfile << "\n";
	RSLfile << shaderData[SHADER_METHOD_BODY_I];
	RSLfile << "}\n";
}
void  Visitor::addShaderMethodBody(
						 const MString &currentNode,
						 const MStringArray& inputVars,
						 const MStringArray& outputVars)
{
	CM_TRACE_FUNC("Visitor::addShaderMethodBody("<<currentNode<<","<<inputVars<<","<<outputVars<<")");

	MString varString;
	{
		MStringArray vars;
		for(std::size_t i=0; i<inputVars.length(); ++i){
			vars.append( renderman::getVariableName(inputVars[i]) );
		}
		for(std::size_t i=0; i<outputVars.length(); ++i){
			vars.append( renderman::getVariableName(outputVars[i]) );
		}

		for(std::size_t index=0; index<vars.length(); ++index){
			varString += (index == vars.length() - 1)?(vars[index]):(vars[index]+", ");
		}
	}

	// Add the current node method to the shader body
	shaderData[ SHADER_METHOD_BODY_I ] += " //" + currentNode +"\n";
	shaderData[ SHADER_METHOD_BODY_I ] += " " + renderman::getShaderName(currentNode) +"("+varString+");\n";
	
	// test the input and output of currentNode
	{	
		MString inputVarsStr; 
		MString outputVarsStr;
		connectMStringArray(inputVarsStr, inputVars);
		connectMStringArray(outputVarsStr, outputVars);
		shaderData[ SHADER_METHOD_BODY_I ] += "//input: " + inputVarsStr +"\n";
		shaderData[ SHADER_METHOD_BODY_I ] += "//output:" + outputVarsStr +"\n\n";
	}
}
void Visitor::addShaderMethodVariavles(const MString &typeSize,
									   const MString &varName)
{
	CM_TRACE_FUNC("Visitor::addShaderMethodVariavles(&shaderMethodVariavles,"<<typeSize<<","<<varName<<")");
	if(typeSize=="")
	{
		shaderData[SHADER_METHOD_VARIAVLES_I] += " float "+renderman::getVariableName(varName)+";\n";
	}else if(typeSize=="3"){
		shaderData[SHADER_METHOD_VARIAVLES_I] += " vector "+renderman::getVariableName(varName)+";\n";
	}else{
		shaderData[SHADER_METHOD_VARIAVLES_I] += " float "+renderman::getVariableName(varName)+"["+typeSize+"];\n";
	}
}
void Visitor::outputEnd()
{
	CM_TRACE_FUNC("Visitor::outputEnd(), close shader file");
	RSLfile.close();
}
void Visitor::postOutput()
{
	CM_TRACE_FUNC("Visitor::postOutput()");

	//compile the shader
	MString shaderdir(getShaderDirectory());
	MString outSLO(renderman::getShaderFilePath_SLO(shaderNodeName.c_str()));
	MString srcSL (renderman::getShaderFilePath_SRC(shaderNodeName.c_str()));

	MString result;
	//"shader.exe -o \"outSLO\" \"srcSL\""
	IfMErrorWarn(MGlobal::executeCommand("system(\"shader -o \\\""+outSLO+"\\\" \\\""+srcSL+"\\\"\")", result, true));

	//show the error if there is.
	std::string strRes(result.toLowerCase().asChar());
	if(strRes.find("error") != std::string::npos)
	{
		liqAssert(strRes.c_str());
	}


}
void Visitor::outputShadingGroup(const char* shadingGroupNode)
{
	CM_TRACE_FUNC("Visitor::outputShadingGroup("<<shadingGroupNode<<")");

	MString cmd;

	MStringArray surfaceShaders;
	MStringArray volumeShaders;
	MStringArray displacementShaders;
	{
		getlistConnections(shadingGroupNode, "surfaceShader", surfaceShaders);

		getlistConnections(shadingGroupNode, "volumeShader", volumeShaders);

		getlistConnections(shadingGroupNode, "displacementShader", displacementShaders);
	}

	// Work out where to put it & make sure the directory exists

//	MString shaderdir(getShaderDirectory());

	//RiOption( tokenCast("RI2RIB_Output"), "Type", (RtPointer)tokenCast("Ascii"),RI_NULL );
	RtContextHandle c = RiGetContext();//push context;
	RiBegin_liq( const_cast<RtToken>(renderman::getShadingGroupFilePath(shadingGroupNode).asChar()) );
	{
		RiArchiveRecord(RI_COMMENT, "shading group: %s", shadingGroupNode);
		//surface shader
		if( surfaceShaders[0].length() != 0 ){
			MString nodetype;
			getNodeType(nodetype, surfaceShaders[0]);
			if( nodetype == "liquidSurface" ){
				liqShader& currentShader = 
					liqShaderFactory::instance().getShader( getMObjectByName(surfaceShaders[0]) );
				currentShader.write();
			}else{
				RiSurface( const_cast<char *>(renderman::getShaderFilePath_NoExt(surfaceShaders[0]).asChar()), RI_NULL );
			}
		}else{
			RiArchiveRecord(RI_COMMENT, "no surface shader.");
		}
		//volume shader
		if( volumeShaders[0].length() != 0 ){
			MString nodetype;
			getNodeType(nodetype, volumeShaders[0]);
			if( nodetype == "liquidVolume" ){
				liqShader& currentShader = 
					liqShaderFactory::instance().getShader( getMObjectByName(volumeShaders[0]) );
				currentShader.write();
			}else{
				RiArchiveRecord(RI_COMMENT, "I'm not sure which one should be used for the volume shader, RiAtmosphere(), RiInterior(), or RiExterior().");
				RiAtmosphere( const_cast<char *>(renderman::getShaderFilePath_NoExt(volumeShaders[0]).asChar()), RI_NULL );
			}
		}else{
			RiArchiveRecord(RI_COMMENT, "no volume shader.");
		}
		//displacement shader
		if( displacementShaders[0].length() != 0 ){
			MString nodetype;
			getNodeType(nodetype, displacementShaders[0]);
			if( nodetype == "liquidDisplacement" ){
				liqShader& currentShader = 
					liqShaderFactory::instance().getShader( getMObjectByName(displacementShaders[0]) );
				currentShader.write();
			}else{
				RiArchiveRecord(RI_COMMENT, "I'm not sure which one should be used for the displacement shader, RiDeformation(), or RiDisplacement().");
				RiDisplacement( const_cast<char *>(renderman::getShaderFilePath_NoExt(displacementShaders[0]).asChar()), RI_NULL );
			}
		}else{
			RiArchiveRecord(RI_COMMENT, "no displacement shader.");
		}
	}
	RiEnd();
	RiContext(c);//pop context
}
MString Visitor::getRSLShaderType(const MString &mayaplug)
{
	MString shaderType;

	if(mayaplug=="surfaceShader"){
		shaderType = "surface";
	}else if(mayaplug=="displacementShader"){
		shaderType = "displacement";
	}else if(mayaplug=="volumeShader"){
		shaderType = "volume";
	}else{
		liquidMessage2(messageError,"unkown shader type for plug %s", mayaplug.asChar());
	}
	return shaderType;
}
//
}//namespace RSL