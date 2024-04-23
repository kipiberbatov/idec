#ifndef _quasi_cube_h
#define _quasi_cube_h

#include <stdio.h>

typedef struct quasi_cube
{
  int dim_embedded;
  int dim;
  double * coord;
} quasi_cube;

void quasi_cube_set(
  quasi_cube * s, int s_dim_embedded, int s_dim, double * s_coord);

void quasi_cube_free(quasi_cube * s);

quasi_cube * quasi_cube_file_scan(FILE * in);

void quasi_cube_file_print(FILE * out, const quasi_cube * s, const char * format);

double quasi_cube_measure(const quasi_cube * s);

void quasi_cube_centroid(double * s_medicenter, const quasi_cube * s);

#endif /* _quasi_cube_h */
