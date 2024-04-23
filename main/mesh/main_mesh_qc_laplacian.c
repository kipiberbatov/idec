#include <errno.h>
#include <string.h>

#include "mesh.h"

int main(int argc, char ** argv)
{
  mesh * m;
  matrix_sparse ** m_bd, ** m_cbd, ** m_cbd_star;
  FILE * m_file, * m_cbd_star_file;

  if (argc != 3)
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
  
  m_cbd = mesh_coboundary(m->dim, m_bd);
  if (errno)
  {
    fprintf(stderr, "main - cannot scan m_cbd\n");
    goto m_bd_free;
  }
  
  m_cbd_star_file = fopen(argv[2], "r");
  if (errno)
  {
    fprintf(stderr, "main: cannot open m_cbd_star_file: %s\n", strerror(errno));
    goto m_cbd_free;
  }

  m_cbd_star = mesh_file_scan_boundary(m_cbd_star_file, m);
  if (errno)
  {
    fputs("main: cannot scan m_cbd_star\n", stderr);
    fclose(m_cbd_star_file);
    goto m_cbd_free;
  }
  fclose(m_cbd_star_file);
  
  matrix_sparse_laplacian_file_print(stdout, m->dim, m_cbd, m_cbd_star, "--raw");
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
