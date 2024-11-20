#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "diffusion_discrete_set_neumann_rows.h"
#include "diffusion_transient_discrete_primal_strong_solve_trapezoidal_next.h"

/*
$result$ stores the final solution $y_0, ..., y_{number_of_steps}$.
$y_0$ is the initial condition.
For $i = 0, ..., number_of_steps$:
  $rhs_final$ is updated using $y_i$ and used to find $y_{i + 1}$.
*/
static void loop(
  double * result,
  double * rhs_final,
  const matrix_sparse * lhs,
  const matrix_sparse * rhs,
  const double * free_part,
  const diffusion_transient_discrete_primal_strong * data,
  int number_of_steps)
{
  int i, n;

  n = rhs->rows;
  for (i = 0; i < number_of_steps; ++i)
  {
    diffusion_transient_discrete_primal_strong_solve_trapezoidal_next(
      result + (i + 1) * n, rhs_final, result + i * n, lhs, rhs, free_part,
      data);
    if (errno)
    {
      fprintf(stderr,
        "%s:%d: loop: error in iteration %d\n", __FILE__, __LINE__, i);
      return;
    }
  }
}

double * diffusion_transient_discrete_primal_strong_solve_trapezoidal(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_transient_discrete_primal_strong * data,
  double time_step,
  int number_of_steps)
{
  int n;
  double * free_part, * rhs_final;
  double * result = NULL;
  double * a;
  matrix_sparse * b;
  matrix_sparse * lhs, * rhs;

  n = m->cn[0];
  a = data->pi_0;

  b = matrix_sparse_material_product(m_cbd_0, data->pi_1, m_cbd_star_1);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);;
    fputs("cannot calculate b\n", stderr);
    goto end;
  }

  /* $lhs =  a + (time_step / 2) * b$ */
  lhs = matrix_sparse_copy(b);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);;
    fputs("cannot calculate matrix lhs\n", stderr);
    goto b_free;
  }
  matrix_sparse_scalar_multiply(lhs, time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(lhs, a);

  /* $rhs =  a - (time_step / 2) * b$ */
  rhs = matrix_sparse_copy(b);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);;
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
    color_error_position(__FILE__, __LINE__);;
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
    color_error_position(__FILE__, __LINE__);;
    fputs("cannot apply Neumann boundary condition\n", stderr);
    goto free_part_free;
  }

  /* allocate memory for $rhs_final$ -> uppdated at each step of the loop */
  rhs_final = (double *) malloc(sizeof(double) * n);
  if (errno)
  {
    fputs("Runtime error stack trace:\n", stderr);
    color_error_position(__FILE__, __LINE__);;
    fputs("cannot allocate memory for rhs_final\n", stderr);
    goto free_part_free;
  }

  /* allocate memory for $result$ -> $n$ elements filled at each step */
  result = (double *) malloc(sizeof(double) * (number_of_steps + 1) * n);
  if (errno)
  {
    fputs("Runtime error stack trace:\n", stderr);
    color_error_position(__FILE__, __LINE__);;
    fputs("cannot allocate memory for result\n", stderr);
    goto rhs_final_free;
  }

  /* the initial $n$ elements of $result$ are the initial condition */
  memcpy(result, data->initial, sizeof(double) * n);

  /* The following $number_of_steps$ elements of $result$ (each of size $n$)
   * are calculated iteratively with $rhs_final$ updating at each step.
   */
  loop(result, rhs_final, lhs, rhs, free_part, data, number_of_steps);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);;
    fputs("error in loop calculating final result\n", stderr);
    free(result);
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
end:
  return result;
}
