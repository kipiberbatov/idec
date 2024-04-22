#include <errno.h>
#include "mesh.h"

int main(int argc, char * argv[])
{
  mesh * m;
  matrix_sparse ** m_bd;
  FILE * in, * out;
  char * format;
  
  out = stdout;
  in = stdin;
  
  m = mesh_file_scan(in, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m\n", stderr);
    return errno;
  }
  
  m_bd = mesh_file_scan_bd(in, m);
  if (errno)
  {
    fputs("main - cannot scan m->bd\n", stderr);
    mesh_free(m);
    return errno;
  }
  
  format = argv[1];
  matrix_sparse_array_file_print(out, m->dim, m_bd, format);
  
  matrix_sparse_array_free(m_bd, m->dim);
  
  mesh_free(m);
  return errno;
}
