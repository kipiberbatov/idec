#ifndef _diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_h
#define _diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_h

#include "diffusion_transient_discrete_primal_strong.h"
#include "mesh.h"

typedef struct diffusion_transient_discrete_primal_strong_trapezoidal_loop_data
{
  matrix_sparse * lhs;
  matrix_sparse * rhs;
  double * free_part;
  const diffusion_transient_discrete_primal_strong * data;
} diffusion_transient_discrete_primal_strong_trapezoidal_loop_data;

diffusion_transient_discrete_primal_strong_trapezoidal_loop_data *
diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_initialize(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_transient_discrete_primal_strong * data,
  double time_step);

void diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_free(
  diffusion_transient_discrete_primal_strong_trapezoidal_loop_data * input);

#endif /* _diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_h */
