#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double.h"
#include "diffusion_transient_discrete_mixed_weak.h"
#include "idec_error_message.h"
#include "int.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_inner_format, * m_inner_name, * m_format, * m_name,
       * number_of_steps_name, * time_step_name;
  int d, m_cn_dm1, m_cn_d, number_of_steps;
  int * m_cn;
  double time_step;
  double * dual_potential, * flow;
  double ** m_inner;
  FILE * data_file, * m_file;
  matrix_sparse * m_cbd_dm1;
  matrix_sparse ** m_bd;
  mesh * m;
  diffusion_transient_discrete_mixed_weak * data;

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
  m_inner_format = argv[3];
  m_inner_name = argv[4];
  data_name = argv[5];
  time_step_name = argv[6];
  number_of_steps_name = argv[7];

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    goto end;
  }

  m = mesh_file_scan(m_file, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    fclose(m_file);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_bd = mesh_file_scan_boundary(m_file, m);
  if (m_bd == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan m_bd\n", stderr);
    fclose(m_file);
    goto m_free;
  }

  fclose(m_file);

  d = m->dim;
  m_cn = m->cn;
  m_cn_dm1 = m_cn[d - 1];
  m_cn_d = m_cn[d];

  m_cbd_dm1 = matrix_sparse_transpose(m_bd[d - 1]);
  if (m_cbd_dm1 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_bd_free;
  }

  m_inner = double_array2_file_scan_by_name(
    m_inner_name, d + 1, m_cn, m_inner_format);
  if (m_inner == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan inner products from file %s in format %s\n",
      m_inner_name, m_inner_format);
    goto m_cbd_dm1_free;
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
  data = diffusion_transient_discrete_mixed_weak_file_scan_raw(data_file);
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

  flow = (double *) malloc(sizeof(double) * (number_of_steps + 1) * m_cn_dm1);
  if (flow == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * (number_of_steps + 1) * m_cn_dm1,
      "flow");
    goto data_free;
  }

  dual_potential = (double *) malloc(
    sizeof(double) * (number_of_steps + 1) * m_cn_d);
  if (dual_potential == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * (number_of_steps + 1) * m_cn_d,
      "dual_potential");
    goto flow_free;
  }

  diffusion_transient_discrete_mixed_weak_solve_trapezoidal(
    flow, dual_potential,
    m, m_cbd_dm1, m_inner[d - 1], m_inner[d], data, time_step, number_of_steps);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot find flow and dual_potential\n", stderr);
    goto dual_potential_free;
  }

  double_matrix_file_print(
    stdout, number_of_steps + 1, m_cn_dm1, flow, "--raw");
  fputc('\n', stdout);
  double_matrix_file_print(
    stdout, number_of_steps + 1, m_cn_d, dual_potential, "--raw");

dual_potential_free:
  free(dual_potential);
flow_free:
  free(flow);
data_free:
  diffusion_transient_discrete_mixed_weak_free(data);
m_inner_free:
  double_array2_free(m_inner, d + 1);
m_cbd_dm1_free:
  matrix_sparse_free(m_cbd_dm1);
m_bd_free:
  matrix_sparse_array_free(m_bd, d);
m_free:
  mesh_free(m);
end:
  return errno;
}
