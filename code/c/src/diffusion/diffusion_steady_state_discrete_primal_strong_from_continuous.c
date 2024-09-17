#include <errno.h>
#include <stdlib.h>

#include "boundary_scalar_field_discretize.h"
#include "de_rham.h"
#include "diffusion_steady_state_continuous.h"
#include "diffusion_steady_state_discrete_primal_strong.h"
#include "unsigned_approximation.h"

diffusion_steady_state_discrete_primal_strong *
diffusion_steady_state_discrete_primal_strong_from_continuous(
  const mesh * m,
  const diffusion_steady_state_continuous * data_continuous)
{
  diffusion_steady_state_discrete_primal_strong * data_discrete;

  data_discrete = (diffusion_steady_state_discrete_primal_strong *)
    malloc(sizeof(diffusion_steady_state_discrete_primal_strong));
  if (errno)
    goto end;

  data_discrete->pi_0 = (double *) malloc(sizeof(double) * m->cn[0]);
  if (errno)
    goto data_discrete_free;
  de_rham_0(data_discrete->pi_0, m, data_continuous->pi_0);

  data_discrete->pi_1 = (double *) malloc(sizeof(double) * m->cn[1]);
  if (errno)
    goto data_discrete_pi_0_free;
  unsigned_approximation_of_scalar_field_on_1_cells(
    data_discrete->pi_1, m, data_continuous->pi_1);

  data_discrete->source = (double *) malloc(sizeof(double) * m->cn[0]);
  if (errno)
    goto data_discrete_pi_1_free;
  de_rham_0(data_discrete->source, m, data_continuous->source);

  data_discrete->boundary_dirichlet
  = mesh_boundary_nodes_from_constraint(m, data_continuous->boundary_dirichlet);
  if (errno)
    goto data_discrete_source_free;

  data_discrete->g_dirichlet
  = (double *) malloc(sizeof(double) * (data_discrete->boundary_dirichlet->a0));
  if (errno)
    goto data_discrete_boundary_dirichlet_free;
  boundary_scalar_field_discretize(
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
  boundary_scalar_field_discretize(
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
data_discrete_pi_1_free:
  free(data_discrete->pi_1);
data_discrete_pi_0_free:
  free(data_discrete->pi_0);
data_discrete_free:
  free(data_discrete);
end:
  return NULL;
}
