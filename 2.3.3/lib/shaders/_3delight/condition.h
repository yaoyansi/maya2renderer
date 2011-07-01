/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __condition_h
#define __condition_h

/*
begin inputs
	float operation
	float firstTerm
	float secondTerm
	color colorIfTrue
	color colorIfFalse
end inputs

begin outputs
	color outColor
end outputs
*/

void
maya_condition(
	// Inputs
	//
	float i_operation;
	float i_firstTerm;
	float i_secondTerm;
	color i_colorIfTrue;
	color i_colorIfFalse;
	// Outpus
	//
	output color o_outColor;)
{
	if(i_operation == 0.0)
	{
		o_outColor = (i_firstTerm == i_secondTerm ? i_colorIfTrue : i_colorIfFalse);
	}
	else if(i_operation == 1.0)
	{
		o_outColor = (i_firstTerm != i_secondTerm ? i_colorIfTrue : i_colorIfFalse);
	}
	else if(i_operation == 2.0)
	{
		o_outColor = (i_firstTerm > i_secondTerm ? i_colorIfTrue : i_colorIfFalse);
	}
	else if(i_operation == 3.0)
	{
		o_outColor = (i_firstTerm >= i_secondTerm ? i_colorIfTrue : i_colorIfFalse);
	}
	else if(i_operation == 4.0)
	{
		o_outColor = (i_firstTerm < i_secondTerm ? i_colorIfTrue : i_colorIfFalse);
	}
	else
	{
		o_outColor = (i_firstTerm <= i_secondTerm ? i_colorIfTrue : i_colorIfFalse);
	}
}

#endif /* __condition_h */

