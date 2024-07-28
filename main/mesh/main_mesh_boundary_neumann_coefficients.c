#include <errno.h>
#include <stdlib.h>

#include "double.h"
#include "matrix.h"
#include "mesh.h"

int x1_axis_constant(const double * x)
{
  return (x[1] == 0. || x[1] == 1) && (0. < x[0] && x[0] < 1.);
}

int main(void)
{
  int i, i_local, size;
  mesh * m;
  jagged1 * m_boundary_nodes;
  jagged1 m_fc_0_1_i;
  jagged2 m_fc_0_1;
  double * result;

  m = mesh_file_scan(stdin, "--raw");
  if (errno)
  {
    fputs("Error: cannot scan input mesh\n", stderr);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("Error: cannot calculate reverse face lattice\n", stderr);
    goto m_free;
  }
  mesh_fc_part2(&m_fc_0_1, m, 0, 1);

  m_boundary_nodes = mesh_boundary_nodes_from_constraint(m, x1_axis_constant);
  if (errno)
  {
    fputs("Error: cannot calculate m_boundary_nodes\n", stderr);
    goto m_free;
  }

  for (i_local = 0; i_local < m_boundary_nodes->a0; ++i_local)
  {
    i = m_boundary_nodes->a1[i_local];
    jagged2_part1(&m_fc_0_1_i, &m_fc_0_1, i);
    size = m_fc_0_1_i.a0;
    result = mesh_boundary_neumann_coefficients(m, i);
    if (errno)
    {
      fprintf(stderr, "Error: cannot calculate the neighbors of N_%d \n", i);
      goto m_boundary_nodes_free;
    }
    printf("%d\n", size);
    double_array_file_print(stdout, size, result, "--raw");
    puts("");
    //free(result);
  }

m_boundary_nodes_free:
  jagged1_free(m_boundary_nodes);
m_free:
  mesh_free(m);
end:
  return errno;
}
