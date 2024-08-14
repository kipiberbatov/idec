#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_metric_corrected_file_print_only_values(
  FILE * out, const mesh_qc * m, double ** m_vol, double * node_curvatures)
{
  int m_dim, p;
  int * m_cn;
  vector_sparse ** m_metric_p;

  m_dim = m->dim;
  m_cn = m->cn;

  for (p = 0; p <= m_dim; ++p)
  {
    m_metric_p = mesh_qc_metric_corrected_p(m, p, m_vol[p], node_curvatures);
    if (errno)
    {
      fprintf(stderr, "mesh_qc_metric_corrected_file_print - cannot calculate "
              "m_metric[%d]\n", p);
      return;
    }

    vector_sparse_array_file_print(out, m_cn[p], m_metric_p, "--only-values");
    if (p != m_dim)
      fputc('\n', out);
    vector_sparse_array_free(m_metric_p, m_cn[p]);
  }
}

int main(int argc, char ** argv)
{
  mesh_qc * m;
  matrix_sparse ** m_bd;
  double * node_curvatures;
  double ** m_vol;
  FILE * m_file;

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

  node_curvatures = double_array_file_scan_by_name(argv[3], m->cn[0], "--raw");
  if (errno)
  {
    fputs("main - cannot scan node_curvature\n", stderr);
    goto m_vol_free;
  }

  mesh_qc_metric_corrected_file_print_only_values(stdout, m, m_vol, node_curvatures);
  if (errno)
  {
    fputs("main - cannot print m_metric\n", stderr);
    goto node_curvatures_free;
  }

node_curvatures_free:
  free(node_curvatures);
m_vol_free:
  double_array2_free(m_vol, m->dim + 1);
m_bd_free:
  matrix_sparse_array_free(m_bd, m->dim);
m_free:
  mesh_free(m);
end:
  return errno;
}
