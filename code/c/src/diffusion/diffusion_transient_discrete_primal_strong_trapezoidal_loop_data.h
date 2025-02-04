#ifndef _diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_h
#define _diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_h

struct diffusion_transient_discrete_primal_strong;
struct matrix_sparse;
struct mesh;

struct diffusion_transient_discrete_primal_strong_trapezoidal_loop_data
{
  struct matrix_sparse * lhs;
  struct matrix_sparse * rhs;
  double * free_part;
  const struct diffusion_transient_discrete_primal_strong * data;
};

struct diffusion_transient_discrete_primal_strong_trapezoidal_loop_data *
diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_initialize(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_0,
  const struct matrix_sparse * m_cbd_star_1,
  const struct diffusion_transient_discrete_primal_strong * data,
  double time_step);

void diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_free(
  struct diffusion_transient_discrete_primal_strong_trapezoidal_loop_data *
    input);

#endif /* _diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_h */
