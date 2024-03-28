#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "int.h"
#include "mesh.h"
#include "spacetime_pde.h"

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
  scalar_field initial)
{
  char * m_format, * m_laplacian_0_format, * m_laplacian_0_name, * m_name;
  double ** result;
  mesh * m;
  jagged1 * m_nodes_bd;
  matrix_sparse * m_laplacian_0;
  int i, number_of_steps;
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
  
  m_laplacian_0_format = argv[3];
  m_laplacian_0_name = argv[4];
  
  m_laplacian_0 = 
    matrix_sparse_fscan_by_name(m_laplacian_0_name, m_laplacian_0_format);
  if (errno)
  {
    fputs("main - cannot calculate m_laplacian[0]\n", stderr);
    goto m_nodes_bd_free;
  }
  matrix_sparse_scalar_multiply(m_laplacian_0, -1);

  time_step = double_sscan(argv[5]);
  if (errno)
  {
    fprintf(stderr, "Error in %s: cannot scan time_step\n", __func__);
    goto m_laplacian_0_free;
  }

  number_of_steps = int_sscan(argv[6]);
  if (errno)
  {
    fprintf(stderr, "Error in %s: cannot scan number_of_steps\n", __func__);
    goto m_laplacian_0_free;
  }
  
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
