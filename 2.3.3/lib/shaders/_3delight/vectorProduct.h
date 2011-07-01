/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __vectorProduct_h
#define __vectorProduct_h

/*
begin inputs
	float operation
	vector input1
	vector input2
	matrix matrix
	float normalizeOutput
end inputs

begin outputs
	vector output
end outputs
*/

void
maya_vectorProduct(
	// Inputs
	float i_operation;
	vector i_input1;
	vector i_input2;
	matrix i_matrix;
	float i_normalizeOutput;

	// Outputs
	output vector o_output )
{
	if( i_operation == 0 )
	{
		o_output = i_input1;
	}
	else if( i_operation == 1 )
	{
		o_output = i_input1 . i_input2;
	}
	else if( i_operation == 2 )
	{
		o_output = i_input1 ^ i_input2;
	}
	else if( i_operation == 3 )
	{
		o_output = vtransform( i_matrix, i_input1 );
	}
	else
	{
		o_output = vector( transform( i_matrix, point(i_input1) ) );
	}

	if( i_normalizeOutput == 1 )
	{
		if( i_operation == 1 )
		{
			/*
				Normalization for the dot product really means normalize the
				inputs so the returned value is the cos of the angle between
				the vectors. This code is equivalent to:
				o_output /= length( i_input1 ) * length( i_input2 );
			*/
			o_output /= sqrt( (i_input1 . i_input1) * (i_input2 . i_input2) );
		}
		else
		{
			o_output = normalize( o_output );
		}
	}
}

#endif /* __vectorProduct_h */

