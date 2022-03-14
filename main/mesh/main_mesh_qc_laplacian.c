#include <errno.h>
#include <string.h>
#include "mesh.h"

int main()
{
  int m_dim;
  mesh * m;
  cs ** m_bd, ** m_cbd, ** m_cbd_star;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_fscan(in);
  /* NULL pointer check */
  m_dim = m->dim;
  m_bd = mesh_fscan_bd(in, m);
  /* NULL pointer check */
  m_cbd = mesh_cbd(m_dim, m_bd);
  /* NULL pointer check */
  m_cbd_star = mesh_fscan_bd(in, m);
  /* NULL pointer check */
  cs_laplacian_fprint(out, m_dim, m_cbd, m_cbd_star, "--raw");
  /* NULL pointer check */
  cs_free_array(m_cbd_star, m_dim);
  cs_free_array(m_cbd, m_dim);
  cs_free_array(m_bd, m_dim);
  mesh_free(m);
  return 0;
}
