/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __ramp_utils_h
#define __ramp_utils_h

color
colorRamp(
	float i_pos;
	float i_positions[];
	uniform float i_interpolation[];
	color i_colorValues[];)
{
	color result = 0;
	
	if(arraylength(i_positions) == arraylength(i_colorValues) &&
			arraylength(i_positions) > 0)
	{
		float min = -1e10;
		float max = 1e10;
		float i = 0;
		float pre_i = -1;   // Index of pos preceeding i
		float post_i = -1;  // Index of pos following i
		
		for(i = 0; i < arraylength(i_positions); i+=1)
		{
			if(i_positions[i] <= i_pos && i_positions[i] > min)
			{
				min = i_positions[i];
				pre_i = i;
			}
			else if(i_positions[i] >= i_pos && i_positions[i] < max)
			{
				max = i_positions[i];
				post_i = i;
			}
		}
		
		if(pre_i < 0)
		{
			result = i_colorValues[post_i];
		}
		else if(post_i < 0)
		{
			result = i_colorValues[pre_i];
		}
		else
		{
			float diff = (i_pos - i_positions[pre_i]) /
				(i_positions[post_i] - i_positions[pre_i]);

			float interp = i_interpolation[0];
			if(arraylength(i_interpolation) > 1)
			{
				interp = i_interpolation[pre_i];
			}
			
			if(interp == 0)
			{
				// No interpolation
				result = i_colorValues[pre_i];
			}
			else if(interp == 1)
			{
				// Linear interpolation
				result = mix(i_colorValues[pre_i], i_colorValues[post_i], diff);
			}
			else
			{
				// Todo: implement other interpolation types than smooth
				result = mix(
					i_colorValues[pre_i], 
					i_colorValues[post_i],
					smoothstep(0, 1, diff));
			}
		}
	}

	return result;
}

float
floatRamp(
	float i_pos;
	float i_positions[];
	uniform float i_interpolation[];
	float i_floatValues[];)
{
	float result = 0;
	
	if(arraylength(i_positions) == arraylength(i_floatValues) &&
			arraylength(i_positions) > 0)
	{
		float min = -1e10;
		float max = 1e10;
		float i = 0;
		float pre_i = -1;   // Index of pos preceeding i
		float post_i = -1;  // Index of pos following i
		
		for(i = 0; i < arraylength(i_positions); i+=1)
		{
			if(i_positions[i] <= i_pos && i_positions[i] > min)
			{
				min = i_positions[i];
				pre_i = i;
			}
			else if(i_positions[i] >= i_pos && i_positions[i] < max)
			{
				max = i_positions[i];
				post_i = i;
			}
		}
		
		if(pre_i < 0)
		{
			result = i_floatValues[post_i];
		}
		else if(post_i < 0)
		{
			result = i_floatValues[pre_i];
		}
		else
		{
			float diff = (i_pos - i_positions[pre_i]) /
				(i_positions[post_i] - i_positions[pre_i]);

			float interp = i_interpolation[0];
			if(arraylength(i_interpolation) > 1)
			{
				interp = i_interpolation[pre_i];
			}
			
			if(interp == 0)
			{
				// No interpolation
				result = i_floatValues[pre_i];
			}
			else if(interp == 1)
			{
				// Linear interpolation
				result = mix(i_floatValues[pre_i], i_floatValues[post_i], diff);
			}
			else
			{
				// Todo: implement other interpolation types than smooth
				result = mix(
					i_floatValues[pre_i], 
					i_floatValues[post_i],
					smoothstep(0, 1, diff));
			}
		}
	}

	return result;
}

#endif /* __ramp_utils_h */

