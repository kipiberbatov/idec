#ifndef SPACETIME_PDE_H
#define SPACETIME_PDE_H

/*
Solves dynamic partial differential eqation, first order with respect to time.
At any moment the participating operators are linear.
The next iteration is find using the trapezoidal rule.
*/

#include "matrix_sparse.h"

void spacetime_pde_boundary_vector(
  double * result,
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * m_boundary_nodes,
  scalar_field g_d);

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
  int number_of_steps);

double ** spacetime_pde_heat_equation_solve_trapezoidal_method(
  const matrix_sparse * m_laplacian,
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * m_nodes_bd,
  scalar_field initial,
  scalar_field f,
  scalar_field g_d,
  double time_step,
  int number_of_steps);

/*
Solves heat equation with Dirichlet boundary conditions.
Command-line arguments give necessary matrices.
Scalar fields are given in main file.
*/
int spacetime_pde_heat_equation_runner(
  int argc,
  char * argv[],
  scalar_field f,
  scalar_field g_d,
  scalar_field initial);

#endif /* SPACETIME_PDE_H */
