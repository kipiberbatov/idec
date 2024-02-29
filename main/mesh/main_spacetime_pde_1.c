#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "matrix_sparse.h"
#include "mesh_qc.h"
#include "spacetime_pde.h"

/*
Solve the following problem:
Given a mesh M for the unit square, and tthe discrete Laplacian, solve:
  . du/dt = -Laplacian(u) + f    in the interior nodes of M
  . u = g_d                      at the boundary nodes of M
  . u(0) = initial               at all nodes of M
For this example it is assumed that f and g_d are time independent.
An artificial example with
  u(t, x, y) = exp(-2 * pi^2) sin(pi x) sin(pi y)
is taken.
This corresponds to f = 0, g_d = 0, initial = sin(pi x) sin(pi y)
*/

static double f(const double * x)
{
  return 0;
}

static double g_d(const double * x)
{
  return 0;
}

static double initial(const double * x)
{
  return sin(M_PI * x[0]) * sin(M_PI * x[1]);
}

int main(int argc, char * argv[])
{
  char * m_format, * m_laplacian_0_format, * m_laplacian_0_name, * m_name;
  double ** result;
  mesh * m;
  jagged1 * m_nodes_bd;
  matrix_sparse * m_laplacian_0;
  int i,   number_of_steps;
  double time_step;
  
  if (argc != 7)
  {
    errno = EINVAL;
    fputs("main - the number of command-line arguments must be 6\n", stderr);
    goto end;
  }
  
  m_format = argv[1];
  m_name = argv[2];
  m = mesh_fscan_by_name(m_name, m_format);
  if (errno)
  {
    fputs("main - cannot scan m\n", stderr);
    goto end;
  }
  mesh_fprint(stderr, m, "--raw");
  fputs("\n", stderr);
  
  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("main - cannot calculate m->fc\n", stderr);
    goto m_free;
  }
  
  m_nodes_bd = mesh_bd_nodes(m);
  if (errno)
  {
    fputs("main - cannot calculate m_nodes_bd\n", stderr);
    goto m_free;
  }
  jagged1_fprint(stderr, m_nodes_bd, "--raw");
  fputs("\n", stderr);
  
  m_laplacian_0_format = argv[3];
  m_laplacian_0_name = argv[4];
  
  m_laplacian_0 = 
    matrix_sparse_fscan_by_name(m_laplacian_0_name, m_laplacian_0_format);
  if (errno)
  {
    fputs("main - cannot calculate m_laplacian[0]\n", stderr);
    goto m_nodes_bd_free;
  }
  matrix_sparse_fprint(stderr, m_laplacian_0, "--raw");
  fputs("\n", stderr);
  matrix_sparse_scalar_multiply(m_laplacian_0, -1);

  time_step = atof(argv[5]);
  fprintf(stderr, "%g\n\n", time_step);
  number_of_steps = atoi(argv[6]);
  fprintf(stderr, "%d\n\n", number_of_steps);
  
  result = spacetime_pde_heat_equation_solve_trapezoidal_method(
    m_laplacian_0,
    m->dim_embedded,
    m->coord,
    m_nodes_bd,
    initial,
    f,
    g_d,
    time_step,
    number_of_steps);
  
  if (errno)
  {
    fputs("main - cannot calculate x\n", stderr);
    goto m_laplacian_0_free;
  }
  
  for (i = 0; i <= number_of_steps; ++i)
  {
    double_array_fprint(stdout, m_laplacian_0->cols, result[i], "--raw");
    fputs("\n", stdout);
  }

  free(result);
m_laplacian_0_free:
  matrix_sparse_free(m_laplacian_0);
m_nodes_bd_free:
  jagged1_free(m_nodes_bd);
m_free:
  mesh_free(m);
end:
  return errno;
}
