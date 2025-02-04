#ifndef _diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_h
#define _diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_h

struct diffusion_transient_discrete_primal_weak;
struct mesh;
struct matrix_sparse;

struct diffusion_transient_discrete_primal_weak_trapezoidal_loop_data
{
  struct matrix_sparse * lhs;
  struct matrix_sparse * rhs;
  double * free_part;
  const struct diffusion_transient_discrete_primal_weak * data;
};

struct diffusion_transient_discrete_primal_weak_trapezoidal_loop_data *
diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_initialize(
  const struct mesh * m,
  const double * m_inner_0,
  const double * m_inner_1,
  const struct diffusion_transient_discrete_primal_weak * data,
  double time_step);

void diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_free(
  struct diffusion_transient_discrete_primal_weak_trapezoidal_loop_data *
    input);

#endif /* _diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_h */
