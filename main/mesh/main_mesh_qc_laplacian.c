#include <errno.h>
#include <string.h>
#include "mesh.h"

int main()
{
  mesh * m;
  matrix_sparse ** m_bd, ** m_cbd, ** m_cbd_star;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  
  m = mesh_file_scan(in, "--raw");
  if (errno)
  {
    fprintf(stderr, "main - cannot scan m\n");
    goto end;
  }
  
  m_bd = mesh_file_scan_boundary(in, m);
  if (errno)
  {
    fprintf(stderr, "main - cannot scan m_bd\n");
    goto m_free;
  }
  
  m_cbd = mesh_coboundary(m->dim, m_bd);
  if (errno)
  {
    fprintf(stderr, "main - cannot scan m_cbd\n");
    goto m_bd_free;
  }
  
  m_cbd_star = mesh_file_scan_boundary(in, m);
  if (errno)
  {
    fprintf(stderr, "main - cannot scan m_cbd_star\n");
    goto m_cbd_free;
  }
  
  matrix_sparse_laplacian_file_print(out, m->dim, m_cbd, m_cbd_star, "--raw");
  if (errno)
  {
    fprintf(stderr, "main - cannot print m_laplacian\n");
    goto m_cbd_star_free;
  }

m_cbd_star_free:
  matrix_sparse_array_free(m_cbd_star, m->dim);
m_cbd_free:
  matrix_sparse_array_free(m_cbd, m->dim);
m_bd_free:
  matrix_sparse_array_free(m_bd, m->dim);
m_free:
  mesh_free(m);
end:
  return errno;
}
