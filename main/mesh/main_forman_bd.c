#include "double.h"
#include "forman.h"

static void mesh_bd_fprint(FILE * out, int m_dim, cs ** m_bd)
{
  int p;
  cs * m_bd_p;

  for (p = 1; p <= m_dim; ++p)
  {
    m_bd_p = m_bd[p - 1];
    double_fprint_array_raw(out, m_bd_p->nzmax, m_bd_p->x);
  }
}

static void forman_bd_fprint(FILE * out, const mesh * m, cs ** m_bd)
{
  int m_dim;
  mesh * m_forman;
  cs ** m_forman_bd;
  
  m_dim = m->dim;
  m_forman = forman(m);
  /* NULL pointer check */
  mesh_fprint(out, m_forman);
  m_forman_bd = forman_bd(m, m_forman, m_bd);
  /* NULL pointer check */
  mesh_bd_fprint(out, m_dim, m_forman_bd);
  cs_free_array(m_forman_bd, m_dim);
  mesh_free(m_forman);
}

int main()
{
  int m_dim;
  mesh * m;
  cs ** m_bd;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_fscan(in);
  /* NULL pointer check */
  m_dim = m->dim;
  m->fc = mesh_fc(m);
  /* NULL pointer check */
  m_bd = mesh_fscan_bd(in, m);
  /* NULL pointer check */
  forman_bd_fprint(out, m, m_bd);
  cs_free_array(m_bd, m_dim);
  mesh_free(m);
}
