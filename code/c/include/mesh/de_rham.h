#ifndef _de_rham_h
#define _de_rham_h

#include "mesh.h"

/* Obtain the values of a 0-cochain coming from a scalar field */
void de_rham_0(double * x, const mesh * m, double (*f)(const double *));

#endif /* _de_rham_h */
