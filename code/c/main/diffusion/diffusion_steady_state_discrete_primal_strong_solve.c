#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "color.h"
#include "double.h"
#include "diffusion_steady_state_discrete_primal_strong.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_cbd_0_name, * m_cbd_star_1_name, * m_format, * m_name;
  double * potential;
  FILE * data_file, * m_cbd_star_1_file;
  matrix_sparse * m_cbd_0, * m_cbd_star_1;
  mesh * m;
  diffusion_steady_state_discrete_primal_strong * data;

#define ARGC 6
  if (argc != ARGC)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of command-line arguments must be %d; instead it is %d\n",
      ARGC, argc);
    errno = EINVAL;
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  m_cbd_0_name = argv[3];
  m_cbd_star_1_name = argv[4];
  data_name = argv[5];

  m = mesh_file_scan_by_name(m_name, m_format);
  if (errno)
  {
    fputs("  main: cannot scan m\n", stderr);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("  main: cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_cbd_0 = matrix_sparse_file_scan_by_name(m_cbd_0_name, "--raw");
  if (errno)
  {
    fputs("  main: cannot scan m_cbd_0\n", stderr);
    goto m_free;
  }

  m_cbd_star_1_file = fopen(m_cbd_star_1_name, "r");
  if (errno)
  {
    fputs("Runtime error stack trace:\n", stderr);
    fprintf(stderr, "  main: cannot open file %s\n", m_cbd_star_1_name);
    goto m_cbd_0_free;
  }
  m_cbd_star_1 = mesh_file_scan_boundary_p(m_cbd_star_1_file, m, 1);
  if (errno)
  {
    fputs("  main: cannot scan m_cbd_star_1\n", stderr);
    fclose(m_cbd_star_1_file);
    goto m_cbd_0_free;
  }
  fclose(m_cbd_star_1_file);

  data_file = fopen(data_name, "r");
  if (data_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem data file %s: %s\n", data_name, strerror(errno));
    goto m_cbd_star_1_free;
  }
  data = diffusion_steady_state_discrete_primal_strong_file_scan_raw(data_file);
  if (data == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    goto m_cbd_star_1_free;
  }
  fclose(data_file);

  potential = diffusion_steady_state_discrete_primal_strong_solve(
    m, m_cbd_0, m_cbd_star_1, data);
  if (potential == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate potential\n", stderr);
    goto data_free;
  }

  double_array_file_print(stdout, m->cn[0], potential, "--raw");

  free(potential);
data_free:
  diffusion_steady_state_discrete_primal_strong_free(data);
m_cbd_star_1_free:
  matrix_sparse_free(m_cbd_star_1);
m_cbd_0_free:
  matrix_sparse_free(m_cbd_0);
m_free:
  mesh_free(m);
end:
  return errno;
}
