#ifndef _boundary_pseudoscalar_field_discretize_h
#define _boundary_pseudoscalar_field_discretize_h

#include "mesh.h"

void boundary_pseudoscalar_field_discretize(
  double * result,
  const mesh * m,
  const double * m_vol_dm1,
  const jagged1 * boundary_hyperfaces,
  double (*g)(const double *));

#endif /* _boundary_pseudoscalar_field_discretize_h */
