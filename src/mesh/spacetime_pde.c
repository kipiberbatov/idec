/*
Solves dynamic partial differential eqation, first order with respect to time.
At any moment the participating operators are linear.
The next iteration is find using the trapezoidal rule
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "spacetime_pde.h"

/* update rhs_final with the boundary conditions */
static void double_array_partial_update(
  double * rhs_final,
  const jagged1 * boundary_positions,
  const double * g)
{
  int j, j_local, size;
  int * values;

  size = boundary_positions->a0;
  values = boundary_positions->a1;

  for (j_local = 0; j_local < size; ++j_local)
  {
    j = values[j_local];
    rhs_final[j] = g[j_local];
  }
}

double * spacetime_pde_dirichlet_boundary_vector(
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * m_nodes_bd,
  scalar_field g_d)
{
  int j, j_loc, m_nodes_bd_a0;
  int * m_nodes_bd_a1;
  double * result;
  
  m_nodes_bd_a0 = m_nodes_bd->a0;
  m_nodes_bd_a1 = m_nodes_bd->a1;
  result = (double *) malloc(sizeof(double) * m_nodes_bd_a0);
  if (errno)
    return NULL;
  
  for (j_loc = 0; j_loc < m_nodes_bd_a0; ++j_loc)
  {
    j = m_nodes_bd_a1[j_loc];
    result[j_loc] = g_d(m_coord + m_dim_embedded * j);
  }
  return result;
}

static void matrix_sparse_set_identity_rows(
  matrix_sparse * lhs,
  const jagged1 * boundary_positions)
{
  int column_j_nonzero_total, i, i_local, j;
  int * column_j_row_indices;
  double * column_j_values;
  
  for (j = 0; j < lhs->cols; ++j)
  {
    column_j_nonzero_total = lhs->cols_total[j + 1] - lhs->cols_total[j];
    column_j_row_indices = lhs->row_indices + lhs->cols_total[j];
    column_j_values = lhs->values + lhs->cols_total[j];
    for (i_local = 0; i_local < column_j_nonzero_total; ++i_local)
    {
      i = column_j_row_indices[i_local];
      if (jagged1_member(boundary_positions, i))
      {
        if (i == j)
          column_j_values[i_local] = 1.;
        else
          column_j_values[i_local] = 0.;
      }
    }
  }
}

/*
find lhs_final that is updated lhs with the trace operator on the boundary
*/

double ** spacetime_pde_time_order_1_linear_trapezoid_method(
  const double * u0,
  const matrix_sparse * a,
  const matrix_sparse * b,
  const double * c,
  const double * g,
  const jagged1 * boundary_positions,
  double time_step,
  int number_of_steps)
{
  int i, n;
  double * free_part, * rhs_final;
  double ** result;
  matrix_sparse * lhs, * lhs_final, * rhs;
  
  n = a->rows;
  
  lhs = matrix_sparse_linear_combination(a, b, 1, - time_step / 2);
  /* NULL pointer checking */
  
  rhs = matrix_sparse_linear_combination(a, b, 1, time_step / 2);
  /* NULL pointer checking */
  
  free_part = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */
  
  memcpy(free_part, c, sizeof(double) * n);
  double_array_multiply_with(free_part, n, time_step);
  
  // lhs_final = matrix_sparse_row_partial_update(lhs, boundary_positions, trace);
  matrix_sparse_set_identity_rows(lhs, boundary_positions);
  
  rhs_final = (double *) malloc(sizeof(double) * n);
  
  result = (double **) malloc(sizeof(double *) * (number_of_steps + 1));
  /* NULL pointer checking */
  
  for (i = 0; i <= number_of_steps; ++i)
  {
    result[i] = (double *) malloc(sizeof(double) * n);
    /* NULL pointer checking */
  }
  
  memcpy(result[0], u0, n);
  
  for (i = 0; i < number_of_steps; ++ i)
  {
    memcpy(rhs_final, free_part, sizeof(double) * n);
    matrix_sparse_vector_multiply_add(rhs_final, rhs, result[i]);
    //double_array_partial_update(rhs_final, boundary_positions, g);
    double_array_partial_update(rhs_final, boundary_positions, g);
    memcpy(result[i + 1], rhs_final, n);
    matrix_sparse_linear_solve(lhs_final, result[i + 1], "--lu");
  }
  
  free(rhs_final);
  free(free_part);
  matrix_sparse_free(rhs);
  matrix_sparse_free(lhs);
  return result;
}

double ** spacetime_pde_heat_equation_solve_trapezoidal_method(
  const matrix_sparse * m_laplacian,
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * m_nodes_bd,
  scalar_field initial,
  scalar_field f,
  scalar_field g_d,
  double time_step,
  int number_of_steps)
{
  int i, n;
  double * u0;
  matrix_sparse * a;
  double * c;
  double * g;
  double ** result;

  n = m_laplacian->cols;
  
  u0 = (double *) malloc(sizeof(double) * n);
  for (i = 0; i < n; ++i)
    u0[i] = initial(m_coord + m_dim_embedded * i);

  for (i = 0; i < n; ++i)

  c = (double *) malloc(sizeof(double) * n);
  for (i = 0; i < n; ++i)
    c[i] = f(m_coord + m_dim_embedded * i);

  g = spacetime_pde_dirichlet_boundary_vector(
    m_dim_embedded,
    m_coord,
    m_nodes_bd,
    g_d);
  
  a = matrix_sparse_identity(n);

  result = spacetime_pde_time_order_1_linear_trapezoid_method(
    u0,
    a,
    m_laplacian,
    c,
    g,
    m_nodes_bd,
    time_step,
    number_of_steps);

  free(a);
  free(g);
  free(c);
  free(u0);
  return result;
}
