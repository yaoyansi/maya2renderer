/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __plusMinusAverage_h
#define __plusMinusAverage_h

/*
begin inputs
	uniform float operation
	float[] input1D[]
	float2[] input2D[]
	color[] input3D[]
end inputs

begin outputs
	float output1D
	float2 output2D
	color output3D
end outputs
*/

void
maya_plusMinusAverage(
	// Inputs
	uniform float i_operation;
	float i_input1D[];
	float i_input2D[];
	color i_input3D[];

	// Outputs
	output float o_output1D;
	output float o_output2D[2];
	output color o_output3D )
{
	uniform float n1 = arraylength(i_input1D);
	uniform float n2 = arraylength(i_input2D) / 2;
	uniform float n3 = arraylength(i_input3D);

	// Start with the first element in output; this is common to all operations.
	o_output1D = (n1 == 0) ? 0 : i_input1D[0];
	if( n2 == 0 )
	{
		o_output2D[0] = 0;
		o_output2D[1] = 0;
	} else {
		o_output2D[0] = i_input2D[0];
		o_output2D[1] = i_input2D[1];
	}
	o_output3D = (n3 == 0) ? color(0) : i_input3D[0];

	if( i_operation != 0 )
	{
		// Compute the sum of the other elements, needed for all but noop.
		uniform float i;
		float sum1 = 0;
		float sum2a = 0, sum2b = 0;
		color sum3 = 0;

		for( i = 1; i < n1; i += 1 )
		{
			sum1 += i_input1D[i];
		}

		for( i = 2; i < n2*2; i += 2 )
		{
			sum2a += i_input2D[i];
			sum2b += i_input2D[i + 1];
		}

		for( i = 1; i < n3; i += 1 )
		{
			sum3 += i_input3D[i];
		}

		if( i_operation == 2 )
		{
			// Subtract
			o_output1D -= sum1;
			o_output2D[0] -= sum2a;
			o_output2D[1] -= sum2b;
			o_output3D -= sum3;
		}
		else
		{
			// Add or average, start by adding.
			o_output1D += sum1;
			o_output2D[0] += sum2a;
			o_output2D[1] += sum2b;
			o_output3D += sum3;

			if( i_operation == 3 )
			{
				// Average
				o_output1D /= n1;
				o_output2D[0] /= n2;
				o_output2D[1] /= n2;
				o_output3D /= n3;
			}
		}
	}
}

#endif /* __plusMinusAverage_h */

