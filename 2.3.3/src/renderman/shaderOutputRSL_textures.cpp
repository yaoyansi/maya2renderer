#include "shaderOutputRSL.h"
#include "../common/mayacheck.h"
#include "../shadergraph/shadermgr.h"
#include "ri_interface.h"

namespace RSL
{
/// 2D Texture ///
// @node	maya shader node name
void Visitor::visitBulge(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
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
// @node	maya shader node name
void Visitor::visitCloth(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
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
// @node	maya shader node name
void Visitor::visitFluidTexture2D(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitFractal(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitGrid(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitMountain(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitMovie(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitNoise(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitOcean(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitPSDFileTex(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitRamp(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitWater(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// 3D Textures ///
// @node	maya shader node name
void Visitor::visitBrownian(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitCloud(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitCrater(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitFluidTexture3D(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitGranite(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitLeather(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitMarbler(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitRock(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSnow(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSolidFractal(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitStucco(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitVolumeNoise(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitWood(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// Env Textures ///
// @node	maya shader node name
void Visitor::visitEnvBall(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitEnvChrome(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitEnvCube(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitEnvSky(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitEnvSphere(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// other textures ///
// @node	maya shader node name
void Visitor::visitLayeredTexture(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}

}//namespace RSL