/*
 Moscow 2009 #003
 */

#ifndef __mib_glossy_refraction_h
#define __mib_glossy_refraction_h

/*
 begin inputs
 valueof_outValue color top_material
 valueof_outValue color deep_material
 valueof_outValue color back_material
 sourcename string back_material
 float render_reverse_of_back_material
 color refraction_color
 float max_distance
 float falloff
 float refraction_base_weight
 float refraction_edge_weight
 float edge_factor
 float ior
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
 
 begin shader_extra_parameters aov_refraction
 #ifdef USE_AOV_aov_refraction
 output varying color aov_refraction = 0;
 #endif
 end shader_extra_parameters
 */

void maya_mib_glossy_refraction (
								 color i_top_material;
								 color i_deep_material;
								 color i_back_material;
								 string i_back_material_string;
								 float i_render_reverse_of_back_material;
								 color i_refraction_color;
								 float i_max_distance;
								 float i_falloff;
								 float i_refraction_base_weight;
								 float i_refraction_edge_weight;
								 float i_edge_factor;
								 float i_ior;
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
	
	extern normal N;
	extern vector I;
	extern point P;
	
	point z = point (0,0,0);
	
	normal Nn = normalize(N);
	vector In = normalize(I);
	normal Ns = faceforward(Nn, In);
	
	float flf = -In.Nn;	
	float backface = flf>0?0:1;
	
	if(backface == 1 && i_back_material_string != "")
	{
		if(i_render_reverse_of_back_material == 1)
			o_result = 0;
		else
			o_result = i_back_material;
	}
	else
	{	
		vector T;
		float eta = 1/i_ior;
		
		color b_refr = 0;
		float b_dist = 0;
		
		float dist;
		color trs;
		
		o_result = i_refraction_color;
		
		vector u_axis;
		if(i_u_axis == vector(0,0,0))
			u_axis = transform("world", "current", vector(1.0, 0.0, 0.0) );
		else
			u_axis = transform("world", "current", i_u_axis);
		
		u_axis = normalize(u_axis);
		
		vector v_axis;
		if(i_v_axis == vector(0,0,0))
			v_axis = transform("world", "current", vector(0.0, 0.0, 1.0) );
		else
			v_axis = transform("world", "current", i_v_axis);
		
		v_axis = normalize(v_axis);
		
		// this constants is HSV (n * 360/7, 1, 1)
		// it is necessary to choose constants more precisely
		
		color rainbow[] = {
			color(1,0,0),
			color(1,0.85,0),
			color(0.2833, 1.0, 0.0),
			color(0,1,0.5667),
			color(0,0.5667,1),
			color(0.2833,0,1),
		color(1,0,0.85) };
		
		float al = arraylength(i_spectrum);
		
		// Close to mi implementation. In mi documentation other information.	
		if(al <= 0 || al > 7)
			al = 7;
		
		float spread_correct = 0.75;
		float i; for(i=0; i<i_samples; i+=1)
		{
			// http://img176.imageshack.us/img176/5514/glossyrefraction.jpg
			// first of all we ned axis to rotate surface normal
			// cross product of two vectors is vector which is perpendicular
			//   to plane containing the two input vectors
			vector Vr = normalize(cross(Ns,u_axis));
			// random value to rotate surface normal 
			// random value in range [-1..1]
			float rru = (random()-0.5)*2;
			// rotating surface normal in the plane
			vector Nt =
			normalize(rotate(Ns,
							 rru * i_u_spread * spread_correct, 
							 z, point(Vr) ));
			// rotating surface normal in plane containing v_axis
			Vr = normalize(cross(Ns,v_axis));
			float rrv = (random()-0.5)*2;
			Nt =
			// spread multipled by sqrt(1-rru*rru) because section of spread is ellipse
			normalize(rotate(Nt,
							 rrv * sqrt(1-rru*rru) * i_v_spread * spread_correct, 
							 z, point(Vr) ));
			
			// refract, trace
			T = refract(In, Nt, eta);
			b_refr += trace(P, T, dist, "maxdist", i_max_distance) *
			// and mutiply by dispersion
			mix(color(1),(myspline(rru/2+0.5, al, rainbow)+
						  myspline(rrv/2+0.5, al, rainbow))*0.75, i_dispersion);
			b_dist += dist;
		}
		
		b_refr /= i_samples;
		b_dist /= i_samples;
		
		o_result *= b_refr;
		
		float deepmult = pow(clamp(1 - b_dist/i_max_distance, 0, 1), i_falloff);
		if(i_max_distance > 0.0)
		{
			o_result *= deepmult;
			o_result += i_deep_material*(1-deepmult);
		}
		
		o_result *= mix(i_refraction_edge_weight, i_refraction_base_weight,
						pow(flf, 1/i_edge_factor));
		
#ifdef USE_AOV_aov_refraction
		extern varying color aov_refraction;
		if( isoutput(aov_refraction) )
		{
			aov_refraction = o_result;
		}
#endif
		
		o_result += i_top_material;
	}
}

#endif /* __mib_glossy_refraction_h */