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
  matrix_sparse * lhs, * rhs;
  
  n = a->rows;
  
  lhs = matrix_sparse_linear_combination(a, b, 1, - time_step / 2);
  /* NULL pointer checking */
  fputs("\nLHS interior matrix:\n", stderr);
  matrix_sparse_fprint(stderr, lhs, "--matrix-form-raw");
  
  rhs = matrix_sparse_linear_combination(a, b, 1, time_step / 2);
  /* NULL pointer checking */
  fputs("\nRHS interior matrix:\n", stderr);
  matrix_sparse_fprint(stderr, rhs, "--matrix-form-raw");
  
  free_part = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */
  
  memcpy(free_part, c, sizeof(double) * n);
  double_array_multiply_with(free_part, n, time_step);
  fputs("\nRight hand side vector:\n", stderr);
  double_array_fprint(stderr, n, free_part, "--raw");
  
  matrix_sparse_set_identity_rows(lhs, boundary_positions);
  fputs("\nLHS interior modified matrix:\n", stderr);
  matrix_sparse_fprint(stderr, lhs, "--matrix-form-raw");
  
  rhs_final = (double *) malloc(sizeof(double) * n);
  
  result = (double **) malloc(sizeof(double *) * (number_of_steps + 1));
  /* NULL pointer checking */
  
  for (i = 0; i <= number_of_steps; ++i)
  {
    result[i] = (double *) malloc(sizeof(double) * n);
    /* NULL pointer checking */
  }
  
  memcpy(result[0], u0, sizeof(double) * n);
  fputs("\nSolution at step 0:\n", stderr);
  double_array_fprint(stderr, n, result[0], "--raw");
  
  for (i = 0; i < number_of_steps; ++ i)
  {
    fprintf(stderr, "\n\nstep = %d\n", i + 1);
    memcpy(rhs_final, free_part, sizeof(double) * n);
    fputs("\nRight hand side final -- initialize:\n", stderr);
    double_array_fprint(stderr, n, rhs_final, "--raw");
    
    matrix_sparse_vector_multiply_add(rhs_final, rhs, result[i]);
    fputs("\nRight hand side final -- added contributions:\n", stderr);
    double_array_fprint(stderr, n, rhs_final, "--raw");

    double_array_partial_update(rhs_final, boundary_positions, g);
    fputs("\nRight hand side final -- applied boundary conditions:\n", stderr);
    double_array_fprint(stderr, n, rhs_final, "--raw");

    memcpy(result[i + 1], rhs_final, sizeof(double) * n);
    fputs("\nCopy into result:\n", stderr);
    double_array_fprint(stderr, n, result[i + 1], "--raw");

    matrix_sparse_linear_solve(lhs, result[i + 1], "--lu");
    fputs("\nSolution at this time step:\n", stderr);
    double_array_fprint(stderr, n, result[i + 1], "--raw");
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
  fputs("Initial condition vector:\n", stderr);
  double_array_fprint(stderr, n, u0, "--raw");

  c = (double *) malloc(sizeof(double) * n);
  for (i = 0; i < n; ++i)
    c[i] = f(m_coord + m_dim_embedded * i);
  fputs("\nRight hand side vector:\n", stderr);
  double_array_fprint(stderr, n, c, "--raw");

  g = spacetime_pde_dirichlet_boundary_vector(
    m_dim_embedded,
    m_coord,
    m_nodes_bd,
    g_d);
  fputs("\nDirichlet boundary condition vector:\n", stderr);
  double_array_fprint(stderr, m_nodes_bd->a0, g, "--raw");
  
  a = matrix_sparse_identity(n);
  fputs("\nIdentity matrix:\n", stderr);
  matrix_sparse_fprint(stderr, a, "--raw");

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
