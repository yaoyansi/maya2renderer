#ifndef __mib_illum_cooktorr_h
#define __mib_illum_cooktorr_h

/*
begin inputs
	color ambience
	color ambient
	color diffuse
	color specular
	float roughness
	color ior
end inputs

begin outputs
	color outValue
end outputs

begin shader_extra_parameters aov_diffuse
#ifdef USE_AOV_aov_diffuse
	output varying color aov_diffuse = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_ambient
#ifdef USE_AOV_aov_ambient
	output varying color aov_ambient = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_specular
#ifdef USE_AOV_aov_specular
	output varying color aov_specular = 0;
#endif
end shader_extra_parameters
*/

#include "shading_utils.h"

void maya_mib_illum_cooktorr(
	color i_ambience;
	color i_ambient;
	color i_diffuse;
	color i_specular;	
	float i_roughness;
	color i_ior;
	
	output color outValue;)
{
	extern normal N;
	extern vector I;
	
	normal sN = ShadingNormal( normalize(N) );
	color diffuse_component = i_diffuse != 0 ? diffuse(sN) * i_diffuse : 0;
	
	color ambient_component =  i_ambience * i_ambient;
	
	color specular_component = 0.0;
	if( i_specular != 0 )
	{
		vector In = normalize(I);
		float etar = 1/comp(i_ior, 0);
		float etag = 1/comp(i_ior, 1);
		float etab = 1/comp(i_ior, 2);
		float Kt, Krr, Krg, Krb;
		fresnel(In, sN, etar, Krr, Kt);
		fresnel(In, sN, etag, Krg, Kt);
		fresnel(In, sN, etab, Krb, Kt);
		
		specular_component = getBlinn(sN, i_roughness, 1.0, 0.0, 0.0);
		specular_component *= i_specular * color(Krr, Krg, Krb);
	}
		
	outValue = diffuse_component + ambient_component + specular_component;
	
	#ifdef USE_AOV_aov_diffuse
		extern varying color aov_diffuse;
		if( isoutput(aov_diffuse) )
		{
			aov_diffuse = diffuse_component;
		}
	#endif
	
	#ifdef USE_AOV_aov_ambient
		extern varying color aov_ambient;
		if( isoutput(aov_ambient) )
		{
			aov_ambient = ambient_component;
		}
	#endif
	
	#ifdef USE_AOV_aov_specular
		extern varying color aov_specular;
		if( isoutput(aov_specular) )
		{
			aov_specular = specular_component;
		}
	#endif
}

#endif /* __mib_illum_cooktorr_h */
