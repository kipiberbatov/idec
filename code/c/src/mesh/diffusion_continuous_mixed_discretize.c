#include <errno.h>
#include <stdlib.h>

#include "boundary_scalar_field_discretize.h"
#include "de_rham.h"
#include "diffusion_continuous.h"
#include "diffusion_discrete.h"
#include "unsigned_approximation.h"

typedef struct diffusion_discrete_mixed
{
  double  * pi_0;
  double  * pi_2;
  double  * initial;
  double  * source;
  jagged1 * boundary_dirichlet;
  double  * g_dirichlet;
  jagged1 * boundary_neumann;
  double  * g_neumann;
} diffusion_discrete_mixed;

static void unsigned_approximation_of_scalar_field_on_2_cells(
  double * x,
  const mesh * m,
  double (*f)(const double *))
{
  return;
}

void boundary_pseudoscalar_field_discretize(
  double * result,
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * boundary_nodes,
  double (*g)(const double *));

diffusion_discrete_mixed * diffusion_continuous_mixed_discretize(
  const mesh * m,
  const diffusion_continuous * data_continuous)
{
  diffusion_discrete_mixed * data_discrete;

  data_discrete
  = (diffusion_discrete_mixed *) malloc(sizeof(diffusion_discrete_mixed));
  if (errno)
    goto end;

  data_discrete->pi_0 = (double *) malloc(sizeof(double) * m->cn[0]);
  if (errno)
    goto data_discrete_free;
  unsigned_approximation_of_scalar_field_on_2_cells(
    data_discrete->pi_0, m, data_continuous->pi_0);

  data_discrete->pi_2 = (double *) malloc(sizeof(double) * m->cn[2]);
  if (errno)
    goto data_discrete_pi_0_free;
  unsigned_approximation_of_scalar_field_on_2_cells(
    data_discrete->pi_2, m, data_continuous->pi_1);

  data_discrete->initial = (double *) malloc(sizeof(double) * m->cn[0]);
  if (errno)
    goto data_discrete_pi_2_free;
  de_rham_0(data_discrete->initial, m, data_continuous->initial);

  data_discrete->source = (double *) malloc(sizeof(double) * m->cn[0]);
  if (errno)
    goto data_discrete_initial_free;
  de_rham_3(data_discrete->source, m, data_continuous->source);

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

  data_discrete->boundary_neumann = mesh_boundary_hyperfaces_from_constraint(
    m, data_continuous->boundary_neumann);
  if (errno)
    goto data_discrete_g_dirichlet_free;

  data_discrete->g_neumann
  = (double *) malloc(sizeof(double) * (data_discrete->boundary_neumann->a0));
  if (errno)
    goto data_discrete_boundary_neumann_free;
  boundary_pseudoscalar_field_discretize(
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
data_discrete_pi_2_free:
  free(data_discrete->pi_2);
data_discrete_pi_0_free:
  free(data_discrete->pi_0);
data_discrete_free:
  free(data_discrete);
end:
  return NULL;
}
