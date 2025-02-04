#ifndef _diffusion_transient_discrete_primal_strong_h
#define _diffusion_transient_discrete_primal_strong_h

#include <stdio.h>

struct diffusion_transient_continuous;
struct double_array_sequence_dynamic;
struct jagged1;
struct matrix_sparse;
struct mesh;

struct diffusion_transient_discrete_primal_strong
{
  int number_of_cells_0;
  int number_of_cells_1;
  double  * pi_0;
  double  * kappa_1;
  double  * initial;
  double  * source;
  struct jagged1 * boundary_dirichlet;
  double  * g_dirichlet;
  struct jagged1 * boundary_neumann;
  double  * g_neumann;
};

void diffusion_transient_discrete_primal_strong_free(
  struct diffusion_transient_discrete_primal_strong * data);

struct diffusion_transient_discrete_primal_strong *
diffusion_transient_discrete_primal_strong_from_continuous(
  const struct mesh * m,
  const struct diffusion_transient_continuous * data_continuous);

double * diffusion_transient_discrete_primal_strong_solve_trapezoidal(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_0,
  const struct matrix_sparse * m_cbd_star_1,
  const struct diffusion_transient_discrete_primal_strong * data,
  double time_step,
  int number_of_steps);

struct double_array_sequence_dynamic *
diffusion_transient_discrete_primal_strong_solve_trapezoidal_to_steady_state(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_0,
  const struct matrix_sparse * m_cbd_star_1,
  const struct diffusion_transient_discrete_primal_strong * data,
  double time_step,
  double tolerance);

void diffusion_transient_discrete_primal_strong_file_print_raw(
  FILE * out,
  const struct diffusion_transient_discrete_primal_strong * data);

struct diffusion_transient_discrete_primal_strong *
diffusion_transient_discrete_primal_strong_file_scan_raw(FILE * in);

#endif /* _diffusion_transient_discrete_primal_strong_h */
