#include "er_groupmgr.h"

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
		const std::string &objInstanceName
		)
	{
		addObjectInstance(GroupID(groupname), objInstanceName);
	}
	void GroupMgr::addObjectInstance(
		const GroupID &id, 
		const std::string &objInstanceName
		)
	{
		if( groups.find(id) == groups.end() )
		{
			// not exist
			createGroup(id);
		}

		std::map<GroupID, Group>::iterator i = groups.find(id);
		assert(i != groups.end());
		i->second.addObjectInstance( objInstanceName);
		
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