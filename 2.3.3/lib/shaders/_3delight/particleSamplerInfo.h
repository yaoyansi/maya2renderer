/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __particleSamplerInfo_h
#define __particleSamplerInfo_h

// Misaligned params should be declared as uniform but DL_translateMayaToSl
// is missing uniform dummy variable declaractions
//

/*
begin inputs
  uniform float outUvType
  uniform float normalizationMethod
  uniform float normalizationVlalue
  uniform float inverseOutUv
end inputs

begin outputs
	color outColor
  color outTransparency
  color outIncandescence
  float ageNormalized
   float colorRed
   float colorGreen
   float colorBlue
  float opacityPP
   float opacity
  float particleId
  float finalLifespanPP
  float lifespanPP
   float lifespan
  float age
  float birthTime
  float parentU
  float parentV
  float collisionU
  float collisionV
  float radiusPP
   float radius
  float userScalar1PP
  float userScalar2PP
  float userScalar3PP
  float userScalar4PP
  float userScalar5PP
  color rgbPP
  color incandescencePP
   color incandescence
  vector acceleration
  vector force
  vector position
  vector worldPosition
  vector birthPosition
  vector birthWorldPosition
  vector velocity
  vector worldVelocity
  vector userVector1PP
  vector userVector2PP
  vector userVector3PP
  vector userVector4PP
  vector userVector5PP  
end outputs

begin shader_extra_parameters surface
#define UNDEFINED_UV -10000000
  varying float ageNormalized = UNDEFINED_UV;
   float colorRed = UNDEFINED_UV;
   float colorGreen = UNDEFINED_UV;
   float colorBlue = UNDEFINED_UV;
   float opacity = UNDEFINED_UV;
  varying float opacityPP = UNDEFINED_UV;
  varying float particleId = UNDEFINED_UV;
  varying float finalLifespanPP = UNDEFINED_UV;
   float lifespan = UNDEFINED_UV;
  varying float lifespanPP = UNDEFINED_UV;
  varying float age = UNDEFINED_UV;
  varying float birthTime = UNDEFINED_UV;
  varying float parentU = UNDEFINED_UV;
  varying float parentV = UNDEFINED_UV;
  varying float collisionU = UNDEFINED_UV;
  varying float collisionV = UNDEFINED_UV;
   float radius = UNDEFINED_UV;
  varying float radiusPP = UNDEFINED_UV;
  varying float userScalar1PP = UNDEFINED_UV;
  varying float userScalar2PP = UNDEFINED_UV;
  varying float userScalar3PP = UNDEFINED_UV;
  varying float userScalar4PP = UNDEFINED_UV;
  varying float userScalar5PP = UNDEFINED_UV;
  varying color rgbPP = UNDEFINED_UV;
  varying color incandescencePP = UNDEFINED_UV;
   color incandescence = UNDEFINED_UV;
  varying vector acceleration = UNDEFINED_UV;
  varying vector force = UNDEFINED_UV;
  varying vector position = UNDEFINED_UV;
  varying vector worldPosition = UNDEFINED_UV;
  varying vector birthPosition = UNDEFINED_UV;
  varying vector birthWorldPosition = UNDEFINED_UV;
  varying vector velocity = UNDEFINED_UV;
  varying vector worldVelocity = UNDEFINED_UV;
  varying vector userVector1PP = UNDEFINED_UV;
  varying vector userVector2PP = UNDEFINED_UV;
  varying vector userVector3PP = UNDEFINED_UV;
  varying vector userVector4PP = UNDEFINED_UV;
  varying vector userVector5PP = UNDEFINED_UV;
end shader_extra_parameters
*/

#include "utils.h"

void
maya_particleSamplerInfo(
	// Inputs
	//
  uniform float i_outUvType;
  uniform float i_normalizationMethod;
  uniform float i_normalizationVlalue;
  uniform float i_inverseOutUv;

  // Outputs
  //
	output varying color o_outColor;
  output color o_outTransparency;
  output color o_outIncandescence;
  output float o_ageNormalized;
  output  float o_colorRed;
  output  float o_colorGreen;
  output  float o_colorBlue;
  output float o_opacityPP;
  output  float o_opacity;
  output float o_particleId;
  output float o_finalLifespanPP;
  output float o_lifespanPP;
  output  float o_lifespan;
  output float o_age;
  output float o_birthTime;
  output float o_parentU;
  output float o_parentV;
  output float o_collisionU;
  output float o_collisionV;
  output float o_radiusPP;
  output  float o_radius;
  output float o_userScalar1PP;
  output float o_userScalar2PP;
  output float o_vuserScalar3PP;
  output float o_userScalar4PP;
  output float o_userScalar5PP;
  output color o_rgbPP;
  output color o_incandescencePP;
  output  color o_incandescence;
  output vector o_acceleration;
  output vector o_force;
  output vector o_position;
  output vector o_worldPosition;
  output vector o_birthPosition;
  output vector o_birthWorldPosition;
  output vector o_velocity;
  output vector o_worldVelocity;
  output vector o_userVector1PP;
  output vector o_userVector2PP;
  output vector o_userVector3PP;
  output vector o_userVector4PP;
  output vector o_userVector5PP; 
	)
{
  extern varying float ageNormalized;
  extern uniform float colorRed;
  extern uniform float colorGreen;
  extern uniform float colorBlue;
  extern uniform float opacity;
  extern varying float opacityPP;
  extern varying float particleId;
  extern varying float finalLifespanPP;
  extern uniform float lifespan;
  extern varying float lifespanPP;
  extern varying float age;
  extern varying float birthTime;
  extern varying float parentU;
  extern varying float parentV;
  extern varying float collisionU;
  extern varying float collisionV;
  extern uniform float radius;
  extern varying float radiusPP;
  extern varying float userScalar1PP;
  extern varying float userScalar2PP;
  extern varying float userScalar3PP;
  extern varying float userScalar4PP;
  extern varying float userScalar5PP;
  extern varying color rgbPP;
  extern varying color incandescencePP;
  extern uniform color incandescence;
  extern varying vector acceleration;
  extern varying vector force;
  extern varying vector position;
  extern varying vector worldPosition;
  extern varying vector birthPosition;
  extern varying vector birthWorldPosition;
  extern varying vector velocity;
  extern varying vector worldVelocity;
  extern varying vector userVector1PP;
  extern varying vector userVector2PP;
  extern varying vector userVector3PP;
  extern varying vector userVector4PP;
  extern varying vector userVector5PP;
  
  color uniformColor = color(colorRed, colorGreen, colorBlue);
  
  if(rgbPP != color(UNDEFINED_UV))
    o_outColor = rgbPP;
  else if(uniformColor != color(UNDEFINED_UV))
    o_outColor = uniformColor;
  else
    o_outColor = 0;
  
  if(opacityPP != UNDEFINED_UV)
    o_outTransparency = 1 - opacityPP;
  else if(opacity != UNDEFINED_UV)
    o_outTransparency = 1 - opacity;
  else
    o_outTransparency = 0;
  
  if(incandescencePP != color(UNDEFINED_UV))
    o_outIncandescence = incandescencePP;
  else if(incandescence != color(UNDEFINED_UV))
    o_outIncandescence = incandescencePP;
  else
    o_outIncandescence = 0;
  
  o_ageNormalized = ageNormalized;
  o_colorRed = colorRed;
  o_colorGreen = colorGreen;
  o_colorBlue = colorBlue;
  o_opacityPP = opacityPP;
  o_opacity = opacity;
  o_particleId = particleId;
  o_finalLifespanPP = finalLifespanPP;
  o_lifespanPP = lifespanPP;
  o_lifespan = lifespan;
  o_age = age;
  o_birthTime = birthTime;
  o_parentU = parentU;
  o_parentV = parentV;
  o_collisionU = collisionU;
  o_collisionV = collisionV;
  o_radiusPP = radiusPP;
  o_radius = radius;
  o_userScalar1PP = userScalar1PP;
  o_userScalar2PP = userScalar2PP;
  o_vuserScalar3PP = userScalar3PP;
  o_userScalar4PP = userScalar4PP;
  o_userScalar5PP = userScalar5PP;
  o_rgbPP = rgbPP;
  o_incandescencePP = incandescencePP;
  o_incandescence = incandescence;
  o_acceleration = acceleration;
  o_force = force;
  o_position = position;
  o_worldPosition = worldPosition;
  o_birthPosition = birthPosition;
  o_birthWorldPosition = birthWorldPosition;
  o_velocity = velocity;
  o_worldVelocity = worldVelocity;
  o_userVector1PP = userVector1PP;
  o_userVector2PP = userVector2PP;
  o_userVector3PP = userVector3PP;
  o_userVector4PP = userVector4PP;
  o_userVector5PP = userVector5PP; 
}

#endif /* __particleSamplerInfo_h */

