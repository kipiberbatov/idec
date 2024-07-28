#include <errno.h>
#include <string.h>

#include "double.h"
#include "mesh_qc.h"

/* if only one hodge star is needed */

/*
static void mesh_qc_hodge_codifferential_p_file_print(
  FILE * out, int m_dim, int p, const matrix_sparse * m_cbd_m_dim_minus_p, matrix_sparse ** m_hodge)
{
  matrix_sparse * m_hodge_codifferential_p;

  m_hodge_codifferential_p =
    mesh_qc_hodge_codifferential_p(m_dim, p, m_cbd_m_dim_minus_p, m_hodge);
  if (errno)
  {
    fprintf(stderr, "During the calculation of *d*_%d", p);
    perror("");
    matrix_sparse_free(m_hodge_codifferential_p);
    return;
  }
  matrix_sparse_file_print_raw(out, m_hodge_codifferential_p);
  if (errno)
  {
    fprintf(stderr, "Unsuccessful printing of *d*_%d", p);
    perror("");
    matrix_sparse_free(m_hodge_codifferential_p);
    return;
  }
  matrix_sparse_free(m_hodge_codifferential_p);
}
*/

static void mesh_qc_hodge_codifferential_file_print_raw(
  FILE * out, int m_dim, matrix_sparse ** m_cbd, matrix_sparse ** m_hodge)
{
  int p;
  matrix_sparse * m_hodge_codifferential_p;

  for (p = 1; p <= m_dim; ++p)
  {
    m_hodge_codifferential_p =
      mesh_qc_hodge_codifferential_p(m_dim, p, m_cbd[m_dim - p], m_hodge);
    if (errno)
    {
      fprintf(stderr, "During the calculation of *d*_%d", p);
      perror("");
      return;
    }
    matrix_sparse_file_print(out, m_hodge_codifferential_p, "--raw");
    if (errno)
    {
      fprintf(stderr, "Unsuccessful printing of *d*_%d", p);
      perror("");
      matrix_sparse_free(m_hodge_codifferential_p);
      return;
    }
    if (p < m_dim)
      fputc('\n', out);
    matrix_sparse_free(m_hodge_codifferential_p);
  }
}

int main(int argc, char ** argv)
{
  int m_dim;
  mesh_qc * m;
  matrix_sparse ** m_bd, ** m_cbd, ** m_hodge;
  FILE * m_file;

  if (argc != 3)
  {
    errno = EINVAL;
    fprintf(stderr, "Number of command line arguments must be 3\n");
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

  m_dim = m->dim;

  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("main - cannot calculate m->fc\n", stderr);
    mesh_free(m);
    fclose(m_file);
    goto end;
  }

  m_bd = mesh_file_scan_boundary(m_file, m);
  if (errno)
  {
    fputs("main - cannot scan m_bd\n", stderr);
    mesh_free(m);
    fclose(m_file);
    goto end;
  }

  mesh_free(m);
  fclose(m_file);

  m_cbd = mesh_coboundary(m_dim, m_bd);
  if (errno)
  {
    fputs("main - cannot calculate m_cbd\n", stderr);
    matrix_sparse_array_free(m_bd, m_dim);
    goto end;
  }
  matrix_sparse_array_free(m_bd, m_dim);

  m_hodge = matrix_sparse_array_file_scan_by_name(argv[2], m_dim + 1, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m_hodge\n", stderr);
    goto m_cbd_free;
  }

  mesh_qc_hodge_codifferential_file_print_raw(stdout, m_dim, m_cbd, m_hodge);
  if (errno)
  {
    fputs("main - print hodge codifferential\n", stderr);
    goto m_hodge_free;
  }

m_hodge_free:
  matrix_sparse_array_free(m_hodge, m_dim + 1);
m_cbd_free:
  matrix_sparse_array_free(m_cbd, m_dim);
end:
  return errno;
}
