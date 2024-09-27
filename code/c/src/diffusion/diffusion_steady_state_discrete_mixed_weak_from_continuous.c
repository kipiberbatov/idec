#include <errno.h>
#include <stdlib.h>

#include "boundary_scalar_field_discretize.h"
#include "boundary_pseudoscalar_field_discretize.h"
#include "color.h"
#include "de_rham.h"
#include "diffusion_steady_state_continuous.h"
#include "diffusion_steady_state_discrete_mixed_weak.h"
#include "double.h"
#include "unsigned_approximation.h"

diffusion_steady_state_discrete_mixed_weak *
diffusion_steady_state_discrete_mixed_weak_from_continuous(
  const mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const diffusion_steady_state_continuous * data_continuous)
{
  int d;
  diffusion_steady_state_discrete_mixed_weak * data_discrete;

  d = m->dim;

  data_discrete = (diffusion_steady_state_discrete_mixed_weak *) malloc(
    sizeof(diffusion_steady_state_discrete_mixed_weak));
  if (errno)
    goto end;

  data_discrete->pi_dm1 = (double *) malloc(sizeof(double) * m->cn[d - 1]);
  if (errno)
    goto data_discrete_free;
  unsigned_approximation_of_scalar_field_on_hyperfaces(
    data_discrete->pi_dm1, m, data_continuous->pi_1);

  data_discrete->source_d = (double *) malloc(sizeof(double) * m->cn[d]);
  if (errno)
    goto data_discrete_pi_dm1_free;
  de_rham_nonzero(
    data_discrete->source_d, m, m->dim, m_vol_d, data_continuous->source);
  fprintf(stderr, "\n%ssource_%d:%s\n", color_red, d - 1, color_none);
  double_array_file_print(stderr, m->cn[d], data_discrete->source_d, "--curly");
  fputc('\n', stderr);

  data_discrete->boundary_dirichlet_dm1
  = mesh_boundary_hyperfaces_from_constraint(
    m, data_continuous->boundary_dirichlet);
  if (errno)
    goto data_discrete_source_d_free;
  fprintf(stderr,
    "\n%sboundary_dirichlet_%d:%s\n", color_red, d - 1, color_none);
  jagged1_file_print(stderr, data_discrete->boundary_dirichlet_dm1, "--curly");

  data_discrete->boundary_dirichlet_0
  = mesh_boundary_nodes_from_constraint(m, data_continuous->boundary_dirichlet);
  if (errno)
    goto data_discrete_boundary_dirichlet_dm1_free;
  fprintf(stderr, "\n%sboundary_dirichlet_0:%s\n", color_red, color_none);
  jagged1_file_print(stderr, data_discrete->boundary_dirichlet_0, "--curly");

  data_discrete->g_dirichlet_0 = (double *) malloc(
    sizeof(double) * data_discrete->boundary_dirichlet_0->a0);
  if (errno)
    goto data_discrete_boundary_dirichlet_0_free;
  boundary_scalar_field_discretize(
    data_discrete->g_dirichlet_0,
    m->dim_embedded,
    m->coord,
    data_discrete->boundary_dirichlet_0,
    data_continuous->g_dirichlet);
  fprintf(stderr, "\n%sg_dirichlet^0:%s\n", color_red, color_none);
  double_array_file_print(stderr,
    data_discrete->boundary_dirichlet_0->a0,
    data_discrete->g_dirichlet_0,
    "--curly");
  fputc('\n', stderr);

  data_discrete->boundary_neumann_dm1
  = mesh_boundary_hyperfaces_from_constraint(
    m, data_continuous->boundary_neumann);
  if (errno)
    goto data_discrete_g_dirichlet_0_free;
  fprintf(stderr,
    "\n%sboundary_neumann_%d:%s\n", color_red, d - 1, color_none);
  jagged1_file_print(stderr, data_discrete->boundary_neumann_dm1, "--curly");

  data_discrete->g_neumann_dm1
  = (double *) malloc(sizeof(double) * data_discrete->boundary_neumann_dm1->a0);
  if (errno)
    goto data_discrete_boundary_neumann_dm1_free;
  boundary_pseudoscalar_field_discretize(
    data_discrete->g_neumann_dm1,
    m,
    m_vol_dm1,
    data_discrete->boundary_neumann_dm1,
    data_continuous->g_neumann);
  fprintf(stderr, "\n%sg_neumann^%d:%s\n", color_red, d - 1, color_none);
  double_array_file_print(stderr,
    data_discrete->boundary_neumann_dm1->a0,
    data_discrete->g_neumann_dm1,
    "--curly");
  fputc('\n', stderr);

  return data_discrete;

  /* cleaning if an error occurs */
  free(data_discrete->g_neumann_dm1);
data_discrete_boundary_neumann_dm1_free:
  jagged1_free(data_discrete->boundary_neumann_dm1);
data_discrete_g_dirichlet_0_free:
  free(data_discrete->g_dirichlet_0);
data_discrete_boundary_dirichlet_0_free:
  jagged1_free(data_discrete->boundary_dirichlet_0);
data_discrete_boundary_dirichlet_dm1_free:
  jagged1_free(data_discrete->boundary_dirichlet_dm1);
data_discrete_source_d_free:
  free(data_discrete->source_d);
data_discrete_pi_dm1_free:
  free(data_discrete->pi_dm1);
data_discrete_free:
  free(data_discrete);
end:
  return NULL;
}
