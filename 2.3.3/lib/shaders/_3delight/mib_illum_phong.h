#ifndef __mib_illum_phong_h
#define __mib_illum_phong_h

/*
begin inputs
	color ambience
	color ambient
	color diffuse
	color specular
	float exponent
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

normal ShadingNormal( normal i_N )
{
	extern vector I;
	normal Nf = i_N;

	Nf = faceforward(Nf, I);

	return Nf;
}

void maya_mib_illum_phong(
	color i_ambience;
	color i_ambient;
	color i_diffuse;
	color i_specular;	
	float i_exponent;
	
	output color outValue;)
{
	extern normal N;
	extern vector I;
	
	normal sN = ShadingNormal( normalize(N) );
	color diffuse_component = i_diffuse != 0 ? diffuse(sN) * i_diffuse : 0;
	// I thought following formula is correct:
	//color ambient_component = i_ambient != 0 ? ambient() * i_ambient : 0;
	//	ambient_component *= i_ambience;
	
	// But after sseveral tests, I think it is correct... Strange mental ray shader :/
	color ambient_component =  i_ambience * i_ambient;
	color specular_component = i_specular != 0 ? i_specular * specularstd(sN, normalize(-I), 1/i_exponent) : 0;
		
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

#endif /* __mib_illum_phong_h */
