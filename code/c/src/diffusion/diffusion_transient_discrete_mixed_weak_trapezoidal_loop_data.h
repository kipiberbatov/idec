#ifndef _diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_h
#define _diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_h

#include "diffusion_transient_discrete_mixed_weak.h"
#include "mesh_qc.h"

typedef struct diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data
{
  jagged1 * boundary_neumann_dm1_bar;
  matrix_sparse * b;
  matrix_sparse * negative_b_bar_transpose; /* - b_bar^T */
  matrix_sparse * l_tau; /* cholesky_decomposition(n_tau) */
  double * c_tau; /* (2 / tau) * c */
  double * v_tau; /* b_bar a_bar^{-1} g_bar + tilde{f} */
  double * p_bar; /* a_bar^{-1} g_bar */
  const diffusion_transient_discrete_mixed_weak * data;
} diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data;

diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data *
diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_initialize(
  const mesh_qc * m,
  const matrix_sparse * m_cbd_dm1,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const diffusion_transient_discrete_mixed_weak * data,
  double time_step);

void diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_free(
  diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data * input);

#endif /* _diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_h */
