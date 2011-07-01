/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __granite_h
#define __granite_h

/*
begin inputs
	color color1
	color color2
	color color3
	color fillerColor
	float cellSize
	float density
	float mixRatio
	float spottyness
	float randomness
	float threshold
	float creases
	color defaultColor
	float alphaGain
	float alphaIsLuminance
	float alphaOffset
	color colorGain
	color colorOffset
	float invert
	float local
	float wrap
	float blend
	normal normalCamera
	matrix placementMatrix
end inputs

begin outputs
	float outAlpha
	color outColor
end outputs


begin shader_extra_parameters Pref_param
	varying point Pref = 0;
end shader_extra_parameters
*/

#include "texture3d.h"
#include "utils.h"
#include "noise_utils.h"

/*
	Mix three colors together. If mixRatio < 0.5, bias toward i_c1.
	If mixRatio > 0.5 bias toward i_c3.
	Does not give exactly the Maya mix ratio but then again, there
	is a bug in Maya's mixRatio ... (try mixRatio=1.0 and see for
	yourself).

	PARAMETERS
	i_c1, i_c2, i_c3
	          :  the three colors to mix
	i_p       : particle's center.
	i_mixRatio, i_spottyness
	          : refer to Maya's documentation (help on granite node)
*/
color SampleColor( color i_c1, i_c2, i_c3; 
	point i_p; 
	float i_mixRatio, i_spotyness )
{
	float rnd = cellnoise( i_p + vector(1023, 13, 1) );
		
	if( i_mixRatio != 0.5 )
		rnd = bias( i_mixRatio, rnd );

	color c;
	if( rnd < 0.333 )
		c = i_c1;
	else if( rnd < 0.666 )
		c = i_c2;
	else
		c = i_c3;

	if( i_spotyness > 0 )
	{
		/* The best way to proceede here is to convert to HSV, varie
		   "V" and then go back to RGB... */
		float l = i_spotyness * 
			( cellnoise( i_p + vector(1, 7, 1023) ) - 0.5 );

		c += l;
		clamp( c, 0, 1 );
	}

	return c;
}

void
maya_granite(
	// Inputs
	//

	/* leather parameters */
	color i_color1, i_color2, i_color3, i_fillerColor;
	float i_cellSize, i_density, i_mixRatio, i_spottyness, i_randomness;
	float i_threshold, i_creases;
 
	/* color related inputs */
	color i_defaultColor;
	float i_alphaGain;
	uniform float i_alphaIsLuminance;
	float i_alphaOffset;
	color i_colorGain;
	color i_colorOffset;
	uniform float i_invert;
	float i_local;
	float i_wrap;
	float i_blend;

	/* geomtric inputs */
	normal i_normalCamera;
	matrix i_placementMatrix;

	// Outputs
	//
	output float o_outAlpha;
	output color o_outColor; )
{
	float edgeDist;
	float outside;

	varying point pp = transformP(i_blend, 
		i_local, 
		i_placementMatrix, 
		i_wrap, edgeDist, 
		outside );

	if( outside<1 )
	{
		point particle_positions[27];

		/* The '5' fudge factor is to have the same thing as maya */
		point Pn = (5*pp) / i_cellSize;

		/* compute radius of one cell */
		float radius = sqrt((0.5*0.5 + 0.5*0.5) * i_density) ;

		/* get particles that surround the current point */
		point p1, p2;
		float f1, f2;
		float num_particles = SuspendedParticles( 
			Pn, 0, radius, i_randomness, 0, f1, p1, f2, p2, particle_positions );

		o_outAlpha = 1;

		if( num_particles == 0 )
		{
			/* outside all particles */
			o_outColor = i_fillerColor;
		}
		else
		{
			if( i_creases == 1 )
			{
				o_outAlpha = (f2 == 1e36) ? f1 / radius : f1/f2;
				color c = SampleColor( 
					i_color1, i_color2, i_color3, p1, 
					i_mixRatio, i_spottyness); 		
				o_outColor = mix( c, i_fillerColor, o_outAlpha );
			}
			else
			{
				/* take into account all englobing spheres */
				o_outAlpha = 1.0;
				color graniteColor = 0;

				float i;
				for( i=0; i<num_particles; i+=1 )
				{ 
					float transmission = ParticleDensity( 
						0, particle_positions[i], Pn, radius );
				
					color c = SampleColor( i_color1, i_color2, i_color3,
						particle_positions[i], i_mixRatio, i_spottyness );

					graniteColor += c * transmission;
					o_outAlpha *= (1-transmission); 
				}

				o_outColor = mix( graniteColor, i_fillerColor, o_outAlpha ); 
			}
		}

		colorBalance( o_outColor, 
			o_outAlpha, 
			i_alphaIsLuminance, 
			i_alphaGain, 
			i_alphaOffset, 
			i_colorGain, 
			i_colorOffset, 
			i_invert );

		o_outAlpha = 1 - o_outAlpha;
	
	}
	else
	{
		o_outColor = i_defaultColor;
		o_outAlpha = 0;
	}
}

#endif /* __granite_h */

