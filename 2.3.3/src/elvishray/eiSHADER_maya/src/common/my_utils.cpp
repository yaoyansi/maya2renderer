
#include "my_utils.h"

//
eiBool less_than(const eiVector *a, const scalar b)
{
	return (a->x<b && a->y<b && a->z <b)? eiTRUE:eiFALSE;
}