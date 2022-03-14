#include <errno.h>
#include "mesh.h"

static void mesh_cbd_fprint(FILE * out, int m_dim, cs ** m_bd, char * format)
{
  int p;
  cs * m_bd_p_plus_1, * m_cbd_p;
  
  for (p = 0; p < m_dim; ++p)
  {
    m_bd_p_plus_1 = m_bd[p];
    m_cbd_p = cs_transpose(m_bd_p_plus_1, 1);
    if (errno)
    {
      perror("During matrix transposition");
      cs_free(m_cbd_p);
      return;
    }
    cs_fprint(out, m_cbd_p, format);
    if (errno)
    {
      perror("During matrix printing");
      cs_free(m_cbd_p);
      return;
    }
    if (p < m_dim - 1)
      fputc('\n', out);
    cs_free(m_cbd_p);
  }
}

int main(int argc, char * argv[])
{
  int m_dim;
  mesh * m;
  cs ** m_bd;
  char * format;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_fscan(in);
  /* NULL pointer check */
  m_dim = m->dim;
  m_bd = mesh_fscan_bd(in, m);
  /* NULL pointer check */
  format = argv[1];
  mesh_cbd_fprint(out, m_dim, m_bd, format);
  /* NULL pointer check */
  cs_free_array(m_bd, m_dim);
  mesh_free(m);
  return 0;
}
