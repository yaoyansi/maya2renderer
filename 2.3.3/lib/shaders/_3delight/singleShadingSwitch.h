/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __singleShadingSwitch_h
#define __singleShadingSwitch_h

/*
begin inputs
	float[] input[].inSingle
	sourcefullshapename string[] input[].inShape
	float default
end inputs

begin outputs
	float output
end outputs
*/

void
maya_singleShadingSwitch(
	// Inputs
	float i_inSingle[];
	uniform string i_inShape[];
	float i_default;

	// Outputs
	output float o_output )
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
				o_output = i_inSingle[i];
				break;
			}
		}
	}
}

#endif /* __singleShadingSwitch_h */

