#ifndef _diffusion_transient_continuous_h
#define _diffusion_transient_continuous_h

#include "mesh.h"

/* typedef double scalar_field(const double *); */
typedef int region_implicit(const double *);

typedef struct diffusion_transient_continuous
{
  scalar_field pi_0;
  scalar_field pi_1;
  scalar_field initial;
  scalar_field source;
  region_implicit * boundary_dirichlet;
  scalar_field g_dirichlet;
  region_implicit * boundary_neumann;
  scalar_field g_neumann;
} diffusion_transient_continuous;

double * diffusion_transient_continuous_primal_weak_solve(
  const mesh * m,
  const double * m_vol_dm1,
  const double * m_inner_1,
  const diffusion_transient_continuous * data_continuous);

#endif /* _diffusion_transient_continuous_h */
