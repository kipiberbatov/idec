#include <errno.h>
#include <string.h>

#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_elasticity_coboundary_star_2_file_print_raw(
  FILE * out, const mesh_qc * m, const matrix_sparse * m_bd_2,
  const double * m_inner_2, const double * m_inner_1, double mu)
{
  int m_elasticity_cbd_star_2_nonzero_max;
  matrix_sparse * m_elasticity_cbd_star_2;

  m_elasticity_cbd_star_2 =
    mesh_qc_elasticity_coboundary_star_2(m, m_bd_2, m_inner_2, m_inner_1, mu);
  /* NULL pointer check */

  m_elasticity_cbd_star_2_nonzero_max
    = m_elasticity_cbd_star_2->cols_total[m_elasticity_cbd_star_2->cols];

  double_array_file_print(out, m_elasticity_cbd_star_2_nonzero_max,
                      m_elasticity_cbd_star_2->values, "--raw");

  matrix_sparse_free_shared(m_elasticity_cbd_star_2);
}

int main(int argc, char ** argv)
{
  mesh_qc * m;
  matrix_sparse ** m_bd;
  double mu;
  double ** m_inner;
  FILE * m_file;

  if (argc != 4)
  {
    errno = EINVAL;
    fprintf(stderr, "Number of command line arguments must be 4\n");
    goto end;
  }

  mu = double_string_scan(argv[1]);
  if (errno)
  {
    fputs("main: cannot scan mu\n", stderr);
    goto end;
  }

  m_file = fopen(argv[2], "r");
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

  m_inner = double_array2_file_scan_by_name(argv[3], m->dim + 1, m->cn, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m_vol\n", stderr);
    goto m_bd_free;
  }

  mesh_qc_elasticity_coboundary_star_2_file_print_raw(
    stdout, m, m_bd[1], m_inner[2], m_inner[1], mu);
  if (errno)
  {
    fputs("main - cannot calculate and print result\n", stderr);
    goto m_inner_free;
  }

m_inner_free:
  double_array2_free(m_inner, m->dim + 1);
m_bd_free:
  matrix_sparse_array_free(m_bd, m->dim);
m_free:
  mesh_free(m);
end:
  return errno;
}
