
surface test_type_array(
	float a_f[4] = {3.14, 2.17, 0, -1.0};
	string a_s[2]= {"AB0","CDE"};
	vector a_v[2]= {(0,0,0), (1,2,3)};
	normal a_n[2]= {(0,0,0), (1,2,3)};
	point a_p[2]= {(0,0,0), (1,2,3)};
	color a_c[2]= {(0,0,0), (1,0,1)};
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
