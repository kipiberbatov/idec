#include <errno.h>
#include "mesh.h"

int main(void)
{
  mesh * m;
  jagged1 * m_boundary_hyperfaces;
  
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
  
  jagged1_file_print(stdout, m_boundary_hyperfaces, "--raw");
  
  jagged1_free(m_boundary_hyperfaces);
m_free:
  mesh_free(m);
end:
  return errno;
}
