#include <errno.h>
#include <stdlib.h>

#include "diffusion_continuous.h"
#include "diffusion_discrete.h"

static void diffusion_continuous_boundary_vector(
  double * result,
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * boundary_nodes,
  scalar_field g)
{
  int j, j_loc, boundary_nodes_a0;
  int * boundary_nodes_a1;
  
  boundary_nodes_a0 = boundary_nodes->a0;
  boundary_nodes_a1 = boundary_nodes->a1;
  
  for (j_loc = 0; j_loc < boundary_nodes_a0; ++j_loc)
  {
    j = boundary_nodes_a1[j_loc];
    result[j_loc] = g(m_coord + m_dim_embedded * j);
  }
}

static void
zero_cochain_from_scalar_field(double * x, const mesh * m, scalar_field f)
{
  int i, m_cn_0, m_dim_embedded;
  double * m_coord;
  
  m_cn_0 = m->cn[0];
  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;
  
  for (i = 0; i < m_cn_0; ++i)
    x[i] = f(m_coord + m_dim_embedded * i);
}

static void
one_cochain_from_scalar_field(double * x, const mesh * m, scalar_field f)
{
  int i, i0, i1, m_cn_1, m_dim_embedded;
  double x0, x1;
  double * m_coord;
  jagged1 m_cf_1_0_i;
  jagged2 m_cf_1_0;
  
  m_cn_1 = m->cn[1];
  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;
  mesh_cf_part2(&m_cf_1_0, m, 1, 0);
  
  for (i = 0; i < m_cn_1; ++i)
  {
    jagged2_part1(&m_cf_1_0_i, &m_cf_1_0, i);
    i0 = m_cf_1_0_i.a1[0];
    i1 = m_cf_1_0_i.a1[1];
    x0 = f(m_coord + m_dim_embedded * i0);
    x1 = f(m_coord + m_dim_embedded * i1);
    x[i] = (x0 + x1) / 2;
  }
}

diffusion_discrete * diffusion_continuous_discretize(
  const mesh * m,
  const diffusion_continuous * data_continuous)
{
  diffusion_discrete * data_discrete;
  
  data_discrete = (diffusion_discrete *) malloc(sizeof(diffusion_discrete));
  if (errno)
    goto end;
  
  data_discrete->pi_0 = (double *) malloc(sizeof(double) * m->cn[0]);
  if (errno)
    goto data_discrete_free;
  zero_cochain_from_scalar_field(data_discrete->pi_0, m, data_continuous->pi_0);
  
  data_discrete->pi_1 = (double *) malloc(sizeof(double) * m->cn[1]);
  if (errno)
    goto data_discrete_pi_0_free;
  one_cochain_from_scalar_field(data_discrete->pi_1, m, data_continuous->pi_1);
  
  data_discrete->initial = (double *) malloc(sizeof(double) * m->cn[0]);
  if (errno)
    goto data_discrete_pi_1_free;
  zero_cochain_from_scalar_field(
    data_discrete->initial, m, data_continuous->initial);
  
  data_discrete->source = (double *) malloc(sizeof(double) * m->cn[0]);
  if (errno)
    goto data_discrete_initial_free;
  zero_cochain_from_scalar_field(
    data_discrete->source, m, data_continuous->source);
  
  data_discrete->boundary_dirichlet
  = mesh_boundary_nodes_from_constraint(m, data_continuous->boundary_dirichlet);
  if (errno)
    goto data_discrete_source_free;
  
  data_discrete->g_dirichlet
  = (double *) malloc(sizeof(double) * (data_discrete->boundary_dirichlet->a0));
  if (errno)
    goto data_discrete_boundary_dirichlet_free;
  diffusion_continuous_boundary_vector(
    data_discrete->g_dirichlet,
    m->dim_embedded,
    m->coord,
    data_discrete->boundary_dirichlet,
    data_continuous->g_dirichlet);
  
  data_discrete->boundary_neumann
  = mesh_boundary_nodes_from_constraint(m, data_continuous->boundary_neumann);
  if (errno)
    goto data_discrete_g_dirichlet_free;
  
  data_discrete->g_neumann
  = (double *) malloc(sizeof(double) * (data_discrete->boundary_neumann->a0));
  if (errno)
    goto data_discrete_boundary_neumann_free;
  diffusion_continuous_boundary_vector(
    data_discrete->g_neumann,
    m->dim_embedded,
    m->coord,
    data_discrete->boundary_neumann,
    data_continuous->g_neumann);
  
  return data_discrete;

  /* cleaning if an error occurs */
  free(data_discrete->g_neumann);
data_discrete_boundary_neumann_free:
  jagged1_free(data_discrete->boundary_neumann);
data_discrete_g_dirichlet_free:
  free(data_discrete->g_dirichlet);
data_discrete_boundary_dirichlet_free:
  jagged1_free(data_discrete->boundary_dirichlet);
data_discrete_source_free:
  free(data_discrete->source);
data_discrete_initial_free:
  free(data_discrete->initial);
data_discrete_pi_1_free:
  free(data_discrete->pi_1);
data_discrete_pi_0_free:
  free(data_discrete->pi_0);
data_discrete_free:
  free(data_discrete);
end:
  return NULL;
}
