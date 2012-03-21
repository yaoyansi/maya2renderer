#include "shaderOutputRSL.h"
#include "../common/mayacheck.h"
#include "ri_interface.h"

namespace RSL
{
//

//
// @node	maya shader node name
void Visitor::visitAnisotropic(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
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
// @node	maya shader node name
void Visitor::visitHairTubeShader(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
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
// @node	maya shader node name
void Visitor::visitLayeredShader(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitOceanShader(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitPhong(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);

	o.addRSLVariable( "vector", "inColor",			"color",		node);
	o.addRSLVariable( "vector", "transparency",		"transparency", node);
	o.addRSLVariable( "vector", "ambColor",			"ambientColor", node);
	o.addRSLVariable( "vector", "incandescence",	"incandescence",node);
	o.addRSLVariable( "float",  "diffusion",		"diffuse",		node);
	o.addRSLVariable( "float",  "cosinePower",		"cosinePower",	node);
	o.addRSLVariable( "vector", "specColor",		"specularColor",node);
	o.addRSLVariable( "vector", "outColor",			"outColor",		node);
	o.addRSLVariable( "vector", "outTransparency",	"outTransparency", node);

	o.addToRSL("extern normal N;");
	o.addToRSL("normal Nn = normalize( N );");
	o.addToRSL("outTransparency = transparency;");
	o.addToRSL("Oi = Os * color ( 1 - outTransparency );");
	o.addToRSL("vector Cdiffuse;");
	o.addToRSL("Cdiffuse = incandescence +");
	o.addToRSL("           ( inColor * ( diffusion * ");
	o.addToRSL("                         vector diffuse( Nn ) +");
	o.addToRSL("                         ambColor ) );");
	o.addToRSL("vector Cspecular;");
	o.addToRSL("Cspecular = vector phong( Nn,");
	o.addToRSL("                          normalize( -I ),");
	o.addToRSL("                          cosinePower );");

	MStringArray con;
	IfMErrorWarn(MGlobal::executeCommand( ("listConnections(\""+MString(node)+"\" + \".reflectedColor\")"), con));
	if( con.length() != 0 )
	{
		o.addRSLVariable("float", "reflectivity", "reflectivity", node);
		o.addRSLVariable("vector", "refColor", "reflectedColor", node);
		o.addToRSL("Cspecular += ( reflectivity * refColor );");
	}
	o.addToRSL("Cspecular *= specColor;");
	o.addToRSL("outColor = Cdiffuse + Cspecular;");
	o.addToRSL("Ci = Cs * Oi * color outColor;");

	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitPhongE(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitRampShader(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitShadingMap(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSurfaceShader(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitUseBackground(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// Volumetric ///
// @node	maya shader node name
void Visitor::visitEnvFog(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitFluidShape(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitLightFog(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitParticleCloud(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitVolumeFog(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitVolumeShader(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
/// DISPLACEMENT ///
// @node	maya shader node name
void Visitor::visitCMuscleShader(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitDisplacementShader(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}

/// Lights ///
// @node	maya shader node name
void Visitor::visitAmbientLight(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitAreaLight(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitDirectionalLight(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitPointLight(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitSpotLight(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}
// @node	maya shader node name
void Visitor::visitVolumeLight(const char* node)
{
	OutputHelper o(RSLfile);
	o.beginRSL(node);
	o.addToRSL("//the type of node '"+MString(node)+"' is not implemented yet. And don't forget to add the valid connections of this type to ShaderValidConnection::setValidConnection()");
	o.endRSL();
}

}//namespace RSL