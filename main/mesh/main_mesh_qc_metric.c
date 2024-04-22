#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_metric_file_print_only_values(
  FILE * out, const mesh_qc * m, double ** m_vol)
{
  int m_dim, p;
  int * m_cn;
  vector_sparse ** m_metric_p;
  
  m_dim = m->dim;
  m_cn = m->cn;
  
  for (p = 0; p <= m_dim; ++p)
  {
    m_metric_p = mesh_qc_metric_p(m, p, m_vol[p]);
    if (errno)
    {
      fprintf(stderr, "mesh_qc_metric_file_print - cannot calculate "
              "m_metric[%d]\n", p);
      return;
    }
    
    vector_sparse_array_file_print(out, m_cn[p], m_metric_p, "--only-values");
    if (p != m_dim)
      fputc('\n', out);
    vector_sparse_array_free(m_metric_p, m_cn[p]);
  }
}

int main()
{
  mesh_qc * m;
  matrix_sparse ** m_bd;
  double ** m_vol;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  
  m = mesh_file_scan(in, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m\n", stderr);
    goto end;
  }
  
  m_bd = mesh_file_scan_bd(in, m);
  if (errno)
  {
    fputs("main - cannot scan m_bd\n", stderr);
    goto m_free;
  }
  
  m_vol = double_array2_file_scan(in, m->dim + 1, m->cn, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m_vol\n", stderr);
    goto m_bd_free;
  }
  
  mesh_qc_metric_file_print_only_values(out, m, m_vol);
  if (errno)
  {
    fputs("main - cannot print m_metric\n", stderr);
    goto m_vol_free;
  }
  
m_vol_free:
  double_array2_free(m_vol, m->dim + 1);
m_bd_free:
  matrix_sparse_array_free(m_bd, m->dim);
m_free:
  mesh_free(m);
end:
  return errno;
}
