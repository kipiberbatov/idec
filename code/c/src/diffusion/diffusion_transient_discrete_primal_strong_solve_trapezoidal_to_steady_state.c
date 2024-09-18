#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "diffusion_discrete_set_neumann_rows.h"
#include "diffusion_transient_discrete_primal_strong.h"
#include "diffusion_transient_discrete_primal_strong_solve_trapezoidal_next.h"

/*
$result$ stores the final solution $y_0, ..., y_{number_of_steps}$.
$y_0$ is the initial condition.
Until error is less than $tolerance$:
  $rhs_final$ is updated using $y_i$ and used to find $y_{i + 1}$.
*/

static void loop(
  double_array_sequence_dynamic * result,
  double * rhs_final,
  const matrix_sparse * lhs,
  const matrix_sparse * rhs,
  const double * free_part,
  const diffusion_transient_discrete_primal_strong * data,
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

    diffusion_transient_discrete_primal_strong_solve_trapezoidal_next(
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

#define FUNCTION "diffusion_transient_discrete_primal_strong_solve_trapezoidal_to_steady_state"
#define START_ERROR_MESSAGE fprintf(stderr,"  %s: ", FUNCTION)

double_array_sequence_dynamic *
diffusion_transient_discrete_primal_strong_solve_trapezoidal_to_steady_state(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_transient_discrete_primal_strong * data,
  double time_step,
  double tolerance)
{
  int n;
  double * free_part, * rhs_final;
  double * a;
  matrix_sparse * b;
  matrix_sparse * m_cbd_star_1_material;
  matrix_sparse * lhs, * rhs;
  double_array_sequence_dynamic * result = NULL;

  n = m->cn[0];
  a = data->pi_0;

  m_cbd_star_1_material = matrix_sparse_copy(m_cbd_star_1);
  if (errno)
  {
    START_ERROR_MESSAGE;
    fputs("cannot initialize m_cbd_star_1_material\n", stderr);
    goto end;
  }
  matrix_sparse_multiply_with_diagonal_matrix(
    m_cbd_star_1_material, data->pi_1);
  b = matrix_sparse_product(m_cbd_star_1_material, m_cbd_0);
  if (errno)
  {
    START_ERROR_MESSAGE;
    fputs("cannot calculate matrix b\n", stderr);
    goto m_cbd_star_1_material_free;
  }

  /* $lhs =  a + (time_step / 2) * b$ */
  lhs = matrix_sparse_copy(b);
  if (errno)
  {
    START_ERROR_MESSAGE;
    fputs("cannot calculate matrix lhs\n", stderr);
    goto b_free;
  }
  matrix_sparse_scalar_multiply(lhs, time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(lhs, a);

  /* $rhs =  a - (time_step / 2) * b$ */
  rhs = matrix_sparse_copy(b);
  if (errno)
  {
    START_ERROR_MESSAGE;
    fputs("cannot calculate matrix lhs\n", stderr);
    goto lhs_free;
  }
  matrix_sparse_scalar_multiply(rhs, - time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(rhs, a);

  /* $free_part = time_step * data->source$ */
  free_part = (double *) malloc(sizeof(double) * n);
  if (errno)
  {
    fputs("Runtime error stack trace:\n", stderr);
    START_ERROR_MESSAGE;
    fputs("cannot allocate memory for free_part\n", stderr);
    goto rhs_free;
  }
  memcpy(free_part, data->source, sizeof(double) * n);
  double_array_multiply_with(free_part, n, time_step);

  /* apply Dirichlet boundary condition on matrix $lhs$ */
  matrix_sparse_set_identity_rows(lhs, data->boundary_dirichlet);

  /* apply Neumann boundary condition on matrix $lhs$ */
  diffusion_discrete_set_neumann_rows(
    lhs, m, data->boundary_neumann, data->pi_1);
  if (errno)
  {
    START_ERROR_MESSAGE;
    fputs("cannot apply Neumann boundary condition\n", stderr);
    goto free_part_free;
  }

  /* allocate memory for $rhs_final$ -> uppdated at each step of the loop */
  rhs_final = (double *) malloc(sizeof(double) * n);
  if (errno)
  {
    fputs("Runtime error stack trace:\n", stderr);
    START_ERROR_MESSAGE;
    fputs("cannot allocate memory for rhs_final\n", stderr);
    goto free_part_free;
  }

  result = double_array_sequence_dynamic_initialize(n);
  if (errno)
  {
    START_ERROR_MESSAGE;
    fputs("cannot initialize result\n", stderr);
    goto rhs_final_free;
  }

  /* the initial $result->values[0]$ is the initial condition */
  memcpy(result->values[0], data->initial, sizeof(double) * n);

  /* The following elements of $result$ (each of size $n$)
   * are calculated iteratively with $rhs_final$ updating at each step
   * (until error is than tolerance).
   */
  loop(result, rhs_final, lhs, rhs, free_part, data, tolerance);
  if (errno)
  {
    START_ERROR_MESSAGE;
    fputs("error in loop calculating final result\n", stderr);
    double_array_sequence_dynamic_free(result);
    goto rhs_final_free;
  }

rhs_final_free:
  free(rhs_final);
free_part_free:
  free(free_part);
rhs_free:
  matrix_sparse_free(rhs);
lhs_free:
  matrix_sparse_free(lhs);
b_free:
  matrix_sparse_free(b);
m_cbd_star_1_material_free:
  matrix_sparse_free(m_cbd_star_1_material);
end:
  return result;
}
