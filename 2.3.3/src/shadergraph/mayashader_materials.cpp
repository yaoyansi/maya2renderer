#include "mayashader_materials.h"
#include "shaderOutputMgr.h"
#include "../common/mayacheck.h"
#include "shaderOutputRSL.h"

namespace liquidmaya
{
	Lambert::Lambert()
	{
		setValidConnection();
	}
	//
	Lambert::~Lambert()
	{

	}
	//
	void Lambert::setValidConnection()
	{
		validConnection.append("color");
		validConnection.append("transparency");
		validConnection.append("ambientColor");
		validConnection.append("incandescence");
		validConnection.append("diffuse");
		validConnection.append("outColor");
		validConnection.append("outTransparency");
	}
	//
// 	void Lambert::writeRSL(const char* node, std::ofstream& RSLfile)
// 	{
// 
// 
// 	}
	//////////////////////////////////////////////////////////////////////////
	Blinn::Blinn()
	{
		setValidConnection();
	}
	//
	Blinn::~Blinn()
	{

	}
	//
	void Blinn::setValidConnection()
	{
		validConnection.append("color");
		validConnection.append("transparency");
		validConnection.append("ambientColor");
		validConnection.append("incandescence");
		validConnection.append("diffuse");
		validConnection.append("eccentricity");
		validConnection.append("specularRollOff");
		validConnection.append("specularColor");
		validConnection.append("reflectivity");
		validConnection.append("reflectedColor");
		validConnection.append("outColor");
	}
	//
// 	void Blinn::writeRSL(const char* node, std::ofstream& RSLfile)
// 	{
// 
// 	}
}