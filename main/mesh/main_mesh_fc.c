#include "mesh.h"

int main()
{
  mesh * m;
  FILE * out, * in;

  out = stdout;
  in = stdin;
  m = mesh_file_scan(in, "--raw");
  /* NULL pointer check */
  m->fc = mesh_fc(m);
  /* NULL pointer check */
  jagged4_file_print(out, m->fc, "--raw");
  mesh_free(m);
  return 0;
}
