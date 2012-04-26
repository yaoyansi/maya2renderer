#ifndef __misss_fast_shader_h
#define __misss_fast_shader_h

/*
begin inputs
 valueof_outValue color diffuse_illum
 sourcename string diffuse_illum
 color diffuse_color
 valueof_outValue color specular_illum
 float diffuse_weight
 color front_sss_color
 float front_sss_weight
 color back_sss_color
 float back_sss_weight
 
 float front_sss_radius
 float back_sss_radius
 float back_sss_depth
 float scale_conversion
 float falloff
 float samples
 float screen_composit
 float output_sss_only
end inputs
 
begin outputs
 color outValue
end outputs
 
begin shader_extra_parameters aov_diffuse
 #ifdef USE_AOV_aov_diffuse
 output varying color aov_diffuse = 0;
 #endif
end shader_extra_parameters
 
begin shader_extra_parameters aov_subsurface
 #ifdef USE_AOV_aov_subsurface
 output varying color aov_subsurface = 0;
 #endif
end shader_extra_parameters
 */

#define bool float
#define true 1
#define false 0

#define cpow(c, n) ( color(pow(comp(c,0),n),pow(comp(c,1),n),pow(comp(c,2),n)) )

void maya_misss_fast_shader(
				color i_diffuse_illum_color;
				string i_diffuse_illum_string;
				color i_diffuse_color;
				color i_specular_illum_color;
				
				float i_diffuse_weight;
				color i_front_sss_color;
				float i_front_sss_weight;
				color i_back_sss_color;
				float i_back_sss_weight;

				float i_front_sss_radius;
				float i_back_sss_radius;
				float i_back_sss_depth;
				float i_scale_conversion;
				float i_falloff;
				float i_samples;
				bool i_screen_composit;
				bool i_output_sss_only;

				output color o_result;
)
{
	color screen_compose(color a, b)
	{
		return 1.0 - (1.0 - a) * (1.0 - b);
	}
	
	normal ShadingNormal( normal i_N )
	{
		extern vector I;
		normal Nf = i_N;
		
		Nf = faceforward(Nf, I);
		
		return Nf;
	}
	
	extern point P;
	extern normal N;
	extern vector I;
	
	normal sN = ShadingNormal( normalize(N) );
	
	uniform string raytype = "unknown";	
	rayinfo( "type", raytype );
	
	if( raytype == "subsurface" )
	{
		normal Nn = normalize(N);
		color d = diffuse(Nn);
		
		if (Nn . I > 0.0)
		{
			// Back scattering.
			o_result = 10.0 * i_back_sss_color * i_back_sss_weight * d;
		}
		else
		{
			// Front scattering.
			o_result = 0.5*i_front_sss_color * i_front_sss_weight * d;
		}
	} else {
		color diffuse = i_diffuse_color * i_diffuse_weight;
		if(i_diffuse_illum_string == "")
			diffuse *= diffuse(sN);
		else
			diffuse *= i_diffuse_illum_color;
		color subsurf = /*(i_diffuse_color != 0) ?*/ subsurface(P); //* i_diffuse_color : 0;
		subsurf = cpow(subsurf, 0.6);
		
		if( i_output_sss_only == true)
		{
			o_result = subsurf;
		}
		else
		{
			if( i_screen_composit == true )
			{
				o_result = screen_compose(diffuse, subsurf);
				o_result = screen_compose(o_result, i_specular_illum_color);
			}
			else
				o_result = diffuse + subsurf + i_specular_illum_color;
			
#ifdef USE_AOV_aov_diffuse
			extern varying color aov_diffuse;
			if( isoutput(aov_diffuse) )
			{
				aov_diffuse = diffuse;
			}
#endif
		}
#ifdef USE_AOV_aov_subsurface
		extern varying color aov_subsurface;
		if( isoutput(aov_subsurface) )
		{
			aov_subsurface = subsurf;
		}
#endif
	}
}

#undef cpow

#undef bool
#undef true
#undef false

#endif /* __misss_fast_shader_h */
