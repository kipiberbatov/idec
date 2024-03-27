#include <errno.h>
#include "mesh.h"

int x1_axis_constant(const double * x)
{
  return (x[1] == 0. || x[1] == 1) && (0. < x[0] && x[0] < 1.);
}

int main(void)
{
  int i, i_local;
  double normal[2];
  mesh * m;
  jagged1 * m_boundary_nodes;
  
  m = mesh_fscan(stdin, "--raw");
  if (errno)
  {
    fputs("Error: cannot scan input mesh\n", stderr);
    goto end;
  }
  
  m_boundary_nodes = mesh_boundary_nodes_from_constraint(m, x1_axis_constant);
  if (errno)
  {
    fputs("Error: cannot calculate m_boundary_nodes\n", stderr);
    goto m_free;
  }
  
  for (i_local = 0; i_local < m_boundary_nodes->a0; ++i_local)
  {
    i = m_boundary_nodes->a1[i_local];
    mesh_boundary_node_normal(normal, m, i);
    printf("%g %g\n", normal[0], normal[1]);
    puts("");
  }
  
  jagged1_free(m_boundary_nodes);
m_free:
  mesh_free(m);
end:
  return errno;
}
