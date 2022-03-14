#include <errno.h>
#include "mesh_qc.h"

static void cs_remove_symmetric_fprint(
  FILE * out, const cs * a, const jagged1 * rows)
{
  cs * b;
  
  b = cs_remove_symmetric(a, rows);
  if (errno)
  {
    perror("Problem in cs scanning");
    goto b_free;
  }
  cs_fprint(out, b, "--raw");
b_free:
  cs_free(b);
}

int main()
{
  jagged1 * m_bd_layer_0_1_nodes;
  cs * m_laplacian_0;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m_bd_layer_0_1_nodes = jagged1_fscan_raw(in);
  /* NULL pointer check */
  m_laplacian_0 = cs_fscan(in);
  /* NULL pointer check */
  cs_remove_symmetric_fprint(out, m_laplacian_0, m_bd_layer_0_1_nodes);
  /* NULL pointer check */
  cs_free(m_laplacian_0);
  jagged1_free(m_bd_layer_0_1_nodes);
  return 0;
}
