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
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_discrete * data,
  double time_step,
  int number_of_steps)
{ 
  int n;
  double * free_part, * rhs_final;
  double * result;
  double * a;
  matrix_sparse * b;
  matrix_sparse * m_cbd_star_1_material;
  matrix_sparse * lhs, * rhs;
  
  n = m->cn[0];
  a = data->pi_0;
  
  m_cbd_star_1_material = matrix_sparse_copy(m_cbd_star_1);
  matrix_sparse_multiply_with_diagonal_matrix(
    m_cbd_star_1_material, data->pi_1);
  b = matrix_sparse_product(m_cbd_star_1_material, m_cbd_0);
  /* NULL pointer checking */
  
  /* lhs =  a + (time_step / 2) * b */
  lhs = matrix_sparse_copy(b);
  /* NULL pointer checking */
  matrix_sparse_scalar_multiply(lhs, time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(lhs, a);
  
  /* lhs =  a - (time_step / 2) * b */
  rhs = matrix_sparse_copy(b);
  /* NULL pointer checking */
  matrix_sparse_scalar_multiply(rhs, - time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(rhs, a);
  
  free_part = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */
  
  memcpy(free_part, data->source, sizeof(double) * n);
  double_array_multiply_with(free_part, n, time_step);
  
  matrix_sparse_set_identity_rows(lhs, data->boundary_dirichlet);
  diffusion_discrete_set_neumann_rows(
    lhs, m, data->boundary_neumann, data->pi_1);
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
  matrix_sparse_free(b);
  matrix_sparse_free(m_cbd_star_1_material);
  return result;
}
