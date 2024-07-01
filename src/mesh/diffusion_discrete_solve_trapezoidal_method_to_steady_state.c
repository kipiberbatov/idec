#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "diffusion_discrete.h"

/*
$result$ stores the final solution $y_0, ..., y_{number_of_steps}$.
$y_0$ is the initial condition.
Until error is less than $tolerance$:
  $rhs_final$ is updated using $y_i$ and used to find $y_{i + 1}$.
*/
static void loop(
  double_array_sequence_dynamic * result,
  matrix_sparse * lhs,
  double * rhs_final,
  const matrix_sparse * rhs,
  const double * free_part,
  const jagged1 * boundary_dirichlet,
  const double * g_dirichlet,
  const jagged1 * boundary_neumann,
  const double * g_neumann,
  double tolerance)
{
  int i, n;
  double relative_norm;

  i = 0;
  n = rhs->rows;
  
  do
  {
    /* let $y_i := result->values[i]$ be the $i$-th solution vector */
    /* $rhs_final += rhs * y_i$ */
    memcpy(rhs_final, free_part, sizeof(double) * n);
    matrix_sparse_vector_multiply_add(rhs_final, rhs, result->values[i]);
    
    /* update Dirichlet rows of rhs_final by Dirichlet boundary conditions */
    double_array_substitute_inverse(
      rhs_final, boundary_dirichlet->a0, g_dirichlet, boundary_dirichlet->a1);
    
    double_array_substitute_inverse(
      rhs_final, boundary_neumann->a0, g_neumann, boundary_neumann->a1);
    if (i == result->capacity - 1)
    {
      double_array_sequence_dynamic_resize(result);
      if (errno)
      {
        fprintf(stderr, "  loop: error in iteration %d\n", i);
        return;
      }
    }
    
    result->values[i + 1] = (double *) malloc(sizeof(double) * n);
    if (errno)
    {
      fputs("Runtime error stack trace:\n", stderr);
      fprintf(stderr, 
        "  loop: cannot allocate memory for result->values[%d]\n",
        i + 1);
      return;
    }
    
    /* $y_{i + 1} = lhs^{-1} . rhs_final$ */
    memcpy(result->values[i + 1], rhs_final, sizeof(double) * n);
    matrix_sparse_linear_solve(lhs, result->values[i + 1], "--lu");
    if (errno)
    {
      fprintf(stderr, "  loop: error in iteration %d\n", i);
      return;
    }
    relative_norm = double_array_pair_norm_uniform_relative(
      n, result->values[i], result->values[i + 1]);
    ++result->length;
    ++i;
  }
  while (relative_norm >= tolerance);
}

#define FUNCTION "diffusion_discrete_solve_trapezoidal_method_to_steady_state"
#define START_ERROR_MESSAGE fprintf(stderr,"  %s: ", FUNCTION)

double_array_sequence_dynamic *
diffusion_discrete_solve_trapezoidal_method_to_steady_state(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_discrete * data,
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
  loop(result, lhs, rhs_final, rhs, free_part,
    data->boundary_dirichlet, data->g_dirichlet,
    data->boundary_neumann, data->g_neumann,
    tolerance);
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
