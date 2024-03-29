#include <errno.h>
#include <stdlib.h>

#include "diffusion_continuous.h"
#include "diffusion_discrete.h"
#include "spacetime_pde.h"

static void vector_initialize(double * x, const mesh * m, scalar_field f)
{
  int i, m_cn_0, m_dim_embedded;
  double * m_coord;
  
  m_cn_0 = m->cn[0];
  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;
  
  for (i = 0; i < m_cn_0; ++i)
    x[i] = f(m_coord + m_dim_embedded * i);
}

diffusion_discrete * diffusion_continuous_discretize(
  const mesh * m,
  const diffusion_continuous * data_continuous)
{
  diffusion_discrete * data_discrete;
  data_discrete = (diffusion_discrete *) malloc(sizeof(diffusion_discrete));
  /* NULL pointer checking */
  
  data_discrete->pi_0 = (double *) malloc(sizeof(double) * m->cn[0]);
  /* NULL pointer checking */
  vector_initialize(data_discrete->pi_0, m, data_continuous->pi_0);
  
  // data_discrete->pi_1 = (double *) malloc(sizeof(double) * m->cn[0]);
  // /* NULL pointer checking */
  // vector_initialize(data_discrete->pi_1, m, data_continuous->pi_1);
  
  data_discrete->initial = (double *) malloc(sizeof(double) * m->cn[0]);
  /* NULL pointer checking */
  vector_initialize(data_discrete->initial, m, data_continuous->initial);
  
  data_discrete->source = (double *) malloc(sizeof(double) * m->cn[0]);
  /* NULL pointer checking */
  vector_initialize(data_discrete->source, m, data_continuous->source);
  
  data_discrete->boundary_dirichlet
  = mesh_boundary_nodes_from_constraint(m, data_continuous->boundary_dirichlet);
  /* NULL pointer checking */
  
  data_discrete->g_dirichlet
  = (double *) malloc(sizeof(double) * (data_discrete->boundary_dirichlet)->a0);
  /* NULL pointer checking */
  spacetime_pde_boundary_vector(
    data_discrete->g_dirichlet,
    m->dim_embedded,
    m->coord,
    data_discrete->boundary_dirichlet,
    data_continuous->g_dirichlet);
  
  data_discrete->boundary_neumann
  = mesh_boundary_nodes_from_constraint(m, data_continuous->boundary_neumann);
  /* NULL pointer checking */
  
  data_discrete->g_neumann
  = (double *) malloc(sizeof(double) * (data_discrete->boundary_neumann)->a0);
  /* NULL pointer checking */
  spacetime_pde_boundary_vector(
    data_discrete->g_neumann,
    m->dim_embedded,
    m->coord,
    data_discrete->boundary_neumann,
    data_continuous->g_neumann);
  
  return data_discrete;
}
