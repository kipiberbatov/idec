#ifndef _de_rham_h
#define _de_rham_h

#include "mesh.h"

/* Obtain the values of a 0-cochain coming from a scalar field */
void de_rham_0(double * x, const mesh * m, double (*f)(const double *));

void de_rham_top_dimension(
  double * x,
  const mesh * m,
  const double * m_vol_d,
  double (*f)(const double *));

void de_rham_nonzero(
  double * x,
  const mesh * m,
  int p,
  const double * m_vol_p,
  double (*f)(const double *));

void de_rham_boundary_0(
  double * x,
  const struct mesh * m,
  const struct jagged1 * boundary,
  double (*f)(const double *));

void de_rham_sequence_0(
  double * w,
  const mesh * m,
  double start,
  double step,
  int number_of_steps,
  double (*f)(double, const double *));

void de_rham_2_hemisphere_polar_forman(
  double * x,
  const mesh * m,
  const double * m_vol_d,
  double (*f)(const double *));

#endif /* _de_rham_h */
