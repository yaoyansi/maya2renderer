#include "er_group.h"


namespace elvishray
{
	//---------------------------------------------------
	GroupID::GroupID()
		:/*frame(-1),*/name("")
	{}
	GroupID::GroupID(
		/*const long int frame_,*/
		const std::string &name_
		//,const std::string &layer
		)
		:/*frame(frame_),*/ name(name_)
	{

	}

	std::string GroupID::toString()
	{
		char tmp[512];
		//sprintf_s(tmp, "f%d_%s", frame, name.c_str() );
		sprintf_s(tmp, "%s", name.c_str() );

		return tmp;
	}

	bool GroupID::operator==(const GroupID &o) const
	{
		return (name==o.name);
	}
	bool GroupID::operator<(const GroupID &o) const
	{
		return (name<o.name);
	}
	//--------------------------------------------------
	Group::Group()
	{

	}
	Group::Group(const GroupID &id_)
		:/*frame(frame_),*/ id(id_)
	{

	}
	Group::~Group()
	{

	}
	void Group::addObjectInstance(const std::string &instname)
	{
		if( isExist(instname) ){
			return;
		}
		lightlink.insert( std::make_pair(MeshName(instname),LightNames()) );
	}
	void Group::addLightLink(const std::string &objInst, 
		const std::string &lightInst)
	{
		if( lightlink.find(objInst) == lightlink.end() )
		{
			// objInst not exist
			lightlink.insert( std::make_pair(MeshName(objInst),LightNames()) );
		}
		lightlink[objInst].insert(lightInst);
	}

	bool Group::isExist(const MeshName& instName)
	{
		return ( lightlink.find(instName)!=lightlink.end() ); 
	}
	LightNames Group::gatherLights()
	{
		LightNames ret;
		std::map<MeshName, LightNames>::iterator obj_i= lightlink.begin();
		std::map<MeshName, LightNames>::iterator obj_e= lightlink.end();
		for(; obj_i!=obj_e; ++obj_i)
		{
			LightNames lights = obj_i->second;
			ret.insert(lights.begin(), lights.end());
		}

		return ret;
	}
	MeshNames Group::gatherMeshs()
	{
		MeshNames ret;
		std::map<MeshName, LightNames>::iterator obj_i= lightlink.begin();
		std::map<MeshName, LightNames>::iterator obj_e= lightlink.end();
		for(; obj_i!=obj_e; ++obj_i)
		{
			ret.insert(obj_i->first);
		}

		return ret;
	}
	const LightNames& Group::getLightLinksOf(const MeshName &mesh)
	{
		return lightlink[mesh];
	}
}