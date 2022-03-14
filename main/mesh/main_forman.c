#include "forman.h"

// void forman_fprint(FILE * out, const mesh * m)
// {
//   mesh * m_forman;
//
//   m_forman = forman(m);
//   /* NULL pointer check */
//   mesh_fprint(out, m_forman);
//   mesh_free(m_forman);
// }

int main()
{
  mesh * m, * m_forman;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_fscan(in);
  /* NULL pointer check */
  m->fc = mesh_fc(m);
  /* NULL pointer check */
  m_forman = forman(m);
  /* NULL pointer check */
  mesh_free(m);
  mesh_fprint(out, m_forman);
  /* NULL pointer check */
  mesh_free(m_forman);
  return 0;
}
