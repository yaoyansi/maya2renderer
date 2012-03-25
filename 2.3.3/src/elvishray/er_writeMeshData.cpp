#include "er_renderer.h"
#include <liqRibMeshData.h>
#include "../common/prerequest_maya.h"
#include "../common/mayacheck.h"
#include "ercall.h"
#include "log_helper.h"
//#include <liqRibNode.h>
#include <liqRibTranslator.h>

namespace elvishray
{
	static void _write(liqRibMeshData* pData, const structJob &currentJob);

	void Renderer::write(
		/*const*/ liqRibMeshData* pData,
		const MString &fileName, 
		const structJob &currentJob,
		const bool bReference)
	{
		if( !bReference ){//write data at first time
			assert(pData->getRibFileFullPath().length()==0);
			pData->setRibFileFullPath(fileName);

// 			renderman::Helper o;
// 			o.RiBeginRef(pData->getRibFileFullPath().asChar());
 			_write(pData, currentJob);
// 			o.RiEndRef();

		}else{
			//write the reference
			assert(pData->getRibFileFullPath() == fileName);
//			RiReadArchive( const_cast< RtToken >( pData->getRibFileFullPath().asChar() ), NULL, RI_NULL );
		}
	}
	//
	void _exportVertexFromNodePlug(
		const liqRibNodePtr &ribNode__,
		unsigned int sample)
	{	
		MStatus status;

		const liqRibDataPtr ribdata = ribNode__->object(sample)->getDataPtr();
		liqRibMeshData* mesh = (liqRibMeshData*)(ribdata.get());
		const std::vector<liqTokenPointer>& tokenPointerArray = mesh->tokenPointerArray;

		liqTokenPointer vertex;
		for( std::vector< liqTokenPointer >::const_iterator iter( tokenPointerArray.begin() ); iter != tokenPointerArray.end(); ++iter ) 
		{
			if( "P" == const_cast< liqTokenPointer* >( &( *iter ) )->getDetailedTokenName() )// find the Position data
			{
				vertex = *iter;
				break;
			}
		}
		assert( !vertex.empty() );
		const RtFloat* vertex_buf = vertex.getTokenFloatArray();

		MFnMesh fnMesh(mesh->objDagPath, &status);
		IfMErrorWarn(status);

		// add vertex position to ER
		for(size_t i=0; i<fnMesh.numVertices(); ++i)
		{
			_S( ei_tab_add_vector( vertex_buf[3*i+0],vertex_buf[3*i+1],vertex_buf[3*i+2] ) );
		}

	}
	//
	static void _write(liqRibMeshData* pData, const structJob &currentJob__)
	{
 		liqRibNodePtr ribNode__ = liqRibTranslator::getInstancePtr()->htable->find(
 			pData->objDagPath.fullPathName(), 
 			pData->objDagPath,
 			MRT_Unknown
 			);
 		assert( ribNode__!=0 );
 		assert( ribNode__->path().fullPathName() == pData->objDagPath.fullPathName() );

		const bool bMotionBlur =
			ribNode__->motion.transformationBlur &&
			( ribNode__->object( 1 ) ) &&
			//( ribNode__->object(0)->type != MRT_Locator ) && // Why the fuck do we not allow motion blur for locators?
			( !currentJob__.isShadow || currentJob__.deepShadows );

		bool bGeometryMotion = 
			liqglo.liqglo_doDef 
			&& bMotionBlur
			&& ( ribNode__->object(0)->type != MRT_RibGen );

		unsigned int sample_first = 0;
		unsigned int sample_last = bGeometryMotion? (liqglo.liqglo_motionSamples - 1):sample_first;

		_s("\n// Renderer::exportOneGeometry_Mesh("<<ribNode__->name.asChar()<<","<<sample_first<<","<<sample_last<<")");

		const liqRibDataPtr mesh = ribNode__->object(sample_first)->getDataPtr();

//


		//
		MStatus status;
		MFnMesh fnMesh(mesh->objDagPath, &status);
		IfMErrorWarn(status);

		MIntArray triangleCounts,triangleVertices;
		IfMErrorWarn(fnMesh.getTriangles(triangleCounts, triangleVertices));

		MString currentUVsetName;
		IfMErrorWarn(fnMesh.getCurrentUVSetName(currentUVsetName));

		// geometry data (shape)
		_s("\n//############################### mesh #");
		_S( ei_object( getObjectName(mesh->getName()).c_str(), "poly" ) );
		_s("{");
		_d( eiTag tag );

		//vertex position
		_s("//### vertex positions, fnMesh.numVertices()="<<fnMesh.numVertices() );
		_d( tag = ei_tab(EI_DATA_TYPE_VECTOR, 1024) )
			_s("//tag="<<tag);
		_S( ei_pos_list( tag ) );

		//_exportVertexFromDagNode(fnMesh);
		_exportVertexFromNodePlug(ribNode__, sample_first);

		_S( ei_end_tab() );

		{//deform motion
			if( sample_first != sample_last )
			{
				_s("//### vertex deform positions, " );
				_d( tag = ei_tab(EI_DATA_TYPE_VECTOR, 1024) )
					_s("//tag="<<tag);
				_S( ei_motion_pos_list( tag ) );

				_exportVertexFromNodePlug(ribNode__, sample_last);

				_S( ei_end_tab() );
			}
		}

// 		_s("//### vertex color");
// 		for(int i=0; i<position.length(); i++)
// 		{
// 			_S( ei_vertex(i) );
// 			//_S( ei_variable_color( "Cs", color( 1.0f, 0.0f, 1.0f ) ) );
// 		}

		// get normal for each vertex
		// but the render result seems very weird, see test/test_er_light/output_img_std/er_pointlight.perspShape.1.elvishray_vertex_normal.bmp
		// so I ommit this section temporarily.
		_s("//vertex normals are not output temporarily.");
		if(fnMesh.numVertices() == fnMesh.numNormals())//smooth normal, like a sphere
		{
			_s("//### N");
			_d( tag = eiNULL_TAG );
			_S( ei_declare("N", eiVARYING, EI_DATA_TYPE_TAG, &tag) );
			_d( tag = ei_tab(EI_DATA_TYPE_VECTOR, 1024) )
			_s("//tag="<<tag);
			_S( ei_variable("N", &tag) );
			MVector nml;
			for(size_t i = 0; i<fnMesh.numVertices(); ++i)
			{
				IfMErrorWarn(fnMesh.getVertexNormal(i, false, nml, MSpace::kObject));
				_S( ei_tab_add_vector(nml.x, nml.y, nml.z) );
			}
			_S( ei_end_tab() );
		}else{//sharp edge, like a cube
			// in this case, like a cube, a vertex has a specified normal corresponding to each adjacent polygon.
			// but elvishray's only allow a vertex to be assigned only one normal.
			// so I can't generate the normal list for this case.
		}

		if( currentUVsetName.length() != 0 )//there is a current uv set
		{
			MFloatArray u_coords;
			MFloatArray v_coords;

			IfMErrorWarn( fnMesh.getUVs(u_coords,v_coords,&currentUVsetName) );
			_s("//### UV("<<currentUVsetName<<"), size="<< fnMesh.numUVs(currentUVsetName) );
			// u
			_d( tag = eiNULL_TAG );
			_S( ei_declare("u", eiVARYING, EI_DATA_TYPE_TAG, &tag) );
			_d( tag = ei_tab(EI_DATA_TYPE_SCALAR, 1024) )
				_s("//tag="<<tag);
			_S( ei_variable("u", &tag) );
			for(size_t i = 0; i<fnMesh.numUVs(currentUVsetName); ++i)
			{
				_S( ei_tab_add_scalar(u_coords[i]) );
			}
			_S( ei_end_tab() );
			// v
			_d( tag = eiNULL_TAG );
			_S( ei_declare("v", eiVARYING, EI_DATA_TYPE_TAG, &tag) );
			_d( tag = ei_tab(EI_DATA_TYPE_SCALAR, 1024) )
				_s("//tag="<<tag);
			_S( ei_variable("v", &tag) );
			for(size_t i = 0; i<fnMesh.numUVs(currentUVsetName); ++i)
			{
				_S( ei_tab_add_scalar(v_coords[i]) );
			}
			_S( ei_end_tab() );
		}

		_s("//### triangles, size="<< triangleCounts);
		_d( tag = ei_tab(EI_DATA_TYPE_INDEX, 1024) )
			_s("//tag="<<tag);
		_S( ei_triangle_list( tag ) );
		for(size_t i=0; i<triangleVertices.length(); i=i+3)
		{
			_S( ei_tab_add_index(triangleVertices[i])); 
			_S( ei_tab_add_index(triangleVertices[i+1])); 
			_S( ei_tab_add_index(triangleVertices[i+2])); 
		}
		_S( ei_end_tab() );
		_s("}//"<<MString(mesh->getName())+"_object");
		_S( ei_end_object() );

		//debug
		if( MString(mesh->getName()) == "Man:groundShape"){
			_s("//break here");
		}


	}
}//namespace elvishray
