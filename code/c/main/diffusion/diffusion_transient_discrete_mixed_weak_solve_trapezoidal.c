#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double.h"
#include "diffusion_transient_discrete_mixed_weak.h"
#include "idec_command_line.h"
#include "idec_error_message.h"
#include "int.h"

static void idec_command_line_set_option_mesh_format(
  idec_command_line * option, char ** value)
{
  idec_command_line_initialize_option_string(option);
  option->name = "--mesh-format";
  option->default_argument = "--raw";
  option->arguments = (void *) value;
}

static void
idec_command_line_set_option_mesh(idec_command_line * option, char ** value)
{
  idec_command_line_initialize_option_string(option);
  option->name = "--mesh";
  option->minimal_number_of_arguments = 1;
  option->default_argument = NULL;
  option->arguments = (void *) value;
}

static void idec_command_line_set_option_mesh_inner_format(
  idec_command_line * option, char ** value)
{
  idec_command_line_initialize_option_string(option);
  option->name = "--mesh-inner-format";
  option->default_argument = "--raw";
  option->arguments = (void *) value;
}

static void idec_command_line_set_option_mesh_inner(
  idec_command_line * option, char ** value)
{
  idec_command_line_initialize_option_string(option);
  option->name = "--mesh-inner";
  option->default_argument = NULL;
  option->arguments = (void *) value;
}

static void idec_command_line_set_option_input_data(
  idec_command_line * option, char ** value)
{
  idec_command_line_initialize_option_string(option);
  option->name = "--input-data";
  option->default_argument = NULL;
  option->arguments = (void *) value;
}

static void idec_command_line_set_option_time_step(
  idec_command_line * option, double * value)
{
  idec_command_line_initialize_option_double(option);
  option->name = "--time-step";
  option->minimal_number_of_arguments = 1;
  option->default_argument = NULL;
  option->arguments = (void *) value;
}

static void idec_command_line_set_option_number_of_steps(
  idec_command_line * option, int * value)
{
  idec_command_line_initialize_option_int(option);
  option->name = "--number-of-steps";
  option->minimal_number_of_arguments = 1;
  option->default_argument = NULL;
  option->arguments = (void *) value;
}

static void idec_command_line_set_no_positional(idec_command_line * option)
{
  idec_command_line_initialize_option_no_arguments(option);
  option->name = NULL;
  option->default_argument = NULL;
  option->arguments = NULL;
}

int main(int argc, char ** argv)
{
  char * data_name, * m_inner_format, * m_inner_name, * m_format, * m_name;
  int d, m_cn_dm1, m_cn_d, number_of_steps, size, status;
  int * m_cn;
  double time_step;
  double * dual_potential, * flow;
  double ** m_inner;
  FILE * data_file, * m_file;
  matrix_sparse * m_cbd_dm1;
  matrix_sparse ** m_bd;
  mesh * m;
  diffusion_transient_discrete_mixed_weak * data;

  idec_command_line option_input_data, option_mesh, option_mesh_format,
    option_mesh_inner, option_mesh_inner_format, option_number_of_steps,
    option_time_step, positional_arguments;
  idec_command_line *(options[]) =
  {
    &option_mesh,
    &option_mesh_format,
    &option_mesh_inner,
    &option_mesh_inner_format,
    &option_input_data,
    &option_time_step,
    &option_number_of_steps,
    &positional_arguments
  };

  idec_command_line_set_option_mesh_format(
    &option_mesh_format, &m_format);
  idec_command_line_set_option_mesh(&option_mesh, &m_name);
  idec_command_line_set_option_mesh_inner_format(
    &option_mesh_inner_format, &m_inner_format);
  idec_command_line_set_option_mesh_inner(&option_mesh_inner, &m_inner_name);
  idec_command_line_set_option_input_data(&option_input_data, &data_name);
  idec_command_line_set_option_time_step(&option_time_step, &time_step);
  idec_command_line_set_option_number_of_steps(
    &option_number_of_steps, &number_of_steps);
  idec_command_line_set_no_positional(&positional_arguments);

  size = (int) (sizeof(options) / sizeof(*options));
  status = 0;
  idec_command_line_parse(options, &status, size, argc, argv);
  if (status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    return status;
  }

  if (time_step <= 0.)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "the time step is %g but it must be positive\n", time_step);
    goto end;
  }

  if (number_of_steps < 0)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of steps is %d but it must be at least 0\n",
      number_of_steps);
    goto end;
  }

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
