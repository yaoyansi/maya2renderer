/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __displacementShader_h
#define __displacementShader_h

/*
begin inputs
	float displacement
end inputs

begin outputs
end outputs
*/

void
maya_displacementShader(
	float i_displacement )
{
	extern varying point P;
	extern varying normal N;
	extern varying normal Ng;

	normal Ndiff = normalize(N) - normalize(Ng);
 
	/* Maya's displacementShader works in world space. */
	point po = transform( "world", P );
	po += i_displacement * normalize( ntransform( "world", N ) );
	P = transform( "world", "current", po );
	N = calculatenormal( P );
  
	N = normalize(N) + Ndiff;
}

#endif /* __displacementShader_h */

