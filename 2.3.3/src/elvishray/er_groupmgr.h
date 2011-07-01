#ifndef _ER_GROUP_MGR_H_
#define _ER_GROUP_MGR_H_

#include "../log/prerequest_std.h"
#include "er_group.h"


namespace elvishray
{
	//

	//
	class Renderer;
	//
	class GroupMgr 
	{
	public:
		GroupMgr(Renderer *renderer_);
		virtual~GroupMgr();
		void createGroup(/*const long frame,*/ const std::string &groupname);
		void createGroup(const GroupID &id);

		void addObjectInstance(const std::string &groupname, const std::string &objname);
		void addObjectInstance( const GroupID &id, const std::string &objInstanceName );
		
		void addLightLink(const std::string &groupname, const std::string &objInst, const std::string &lightInst);
		void addLightLink( const GroupID &id, const std::string &objInst, const std::string &lightInst);

		Renderer *m_renderer;


		std::map<GroupID, Group> groups;

	};
}

#endif//_ER_GROUP_MGR_H_