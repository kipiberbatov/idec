#include <errno.h>
#include "double.h"
#include "forman.h"

static void mesh_boundary_file_print_raw(FILE * out, int m_dim, matrix_sparse ** m_bd)
{
  int m_bd_p_nonzero_max, p;
  const matrix_sparse * m_bd_p;

  for (p = 1; p <= m_dim; ++p)
  {
    m_bd_p = m_bd[p - 1];
    m_bd_p_nonzero_max = m_bd_p->cols_total[m_bd_p->cols];
    double_array_file_print(out, m_bd_p_nonzero_max, m_bd_p->values, "--raw");
  }
}

static void forman_boundary_file_print_raw(
  FILE * out, const mesh * m, matrix_sparse ** m_bd)
{
  mesh * m_forman;
  matrix_sparse ** m_forman_boundary;
  
  m_forman = forman(m);
  if (errno)
  {
    fputs("forman_boundary_file_print - cannot calculate m_forman\n", stderr);
    goto end;
  }
  mesh_file_print(out, m_forman, "--raw");
  
  m_forman_boundary = forman_boundary(m, m_forman, m_bd);
  if (errno)
  {
    fputs("forman_boundary_file_print - cannot calculate m_forman->bd\n", stderr);
    goto m_forman_free;
  }
  
  mesh_boundary_file_print_raw(out, m->dim, m_forman_boundary);
  
  matrix_sparse_array_free(m_forman_boundary, m->dim);
m_forman_free:
  mesh_free(m_forman);
end:
  return;
}

int main()
{
  mesh * m;
  matrix_sparse ** m_bd;
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
  
  m_bd = mesh_file_scan_boundary(in, m);
  if (errno)
  {
    fputs("main - cannot calculate m->bd\n", stderr);
    goto m_free;
  }
  
  forman_boundary_file_print_raw(out, m, m_bd);
  if (errno)
  {
    fputs("main - cannot calculate and print m_forman->bd\n", stderr);
    goto m_bd_free;
  }
  
m_bd_free:
  matrix_sparse_array_free(m_bd, m->dim);
m_free:
  mesh_free(m);
end:
  return errno;
}
