#include <liqLocatorMgr.h>

#include <maya/MItDag.h>
#include <maya/MFnDagNode.h>
#include <maya/MDagModifier.h>
#include <maya/MPlug.h>

#include <liqRibHT.h>


//
tLocatorMgr::tLocatorMgr()
{

}
//
tLocatorMgr::~tLocatorMgr()
{

}
//
void tLocatorMgr::scanScene(const float lframe__, const int sample__,
						  boost::shared_ptr< liqRibHT > &htable__,
						  int &count__,
						  MStatus &returnStatus__)
{
	CM_TRACE_FUNC("tLocatorMgr::scanScene("<<lframe__<<","<<sample__<<",htable__,count__,returnStatus__)");

	MItDag dagCoordSysIterator( MItDag::kDepthFirst, MFn::kLocator, &returnStatus__);

	for (; !dagCoordSysIterator.isDone(); dagCoordSysIterator.next()) 
	{
#if (Refactoring == 0)
		LIQ_CHECK_CANCEL_REQUEST;
#endif
		MDagPath path;
		MObject currentNode;
		currentNode = dagCoordSysIterator.item();
		MFnDagNode dagNode;
		dagCoordSysIterator.getPath( path );
		if(MS::kSuccess != returnStatus__) 
			continue;
		if(!currentNode.hasFn(MFn::kDagNode)) 
			continue;
		returnStatus__ = dagNode.setObject( currentNode );
		if(MS::kSuccess != returnStatus__) 
			continue;

		// scanScene: if it's a coordinate system then insert it into the hash table
		if( dagNode.typeName() == "liquidCoordSys" ) 
		{
			int coordType = 0;
			MPlug typePlug = dagNode.findPlug( "type", &returnStatus__ );
			if( MS::kSuccess == returnStatus__ ) 
				typePlug.getValue( coordType );

			if( ( sample__ > 0 ) && isObjectMotionBlur( path )) 
			{
				// philippe : should I store a motion-blurred clipping plane ?
				if( coordType == 5 ) 
					htable__->insert(path, lframe__, sample__, MRT_ClipPlane,count__++ );
				else 
					htable__->insert(path, lframe__, sample__, MRT_Coord,count__++ );
			} 
			else 
			{
				if( coordType == 5 ) 
					htable__->insert(path, lframe__, 0, MRT_ClipPlane,count__++ );
				htable__->insert(path, lframe__, 0, MRT_Coord,count__++ );
			}
			continue;
		}
	}
}