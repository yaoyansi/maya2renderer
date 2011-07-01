#ifndef __mib_glossy_reflection_h
#define __mib_glossy_reflection_h

/*
begin inputs
	valueof_outValue color base_material
	color reflection_color
	float max_distance
	float falloff
	color environment_color
	float reflection_base_weight
	float reflection_edge_weight
	float edge_factor

	float single_env_sample
	float samples
	float u_spread

	float v_spread

	vector u_axis
	vector v_axis
	float dispersion
	color[] spectrum[]
end inputs

begin outputs
	color outValue
end outputs

begin shader_extra_parameters aov_reflection
#ifdef USE_AOV_aov_reflection
	output varying color aov_reflection = 0;
#endif
end shader_extra_parameters
*/

vector cross(vector a, b)
{
	float ax = xcomp(a);
	float ay = ycomp(a);
	float az = zcomp(a);
	float bx = xcomp(b);
	float by = ycomp(b);
	float bz = zcomp(b);
	return vector (
		ay*bz - az*by,
		az*bx - ax*bz,
		ax*by - ay*bx );
}

color myspline(float value; float al; color acolors[])
{
	float clength = al;
	float j = value*(clength-1);
	j = j<(clength-1)?j:clength-1.0001;
	if(clength == 1)
		return acolors[0];
	else
		return mix(
			acolors[floor(j)],
			acolors[floor(j+1)],
			mod(j, 1) );
}

void maya_mib_glossy_reflection (
	color i_base_material;
	color i_reflection_color;
	float i_max_distance;
	float i_falloff;
	color i_environment_color;
	float i_reflection_base_weight;
	float i_reflection_edge_weight;
	float i_edge_factor;

	float i_single_env_sample;
	float i_samples;
	
	float i_u_spread;
	float i_v_spread;

	vector i_u_axis;
	vector i_v_axis;
	
	float i_dispersion;
	color i_spectrum[];
	
	output color o_result;
)
{
	extern normal N;
	extern vector I;
	extern point P;
	
	point z = point (0,0,0);
	
	normal Nn = normalize(N);
	vector In = normalize(I);
	
	vector Rn = normalize( reflect(In, Nn) );
	
	color b_refl = 0;
	float b_dist = 0;
	color b_trs = 0;
	color b_disp = 0;
	
	float dist;
	color trs;
	
	float flf = -In.Nn;
	
	o_result = i_reflection_color;
	
	
	vector u_axis;
	if(i_u_axis == vector(0,0,0))
		u_axis = transform("object", "current", vector(1.0, 0.0, 0.0) );
	else
		u_axis = transform("object", "current", i_u_axis);
	
	u_axis = normalize(u_axis);
	
	vector v_axis;
	if(i_v_axis == vector(0,0,0))
		v_axis = transform("object", "current", vector(0.0, 0.0, 1.0) );
	else
		v_axis = transform("object", "current", i_v_axis);
		
	v_axis = normalize(v_axis);
		
	color rainbow[] = {
		color(1,0,0),
		color(1,0.85,0),
		color(0.2833, 1.0, 0.0),
		color(0,1,0.5667),
		color(0,0.5667,1),
		color(0.2833,0,1),
		color(1,0,0.85) };
	
	float al = arraylength(i_spectrum);
		
	if(al <= 0 || al > 7)
		al = 7;
	
	float i; for(i=0; i<i_samples; i+=1)
	{
		vector myrotatev = normalize(cross(Nn,u_axis));
		float rru = (random()-0.5)*2;
		vector tNn =
			normalize(rotate(vector(Nn),
			rru * i_u_spread, 
			z, point(myrotatev)));
		myrotatev = normalize(cross(Nn,v_axis));
		float rrv = (random()-0.5)*2;
		tNn =
			normalize(rotate(vector(tNn),
			rrv * sqrt(1-rru*rru) * i_v_spread, 
			z, point(myrotatev)));
		vector R = reflect(In, tNn);
		b_refl += trace(P, R, dist, "transmission", trs, "maxdist", i_max_distance) *
			mix(color(1),(myspline(rru/2+0.5, al, rainbow)+
				myspline(rrv/2+0.5, al, rainbow))*0.75, i_dispersion);
		b_dist += dist;
		b_trs  += trs;
	}
	
	b_refl /= i_samples;
	b_dist /= i_samples;
	b_trs  /= i_samples;
	
	o_result *= b_refl;
	
	if(i_max_distance > 0.0)
		o_result *= pow(clamp(1 - b_dist/i_max_distance, 0, 1), i_falloff);
	
	o_result *= mix(i_reflection_edge_weight, i_reflection_base_weight,
						pow(flf, 1/i_edge_factor));

	#ifdef USE_AOV_aov_reflection
		extern varying color aov_reflection;
		if( isoutput(aov_reflection) )
		{
			aov_reflection = o_result;
		}
	#endif
	
	o_result += i_base_material;
}
#endif /* __mib_glossy_reflection_h */