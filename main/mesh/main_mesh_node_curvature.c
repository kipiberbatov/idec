#include "double.h"
#include "mesh.h"

static void mesh_node_curvature_fprint(FILE * out, const mesh * m)
{
  double * res;

  res = mesh_node_curvature(m);
  /* NULL pointer check */
  double_fprint_array_raw(out, m->cn[0], res);
  /* NULL pointer check */
  free(res);
}

int main()
{
  mesh * m;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_fscan(in);
  /* NULL pointer and successfull reading check */
  m->fc = mesh_fc(m);
  /* NULL pointer check */
  mesh_node_curvature_fprint(out, m);
  /* NULL pointer check */
  mesh_free(m);
  return 0;
}
