#ifndef QUASI_CUBE_H
#define QUASI_CUBE_H

#include <stdio.h>

typedef struct quasi_cube
{
  int dim_embedded;
  int dim;
  double * coord;
} quasi_cube;

void quasi_cube_free(quasi_cube * s);
quasi_cube * quasi_cube_fscan(FILE * in);
void quasi_cube_fprint(FILE * out, const quasi_cube * s, const char * format);

double quasi_cube_measure(const quasi_cube * s);
void quasi_cube_centroid(double * s_medicenter, const quasi_cube * s);

#endif /* QUASI_CUBE_H */
