#include "liqGlobalNodeRenderer.h"
#include <liqMayaNodeIds.h>
// static data
MTypeId liqGlobalsNodeRenderer::id( liqGlobalsNodeRendererId );


liqGlobalsNodeRenderer::liqGlobalsNodeRenderer()
{
}

liqGlobalsNodeRenderer::~liqGlobalsNodeRenderer()
{
}

void* liqGlobalsNodeRenderer::creator()
{
	return new liqGlobalsNodeRenderer();
}

MStatus liqGlobalsNodeRenderer::initialize()
{
	return MS::kSuccess;
}


