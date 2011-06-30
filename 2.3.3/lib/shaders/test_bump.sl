
displacement 
test_bump(
	float amplitude = 0.5;
	float frequency = 1;
	float details   = 12;
)
{
	uniform float i;
	float div=1, bmp=0;
	normal Nn;
	point Pt;
	vector poffset = vector( 15, 37, 22 );

	Pt = transform( "object", P );
	Nn = normalize( N );

	for( i=0; i < details; i+=1 )
	{
		bmp += abs( float noise((frequency * Pt + poffset)*i)-0.5 )/div;
		div *= 1.8;
	}
	P += 2 * amplitude * bmp * Nn;
	N = calculatenormal(P);
}