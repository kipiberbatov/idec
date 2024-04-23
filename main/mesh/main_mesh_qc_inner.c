#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "mesh_qc.h"
#include "vector_sparse.h"

static void mesh_qc_inner_file_print_raw(
  FILE * out, const mesh_qc * m,
  const double * m_vol_d, vector_sparse *** m_metric)
{
  int m_dim, p;
  int * m_cn;
  double * m_inner_p;
  
  m_dim = m->dim;
  m_cn = m->cn;
  for (p = 0; p <= m_dim; ++p)
  {
    m_inner_p = mesh_qc_inner_p(m, m_vol_d, p, m_metric[p]);
    if (errno)
    {
      fprintf(stderr,
              "mesh_qc_inner_file_print - cannot calculate m_inner[%d]\n", p);
      return;
    }
    
    double_array_file_print(out, m_cn[p], m_inner_p, "--raw");
    if (p != m_dim)
      fputc('\n', out);
    
    free(m_inner_p);
  }
}

int main(int argc, char ** argv)
{
  mesh_qc * m;
  matrix_sparse ** m_bd;
  double ** m_vol;
  vector_sparse *** m_metric;
  FILE * m_file, * m_metric_file;

  if (argc != 4)
  {
    errno = EINVAL;
    fprintf(stderr, "Number of command line arguments must be 4\n");
    goto end;
  }
  
  m_file = fopen(argv[1], "r");
  if (errno)
  {
    fprintf(stderr, "Cannot open mesh file: %s\n", strerror(errno));
    goto end;
  }

  m = mesh_file_scan(m_file, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m\n", stderr);
    fclose(m_file);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("main - cannot calculate m->fc\n", stderr);
    fclose(m_file);
    goto m_free;
  }
  
  m_bd = mesh_file_scan_boundary(m_file, m);
  if (errno)
  {
    fputs("main - cannot scan m_bd\n", stderr);
    fclose(m_file);
    goto m_free;
  }
  
  fclose(m_file);
  
  m_vol = double_array2_file_scan_by_name(argv[2], m->dim + 1, m->cn, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m_vol\n", stderr);
    goto m_bd_free;
  }
  
  m_metric_file = fopen(argv[3], "r");
  if (errno)
  {
    fprintf(stderr, "Cannot open mesh file: %s\n", strerror(errno));
    goto m_vol_free;
  }
  
  m_metric = mesh_qc_metric_file_scan(m_metric_file, m);
  if (errno)
  {
    fputs("main - cannot scan m_metric\n", stderr);
    fclose(m_metric_file);
    goto m_vol_free;
  }

  fclose(m_metric_file);
  
  mesh_qc_inner_file_print_raw(stdout, m, m_vol[m->dim], m_metric);
  if (errno)
  {
    fputs("main - cannot print m_inner\n", stderr);
    goto m_metric_free;
  }

m_metric_free:
  vector_sparse_array2_free(m_metric, m->dim + 1, m->cn);
m_vol_free:
  double_array2_free(m_vol, m->dim + 1);
m_bd_free:
  matrix_sparse_array_free(m_bd, m->dim);
m_free:
  mesh_free(m);
end:
  return errno;
}
