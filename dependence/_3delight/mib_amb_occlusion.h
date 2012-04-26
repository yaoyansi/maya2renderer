/*
	Copyright (c) 2008 TAARNA Studios International.
*/

#ifndef __mib_amb_occlusion_h
#define __mib_amb_occlusion_h

/*
begin inputs
float    samples
color    bright
color    dark
float    spread
float    max_distance
float    reflective
end inputs

begin outputs
    color    outValue
end outputs

begin shader_extra_parameters aov_occlusion
#ifdef USE_AOV_aov_occlusion
	output varying color aov_occlusion = 0;
#endif
end shader_extra_parameters
*/

void maya_mib_amb_occlusion(
    // Inputs
    //
    float i_samples;
    color i_bright, i_dark;
    float i_spread;
    float i_max_distance;
    float i_reflective;

    // Outputs
    //
    output color    o_outValue; ) 
{
	extern point P;
	extern normal N;
	extern vector I;

	normal Nn = faceforward(normalize(N), I);

	if(i_reflective != 0)
		Nn = normal reflect( I, Nn );

	float occ= 1 - occlusion(
			P, Nn, i_samples,
			"adaptive", 1,
			"maxdist", i_max_distance,
			"coneangle", i_spread * PI / 2);

	o_outValue = mix( i_dark, i_bright, occ );

#	ifdef USE_AOV_aov_occlusion
	extern color aov_occlusion;
	aov_occlusion = o_outValue;
#	endif
}

#endif /* __mib_amb_occlusion_h */

