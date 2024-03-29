#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "int.h"
#include "mesh.h"
#include "diffusion_continuous.h"

/*
Solves heat equation with mixed boundary conditions.
Command-line arguments give necessary matrices.
Scalar fields are given in main file.
*/
int diffusion_continuous_runner(
  int argc,
  char ** argv,
  const diffusion_continuous * data)
{
  char * m_format, * m_laplacian_0_format, * m_laplacian_0_name, * m_name;
  double ** result;
  mesh * m;
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
  
  m_laplacian_0_format = argv[3];
  m_laplacian_0_name = argv[4];
  
  m_laplacian_0 = 
    matrix_sparse_fscan_by_name(m_laplacian_0_name, m_laplacian_0_format);
  if (errno)
  {
    fputs("main - cannot calculate m_laplacian[0]\n", stderr);
    goto m_free;
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
  
  result = diffusion_continuous_solve_trapezoidal_method(
    m,
    m_laplacian_0,
    data,
    time_step,
    number_of_steps);

  if (errno)
  {
    fputs("main - cannot calculate x\n", stderr);
    goto m_laplacian_0_free;
  }

  for (i = 0; i <= number_of_steps; ++i)
  {
    double_array_fprint(stdout, m->cn[0], result[i], "--raw");
    fputs("\n", stdout);
  }

  free(result);
m_laplacian_0_free:
  matrix_sparse_free(m_laplacian_0);
m_free:
  mesh_free(m);
end:
  return errno;
}
