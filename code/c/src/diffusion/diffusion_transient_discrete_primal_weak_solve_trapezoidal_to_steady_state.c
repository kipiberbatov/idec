#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "diffusion_transient_discrete_primal_weak_solve_trapezoidal_next.h"
#include "mesh_qc.h"

/*
$result$ stores the final solution $y_0, ..., y_{number_of_steps}$.
$y_0$ is the initial condition.
For $i = 0, ..., number_of_steps$:
  $rhs_final$ is updated using $y_i$ and used to find $y_{i + 1}$.
*/

static void loop(
  double_array_sequence_dynamic * result,
  double * rhs_final,
  const matrix_sparse * lhs,
  const matrix_sparse * rhs,
  const double * free_part,
  const diffusion_transient_discrete_primal_weak * data,
  double tolerance)
{
  int i, n;
  double relative_norm;

  i = 0;
  n = rhs->rows;

  do
  {
    if (i == result->capacity - 1)
    {
      double_array_sequence_dynamic_resize(result);
      if (errno)
      {
        fprintf(stderr,
          "%s:%d: loop: cannot resize in iteration %d\n",
          __FILE__, __LINE__, i);
        return;
      }
    }

    result->values[i + 1] = (double *) malloc(sizeof(double) * n);
    if (errno)
    {
      fputs("Runtime error stack trace:\n", stderr);
      fprintf(stderr,
        "%s:%d: loop: cannot allocate memory for result->values[%d]\n",
        __FILE__, __LINE__, i + 1);
      return;
    }

    diffusion_transient_discrete_primal_weak_solve_trapezoidal_next(
      result->values[i + 1], rhs_final, result->values[i], lhs, rhs, free_part,
      data);
    if (errno)
    {
      fprintf(stderr,
        "%s:%d: loop: cannot calculate result->values[%d]\n",
        __FILE__, __LINE__, i + 1);
      return;
    }

    relative_norm = double_array_pair_norm_uniform_relative(
      n, result->values[i], result->values[i + 1]);
    ++result->length;
    ++i;
  }
  while (relative_norm >= tolerance);
}

double_array_sequence_dynamic *
diffusion_transient_discrete_primal_weak_solve_trapezoidal_to_steady_state(
  const mesh * m,
  const double * m_inner_0,
  const double * m_inner_1,
  const diffusion_transient_discrete_primal_weak * data,
  double time_step,
  double tolerance)
{
  int m_cn_0;
  double * b, * f, * free_part, * g, * rhs_final;
  double_array_sequence_dynamic * result;
  matrix_sparse * a, * lhs, * rhs;

  result = NULL;
  m_cn_0 = m->cn[0];

  a = mesh_qc_matrix_sparse_from_inner_of_delta_basis_0_cup_pi_1_delta_basis_0(
    m, m_inner_1, data->pi_1);
  if (a == NULL)
  {
    fprintf(stderr, "%s:%d: cannot calculate matrix a\n", __FILE__, __LINE__);
    goto end;
  }

  b = (double *) malloc(sizeof(double) * m_cn_0);
  if (b == NULL)
  {
    fputs("Runtime error stack trace:\n", stderr);
    fprintf(stderr,
      "%s:%d: cannot allocate memory for diagonal matrix b\n",
      __FILE__, __LINE__);
    goto a_free;
  }
  mesh_qc_matrix_diagonal_from_inner_of_basis_0_cup_pi_0_basis_0(
    b, m, m_inner_0, data->pi_0);

  lhs = a;
  rhs = matrix_sparse_copy(a);
  if (rhs == NULL)
  {
    fprintf(stderr, "%s:%d: cannot copy sparse matrix a\n", __FILE__, __LINE__);
    goto b_free;
  }

  /* $lhs = (time_step / 2) * a + b$ */
  matrix_sparse_scalar_multiply(lhs, time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(lhs, b);

  /* $rhs = - (time_step / 2) * a + b$ */
  matrix_sparse_scalar_multiply(rhs, - time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(rhs, b);

  f = (double *) malloc(sizeof(double) * m_cn_0);
  if (f == NULL)
  {
    fputs("Runtime error stack trace:\n", stderr);
    fprintf(stderr,
      "%s:%d: cannot allocate memory for vector f\n", __FILE__, __LINE__);
    goto rhs_free;
  }
  mesh_qc_vector_from_integral_of_basis_0_cup_d_cochain(f, m, data->source);

  g = (double *) malloc(sizeof(double) * data->boundary_neumann->a0);
  if (g == NULL)
  {
    fputs("Runtime error stack trace:\n", stderr);
    fprintf(stderr,
      "%s:%d: cannot allocate memory for vector g\n", __FILE__, __LINE__);
    goto f_free;
  }
  mesh_qc_vector_from_boundary_integral_of_basis_0_cup_dm1_cochain(
    g, m, data->boundary_neumann, data->g_neumann);

  double_array_add_sparse_to(f, data->boundary_neumann, g);

  /* $free_part = time_step * rhs_vector$ */
  free_part = f;
  double_array_multiply_with(free_part, m_cn_0, time_step);

  /* apply Dirichlet boundary condition on matrix $lhs$ */
  matrix_sparse_set_identity_rows(lhs, data->boundary_dirichlet);

  /* allocate memory for $rhs_final$ -> uppdated at each step of the loop */
  rhs_final = (double *) malloc(sizeof(double) * m_cn_0);
  if (errno)
  {
    fputs("Runtime error stack trace:\n", stderr);
    fprintf(stderr,
      "%s:%d: cannot allocate memory for rhs_final\n", __FILE__, __LINE__);
    goto g_free;
  }

  /* allocate memory for $result$ -> $m_cn_0$ elements filled at each step */
  result = double_array_sequence_dynamic_initialize(m_cn_0);
  if (errno)
  {
    fputs("Runtime error stack trace:\n", stderr);
    fprintf(stderr,
      "%s:%d: cannot allocate memory for result\n", __FILE__, __LINE__);
    goto rhs_final_free;
  }

  /* the initial $n$ elements of $result$ are the initial condition */
  memcpy(result->values[0], data->initial, sizeof(double) * m_cn_0);

  loop(result, rhs_final, lhs, rhs, free_part, data, tolerance);
  if (errno)
  {
    fprintf(stderr, "%s:%d: cannot execute loop\n", __FILE__, __LINE__);
    free(result);
    goto rhs_final_free;
  }

rhs_final_free:
  free(rhs_final);
g_free:
  free(g);
f_free:
  free(f);
rhs_free:
  matrix_sparse_free(rhs);
b_free:
  free(b);
a_free:
  matrix_sparse_free(a);
end:
  return result;
}
