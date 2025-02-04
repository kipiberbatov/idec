#ifndef _diffusion_steady_state_discrete_primal_strong_h
#define _diffusion_steady_state_discrete_primal_strong_h

#include <stdio.h>

struct diffusion_steady_state_continuous;
struct jagged1;
struct matrix_sparse;
struct mesh;

struct diffusion_steady_state_discrete_primal_strong
{
  int number_of_cells_1;
  int number_of_cells_0;
  double * kappa_1;
  double * source;
  struct jagged1 * boundary_dirichlet;
  double * g_dirichlet;
  struct jagged1 * boundary_neumann;
  double * g_neumann;
};

void diffusion_steady_state_discrete_primal_strong_free(
  struct diffusion_steady_state_discrete_primal_strong * data);

struct diffusion_steady_state_discrete_primal_strong *
diffusion_steady_state_discrete_primal_strong_from_continuous(
  const struct mesh * m,
  const struct diffusion_steady_state_continuous * data_continuous);

double * diffusion_steady_state_discrete_primal_strong_solve(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_0,
  const struct matrix_sparse * m_cbd_star_1,
  const struct diffusion_steady_state_discrete_primal_strong * data);

void diffusion_steady_state_discrete_primal_strong_file_print_raw(
  FILE * out,
  const struct diffusion_steady_state_discrete_primal_strong * data);

struct diffusion_steady_state_discrete_primal_strong *
diffusion_steady_state_discrete_primal_strong_file_scan_raw(FILE * in);

#endif /* _diffusion_steady_state_discrete_primal_strong_h */
