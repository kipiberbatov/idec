#include <errno.h>
#include <stdlib.h>
#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_hodge_file_print_raw(
  FILE * out, const mesh_qc * m, matrix_sparse ** m_bd,
  double ** m_inner, double ** m_coeff)
{
  int m_dim, p, q;
  matrix_sparse * m_hodge_p;
  
  m_dim = m->dim;
  for (p = 0; p <= m_dim; ++p)
  {
    q = m_dim - p;
    m_hodge_p = mesh_qc_hodge_p(m, m_bd, p, m_inner[q], m_coeff[q]);
    if (errno)
    {
      fprintf(stderr,
              "mesh_qc_hodge_file_print - cannot calculate m_hodge[%d]\n", p);
      return;
    }
    matrix_sparse_file_print(out, m_hodge_p, "--raw");
    if (p != m_dim)
      fputc('\n', out);
    free(m_hodge_p);
  }
}

int main()
{
  mesh_qc * m;
  matrix_sparse ** m_bd;
  double ** m_inner, ** m_coeff;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  
  m = mesh_file_scan(in, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m\n", stderr);
    goto end;
  }
  
  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("main - cannot calculate m->fc\n", stderr);
    goto m_free;
  }
  
  m_bd = mesh_file_scan_bd(in, m);
  if (errno)
  {
    fputs("main - cannot scan m->bd\n", stderr);
    goto m_free;
  }
  
  m_inner = double_array2_file_scan(in, m->dim + 1, m->cn, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m_inner\n", stderr);
    goto m_bd_free;
  }
  
  m_coeff = double_array2_file_scan(in, m->dim + 1, m->cn, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m_coeff\n", stderr);
    goto m_inner_free;
  }
  
  mesh_qc_hodge_file_print_raw(out, m, m_bd, m_inner, m_coeff);
  if (errno)
  {
    fputs("main - cannot calculate and print m_hodge\n", stderr);
    goto m_coeff_free;
  }

m_coeff_free:
  double_array2_free(m_coeff, m->dim + 1);
m_inner_free:
  double_array2_free(m_inner, m->dim + 1);
m_bd_free:
  matrix_sparse_array_free(m_bd, m->dim);
m_free:
  mesh_free(m);
end:
  return errno;
}
