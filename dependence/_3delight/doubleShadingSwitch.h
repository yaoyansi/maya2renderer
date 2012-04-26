/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __doubleShadingSwitch_h
#define __doubleShadingSwitch_h

/*
begin inputs
	float2[] input[].inDouble
	sourcefullshapename string[] input[].inShape
	float2 default
end inputs

begin outputs
	float2 output
end outputs
*/

void maya_doubleShadingSwitch(
	// Inputs
	float i_inDouble[];
	uniform string i_inShape[];
	float i_default[2];

	// Outputs
	output float o_output[2] )
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
				o_output[0] = i_inDouble[i * 2];
				o_output[1] = i_inDouble[i * 2 + 1];
				break;
			}
		}
	}
}

#endif /* __doubleShadingSwitch_h */

