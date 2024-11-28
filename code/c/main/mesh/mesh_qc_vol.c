#include <errno.h>
#include <stdlib.h>

#include "color.h"
#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_vol_file_print_raw(FILE * out, const mesh_qc * m)
{
  int d, p;
  int * m_cn;
  double * m_vol_p;

  d = m->dim;
  m_cn = m->cn;
  for(p = 0; p <= d; ++p)
  {
    m_vol_p = mesh_qc_vol_p(m, p);
    if (m_vol_p == NULL)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr, "cannot calculate m_col[%d]\n", p);
      return;
    }
    double_array_file_print(out, m_cn[p], m_vol_p, "--raw");
    free(m_vol_p);
  }
}

int main(void)
{
  mesh_qc * m;
  FILE * in, * out;

  out = stdout;
  in = stdin;

  m = mesh_file_scan(in, "--raw");
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan mesh m in format --raw\n", stderr);
    return errno;
  }

  mesh_qc_vol_file_print_raw(out, m);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate mesh measures and print them\n", stderr);
  }

  mesh_free(m);
  return errno;
}
