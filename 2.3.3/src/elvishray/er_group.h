#ifndef _ER_GROUP_H_
#define _ER_GROUP_H_

#include "../common/prerequest_std.h"

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
		GroupID& operator=(const GroupID &o);

		const std::string toString() const;

		bool operator==(const GroupID &o) const;
		bool operator<(const GroupID &o) const;
		void swap(GroupID &o);

	};
	//typedef struct sGroupID GroupID;
	
	typedef std::string MeshName;
	typedef std::string LightName;
	typedef std::string CameraName;
	typedef std::set<MeshName> MeshNames;
	typedef std::set<LightName> LightNames;

	enum GroupInstanceType
	{
		GIT_Camera   = 0,
		GIT_Geometry = 1,

		GIT_Num
	};
	
	class Group
	{
	public:
		Group();
		Group(const GroupID &id);
		~Group();
		void addMeshInstance(const std::string &instname);
		void addCameraInstance(const std::string &instname);
		const CameraName getCamera() const;

		void addLightLink(const std::string &objInst, const std::string &lightInst);
		LightNames gatherLights();
		MeshNames gatherMeshs();
		const LightNames& getLightLinksOf(const MeshName &mesh);
		bool isExist(const MeshName& instName);

		std::map<MeshName, LightNames> lightlink;

		std::set<CameraName> cameras;
	protected:
		GroupID id; 



		//LightNames gatherLightLinksOf(const std::string &meshname);


	};
}

#endif//_ER_GROUP_H_