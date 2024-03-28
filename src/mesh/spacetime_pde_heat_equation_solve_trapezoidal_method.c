/*
Solves dynamic partial differential eqation, first order with respect to time.
At any moment the participating operators are linear.
The next iteration is find using the trapezoidal rule
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "int.h"
#include "mesh.h"
#include "spacetime_pde.h"

static void vector_initialize(
  double * x, int n, int m_dim_embedded, const double * m_coord, scalar_field f)
{
  int i;
  
  for (i = 0; i < n; ++i)
    x[i] = f(m_coord + m_dim_embedded * i);
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
  int n;
  double * u0;
  matrix_sparse * a;
  double * c;
  double * g;
  double ** result;

  n = m_laplacian->cols;
  
  u0 = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */
  vector_initialize(u0, n, m_dim_embedded, m_coord, initial);

  c = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */
  vector_initialize(c, n, m_dim_embedded, m_coord, f);

  g = (double *) malloc(sizeof(double) * m_nodes_bd->a0);
  /* NULL pointer checking */
  spacetime_pde_boundary_vector(
    g,
    m_dim_embedded,
    m_coord,
    m_nodes_bd,
    g_d);
  
  a = matrix_sparse_identity(n);
  /* NULL pointer checking */

  result = spacetime_pde_time_order_1_linear_trapezoid_method(
    u0,
    a,
    m_laplacian,
    c,
    g,
    m_nodes_bd,
    time_step,
    number_of_steps);
  /* NULL pointer checking */

  free(a);
  free(g);
  free(c);
  free(u0);
  return result;
}
