/**
 *  Liquid Maya Paint Effects default surface shader
 */


float sqr__( float x ) {
	return x * x;
}


surface liquidpfx(
	varying float roughness        = 0.1;

    // Rest is filled-in by primvars
	varying float width            = 0;
	varying float pfxflatness      = 0;
	varying color pfxincandescence = 0;
) {

	// Create a new normal as we'd have if the curve was a tube
	float radius = width * 0.5;
	float x = s * width - radius;
	float y = sqrt( sqr__( radius ) - sqr__( x ) );

	y *= clamp( 1 - pfxflatness, 0, 1 );

	point Pshad = transform( "shader", P );
	normal Nshad = normalize( ntransform( "shader", N ) );

	uniform float otherside = 1;
	attribute( "user:otherside", otherside );
    Nshad *= otherside;

	point PP = transform( "shader", "current", Pshad + Nshad * y );
	normal Nf = normalize( calculatenormal( PP ) );
	Nf = faceforward( Nf, I, Nf );

	vector V = normalize( -I );
	Oi = Os;
	Ci = Oi * ( pfxincandescence + Cs * diffuse( Nf ) ) + specular( Nf, V, roughness );
}
