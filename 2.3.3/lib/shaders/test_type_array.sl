
surface test_type_array(
	float a_f[4] = {3.14, 2.17, 0, -1.0};
	string a_s[2]= {"AB0","CDE"};
	vector a_v[2]= {(0,0,0), (7,8,9)};
	normal a_n[2]= {(0,0,0), (1,2,3)};
	point a_p[2]= {(0,0,0), (4,5,6)};
	color a_c[2]= {(0,0,0), (1,0,1)};
	
	varying float a_vf[4] = {3.14, 2.17, 0, -1.0};
	//varying string a_vs[2]= {"AB0V","CDEV"}; //NOTE: strings cannot be varying
	varying vector a_vv[2]= {(1,0,0), (2,2,3)};
	varying normal a_vn[2]= {(1,0,0), (3,2,3)};
	varying point a_vp[2]= {(1,0,0), (4,2,3)};
	varying color a_vc__[2]= {(0,0,0), (1,0,1)};//NOTE: a_vc__ will cause a name collision
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
