#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "diffusion_discrete.h"

/*
$result$ stores the final solution $y_0, ..., y_{number_of_steps}$.
$y_0$ is the initial condition.
For $i = 0, ..., number_of_steps$:
  $rhs_final$ is updated using $y_i$ and used to find $y_{i + 1}$.
*/
static void loop(
  double * result,
  double * rhs_final,
  matrix_sparse * lhs,
  const matrix_sparse * rhs,
  const double * free_part,
  const jagged1 * boundary_dirichlet,
  const double * g_dirichlet,
  const jagged1 * boundary_neumann,
  const double * g_neumann,
  int number_of_steps)
{
  int i, n;
  
  n = rhs->rows;
  // fprintf(stderr, "result[%d]:\n", 0);
  // double_array_file_print(stderr, n, result, "--raw");
  // fputs("\n", stderr);
  for (i = 0; i < number_of_steps; ++i)
  {
    /* let $y_i := result + i * n$ be the $i$-th solution vector */
    /* $rhs_final += rhs * y_i$ */
    memcpy(rhs_final, free_part, sizeof(double) * n);
    matrix_sparse_vector_multiply_add(rhs_final, rhs, result + i * n);

    /* update Dirichlet rows of rhs_final by Dirichlet boundary conditions */
    double_array_substitute_inverse(
      rhs_final, boundary_dirichlet->a0, g_dirichlet, boundary_dirichlet->a1);

    /* update Neumann rows of rhs_final by Neumann boundary conditions */
    double_array_substitute_inverse(
      rhs_final, boundary_neumann->a0, g_neumann, boundary_neumann->a1);
    // if (i < 2)
    // {
    //   fprintf(stderr, "rhs[%d]:\n", i + 1);
    //   double_array_file_print(stderr, n, rhs_final, "--raw");
    //   fputs("\n", stderr);
    // }

    /* $y_{i + 1} = lhs^{-1} . rhs_final$ */
    memcpy(result + (i + 1) * n, rhs_final, sizeof(double) * n);
    matrix_sparse_linear_solve(lhs, result + (i + 1) * n, "--lu");
    if (errno)
    {
      fprintf(stderr, "  loop: error in iteration %d\n", i);
      return;
    }
    // if (i < 2)
    // {
    //   fprintf(stderr, "result[%d]:\n", i + 1);
    //   double_array_file_print(stderr, n, result + (i + 1) * n, "--raw");
    //   fputs("\n", stderr);
    // }
  }
}

#define FUNCTION "diffusion_discrete_solve_trapezoidal_method"
#define START_ERROR_MESSAGE fprintf(stderr,"  %s: ", FUNCTION)

double * diffusion_discrete_solve_trapezoidal_method(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_discrete * data,
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
    START_ERROR_MESSAGE;
    fputs("cannot calculate b\n", stderr);
    goto end;
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

  /* allocate memory for $result$ -> $n$ elements filled at each step */
  result = (double *) malloc(sizeof(double) * (number_of_steps + 1) * n);
  if (errno)
  {
    fputs("Runtime error stack trace:\n", stderr);
    START_ERROR_MESSAGE;
    fputs("cannot allocate memory for result\n", stderr);
    goto rhs_final_free;
  }

  /* the initial $n$ elements of $result$ are the initial condition */
  memcpy(result, data->initial, sizeof(double) * n);
  
  // fputs("\nInitial: \n", stderr);
  // double_array_file_print(stderr, n, data->initial, "--raw");

  // fputs("\nDirichlet: \n", stderr);
  // jagged1_file_print(stderr, data->boundary_dirichlet, "--raw");
  // double_array_file_print(stderr,
  //   data->boundary_dirichlet->a0, data->g_dirichlet, "--raw");

  // fputs("\nNeumann: \n", stderr);
  // jagged1_file_print(stderr, data->boundary_neumann, "--raw");
  // double_array_file_print(stderr,
  //   data->boundary_neumann->a0, data->g_neumann, "--raw");

  // fputs("\n", stderr);
  // matrix_sparse_file_print(stderr, lhs, "--matrix-form-raw");
  // fputs("\n\n", stderr);
  
  /* The following $number_of_steps$ elements of $result$ (each of size $n$)
   * are calculated iteratively with $rhs_final$ updating at each step.
   */
  loop(result, rhs_final,
    lhs, rhs, free_part,
    data->boundary_dirichlet, data->g_dirichlet,
    data->boundary_neumann, data->g_neumann,
    number_of_steps);
  if (errno)
  {
    START_ERROR_MESSAGE;
    fputs("error in loop calculating final result\n", stderr);
    free(result);
    goto rhs_final_free;
  }
  // double_matrix_file_print(stderr, 2, n, result, "--raw");

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
