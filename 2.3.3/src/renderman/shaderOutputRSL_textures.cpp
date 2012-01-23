#include "shaderOutputRSL.h"
#include "../common/mayacheck.h"
#include "../shadergraph/shadermgr.h"
#include "ri_interface.h"

namespace RSL
{
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
//
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