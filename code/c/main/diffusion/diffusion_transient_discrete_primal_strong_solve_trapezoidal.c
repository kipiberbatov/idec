#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "color.h"
#include "double.h"
#include "diffusion_transient_discrete_primal_strong.h"
#include "idec_error_message.h"
#include "int.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_cbd_0_name, * m_cbd_star_1_name, * m_format, * m_name,
       * number_of_steps_name, * time_step_name;
  int number_of_steps;
  double time_step;
  double * potential;
  FILE * data_file, * m_cbd_star_1_file;
  matrix_sparse * m_cbd_0, * m_cbd_star_1;
  mesh * m;
  diffusion_transient_discrete_primal_strong * data;

#define ARGC 8
  if (argc != ARGC)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    errno = EINVAL;
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  m_cbd_0_name = argv[3];
  m_cbd_star_1_name = argv[4];
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

  m_cbd_0 = matrix_sparse_file_scan_by_name(m_cbd_0_name, "--raw");
  if (m_cbd_0 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan m_cbd[0] from file %s in format %s\n",
      m_cbd_0_name, "--raw");
    goto m_free;
  }

  m_cbd_star_1_file = fopen(m_cbd_star_1_name, "r");
  if (m_cbd_star_1_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open file %s: %s\n",
      m_cbd_star_1_name, strerror(errno));
    goto m_cbd_0_free;
  }
  m_cbd_star_1 = mesh_file_scan_boundary_p(m_cbd_star_1_file, m, 1);
  if (m_cbd_star_1 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan m_cbd_star_1 from file %s\n",
      m_cbd_star_1_name);
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
  data = diffusion_transient_discrete_primal_strong_file_scan_raw(data_file);
  if (data == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    goto m_cbd_star_1_free;
  }
  fclose(data_file);

  time_step = double_string_scan(time_step_name);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan time step from string %s\n", number_of_steps_name);
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
      "cannot scan number of steps from string %s\n", number_of_steps_name);
    goto data_free;
  }
  if (number_of_steps < 0)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of steps is %d but it must be at least 0\n", number_of_steps);
    goto data_free;
  }

  potential = diffusion_transient_discrete_primal_strong_solve_trapezoidal(
    m, m_cbd_0, m_cbd_star_1, data, time_step, number_of_steps);
  if (potential == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate potential\n", stderr);
    goto data_free;
  }

  double_matrix_file_print(
    stdout, number_of_steps + 1, m->cn[0], potential, "--raw");

  free(potential);
data_free:
  diffusion_transient_discrete_primal_strong_free(data);
m_cbd_star_1_free:
  matrix_sparse_free(m_cbd_star_1);
m_cbd_0_free:
  matrix_sparse_free(m_cbd_0);
m_free:
  mesh_free(m);
end:
  return errno;
}
