/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __tripleShadingSwitch_h
#define __tripleShadingSwitch_h

/*
begin inputs
	color[] input[].inTriple
	sourcefullshapename string[] input[].inShape
	color default
end inputs

begin outputs
	color output
end outputs
*/

void
maya_tripleShadingSwitch(
	// Inputs
	color i_inTriple[];
	uniform string i_inShape[];
	color i_default;

	// Outputs
	output color o_output )
{
	o_output = i_default;

	uniform string objectname;

	if( 1 == attribute( "identifier:name", objectname ) )
	{
		uniform float nshapes = arraylength( i_inShape );
		uniform float i;

		for( i = 0; i < nshapes; i += 1 )
		{
			if( i_inShape[i] == objectname )
			{
				o_output = i_inTriple[i];
				break;
			}
		}
	}
}

#endif /* __tripleShadingSwitch_h */

