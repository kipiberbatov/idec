#ifndef _polytope_h
#define _polytope_h

#include "jagged.h"

void polytope_coordinates_arithmetic_mean(
  double * result,
  int embedding_dimension,
  const jagged1 * nodes,
  const double * coordinates);

#endif /* _polytope_h */
