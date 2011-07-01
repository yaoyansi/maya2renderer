/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __quadShadingSwitch_h
#define __quadShadingSwitch_h

/*
begin inputs
	color[] input[].inTriple
	float[] input[].inSingle
	sourcefullshapename string[] input[].inShape
	color defTriple
	float defSingle
end inputs

begin outputs
	color outTriple
	float outSingle
end outputs
*/

void
maya_quadShadingSwitch(
	// Inputs
	color i_inTriple[];
	float i_inSingle[];
	uniform string i_inShape[];
	color i_defTriple;
	float i_defSingle;

	// Outputs
	output color o_outTriple;
	output float o_outSingle )
{
	o_outTriple = i_defTriple;
	o_outSingle = i_defSingle;

	uniform string objectname;

	if( 1 == attribute( "identifier:name", objectname ) )
	{
		uniform float nshapes = arraylength( i_inShape );
		uniform float i;

		for( i = 0; i < nshapes; i += 1 )
		{
			if( i_inShape[i] == objectname )
			{
				o_outTriple = i_inTriple[i];
				o_outSingle = i_inSingle[i];
				break;
			}
		}
	}
}

#endif /* __quadShadingSwitch_h */

