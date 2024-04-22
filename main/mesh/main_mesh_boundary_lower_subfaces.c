#include <errno.h>
#include "mesh.h"

int main(void)
{
  mesh * m;
  jagged1 * m_boundary_hyperfaces;
  jagged1 * m_boundary_0_cells;
  
  m = mesh_file_scan(stdin, "--raw");
  if (errno)
  {
    fputs("Error: cannot scan input mesh\n", stderr);
    goto end;
  }
  
  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("Error: cannot calculate m->fc\n", stderr);
    goto m_free;
  }
  
  m_boundary_hyperfaces = mesh_boundary_hyperfaces(m);
  if (errno)
  {
    fputs("Error: cannot calculate m_boundary_hyperfaces\n", stderr);
    goto m_free;
  }
  
  m_boundary_0_cells
  = mesh_boundary_lower_subfaces(m, 0, m_boundary_hyperfaces);
  if (errno)
  {
    fputs("Error: cannot calculate m_boundary_0_cells\n", stderr);
    goto m_boundary_hyperfaces_free;
  }
  
  jagged1_file_print(stdout, m_boundary_0_cells, "--raw");
  
  jagged1_free(m_boundary_0_cells);
m_boundary_hyperfaces_free:
  jagged1_free(m_boundary_hyperfaces);
m_free:
  mesh_free(m);
end:
  return errno;
}
