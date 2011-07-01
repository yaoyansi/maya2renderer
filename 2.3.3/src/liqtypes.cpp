#include "liqtypes.h"
#include <cmath>

void setColor(liqColor& color, const liqFloat &c )
{
	color[0] = color[1] = color[2] = c;
}

void setColor(liqColor& to, const liqColor& from )
{
	to[0] = from[0];
	to[1] = from[1];
	to[2] = from[2];
}

// void setColor(liqColor& to, const liqFloat from[3] )
// {
// 	to[0] = from[0];
// 	to[1] = from[1];
// 	to[2] = from[2];
// }

liqFloat toRadians(const liqFloat &angle)
{
	return (liqFloat)(angle * M_PI/180.0f);
}