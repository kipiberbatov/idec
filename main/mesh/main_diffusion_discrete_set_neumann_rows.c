#include <errno.h>
#include <stdlib.h>


#include "diffusion_discrete.h"

static int x1_axis_constant(const double * x)
{
  return (x[1] == 0. || x[1] == 1) && (0. < x[0] && x[0] < 1.);
}

int main(int argc, char ** argv)
{
  char * m_format, * m_laplacian_0_format, * m_laplacian_0_name, * m_name;
  mesh * m;
  jagged1 * neumann_nodes;
  matrix_sparse * m_laplacian_0;
  
  if (argc != 5)
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
  
  neumann_nodes = mesh_boundary_nodes_from_constraint(m, x1_axis_constant);
  if (errno)
  {
    fputs("main - cannot calculate neumann_nodes\n", stderr);
    goto m_laplacian_0_free;
  }
  
  diffusion_discrete_set_neumann_rows(m_laplacian_0, m, neumann_nodes);
  if (errno)
  {
    fputs("main - cannot apply diffusion_discrete_set_neumann_rows\n", stderr);
    goto neumann_node_free;
  }
  
  matrix_sparse_fprint(stdout, m_laplacian_0, "--raw");

neumann_node_free:
  free(neumann_nodes);
m_laplacian_0_free:
  matrix_sparse_free(m_laplacian_0);
m_free:
  mesh_free(m);
end:
  return errno;
}
