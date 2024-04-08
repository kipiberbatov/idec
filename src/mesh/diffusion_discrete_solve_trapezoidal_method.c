#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "diffusion_discrete.h"

static void loop(
  double ** result,
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
    
    matrix_sparse_vector_multiply_add(rhs_final, rhs, result[i]);
    
    /* update rhs_final with the boundary conditions */
    double_array_substitute_inverse(
      rhs_final, boundary_dirichlet->a0, g_dirichlet, boundary_dirichlet->a1);
    
    double_array_substitute_inverse(
      rhs_final, boundary_neumann->a0, g_neumann, boundary_neumann->a1);

    memcpy(result[i + 1], rhs_final, sizeof(double) * n);

    matrix_sparse_linear_solve(lhs, result[i + 1], "--lu");
    /* NULL pointer checking */
  }
}

static double ** double_matrix_allocate_pointer_to_pointer(int m, int n)
{
  int i;
  double ** result;
  
  result = (double **) malloc(sizeof(double *) * m);
  /* NULL pointer checking */
  
  for (i = 0; i < m; ++i)
  {
    result[i] = (double *) malloc(sizeof(double) * n);
    /* NULL pointer checking */
  }
  return result;
}

static void
matrix_sparse_add_with_diagonal(matrix_sparse * a, const double * b)
{
  int i_loc, j, n;
  int * a_cols_total, * a_row_indices;
  double * a_values;
  
  n = a->cols;
  a_cols_total = a->cols_total;
  a_row_indices = a->row_indices;
  a_values = a->values;
  for (j = 0; j < n; ++j)
  {
    for (i_loc = a_cols_total[j]; i_loc < a_cols_total[j + 1]; ++i_loc)
    {
      if (a_row_indices[i_loc] == j)
      {
        a_values[i_loc] += b[j];
        break;
      }
    }
  }
}

/*
Solve the following differential equation
  d(a u)/(d t) = b u + c on M,
  u|_{G_D} = g_dirichlet
  (pi_1 nabla(u))|_{G_N} = g_neumann
with given $time_step and prescribed $number_of_steps.
*/
double ** diffusion_discrete_solve_trapezoidal_method(
  const mesh * m,
  const matrix_sparse * m_laplacian_0,
  const diffusion_discrete * data,
  double time_step,
  int number_of_steps)
{ 
  int n;
  double * free_part, * rhs_final;
  double ** result;
  // matrix_sparse * a;
  double * a;
  const matrix_sparse * b;
  matrix_sparse * lhs, * rhs;
  
  a = data->pi_0;
  // a = matrix_sparse_identity(m_laplacian_0->rows);
  /* NULL pointer checking */
  b = m_laplacian_0;
  //b = data->pi_1; 
  
  /* b = pi_0 * cbd_star_*/
  
  // n = a->rows;
  n = m->cn[0];
  
  // lhs = matrix_sparse_linear_combination(a, b, 1, - time_step / 2);
  lhs = matrix_sparse_copy(b);
  /* NULL pointer checking */
  matrix_sparse_scalar_multiply(lhs, - time_step / 2);
  matrix_sparse_add_with_diagonal(lhs, a);
  
  // rhs = matrix_sparse_linear_combination(a, b, 1, time_step / 2);
  rhs = matrix_sparse_copy(b);
  /* NULL pointer checking */
  matrix_sparse_scalar_multiply(rhs, time_step / 2);
  matrix_sparse_add_with_diagonal(rhs, a);
  
  free_part = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */
  
  memcpy(free_part, data->source, sizeof(double) * n);
  double_array_multiply_with(free_part, n, time_step);
  
  matrix_sparse_set_identity_rows(lhs, data->boundary_dirichlet);
  diffusion_discrete_set_neumann_rows(lhs, m, data->boundary_neumann);
  /* NULL pointer checking */
  
  rhs_final = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */
  
  result = double_matrix_allocate_pointer_to_pointer(number_of_steps + 1, n);
  /* NULL pointer checking */
  
  memcpy(result[0], data->initial, sizeof(double) * n);
  
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

// double ** diffusion_discrete_solve_trapezoidal_method(
//   const mesh * m,
//   const diffusion_discrete * data,
//   double time_step,
//   int number_of_steps)
// {
//   return NULL;
// }