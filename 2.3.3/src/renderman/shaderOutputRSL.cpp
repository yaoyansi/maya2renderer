#include "shaderOutputRSL.h"
#include <liqlog.h>
#include <liqShader.h>
#include <liqShaderFactory.h>
#include "../common/mayacheck.h"
#include "../shadergraph/convertShadingNetwork.h"
#include "../shadergraph/shadermgr.h"
#include "ri_interface.h"

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
void OutputHelper::beginRSL (const MString& $name)
{
	// "Open" the header and body.
	//
	rslShaderHeader = ( "void " + $name + " (\n" );
	rslShaderBody = "{\n";
}
//
void OutputHelper::endRSL ()
{
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
void Visitor::preOutput(const char* shaderNodeName)
{
	this->shaderNodeName = shaderNodeName;
}
void Visitor::outputBegin(const char* shaderNodeName)
{
	RSLfile.open( (getShaderDirectory()+shaderNodeName+".sl_my").asChar() );
}
void Visitor::outputUpstreamShader(const char* shaderNodeName)
{
	MString nodetype;
	IfMErrorWarn(MGlobal::executeCommand( ("nodeType \""+MString(shaderNodeName)+"\""), nodetype));

	_outputUpstreamShader(shaderNodeName, nodetype.asChar());
}
void Visitor::outputShaderMethod(const char* shaderName,
						const char* shaderMethodVariavles,const char* shaderMethodBody)
{
	RSLfile << "surface " << shaderName << "()\n{\n";
	RSLfile << shaderMethodVariavles;
	RSLfile << "\n";
	RSLfile << shaderMethodBody;
	RSLfile << "}\n";
}
void Visitor::outputEnd()
{
	RSLfile.close();
}
void Visitor::postOutput()
{
	//compile the shader
	MString shaderdir(getShaderDirectory());
	MString outSLO(shaderdir+shaderNodeName.c_str()+".slo");
	MString srcSL (shaderdir+shaderNodeName.c_str()+".sl_my");

	//"shader.exe -o \"outSLO\" \"srcSL\""
	IfMErrorWarn(MGlobal::executeCommand("system(\"shader -o \\\""+outSLO+"\\\" \\\""+srcSL+"\\\"\")", true));

}
void Visitor::outputShadingGroup(const char* shadingGroupNode)
{
	MString cmd;

	MStringArray surfaceShaders;
	MStringArray volumeShaders;
	MStringArray displacementShaders;
	{
		cmd = "listConnections (\""+MString(shadingGroupNode)+"\" + \".surfaceShader\")";
		IfMErrorWarn(MGlobal::executeCommand( cmd, surfaceShaders));

		cmd = "listConnections (\""+MString(shadingGroupNode)+"\" + \".volumeShader\")";
		IfMErrorWarn(MGlobal::executeCommand( cmd, volumeShaders));

		cmd = "listConnections (\""+MString(shadingGroupNode)+"\" + \".displacementShader\")";
		IfMErrorWarn(MGlobal::executeCommand( cmd, displacementShaders));
	}

	// Work out where to put it & make sure the directory exists

	MString shaderdir(getShaderDirectory());
	MString shadingGroupFileName(shaderdir+shadingGroupNode);

	//RiOption( tokenCast("RI2RIB_Output"), "Type", (RtPointer)tokenCast("Ascii"),RI_NULL );
	RtContextHandle c = RiGetContext();//push context;
	{
		RiBegin( const_cast<RtToken>((shadingGroupFileName+".rmsg").asChar()));
		RiArchiveRecord(RI_COMMENT, "shading group: %s", shadingGroupNode);
		//surface shader
		if( surfaceShaders[0].length() != 0 ){
			MString nodetype;
			getShaderType(nodetype, surfaceShaders[0]);
			if( nodetype == "liquidSurface" ){
				liqShader& currentShader = 
					liqShaderFactory::instance().getShader( getMObjectByName(surfaceShaders[0]) );
				currentShader.write();
			}else{
				RiSurface( const_cast<char *>((shaderdir+surfaceShaders[0]).asChar()), RI_NULL );
			}
		}else{
			RiArchiveRecord(RI_COMMENT, "no surface shader.");
		}
		//volume shader
		if( volumeShaders[0].length() != 0 ){
			MString nodetype;
			getShaderType(nodetype, volumeShaders[0]);
			if( nodetype == "liquidVolume" ){
				liqShader& currentShader = 
					liqShaderFactory::instance().getShader( getMObjectByName(volumeShaders[0]) );
				currentShader.write();
			}else{
				RiArchiveRecord(RI_COMMENT, "I'm not sure which one should be used for the volume shader, RiAtmosphere(), RiInterior(), or RiExterior().");
				RiAtmosphere( const_cast<char *>((shaderdir+volumeShaders[0]).asChar()), RI_NULL );
			}
		}else{
			RiArchiveRecord(RI_COMMENT, "no volume shader.");
		}
		//displacement shader
		if( displacementShaders[0].length() != 0 ){
			MString nodetype;
			getShaderType(nodetype, displacementShaders[0]);
			if( nodetype == "liquidDisplacement" ){
				liqShader& currentShader = 
					liqShaderFactory::instance().getShader( getMObjectByName(displacementShaders[0]) );
				currentShader.write();
			}else{
				RiArchiveRecord(RI_COMMENT, "I'm not sure which one should be used for the displacement shader, RiDeformation(), or RiDisplacement().");
				RiDisplacement( const_cast<char *>((shaderdir+displacementShaders[0]).asChar()), RI_NULL );
			}
		}else{
			RiArchiveRecord(RI_COMMENT, "no displacement shader.");
		}
		RiEnd();
	}
	RiContext(c);//pop context



}
//
void Visitor::visitLambert(const char* node)
{
	OutputHelper o(RSLfile);

	o.beginRSL(node);

	o.addRSLVariable("vector", "inColor",		"color",		node);
	o.addRSLVariable("vector", "transparency", "transparency", node);
	o.addRSLVariable("vector", "ambientColor",	"ambientColor", node);
	o.addRSLVariable("vector", "incandescence","incandescence",node);
	o.addRSLVariable("float",  "diffusion",	"diffuse",		node);
	o.addRSLVariable("vector", "outColor",		"outColor",		node);
	o.addRSLVariable("vector", "outTransparency","outTransparency",node);

	o.addToRSL( "extern normal N;");
	o.addToRSL( "normal Nn = normalize( N );");
	o.addToRSL( "outTransparency = transparency;");
	o.addToRSL( "Oi = Os * color ( 1 - outTransparency );");
	o.addToRSL( "outColor = incandescence +");
	o.addToRSL( "           ( inColor * ( diffusion * ");
	o.addToRSL( "                         vector diffuse( Nn ) +");
	o.addToRSL( "                         ambientColor ) );");
	o.addToRSL( "Ci = Cs * Oi * color outColor;");

	o.endRSL();
}
void Visitor::visitBlinn(const char* node)
{
	OutputHelper o(RSLfile);

	o.beginRSL(node);

	o.addRSLVariable("vector", "inColor",		"color",		node);
	o.addRSLVariable("vector", "transparency", "transparency", node);
	o.addRSLVariable("vector", "ambColor",		"ambientColor", node);
	o.addRSLVariable("vector", "incandescence","incandescence",node);
	o.addRSLVariable("float",  "diffusion",	"diffuse",		node);
	o.addRSLVariable("float",  "eccentricity", "eccentricity", node);
	o.addRSLVariable("float",  "specRollOff",	"specularRollOff",node);
	o.addRSLVariable("vector", "specColor",	"specularColor",node);
	o.addRSLVariable("vector", "outColor",		"outColor",		node);

	o.addToRSL( "extern normal N;");
	o.addToRSL( "normal Nn = normalize( N );");
	o.addToRSL( "Oi = Os * color ( 1 - transparency );");
	o.addToRSL( "vector Cdiffuse;");
	o.addToRSL( "Cdiffuse = incandescence +");
	o.addToRSL( "           ( inColor * ( diffusion * ");
	o.addToRSL( "                         vector diffuse( Nn ) +");
	o.addToRSL( "                         ambColor ) );");
	o.addToRSL( "vector Cspecular = 0;");
	o.addToRSL( "float eccSq = pow( eccentricity, 2 );");
	o.addToRSL( "vector V = normalize( -I );");
	o.addToRSL( "float NV = Nn . V;");
	o.addToRSL( "illuminance( P, Nn, PI / 2 )");
	o.addToRSL( "{");
	o.addToRSL( " vector Ln = normalize( L );");
	o.addToRSL( " vector H = normalize( V + Ln );");
	o.addToRSL( " float NH = Nn . H;");
	o.addToRSL( " float NL = Nn . Ln;");
	o.addToRSL( " float VH = V . H;");
	o.addToRSL( " float D = pow( eccSq / ");
	o.addToRSL( "                ( pow( NH, 2 ) * ");
	o.addToRSL( "                  ( eccSq - 1 ) + 1 ), 2 );");
	o.addToRSL( " float G = min( min( 1, 2 * NH * NV / VH ), ");
	o.addToRSL( "                2 * NH * NL / VH );");
	o.addToRSL( " Cspecular += ( vector Cl * ( D * G / NV ) );");
	o.addToRSL( "}");

	MStringArray con;
	IfMErrorWarn(MGlobal::executeCommand( ("listConnections(\""+MString(node)+"\" + \".reflectedColor\")"), con));
	if( con.length() != 0 )
	{
		o.addRSLVariable( "float", "reflectivity", "reflectivity", node);
		o.addRSLVariable( "vector", "refColor", "reflectedColor", node);
		o.addToRSL( "Cspecular += ( reflectivity * refColor );");
	}
	o.addToRSL( "Cspecular *= specColor;");
	o.addToRSL( "Cspecular *= mix( 1, specRollOff, );");
	o.addToRSL( "outColor = Cdiffuse + Cspecular;");
	o.addToRSL( "Ci = Cs * Oi * color outColor;");

	o.endRSL();
}
//
void Visitor::visitFile(const char* node)
{	
	OutputHelper o(RSLfile);

	o.beginRSL( node );

	o.addRSLVariable( "float2", "uvCoord", "uvCoord",node);
	o.addRSLVariable( "vector", "outColor", "outColor", node);

	MString mayaTexName;
	IfMErrorWarn(MGlobal::executeCommand("getAttr (\""+MString(node)+".fileTextureName\")", mayaTexName));
	MString texName = mayaTexName + ".tex";
	//system("txmake mayaTexName texName");
	IfMErrorWarn(MGlobal::executeCommand("system(\"txmake "+mayaTexName+" "+texName+"\")", true));

	o.addToRSL( "string texName = \"" + texName + "\";" );
	o.addToRSL( "float ss = uvCoord[ 0 ], tt = uvCoord[ 1 ];");
	o.addToRSL( "outColor = vector color texture( texName, ss, tt );");

	int connected = liquidmaya::ShaderMgr::getSingletonPtr()->
		convertibleConnection((MString(node)+".outTransparency").asChar());

	if( connected )
	{
		o.addRSLVariable( "vector", "outTrans", "outTransparency", node);
		o.addToRSL( "float alpha = float texture( texName[3], ss, tt );");
		o.addToRSL( "outTrans = vector ( 1 -  alpha );");
	}

	o.endRSL();
}
void Visitor::visitPlace2dTexture(const char* node)
{
	OutputHelper o(RSLfile);

	o.beginRSL(node);

	o.addRSLVariable("float2", "repeatUV", "repeatUV", node);
	o.addRSLVariable("float2", "outUV", "outUV", node);

	o.addToRSL("extern float s, t;");
	o.addToRSL("outUV[ 0 ] = mod( t * repeatUV[ 0 ], 1 );");
	o.addToRSL("outUV[ 1 ] = mod( s * repeatUV[ 1 ], 1 );");

	o.endRSL();
}
void Visitor::visitChecker(const char* node)
{
	OutputHelper o(RSLfile);

	o.beginRSL(node);

	int connected;
	//color1
	connected = liquidmaya::ShaderMgr::getSingletonPtr()->
		convertibleConnection((MString(node)+".color1").asChar());
	if( connected )
	{
        o.addRSLVariable( "vector", "color1", "color1", node);
    }else{
        o.addRSLVariable( "float", "color1R", "color1R", node);
        o.addRSLVariable( "float", "color1G", "color1G", node);
        o.addRSLVariable( "float", "color1B", "color1B", node);
        o.addToRSL( "vector color1 = vector ( color1R, color1G, color1B );" );
	}
	//color2
	connected = liquidmaya::ShaderMgr::getSingletonPtr()->
		convertibleConnection((MString(node)+".color2").asChar());
	if( connected )
	{
		o.addRSLVariable( "vector", "color2", "color2", node);
	}else{
		o.addRSLVariable( "float", "color2R", "color2R", node);
		o.addRSLVariable( "float", "color2G", "color2G", node);
		o.addRSLVariable( "float", "color2B", "color2B", node);
		o.addToRSL( "vector color2 = vector ( color2R, color2G, color2B );" );
	}
	//uvCoord
	connected = liquidmaya::ShaderMgr::getSingletonPtr()->
		convertibleConnection((MString(node)+".uvCoord").asChar());
	if( connected )
	{
		o.addRSLVariable( "float2", "uvCoord", "uvCoord", node);
		o.addToRSL( "float ss = uvCoord[0];");
		o.addToRSL( "float tt = uvCoord[1];");
	}else{
		o.addRSLVariable( "float", "ss", "uCoord", node);
		o.addRSLVariable( "float", "tt", "vCoord", node);
	}
	//outColor
	int outColorConnected = liquidmaya::ShaderMgr::getSingletonPtr()->
		convertibleConnection((MString(node)+".outColor").asChar());
	if( outColorConnected )
	{
		o.addRSLVariable( "vector", "outColor", "outColor", node);

		o.addToRSL( "if( floor( ss * 2 ) == floor( tt * 2 ) )");
		o.addToRSL( "{");
		o.addToRSL( " outColor = color1;");
		o.addToRSL( "}else{");
		o.addToRSL( " outColor = color2;");
		o.addToRSL( "}");
	}else{
		o.addRSLVariable( "float", "outColorR", "outColorR", node);
		o.addRSLVariable( "float", "outColorG", "outColorG", node);
		o.addRSLVariable( "float", "outColorB", "outColorB", node);
		o.addToRSL( "vector outColor = vector ( outColorR, outColorG, outColorB );" );
		
		o.addToRSL( "if( floor( ss * 2 ) == floor( tt * 2 ) )");
		o.addToRSL( "{");	
		o.addToRSL( " outColorR = color1R;");
		o.addToRSL( " outColorG = color1G;");
		o.addToRSL( " outColorB = color1B;");
		o.addToRSL( "}else{");
		o.addToRSL( " outColorR = color2R;");
		o.addToRSL( " outColorG = color2G;");
		o.addToRSL( " outColorB = color2B;");
		o.addToRSL( "}");
	}

	o.endRSL();
}
}//namespace RSL