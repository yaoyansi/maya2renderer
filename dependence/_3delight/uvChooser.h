/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __uvChooser_h
#define __uvChooser_h

/*
begin inputs
	byprimitive string[] uvSets[]
end inputs

begin outputs
	float2 outUv
end outputs


begin shader_extra_parameters uvChooserParams
	string uvsets_name[] = {};     // for uvChooser node
	varying float uvsets_u[] = {}; // for uvChooser node
	varying float uvsets_v[] = {}; // for uvChooser node
end shader_extra_parameters
*/

/*
	For each object which has a non-default uv set assigned, we get the name of
	that set in i_uvSets.

	We can look for that uv set in the parameters which were passed to the
	object (the extern uvsets_*).
*/
void
maya_uvChooser(
	// Inputs
	uniform string i_uvSets;

	// Outputs
	output float o_outUv[2] )
{
	extern uniform string uvsets_name[0];
	extern varying float uvsets_u[0];
	extern varying float uvsets_v[0];

	extern varying float ss, tt;

	uniform float found = 0;

	if( i_uvSets != "" )
	{
		uniform float i;
		uniform float nsets = arraylength( uvsets_name );

		for( i = 0; i < nsets; i += 1 )
		{
			if( uvsets_name[i] == i_uvSets )
			{
				o_outUv[0] = uvsets_u[i];
				o_outUv[1] = 1.0 - uvsets_v[i];

				found = 1;
				break;
			}
		}
	}

	if( found == 0 )
	{
		o_outUv[0] = ss;
		o_outUv[1] = tt;
	}
}

#endif /* __uvChooser_h */

