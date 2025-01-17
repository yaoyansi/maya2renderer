
surface test_type(
	float frequency = 7;
	string s0="test stringATT";
	color c0 = color(1.0, 1.0, 1.0);
	point p0 = point(2, 2, 2);
	vector v0=vector(3, 3, 3);
	normal n0 = normal (4, 4, 4);
	matrix m0 = 0;
	matrix m1 = matrix (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
) 
{
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
