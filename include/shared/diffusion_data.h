#ifndef _diffusion_data_h
#define _diffusion_data_h

#include "matrix_sparse.h"

typedef struct diffusion_data
{
  scalar_field initial;
  scalar_field source;
  boolean_domain boundary_dirichlet;
  scalar_field g_dirichlet;
  boolean_domain boundary_neumann;
  scalar_field g_neumann;
} diffusion_data;

#endif /* _diffusion_data_h */
