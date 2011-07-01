#ifndef _ER_GROUP_H_
#define _ER_GROUP_H_

#include "../log/prerequest_std.h"

namespace elvishray
{
	class GroupID
	{
	public:
		//long frame;//
		std::string name;
		//std::string layer;//

		GroupID();
		GroupID(
			/*const long int frame_,*/
			const std::string &name_ 
			//,const std::string &layer
			);
		std::string toString();

		bool operator==(const GroupID &o) const;
		bool operator<(const GroupID &o) const;

	};
	//typedef struct sGroupID GroupID;
	
	typedef std::string MeshName;
	typedef std::string LightName;
	typedef std::set<MeshName> MeshNames;
	typedef std::set<LightName> LightNames;
	
	class Group
	{
	public:
		Group();
		Group(const GroupID &id);
		~Group();
		void addObjectInstance(const std::string &instname);
		void addLightLink(const std::string &objInst, const std::string &lightInst);
		LightNames gatherLights();
		MeshNames gatherMeshs();
		const LightNames& getLightLinksOf(const MeshName &mesh);
		bool isExist(const MeshName& instName);
		std::map<MeshName, LightNames> lightlink;

	protected:
		GroupID id; 



		//LightNames gatherLightLinksOf(const std::string &meshname);


	};
}

#endif//_ER_GROUP_H_