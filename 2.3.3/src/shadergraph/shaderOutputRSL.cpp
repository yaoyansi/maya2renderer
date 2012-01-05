#include "shaderOutputRSL.h"
#include <liqlog.h>
#include "../common/mayacheck.h"
#include "convertShadingNetwork.h"
#include "shadermgr.h"
#include "mayashader_materials.h"

namespace liquidmaya
{

RSLShaderHelper::RSLShaderHelper(std::ofstream& RSLfile)
:RSLfileRef(RSLfile)
{
	assert(RSLfileRef.is_open());
}
//
RSLShaderHelper::~RSLShaderHelper()
{

}
//
void RSLShaderHelper::addRSLVariable(MString rslType, const MString& rslName,
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
	int connected = ShaderMgr::getSingletonPtr()->convertibleConnection(plug.asChar());

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
void RSLShaderHelper::addToRSL(const MString& code)
{
	rslShaderBody += (" "+code+"\n");
}
//
void RSLShaderHelper::beginRSL (const MString& $name)
{
	// "Open" the header and body.
	//
	rslShaderHeader = ( "void " + $name + " (\n" );
	rslShaderBody = "{\n";
}
//
void RSLShaderHelper::endRSL ()
{
	// "Close" the header and body.
	//
	rslShaderHeader += ")\n";
	rslShaderBody += "}\n";

	RSLfileRef << rslShaderHeader + rslShaderBody + "\n" ;
}
//////////////////////////////////////////////////////////////////////////
RSL::RSL()
{

}
//
RSL::~RSL()
{

}
//

//
void RSL::_outputUpstreamShader(const char* shaderNodeName, const char* nodetype)
{
	if( strcmp("lambert", nodetype) == 0 )
	{
		Lambert::writeRSL(shaderNodeName, RSLfile);
	}
	else if( strcmp("blinn", nodetype) == 0 ){
		Blinn::writeRSL(shaderNodeName, RSLfile);
	}
	//else if(...){}
	else{
		liquidMessage2(messageError, ("shader type <"+std::string(nodetype)+"> is not supported.").c_str() );
		assert( 0 && "shader type is not support.");
	}
}
//
void RSL::outputBegin(const char* startingNode)
{
	// Work out where to put it & make sure the directory exists
	MString wsdir;
	IfMErrorWarn(MGlobal::executeCommand( "workspace -q -rd", wsdir));
	MString shaderdir;
	IfMErrorWarn(MGlobal::executeCommand( "getAttr \"liquidGlobals.shaderDirectory\"", shaderdir));
	shaderdir = wsdir + shaderdir;
	
	MString shaderFileName;
	IfMErrorWarn(MGlobal::executeCommand( "toLinuxPath(\""+shaderdir+"/"+MString(startingNode)+"\")", shaderFileName));

	RSLfile.open( (shaderFileName+".er").asChar() );
}
void RSL::outputUpstreamShader(const char* shaderNodeName)
{
	MString nodetype;
	IfMErrorWarn(MGlobal::executeCommand( ("nodeType \""+MString(shaderNodeName)+"\""), nodetype));

	_outputUpstreamShader(shaderNodeName, nodetype.asChar());
}
void RSL::outputShaderMethod(const char* shaderName,
						const char* shaderMethodVariavles,const char* shaderMethodBody)
{
	RSLfile << "surface " << shaderName << "()\n{\n";
	RSLfile << shaderMethodVariavles;
	RSLfile << "\n";
	RSLfile << shaderMethodBody;
	RSLfile << "}\n";
}
void RSL::outputEnd()
{
	RSLfile.close();
}
//
}//namespace liquidmaya