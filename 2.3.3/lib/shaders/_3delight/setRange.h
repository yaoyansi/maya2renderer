/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __setRange_h
#define __setRange_h

/*
begin inputs
	point value
	point min
	point max
	point oldMin
	point oldMax
end inputs

begin outputs
	point outValue
end outputs
*/

void
maya_setRange(
	// Inputs
	point i_value;
	point i_min;
	point i_max;
	point i_oldMin;
	point i_oldMax;

	// Outputs
	output point o_outValue )
{
	vector oldRange = i_oldMax - i_oldMin;

	o_outValue =
		i_min + (((i_value - i_oldMin) / oldRange) * (i_max - i_min ));

	/* Maya clamps the output to the [min, max] range. */
	o_outValue = clamp( o_outValue, i_min, i_max );

	/*
		While we're not affected by division by zero, we do this check anyway
		to match maya's behavior which is to pass i_value through.
	*/
	if( xcomp( oldRange ) == 0 )
	{
		setxcomp( o_outValue, xcomp( i_value ) );
	}

	if( ycomp( oldRange ) == 0 )
	{
		setycomp( o_outValue, ycomp( i_value ) );
	}

	if( zcomp( oldRange ) == 0 )
	{
		setzcomp( o_outValue, zcomp( i_value ) );
	}
}

#endif /* __setRange_h */

