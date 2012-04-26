/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __smear_h
#define __smear_h

/*
begin inputs
	color inRgb
end inputs
begin outputs
	float2 outUV
end outputs
*/

void
maya_smear(
	// Inputs
	color i_inRgb;

	// Outputs
	output float o_outUV[2] )
{
	color cHsv = ctransform( "hsv", i_inRgb );

	float ch = comp( cHsv, 0 );
	float cs = comp( cHsv, 1 );
	float cv = comp( cHsv, 2 );

	/* Don't ask me why, but somehow hue must be scaled by saturation. */
	ch *= cs;

	/* 0 is up, apparently. And it turns the wrong way. */
	ch = 0.25 - ch;

	/*
		It seems a color wheel is too complex for these guys... so they use a
		color hexagon. Yes, a ******* hexagon. Or rather the projection of an
		hexagon on a unit circle since the resulting vector is normalized. By
		then, why didn't anyone think of simply using sin() and cos() to get a
		circle? It's nearly the same and far simpler.
	*/
	float h = mod( ch * 6, 1 );
	float uu = 1 - 0.5 * h;
	float vv = (sqrt(3) / 2) * h;
	vector p = normalize( vector(uu, vv, 0) );
	p = rotate(p, (ch - h/6)*2*PI, point(0,0,0), point(0,0,1));

	/* Scale by value. */
	p *= cv;

	o_outUV[0] = comp(p, 0);
	o_outUV[1] = comp(p, 1);
}

#endif /* __smear_h */

