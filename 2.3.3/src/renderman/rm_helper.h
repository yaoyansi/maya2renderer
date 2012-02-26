#ifndef RM_HELPER_H
#define RM_HELPER_H

#include "../common/prerequest_std.h"

#include "ri_interface.h"
#include "liqRibLightData.h"
#include "liqRibMeshData.h"
#include "liqRibShaveData.h"
#include "liqRibPfxHairData.h"
#include "liqRibPfxData.h"

namespace renderman
{
	class Helper
	{
	public:
		Helper();
		explicit Helper(const std::string& ribFile);
		~Helper();

		void RiBeginRef(const std::string& ribFile);
		void RiEndRef();

	protected:
		std::string m_ribFile;
		RtContextHandle m_contex;
	};
	//-------------------------------------------------------
	//
	//-------------------------------------------------------
	class RibDataExportHelper
	{
	public:
		RibDataExportHelper();
		~RibDataExportHelper();

		static void exportMesh( 
			const liqRibMeshDataPtr& meshdata,
			const MString& ribFile);
		
		static void exportMeshLight( const liqRibMeshDataPtr& meshdata );
		static void exportShaveData(const liqRibShaveDataPtr& data);
		static void exportPfxHairData(const liqRibPfxHairDataPtr& data);
		static void exportPfxData(const liqRibPfxDataPtr& data);
		
		static void exportLight();
	};
}

#endif