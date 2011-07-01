
surface test_type_VaryingColorArray(
	varying color a_vc___[2]= {(0,0,0), (1,0,1)};
) 
{
	float frequency = 7;
	varying float ss, tt, x, y;

	ss = s * frequency;
	tt = t * frequency;
	x = mod( ss - 0.5, 1 );
	y = mod( tt - 0.5, 1 );

	x = filterstep( 0.5, x, x + du );
	y = filterstep( 0.5, y, y + dv );

	Oi = Os;
	Ci = Oi * Cs * mix( 0.33 * x, ( 0.66 - x ), y );
}
