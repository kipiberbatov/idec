#include <errno.h>
#include <stdlib.h>
#include "double.h"
#include "mesh.h"

// static void mesh_measure_file_print_raw(FILE * out, const mesh * m)
// {
//   int m_dim, p;
//   int * m_cn;
//   double * m_vol_p;
//
//   m_dim = m->dim;
//   m_cn = m->cn;
//   for(p = 0; p <= m_dim; ++p)
//   {
//     m_vol_p = mesh_measure_p(m, p);
//     if (errno)
//     {
//       fprintf(stderr,
//               "mesh_measure_file_print_raw - cannot calculate m_vol[%d]\n", p);
//       return;
//     }
//     double_array_file_print(out, m_cn[p], m_vol_p, "--raw");
//     free(m_vol_p);
//   }
// }

int main()
{
  int ind, m_dim, p;
  int * m_cn;
  double * m_vol;
  mesh * m;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  
  m = mesh_file_scan(in, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m\n", stderr);
    goto end;
  }
  
  m_dim = m->dim;
  m_cn = m->cn;
  
  m_vol = mesh_measure(m);
  if (errno)
  {
    fputs("main - cannot find m_vol\n", stderr);
    goto m_free;
  }
  
  ind = 0;
  for (p = 0; p <= m_dim; ++p)
  {
    double_array_file_print(out, m_cn[p], m_vol + ind, "--raw");
    ind += m_cn[p];
  }
  
  free(m_vol);
m_free:
  mesh_free(m);
end:
  return errno;
}
