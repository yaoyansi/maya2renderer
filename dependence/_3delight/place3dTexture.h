/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __place3dTexture_h
#define __place3dTexture_h

/*
begin inputs
	uniform matrix worldInverseMatrix[]
end inputs

begin outputs
	uniform matrix worldInverseMatrix[0]
end outputs
*/

void
maya_place3dTexture(
	// Inputs
	//
	uniform matrix i_trs;
	// Outputs
	//
	output uniform matrix o_worldInverseMatrix;)
{
	o_worldInverseMatrix = i_trs;
}

#endif /* __place3dTexture_h */

