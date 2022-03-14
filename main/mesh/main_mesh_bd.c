#include <errno.h>
#include "mesh.h"

int main(int argc, char * argv[])
{
  int m_dim;
  mesh * m;
  cs ** m_bd;
  FILE * in, * out;
  char * format;
  
  out = stdout;
  in = stdin;
  m = mesh_fscan(in);
  if (errno)
  {
    perror("Unsuccessful mesh scanning");
    goto m_free;
  }
  m_dim = m->dim;
  m->fc = NULL;
  m_bd = mesh_fscan_bd(in, m);
  if (errno)
  {
    perror("Unsuccessful mesh boundary scanning");
    goto m_bd_free;
  }
  format = argv[1];
  cs_fprint_array(out, m_dim, m_bd, format);
  if (errno)
  {
    perror("Unsuccessful mesh boundary printing");
    goto end;
  }
m_bd_free:
  cs_free_array(m_bd, m_dim);
m_free:
  mesh_free(m);
end:
  return errno;
}
