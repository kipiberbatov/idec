#ifndef _unsigned_approximation_h
#define _unsigned_approximation_h

#include "mesh.h"

/* Takes a scalar field $f$ and -- $x$ is $f$ averaged on $1$-cells of $m$ */
void unsigned_approximation_of_scalar_field_on_1_cells(
  double * x,
  const mesh * m,
  double (*f)(const double *));

/* Takes a scalar field $f$ and -- $x$ is $f$ averaged on $2$-cells of $m$ */
void unsigned_approximation_of_scalar_field_on_hyperfaces(
  double * x,
  const mesh * m,
  double (*f)(const double *));

void unsigned_approximation_of_scalar_field_on_nonzero_cells(
  double * x, const mesh * m, double (*f)(const double *), int p);

#endif /* _unsigned_approximation_h */
