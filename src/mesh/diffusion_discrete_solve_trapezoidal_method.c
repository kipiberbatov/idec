#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "diffusion_discrete.h"

static void loop(
  double * result,
  matrix_sparse * lhs,
  double * rhs_final,
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
  for (i = 0; i < number_of_steps; ++i)
  {
    memcpy(rhs_final, free_part, sizeof(double) * n);
    
    matrix_sparse_vector_multiply_add(rhs_final, rhs, result + i * n);
    
    /* update rhs_final with the boundary conditions */
    double_array_substitute_inverse(
      rhs_final, boundary_dirichlet->a0, g_dirichlet, boundary_dirichlet->a1);
    
    double_array_substitute_inverse(
      rhs_final, boundary_neumann->a0, g_neumann, boundary_neumann->a1);

    memcpy(result + (i + 1) * n, rhs_final, sizeof(double) * n);

    matrix_sparse_linear_solve(lhs, result + (i + 1) * n, "--lu");
    /* NULL pointer checking */
  }
}

double * diffusion_discrete_solve_trapezoidal_method(
  const mesh * m,
  const matrix_sparse * m_laplacian_0,
  const diffusion_discrete * data,
  double time_step,
  int number_of_steps)
{ 
  int n;
  double * free_part, * rhs_final;
  double * result;
  // matrix_sparse * a;
  double * a;
  const matrix_sparse * b;
  matrix_sparse * lhs, * rhs;
  
  a = data->pi_0;
  b = m_laplacian_0;
  //b = data->pi_1; 
  
  /* b = pi_0 * cbd_star_*/
  
  n = m->cn[0];
  
  // lhs = matrix_sparse_linear_combination(a, b, 1, - time_step / 2);
  lhs = matrix_sparse_copy(b);
  /* NULL pointer checking */
  matrix_sparse_scalar_multiply(lhs, - time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(lhs, a);
  
  // rhs = matrix_sparse_linear_combination(a, b, 1, time_step / 2);
  rhs = matrix_sparse_copy(b);
  /* NULL pointer checking */
  matrix_sparse_scalar_multiply(rhs, time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(rhs, a);
  
  free_part = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */
  
  memcpy(free_part, data->source, sizeof(double) * n);
  double_array_multiply_with(free_part, n, time_step);
  
  matrix_sparse_set_identity_rows(lhs, data->boundary_dirichlet);
  diffusion_discrete_set_neumann_rows(lhs, m, data->boundary_neumann);
  /* NULL pointer checking */
  
  rhs_final = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */
  
  result = (double *) malloc(sizeof(double) * (number_of_steps + 1) * n);
  /* NULL pointer checking */
  
  memcpy(result, data->initial, sizeof(double) * n);
  
  loop(result, lhs, rhs_final, rhs, free_part,
    data->boundary_dirichlet, data->g_dirichlet,
    data->boundary_neumann, data->g_neumann,
    number_of_steps);
  /* NULL pointer checking */
  
  free(rhs_final);
  free(free_part);
  matrix_sparse_free(rhs);
  matrix_sparse_free(lhs);
  // matrix_sparse_free(a);
  return result;
}
