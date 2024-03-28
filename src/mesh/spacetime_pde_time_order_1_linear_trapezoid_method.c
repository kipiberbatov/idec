#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "mesh.h"
#include "spacetime_pde.h"

static void loop(
  double ** result,
  matrix_sparse * lhs,
  double * rhs_final,
  const matrix_sparse * rhs,
  const jagged1 * boundary_positions,
  const double * free_part,
  const double * g,
  int number_of_steps)
{
  int i, n;
  
  n = rhs->rows;
  for (i = 0; i < number_of_steps; ++ i)
  {
    memcpy(rhs_final, free_part, sizeof(double) * n);
    
    matrix_sparse_vector_multiply_add(rhs_final, rhs, result[i]);
    
    /* update rhs_final with the boundary conditions */
    double_array_substitute_inverse(
      rhs_final, boundary_positions->a0, g, boundary_positions->a1);

    memcpy(result[i + 1], rhs_final, sizeof(double) * n);

    matrix_sparse_linear_solve(lhs, result[i + 1], "--lu");
    /* NULL pointer checking */
  }
}

static double * double_matrix_allocate_pointer_to_pointer(int m, int n)
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

/*
Solve the following differential equation
  d(a u)/(d t) = b u + c on M,
  u|_{boundary(M)} = g
with given $time_step and prescribed $number_of_steps.
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
  int n;
  double * free_part, * rhs_final;
  double ** result;
  matrix_sparse * lhs, * rhs;
  
  n = a->rows;
  
  lhs = matrix_sparse_linear_combination(a, b, 1, - time_step / 2);
  /* NULL pointer checking */
  
  rhs = matrix_sparse_linear_combination(a, b, 1, time_step / 2);
  /* NULL pointer checking */
  
  free_part = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */
  
  memcpy(free_part, c, sizeof(double) * n);
  double_array_multiply_with(free_part, n, time_step);
  
  matrix_sparse_set_identity_rows(lhs, boundary_positions);
  
  rhs_final = (double *) malloc(sizeof(double) * n);
  
  result = double_matrix_allocate_pointer_to_pointer(number_of_steps + 1, n);
  /* NULL pointer checking */
  
  memcpy(result[0], u0, sizeof(double) * n);
  
  loop(result, lhs, rhs_final, rhs, boundary_positions, free_part, g,
       number_of_steps);
  /* NULL pointer checking */
  
  free(rhs_final);
  free(free_part);
  matrix_sparse_free(rhs);
  matrix_sparse_free(lhs);
  return result;
}
