
surface myLambert()
{
	color ambientColor	= color (0);
	color _color		= color (0.0, 0.8, 0.0);
	float diffuse		= 0.8;
	color incandescence	= color (0);
	float matteOpacityMode  = 2;
	float matteOpacity	= 1;

	/* Refraction. */
	uniform float refractions	= 0;
	float refractiveIndex	= 1;
	uniform float refractionLimit	= 6;
	float lightAbsorbance	= 0;
	float shadowAttenuation	= 0;

	normal normalCamera	= normal(1);
	color transparency	= color(0.8);
	float translucence	= 0;
	float translucenceDepth = 0;
	float translucenceFocus	= 0;

	// Outputs:
	//
	color outColor;
	color outTransparency;

	color __transparency = color ( 0.2, 0.2, 0.2 );
	extern normal N;
#include <lambert.h>
	maya_lambert(
		ambientColor,
		_color,
		diffuse,
		incandescence,
		matteOpacityMode,
		matteOpacity,
		/* Refraction. */
		refractions,
		refractiveIndex,
		refractionLimit,
		lightAbsorbance,
		shadowAttenuation,
		N,
		transparency,
		translucence,
		translucenceDepth,
		translucenceFocus,
		// Outputs:
		outColor,
		outTransparency
	);

	Oi = outTransparency;
	Ci = Oi * Cs * outColor;
}