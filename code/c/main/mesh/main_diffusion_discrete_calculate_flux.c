#include <errno.h>
#include <stdlib.h>

#include "double.h"
#include "diffusion_discrete_calculate_flux.h"
#include "int.h"

int main(int argc, char ** argv)
{
  mesh * m;
  matrix_sparse * m_cbd = NULL;
  int i, n, number_of_steps;
  double * temperature, * flux;

  if (argc != 4)
  {
    fprintf(stderr, "Number of command line arguments should be 4\n");
    return EINVAL;
  }

  m = mesh_file_scan_by_name(argv[1], "--raw");
  if (errno)
  {
    fprintf(stderr, "Cannot scan mesh m\n");
    goto end;
  }

  number_of_steps = int_string_scan(argv[2]);
  if (errno)
  {
    fprintf(stderr, "Cannot scan number_of_steps\n");
    goto m_free;
  }

  temperature = double_array_file_scan_by_name(
    argv[3],
    m->cn[0] * (number_of_steps + 1),
    "--raw");
  if (errno)
  {
    fprintf(stderr, "Cannot scan temperature\n");
    goto m_free;
  }

  flux
  = diffusion_discrete_calculate_flux(m, m_cbd, number_of_steps, temperature);
  if (errno)
  {
    fprintf(stderr, "Cannot calculaate flux\n");
    goto temperature_free;
  }

  n = m->cn[1];
  for (i = 0; i <= number_of_steps; ++i)
  {
    double_array_file_print(stdout, n, flux + i * n, "--raw");
    fputs("\n", stdout);
  }

  free(flux);
temperature_free:
  free(temperature);
m_free:
  mesh_free(m);
end:
  return errno;
}
