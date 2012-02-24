#include "er_groupmgr.h"
#include "liqlog.h"

namespace elvishray
{

	//
	GroupMgr::GroupMgr(Renderer *renderer_)
		:m_renderer(renderer_)
	{
		
	}
	GroupMgr::~GroupMgr()
	{
		m_renderer = 0;
	}
	void GroupMgr::createGroup(/*const long frame,*/ const std::string &groupname)
	{
		createGroup(GroupID(/*frame,*/ groupname));
	}
	void GroupMgr::createGroup(const GroupID &id)
	{
		groups[id] = Group();
	}

	void GroupMgr::addObjectInstance(
		const std::string &groupname, 
		const std::string &objInstanceName,
		const GroupInstanceType type
		)
	{
		addObjectInstance(GroupID(groupname), objInstanceName, type);
	}
	void GroupMgr::addObjectInstance(
		const GroupID &id, 
		const std::string &objInstanceName,
		const GroupInstanceType type
		)
	{
		if( groups.find(id) == groups.end() )
		{
			// not exist
			createGroup(id);
		}

		std::map<GroupID, Group>::iterator i = groups.find(id);
		assert(i != groups.end());
		
		switch( type )
		{
		case GIT_Camera:
			i->second.addCameraInstance( objInstanceName );
			break;
		case GIT_Geometry:
			i->second.addMeshInstance( objInstanceName );
			break;
		default:
			liquidMessage2(messageError, "group instance type %d is unknown.",type);
			assert(0&&"group instance type is unknown. see script window for more details.");
		}

		
	}
	void GroupMgr::addLightLink(
		const std::string &groupname, 
		const std::string &objInst, 
		const std::string &lightInst)
	{
		addLightLink(GroupID(groupname), objInst, lightInst);
	}
	void GroupMgr::addLightLink( const GroupID &id, const std::string &objInst, const std::string &lightInst)
	{
		if( groups.find(id) == groups.end() )
		{
			// not exist
			createGroup(id);
		}
		std::map<GroupID, Group>::iterator i = groups.find(id);
		assert(i != groups.end());
		i->second.addLightLink( objInst, lightInst);
	}
}