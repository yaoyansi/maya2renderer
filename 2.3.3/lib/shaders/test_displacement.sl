
#define EPS (1/1024)

displacement 
test_displacement(
	string texturename = "";
	float sstart = 0, sscale = 1;
	float tstart = 0, tscale = 1;
	float amp = 1, amp2=1;
)
{
	float ss = (s - sstart)/sscale;
	float tt = (t - tstart)/tscale;

	float x;
	color move;
	if( texturename!="" ){
		x = float texture( texturename[0], ss, tt, ss+EPS, tt, ss, tt+EPS, ss+EPS, tt+EPS );
		move = color texture( texturename, ss, tt, ss+EPS, tt, ss, tt+EPS, ss+EPS, tt+EPS );
	}else{
		x = 1.0;
		move = color(1, 1, 1);
	}

	vector Vmove = normalize( vector  move );
	vector Nshader = vtransform( "object", N );
	point  Pshader = transform( "object", P );

	Pshader += amp * x * normalize( Nshader ) + vector Vmove *amp2;
	P = transform( "object", "current", Pshader );
	N = calculatenormal( P );


}