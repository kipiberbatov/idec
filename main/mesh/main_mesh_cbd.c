#include <errno.h>
#include <stdlib.h>
#include "mesh.h"

static void mesh_cbd_file_print(
  FILE * out, int m_dim, matrix_sparse ** m_bd, char * format)
{
  int p;
  matrix_sparse * m_bd_p_plus_1, * m_cbd_p;
  
  for (p = 0; p < m_dim; ++p)
  {
    m_bd_p_plus_1 = m_bd[p];
    m_cbd_p = matrix_sparse_transpose(m_bd_p_plus_1);
    if (errno)
    {
      perror("During matrix transposition");
      matrix_sparse_free(m_cbd_p);
      return;
    }
    matrix_sparse_file_print(out, m_cbd_p, format);
    if (errno)
    {
      perror("During matrix printing");
      matrix_sparse_free(m_cbd_p);
      return;
    }
    if (p < m_dim - 1)
      fputc('\n', out);
    matrix_sparse_free(m_cbd_p);
  }
}

int main(int argc, char * argv[])
{
  int m_dim;
  mesh * m;
  matrix_sparse ** m_bd;
  char * format;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_file_scan(in, "--raw");
  /* NULL pointer check */
  m_dim = m->dim;
  m_bd = mesh_file_scan_bd(in, m);
  /* NULL pointer check */
  format = argv[1];
  mesh_cbd_file_print(out, m_dim, m_bd, format);
  /* NULL pointer check */
  matrix_sparse_array_free(m_bd, m_dim);
  mesh_free(m);
  return 0;
}
