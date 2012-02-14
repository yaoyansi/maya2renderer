/*
**
** The contents of this file are subject to the Mozilla Public License Version
** 1.1 (the "License"); you may not use this file except in compliance with
** the License. You may obtain a copy of the License at
** http://www.mozilla.org/MPL/
**
** Software distributed under the License is distributed on an "AS IS" basis,
** WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
** for the specific language governing rights and limitations under the
** License.
**
** The Original Code is the Liquid Rendering Toolkit.
**
** The Initial Developer of the Original Code is Colin Doncaster. Portions
** created by Colin Doncaster are Copyright (C) 2002. All Rights Reserved.
**
** Contributor(s): Philippe Leprince.
**
**
** The RenderMan (R) Interface Procedures and Protocol are:
** Copyright 1988, 1989, Pixar
** All Rights Reserved
**
**
** RenderMan (R) is a registered trademark of Pixar
*/

/* ______________________________________________________________________
**
** Liquid Light Shader Node Header
** ______________________________________________________________________
*/


#ifndef liqLightNode_H
#define liqLightNode_H

#include <maya/MPxNode.h>

class liqNodeSwatch;

class liqLightNode : public MPxNode
{
  public:
                      liqLightNode();
    virtual          ~liqLightNode();

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
    static MObject aRmanShaderType;
    static MObject aRmanShaderLong;
    static MObject aRmanShaderLif;
    static MObject aRmanParams;
    static MObject aRmanDetails;
    static MObject aRmanTypes;
    static MObject aRmanDefaults;
    static MObject aRmanArraySizes;
    static MObject aRmanLifCmds;
	static MObject aRmanMethods;
	static MObject aRmanIsOutput;

    static MObject aPreviewPrimitive;
    static MObject aPreviewCustomPrimitive;
    static MObject aPreviewObjectSize;
    static MObject aPreviewShadingRate;
    static MObject aPreviewBackplane;

    static MObject aOutputInShadow;

    static MObject aGenerateMainShadow;
    static MObject aDeepShadows;
    static MObject aPixelSamples;
    static MObject aVolumeInterpretation;
    static MObject aEveryFrame;
    static MObject aRenderAtFrame;
    static MObject aAggregateShadowMaps;
    static MObject aGeometrySet;
    static MObject aShadingRateFactor;
    static MObject aNearClipPlane;
    static MObject aFarClipPlane;
    static MObject aShadowCameras;

    static MObject aResolution;
    static MObject aRefreshPreview;

    // Output attributes
    static MObject aOutColor;
    static MObject aOutTransparency;
    static MObject aAssignedObjects;

	bool   swatchInit;

private:
	liqLightNode(const liqLightNode&);
	liqLightNode& operator=(const liqLightNode&);
};




#endif
