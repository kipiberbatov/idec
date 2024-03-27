#include <errno.h>
#include "mesh.h"

int x0_axis_constant(const double * x)
{
  return (x[0] == 0. || x[0] == 1) && (0. <= x[0] && x[0] <= 1.);
}

int main(void)
{
  mesh * m;
  jagged1 * m_boundary_nodes;
  
  m = mesh_fscan(stdin, "--raw");
  if (errno)
  {
    fputs("Error: cannot scan input mesh\n", stderr);
    goto end;
  }
  
  m_boundary_nodes = mesh_boundary_nodes_from_constraint(m, x0_axis_constant);
  if (errno)
  {
    fputs("Error: cannot calculate m_boundary_nodes\n", stderr);
    goto m_free;
  }
  
  jagged1_fprint(stdout, m_boundary_nodes, "--raw");
  
  jagged1_free(m_boundary_nodes);
m_free:
  mesh_free(m);
end:
  return errno;
}
