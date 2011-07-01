/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __distanceBetween_h
#define __distanceBetween_h

/*
begin inputs
	point point1
	point point2
	
end inputs

begin outputs
	float distance
	
end outputs
*/

void
maya_distanceBetween(
	// Inputs
	point i_point1;
	point i_point2;
	// Outputs
	output float o_distance )
{
	o_distance = distance( i_point2, i_point1 );
}

#endif /* __distanceBetween_h */

