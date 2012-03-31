#ifndef _MY_UTILS_H_
#define _MY_UTILS_H_

#include <eiAPI/ei_shaderx.h>

#define LIQ_SCALAR_ALMOST_ZERO (0.0001f)

// a->x<b && a->y<b && a->z <b
eiBool less_than(const eiVector *a, const scalar b);

#endif//_MY_UTILS_H_