
#ifndef liqGlobalNodeRenderer_H
#define liqGlobalNodeRenderer_H

/* ______________________________________________________________________
**
** Liquid Globals Node For Custom Renderer
** ______________________________________________________________________
*/
#include <maya/MPxNode.h>

class liqGlobalsNodeRenderer : public MPxNode
{
public:
	liqGlobalsNodeRenderer();
	//no need to inherent from this class. //  [3/4/2012 yaoyansi]
	~liqGlobalsNodeRenderer();

	static void* creator();
	static MStatus initialize();
	
	//  Id tag for use with binary file format
	static  MTypeId   id;

private:
	// attributes
	//static MObject aRenderName;

private:
	liqGlobalsNodeRenderer(const liqGlobalsNodeRenderer&);
	liqGlobalsNodeRenderer& operator=(const liqGlobalsNodeRenderer&);
};
#endif//liqGlobalNodeRenderer_H