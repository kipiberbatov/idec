#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double.h"
#include "int.h"
#include "matrix_sparse.h"
#include "mesh_qc.h"

// u(t, {x, y}) = (t + 1) (x^2 + y^2)
// du / dt = x^2 + y^2
// delta u = -4 (t + 1)
// f(t, x) = -4 * (t + 1) + x^2 + y^2
// u

static double norm_square(const double * x)
{
  return x[0] * x[0] + x[1] * x[1];
}

static double f(double t, const double * x)
{
  return - 4 * (t + 1) + norm_square(x);
}

static double g_d(double t, const double * x)
{
  return (t + 1) * norm_square(x);
}

static double u_0(const double * x)
{
  return norm_square(x);
}

int main(int argc, char * argv[])
{
  char * m_format, * m_inner_0_format, * m_inner_0_name, * m_laplacian_0_format,
       * m_laplacian_0_name, * m_name, * out_format;
  int N;
  double tau;
  double * m_inner_0, * x;
  mesh * m;
  jagged1 * m_nodes_bd;
  matrix_sparse * m_laplacian_0;
  
  if (argc != 10)
  {
    errno = EINVAL;
    fputs("main - the number of command-line arguments must be 10\n", stderr);
    goto end;
  }
  
  m_name = argv[1];
  m_format = argv[2];
  m = mesh_file_scan_by_name(m_name, m_format);
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
  
  m_laplacian_0_name = argv[3];
  m_laplacian_0_format = argv[4];
  
  m_laplacian_0 = 
    matrix_sparse_file_scan_by_name(m_laplacian_0_name, m_laplacian_0_format);
  if (errno)
  {
    fputs("main - cannot calculate m_laplacian[0]\n", stderr);
    goto m_nodes_bd_free;
  }
  
  m_inner_0_name = argv[5];
  m_inner_0_format = argv[6];
  m_inner_0 = 
    double_array_file_scan_by_name(m_inner_0_name, m->cn[0], m_inner_0_format);
  if (errno)
  {
    fputs("main - cannot scan m_inner\n", stderr);
    goto m_laplacian_0_free;
  }
  
  tau = double_string_scan(argv[7]);
  if (errno)
  {
    fputs("main - cannot scan tau\n", stderr);
    goto m_inner_0_free;
  }
  
  N = int_string_scan(argv[8]);
  if (errno)
  {
    fputs("main - cannot scan N\n", stderr);
    goto m_inner_0_free;
  }
  
  x = matrix_sparse_heat_conduction_solve_non_grid(
      m_laplacian_0, m->dim_embedded, m->coord, m_inner_0, m_nodes_bd, f, g_d,
      u_0, tau, N);
  if (errno)
  {
    fputs("main - cannot calculate x\n", stderr);
    goto m_inner_0_free;
  }
  
  // {
  //   int i;
  //   double error;
  //   for (i = 0; i < m_laplacian_0->rows; ++i)
  //   {
  //     error = x[i] - g_d(m->coord + m->dim_embedded * i);
  //     fprintf(stderr, "%g\n", error);
  //   }
  // }
  
  out_format = argv[9];
  double_matrix_file_print(stdout, (N + 1), m_laplacian_0->rows, x, out_format);

  free(x);
m_inner_0_free:
  free(m_inner_0);
m_laplacian_0_free:
  matrix_sparse_free(m_laplacian_0);
m_nodes_bd_free:
  jagged1_free(m_nodes_bd);
m_free:
  mesh_free(m);
end:
  return errno;
}
