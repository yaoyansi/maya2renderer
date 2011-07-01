
#ifndef liqRibboxNode_H
#define liqRibboxNode_H

#include <maya/MPxNode.h>

class liqNodeSwatch;

class liqRibboxNode : public MPxNode
{
	public:
                      liqRibboxNode();
    virtual          ~liqRibboxNode();

    //virtual MStatus   compute( const MPlug&, MDataBlock& );
    virtual void      postConstructor();

    static  void *    creator();
    static  MStatus   initialize();

    //  Id tag for use with binary file format
    static  MTypeId   id;
    liqNodeSwatch*    renderSwatch;

	private:

    // Input attributes
    static MObject aRmanShader;
    static MObject aRmanShaderLong;
    static MObject aRibbox;

    // Output attributes
    static MObject aOutColor;

    bool    swatchInit;
};




#endif
