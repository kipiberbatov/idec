#ifndef _diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_h
#define _diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_h

#include "diffusion_transient_discrete_primal_weak.h"
#include "mesh_qc.h"

typedef struct diffusion_transient_discrete_primal_weak_trapezoidal_loop_data
{
  matrix_sparse * lhs;
  matrix_sparse * rhs;
  double * free_part;
  const diffusion_transient_discrete_primal_weak * data;
} diffusion_transient_discrete_primal_weak_trapezoidal_loop_data;

diffusion_transient_discrete_primal_weak_trapezoidal_loop_data *
diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_initialize(
  const mesh_qc * m,
  const double * m_inner_0,
  const double * m_inner_1,
  const diffusion_transient_discrete_primal_weak * data,
  double time_step);

void diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_free(
  diffusion_transient_discrete_primal_weak_trapezoidal_loop_data * input);

#endif /* _diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_h */
