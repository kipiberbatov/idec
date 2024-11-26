#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double.h"
#include "diffusion_transient_discrete_primal_weak.h"
#include "int.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_inner_format, * m_inner_name, * m_format, * m_name,
       * number_of_steps_name, * time_step_name;
  int d, number_of_steps;
  int * m_cn;
  double time_step;
  double * potential;
  double ** m_inner;
  FILE * data_file;
  mesh * m;
  diffusion_transient_discrete_primal_weak * data;

#define ARGC 8
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
  m_inner_format = argv[3];
  m_inner_name = argv[4];
  data_name = argv[5];
  time_step_name = argv[6];
  number_of_steps_name = argv[7];

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n",
      m_name, m_format);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  d = m->dim;
  m_cn = m->cn;

  m_inner = double_array2_file_scan_by_name(
    m_inner_name, d + 1, m_cn, m_inner_format);
  if (m_inner == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan inner products from file %s in format %s\n",
      m_inner_name, m_inner_format);
    goto m_free;
  }

  data_file = fopen(data_name, "r");
  if (data_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem data file %s for reading: %s\n",
      data_name, strerror(errno));
    goto m_inner_free;
  }
  data = diffusion_transient_discrete_primal_weak_file_scan_raw(data_file);
  if (data == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    goto m_inner_free;
  }
  fclose(data_file);

  time_step = double_string_scan(time_step_name);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan time step from string %s\n",
      number_of_steps_name);
    goto data_free;
  }
  if (time_step <= 0.)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "the time step is %g but it must be positive\n", time_step);
    goto data_free;
  }

  number_of_steps = int_string_scan(number_of_steps_name);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan number of steps from string %s\n",
      number_of_steps_name);
    goto data_free;
  }
  if (number_of_steps < 0)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of steps is %d but it must be at least 0\n",
      number_of_steps);
    goto data_free;
  }

  potential = diffusion_transient_discrete_primal_weak_solve_trapezoidal(
    m, m_inner[0], m_inner[1], data, time_step, number_of_steps);
  if (potential == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot find potential\n", stderr);
    goto data_free;
  }

  double_matrix_file_print(
    stdout, number_of_steps + 1, m_cn[0], potential, "--raw");

  free(potential);
data_free:
  diffusion_transient_discrete_primal_weak_free(data);
m_inner_free:
  double_array2_free(m_inner, d + 1);
m_free:
  mesh_free(m);
end:
  return errno;
}
