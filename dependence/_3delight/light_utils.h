/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __light_utils_h
#define __light_utils_h

#include "utils.h"

float receive_shadows()
{
	uniform float receive_shad = 1;
	attribute( "user:delight_receive_shadows", receive_shad );
	return receive_shad;
}

color computeLightColor(
	color i_color;
	color i_shadowColor;
	uniform string i_shadowmapName;
	uniform float i_shadowBlur;
	uniform float i_shadowSamples;
	uniform float i_dmapFilterSize;
	uniform float i_dmapBias;
	)
{
	extern point Ps;
  
	color lcolor = i_color;

	if( i_shadowmapName != "" && 1 == receive_shadows() )
	{
		color Cshad;
  
		uniform float filterwidth = i_dmapFilterSize;
		uniform float samples = i_shadowSamples;

		if( i_dmapFilterSize > 1 )
		{
			uniform float shadingrate = 1;
			attribute("ShadingRate", shadingrate);

			filterwidth = 2.5 * i_dmapFilterSize / sqrt(shadingrate);
			if( filterwidth < 1 )
			{
				filterwidth = 1;
			}

			if( i_dmapFilterSize > 2 )
			{
				samples *= 2 + i_dmapFilterSize / 10;
			}
		}

		if( i_dmapBias == 0)
		{
			Cshad = shadow(
				i_shadowmapName, Ps,
				"blur", i_shadowBlur,
				"width", filterwidth,
				"samples", samples );
		}
		else
		{
			Cshad = shadow(
				i_shadowmapName, Ps,
				"bias", i_dmapBias,
				"blur", i_shadowBlur,
				"width", filterwidth,
				"samples", samples );
		}

#if defined(USE_AOV_aov_shadow) || \
    defined(USE_SHADER_usebackground)
        extern float __3dfm_shadowing;
        __3dfm_shadowing = luminance(Cshad);
#endif
    
		lcolor = mix( lcolor, i_shadowColor, Cshad );
	}

	return lcolor;
}

/*
	This would normally go in computeLightColor but maya's messed up handling
	of shadowColor.  While for depth map shadows the shadow color simply
	replaces the light color in the shadows, with raytraced shadows it
	completely overrides the light's color and intensity. I'm sure arguments
	can be made for either behavior but it should at least be the same for both
	shadowing methods...
*/
color computeRtShadowing(
	color i_Cl;
	color i_shadowColor;
	uniform float i_rtShadSamples;
	uniform float i_rtShadLightIsDirectional;
	uniform float i_rtShadLightRadiusOrAngle;
	)
{
	extern point Ps;

	color lcolor = i_Cl;

	if( i_rtShadSamples != 0 && 1 == receive_shadows() )
	{
		point to;
		float angle;

		if( i_rtShadLightIsDirectional == 1.0 )
		{
			to = Ps + (vector "shader" (0,0,-1)) * 1e10;
			angle = radians(i_rtShadLightRadiusOrAngle);
		} else {
			to = point "shader" 0;
			angle = atan( i_rtShadLightRadiusOrAngle / distance( Ps, to ) );
		}

		color Cshad = 1.0 - 
			transmission(
				Ps, to,
				"samples", i_rtShadSamples,
				"samplecone", angle );

#if defined(USE_AOV_aov_shadow) || \
    defined(USE_SHADER_usebackground)
        extern float __3dfm_shadowing;
        __3dfm_shadowing = luminance(Cshad);
#endif

		lcolor = mix( i_Cl, i_shadowColor, Cshad );
	}

	return lcolor;
}

#endif
