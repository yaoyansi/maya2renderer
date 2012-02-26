#include "rm_helper.h"
#include<maya/MGlobal.h>
#include "liqGlobalHelpers.h"
#include <liqRibTranslator.h>

namespace renderman
{
	Helper::Helper()
	{

	}
	//
	Helper::Helper(const std::string& ribFile)
		:m_ribFile(ribFile)
	{

	}
	Helper::~Helper()
	{

	}
	//
	void Helper::RiBeginRef(const std::string& ribFile)
	{
		m_ribFile = ribFile;

		//if m_ribFileFullPath is "", write the data into the current rib file.
		if( m_ribFile != "" ){
			//1)make a reference
			RiReadArchive( const_cast< RtToken >( m_ribFile.c_str() ), NULL, RI_NULL );
			//2)write the data into another rib file.
			m_contex = RiGetContext();//push context
			liquidMessage("output geometry rib: "+ std::string(m_ribFile.c_str()) , messageInfo);
			RiBegin( const_cast< RtToken >( m_ribFile.c_str() ) );
		}
	}
	//
	void Helper::RiEndRef()
	{
		if( m_ribFile != "" ){
			RiEnd();
			RiContext(m_contex);//pop context
		}
	}
	//-------------------------------------------------------
	//
	//-------------------------------------------------------
	RibDataExportHelper::RibDataExportHelper(){}
	RibDataExportHelper::~RibDataExportHelper(){}

	void RibDataExportHelper::exportMesh( 
		const liqRibMeshDataPtr& meshdata,
		const MString& ribFile
		)
	{
		if( meshdata->isEmpty() )
		{
			liquidMessage( "Could not export degenerate mesh", messageError );
			return;
		}

		Helper o;
		o.RiBeginRef( ribFile.asChar() );

		//mesh data begin
		//
		// Each loop has one polygon, so we just want an array of 1's of
		// the correct size. Stack version.
		//vector< RtInt > nloops( numFaces, 1 );
		// Alternatively (heap version):
		boost::scoped_array< RtInt > nloops( new RtInt[ meshdata->getNumFaces() ] );
		std::fill( nloops.get(), nloops.get() + meshdata->getNumFaces(), ( RtInt )1 );

		unsigned numTokens( meshdata->tokenPointerArray.size() );
		boost::scoped_array< RtToken > tokenArray( new RtToken[ numTokens ] );
		boost::scoped_array< RtPointer > pointerArray( new RtPointer[ numTokens ] );
		assignTokenArraysV( meshdata->tokenPointerArray, tokenArray.get(), pointerArray.get() );

		RiPointsGeneralPolygonsV( meshdata->getNumFaces(),
			&nloops[ 0 ],
			meshdata->getNverts().get(),
			meshdata->getVerts().get(),
			numTokens,
			tokenArray.get(),
			pointerArray.get() );
		//mesh data end

		o.RiEndRef();
	}

// 	bool RibDataExportHelper::isMeshLight()
// 	{
// 
// 	}

	void RibDataExportHelper::exportMeshLight( const liqRibMeshDataPtr& meshdata )
	{
		if( meshdata->isEmpty() )
		{
			liquidMessage( "Could not export degenerate mesh", messageError );
			return;
		}

		if( meshdata->isAreaLight() )
		{
			// this code section comes from liqRibMeshData::_write(const structJob &currentJob)

			RtLightHandle handle = INVALID_LIGHT_INDEX;

			{ // What happens if we're inside a motion block????? This whole approach of Liquid is flawed...
				LIQDEBUGPRINTF( "-> mesh is area light\n" );
				//	RiAttributeBegin();
				RtString ribname = const_cast< char* >( meshdata->getName().asChar() );
				RiAttribute( "identifier", "name", &ribname, RI_NULL );
				RtMatrix tmp;
				memcpy( tmp, meshdata->getTransformationMatrixPtr(), sizeof( RtMatrix ) );
				RiTransform( tmp );
				float areaIntensity = meshdata->getAreaIntensity();
				handle = RiAreaLightSource( "arealight", "intensity", &areaIntensity, RI_NULL );
			}
			//
			//mesh data begin
			//
			// Each loop has one polygon, so we just want an array of 1's of
			// the correct size. Stack version.
			//vector< RtInt > nloops( numFaces, 1 );
			// Alternatively (heap version):
			boost::scoped_array< RtInt > nloops( new RtInt[ meshdata->getNumFaces() ] );
			std::fill( nloops.get(), nloops.get() + meshdata->getNumFaces(), ( RtInt )1 );

			unsigned numTokens( meshdata->tokenPointerArray.size() );
			boost::scoped_array< RtToken > tokenArray( new RtToken[ numTokens ] );
			boost::scoped_array< RtPointer > pointerArray( new RtPointer[ numTokens ] );
			assignTokenArraysV( meshdata->tokenPointerArray, tokenArray.get(), pointerArray.get() );

			RiPointsGeneralPolygonsV( meshdata->getNumFaces(),
				&nloops[ 0 ],
				meshdata->getNverts().get(),
				meshdata->getVerts().get(),
				numTokens,
				tokenArray.get(),
				pointerArray.get() );
			//mesh data end

			{
				// RiAttributeEnd();
				RiIlluminate( handle, 1 );
			}
		}
	}

	void RibDataExportHelper::exportLight()
	{

	}

	void RibDataExportHelper::exportShaveData(const liqRibShaveDataPtr& data)
	{
		LIQDEBUGPRINTF( "-> writing shave surface\n" );

		LIQDEBUGPRINTF( "-> writing shave surface trims\n" );
		liqRIBMsg("This is a shave object data:\n" );

		MString nodeName(data->objDagPath.partialPathName());
		liqRIBMsg( "node name = %s", nodeName.asChar() );

		MString frame; 
		frame.set(liqglo.liqglo_lframe);
		MString prefix("shv_");
		MString shv_RibFile( liquidGetRelativePath( false, getLiquidRibName( (prefix+nodeName).asChar() ), liqglo.liqglo_ribDir ) +"."+frame+".rib" );

		//1)make a reference
		RiReadArchive( const_cast< RtToken >( shv_RibFile.asChar() ), NULL, RI_NULL );

		//call shave command to write the rib file(not support motion blur)
		MGlobal::executeCommand(
			"shaveWriteRib -hairNode \""+nodeName+"\" \""+shv_RibFile+"\";"
			);

		LIQDEBUGPRINTF( "-> done writing shave surface\n" );
	}
}