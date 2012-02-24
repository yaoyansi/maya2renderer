#include "er_group.h"
#include "liqlog.h"

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
	GroupID& GroupID::operator=(const GroupID &o)
	{
		GroupID tmp(o);
		swap(tmp);
		return *this;
	}

	const std::string GroupID::toString() const
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
	void GroupID::swap(GroupID &o)
	{
		using std::swap;
		swap(this->name, o.name);
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
	void Group::addMeshInstance(const std::string &instname)
	{
		if( isExist(instname) ){
			return;
		}
		lightlink.insert( std::make_pair(MeshName(instname),LightNames()) );
	}
	void Group::addCameraInstance(const std::string &instname)
	{
		cameras.insert(instname);
	}
	const CameraName Group::getCamera() const
	{
		if( cameras.empty() )
		{
			liquidMessage2(messageError, ("group["+id.toString()+"] has no camera.").c_str())
			assert(0&&"group has no camera. see script window for more details.");
		}
		if( cameras.size()>1 )
		{
			std::stringstream ss;
			std::copy(cameras.begin(), cameras.end(), std::ostream_iterator<CameraName>(ss, ","));
			liquidMessage2(messageError, ("group["+id.toString()+"] has too many cameras:"+ss.str()).c_str())
			assert(0&&"group has too many cameras. see script window for more details.");		
		}
		return *cameras.begin();
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