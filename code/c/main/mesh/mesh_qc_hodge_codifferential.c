#include <errno.h>
#include <string.h>

#include "color.h"
#include "double.h"
#include "mesh_qc.h"

/* if only one hodge star is needed */

/*
static void mesh_qc_hodge_codifferential_p_file_print(
  FILE * out, int d, int p, const matrix_sparse * m_cbd_d_minus_p, matrix_sparse ** m_hodge)
{
  matrix_sparse * m_hodge_codifferential_p;

  m_hodge_codifferential_p =
    mesh_qc_hodge_codifferential_p(d, p, m_cbd_d_minus_p, m_hodge);
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
  FILE * out, int d, matrix_sparse ** m_cbd, matrix_sparse ** m_hodge)
{
  int p;
  matrix_sparse * m_hodge_codifferential_p;

  for (p = 1; p <= d; ++p)
  {
    m_hodge_codifferential_p =
      mesh_qc_hodge_codifferential_p(d, p, m_cbd[d - p], m_hodge);
    if (errno)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr, "cannot calculate *d*_%d", p);
      return;
    }
    matrix_sparse_file_print(out, m_hodge_codifferential_p, "--raw");
    if (errno)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr, "cannot print of *d*_%d", p);
      matrix_sparse_free(m_hodge_codifferential_p);
      return;
    }
    if (p < d)
      fputc('\n', out);
    matrix_sparse_free(m_hodge_codifferential_p);
  }
}

int main(int argc, char ** argv)
{
  int d;
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
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", argv[1], strerror(errno));
    goto end;
  }

  m = mesh_file_scan(m_file, "--raw");
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan m\n", stderr);
    fclose(m_file);
    goto end;
  }

  d = m->dim;

  m->fc = mesh_fc(m);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    mesh_free(m);
    fclose(m_file);
    goto end;
  }

  m_bd = mesh_file_scan_boundary(m_file, m);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan m_bd\n", stderr);
    mesh_free(m);
    fclose(m_file);
    goto end;
  }

  mesh_free(m);
  fclose(m_file);

  m_cbd = mesh_coboundary(d, m_bd);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m_cbd\n", stderr);
    matrix_sparse_array_free(m_bd, d);
    goto end;
  }
  matrix_sparse_array_free(m_bd, d);

  m_hodge = matrix_sparse_array_file_scan_by_name(argv[2], d + 1, "--raw");
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan m_hodge\n", stderr);
    goto m_cbd_free;
  }

  mesh_qc_hodge_codifferential_file_print_raw(stdout, d, m_cbd, m_hodge);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("print hodge codifferential\n", stderr);
    goto m_hodge_free;
  }

m_hodge_free:
  matrix_sparse_array_free(m_hodge, d + 1);
m_cbd_free:
  matrix_sparse_array_free(m_cbd, d);
end:
  return errno;
}
