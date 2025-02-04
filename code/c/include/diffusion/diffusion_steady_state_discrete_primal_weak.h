#ifndef _diffusion_steady_state_discrete_primal_weak_h
#define _diffusion_steady_state_discrete_primal_weak_h

#include <stdio.h>

struct diffusion_steady_state_continuous;
struct jagged1;
struct matrix_sparse;
struct mesh;

struct diffusion_steady_state_discrete_primal_weak
{
  int number_of_cells_1;
  int number_of_cells_d;
  double * kappa_1;
  double * source;
  struct jagged1 * boundary_dirichlet;
  double * g_dirichlet;
  struct jagged1 * boundary_neumann;
  double * g_neumann;
};

struct diffusion_steady_state_discrete_primal_weak *
diffusion_steady_state_discrete_primal_weak_from_continuous(
  const struct mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const struct diffusion_steady_state_continuous * data_continuous);

void diffusion_steady_state_discrete_primal_weak_free(
  struct diffusion_steady_state_discrete_primal_weak * data);

double * diffusion_steady_state_discrete_primal_weak_solve(
  const struct mesh * m,
  const double * m_inner_1,
  const struct diffusion_steady_state_discrete_primal_weak * data);

void diffusion_steady_state_discrete_primal_weak_file_print_raw(
  FILE * out,
  const struct diffusion_steady_state_discrete_primal_weak * data);

struct diffusion_steady_state_discrete_primal_weak *
diffusion_steady_state_discrete_primal_weak_file_scan_raw(FILE * in);

#endif /* _diffusion_steady_state_discrete_primal_weak_h */
