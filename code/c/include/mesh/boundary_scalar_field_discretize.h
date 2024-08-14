#ifndef _boundary_scalar_field_discretize_h
#define _boundary_scalar_field_discretize_h

#include "mesh.h"

void boundary_scalar_field_discretize(
  double * result,
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * boundary_nodes,
  double (*g)(const double *));

#endif /* _boundary_scalar_field_discretize_h */
