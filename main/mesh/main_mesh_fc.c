#include "mesh.h"

int main()
{
  mesh * m;
  FILE * out, * in;
  
  out = stdout;
  in = stdin;
  m = mesh_fscan(in);
  /* NULL pointer check */
  m->fc = mesh_fc(m);
  /* NULL pointer check */
  jagged4_fprint_raw(out, m->fc);
  mesh_free(m);
  return 0;
}
