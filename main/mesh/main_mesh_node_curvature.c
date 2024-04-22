#include <stdlib.h>
#include "double.h"
#include "mesh.h"

static void mesh_node_curvature_file_print_raw(FILE * out, const mesh * m)
{
  double * res;

  res = mesh_node_curvature(m);
  /* NULL pointer check */
  double_array_file_print(out, m->cn[0], res, "--raw");
  /* NULL pointer check */
  free(res);
}

int main()
{
  mesh * m;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_file_scan(in, "--raw");
  /* NULL pointer and successfull reading check */
  m->fc = mesh_fc(m);
  /* NULL pointer check */
  mesh_node_curvature_file_print_raw(out, m);
  /* NULL pointer check */
  mesh_free(m);
  return 0;
}
