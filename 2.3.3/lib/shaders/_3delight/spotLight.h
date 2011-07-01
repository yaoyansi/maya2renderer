/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __spotLight_h
#define __spotLight_h

/*
begin inputs
	prepare color color
	prepare float intensity
	prepare float decayRate
	uniform float coneAngle
	float penumbraAngle
	prepare float dropoff

	uniform float barnDoors
	float leftBarnDoor
	float rightBarnDoor
	float topBarnDoor
	float bottomBarnDoor

	prepare color shadowColor
	uniform float dmapFilterSize
	uniform float dmapBias

	uniform float useRayTraceShadows
	uniform float lightRadius
	uniform float shadowRays
end inputs

begin outputs
end outputs

begin shader_extra_parameters lightsource
	string shadowmapname = "";
	float shadowBlur = 0;
	float shadowSamples = 16;
	float __nonspecular = 0;
	float __nondiffuse = 0;
	string __category = "";
	float iskeylight = 0;
#if defined(USE_AOV_aov_shadow) || \
	defined(USE_SHADER_usebackground)
		output varying float __3dfm_shadowing = 0;
#endif
#if defined(USE_AOV_aov_shadow) || \
	defined(USE_AOV_aov_diffuse_no_shadow) || \
	defined(USE_AOV_aov_diffuse_intensity_no_shadow) || \
	defined(USE_AOV_aov_key_lights_diffuse_intensity_no_shadow) || \
	defined(USE_AOV_aov_specular_no_shadow) || \
	defined(USE_AOV_aov_specular_intensity_no_shadow) || \
	defined(USE_AOV_aov_key_lights_specular_intensity_no_shadow) || \
	defined(USE_AOV_aov_color_no_shadow) || \
	defined(USE_SHADER_usebackground)
		output varying color __3dfm_unshadowed_cl = 0;
#endif
end shader_extra_parameters
*/

#include "light_utils.h"

void
prepare_maya_spotLight(
  // Inputs:
  //
  color i_color;
  float i_intensity;
  float i_decayRate;
  uniform float i_coneAngle;
  float i_penumbraAngle;
  float i_dropoff;

  uniform float barnDoors;
  float i_leftBarnDoor;
  float i_rightBarnDoor;
  float i_topBarnDoor;
  float i_bottomBarnDoor;

  color i_shadowColor;
  uniform float i_dmapFilterSize;
  uniform float i_dmapBias;

  uniform float i_useRayTraceShadows;
  uniform float i_lightRadius;
  uniform float i_shadowRays;

  // Outputs:
  //
  )
{
	uniform point from = point "shader" (0,0,0);
	uniform point to = point "shader" (0,0,1);

	extern vector L;
	extern float ss, tt;

	float coneangle = radians(i_coneAngle);
	float penumbraangle = radians(i_penumbraAngle);
	float max_angle = coneangle / 2;
	if( penumbraangle > 0.0 )
		max_angle += penumbraangle;


	uniform vector A = (to - from)/length(to-from);
	uniform vector xaxis = A ^ vector "shader" (1,0,0);
	if (length(xaxis) == 0)
		xaxis = A ^ vector "shader" (0,1,0);

	uniform vector yaxis = normalize(A ^ xaxis);

	illuminate( from, A, max_angle )
	{
		float anglex = atan(L.xaxis, L.A);
		float angley = atan(L.yaxis, L.A);

		tt = 1 - ((tan(anglex) / tan(max_angle)) * 0.5 + 0.5);
		ss = (tan(angley) / tan(max_angle)) * 0.5 + 0.5;
	}
}

void
end_maya_spotLight(
	// Inputs:
	//
	color i_color;
	float i_intensity;
	float i_decayRate;
	uniform float i_coneAngle;
	float i_penumbraAngle;
	float i_dropoff;

	uniform float barnDoors;
	float i_leftBarnDoor;
	float i_rightBarnDoor;
	float i_topBarnDoor;
	float i_bottomBarnDoor;

	color i_shadowColor;
	uniform float i_dmapFilterSize;
	uniform float i_dmapBias;

	uniform float i_useRayTraceShadows;
	uniform float i_lightRadius;
	uniform float i_shadowRays;

	// Outputs:
	//
	)
{
	uniform point from = point "shader" (0,0,0);
	uniform point to = point "shader" (0,0,1);

	extern color Cl;
	extern vector L;
	extern string shadowmapname;
	extern float shadowBlur;
	extern float shadowSamples;

	float coneangle = radians(i_coneAngle);
	float penumbraangle = radians(i_penumbraAngle);
	float leftBarnDoor = radians(i_leftBarnDoor);
	float rightBarnDoor = radians(i_rightBarnDoor);
	float topBarnDoor = radians(i_topBarnDoor);
	float bottomBarnDoor = radians(i_bottomBarnDoor);

	uniform vector A = (to - from)/length(to-from);
	uniform vector xaxis = A ^ vector "shader" (1,0,0);
	if (length(xaxis) == 0)
		xaxis = A ^ vector "shader" (0,1,0);

	uniform vector yaxis = normalize(A ^ xaxis);
	xaxis = normalize(xaxis);
	uniform float coslimit = cos(coneangle / 2);
	uniform float cospen = cos((coneangle / 2) + penumbraangle);
	uniform float low = min(cospen, coslimit);
	uniform float high = max(cospen, coslimit);
	uniform float max = sin((coneangle / 2) + penumbraangle); 
  
	float max_angle = coneangle / 2;
	if( penumbraangle > 0.0 )
		max_angle += penumbraangle;
		
	illuminate( from, A, max_angle )
	{
		float distance_squared = L.L;
		float distance = sqrt( distance_squared );
		float cosangle = L.A / distance;

		float atten = 1.0;
		
		if( i_decayRate == 0.0 )
			/* do nothing */ ;
		else if( i_decayRate == 2.0 )
			atten /= distance_squared;
		else if( i_decayRate == 1.0 )
			atten /= distance;
		else
			atten /= pow(distance, i_decayRate);

		if (i_dropoff > 0) 
			atten *= clamp(pow(cosangle, 1 + i_dropoff),0,1);

		if (barnDoors > 0)
		{
			float anglex = atan(L.xaxis, L.A);
			float angley = atan(L.yaxis, L.A);

			atten *= smoothstep(min(-bottomBarnDoor, -bottomBarnDoor - penumbraangle),
					max(-bottomBarnDoor, -bottomBarnDoor - penumbraangle), anglex) * 
				(1 - smoothstep(min(topBarnDoor, topBarnDoor + penumbraangle), 
								max(topBarnDoor, topBarnDoor + penumbraangle), anglex));
			atten *= smoothstep(min(-rightBarnDoor, -rightBarnDoor - penumbraangle),
					max(-rightBarnDoor, -rightBarnDoor - penumbraangle), angley) * 
				(1 - smoothstep(min(leftBarnDoor, leftBarnDoor + penumbraangle), 
								max(leftBarnDoor, leftBarnDoor + penumbraangle), angley));
		}

		atten *= smoothstep(low, high, cosangle);

		color lcolor = computeLightColor(
			i_color, i_shadowColor, shadowmapname,
			shadowBlur, shadowSamples, i_dmapFilterSize, i_dmapBias );

#if defined(USE_AOV_aov_shadow) || \
	defined(USE_AOV_aov_diffuse_no_shadow) || \
	defined(USE_AOV_aov_diffuse_intensity_no_shadow) || \
	defined(USE_AOV_aov_key_lights_diffuse_intensity_no_shadow) || \
	defined(USE_AOV_aov_specular_no_shadow) || \
	defined(USE_AOV_aov_specular_intensity_no_shadow) || \
	defined(USE_AOV_aov_key_lights_specular_intensity_no_shadow) || \
	defined(USE_AOV_aov_color_no_shadow) || \
	defined(USE_SHADER_usebackground)
		extern color __3dfm_unshadowed_cl;
		__3dfm_unshadowed_cl = atten * i_intensity * i_color;
#endif

		Cl = atten * i_intensity * lcolor;

		Cl = computeRtShadowing(
			Cl, i_shadowColor,
			i_useRayTraceShadows * i_shadowRays, 0, i_lightRadius );
	}
}

#endif /* __spotLight_h */

