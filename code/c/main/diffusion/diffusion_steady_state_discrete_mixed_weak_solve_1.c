#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "diffusion_steady_state_discrete.h"
#include "diffusion_steady_state_discrete_mixed_weak_solve_1.h"
#include "diffusion_steady_state_discrete_file_scan_raw.h"
#include "diffusion_steady_state_discrete_free.h"
#include "double_array.h"
#include "double_array2.h"
#include "cmc_command_line.h"
#include "cmc_error_message.h"
#include "mesh.h"

static void print_solution(
  FILE * out,
  int m_cn_dm1, int m_cn_d,
  const double * flow_rate, const double * dual_potential)
{
  fprintf(out, "%d\n", m_cn_dm1);
  fprintf(out, "%d\n", m_cn_d);
  double_array_file_print(out, m_cn_dm1, flow_rate, "--raw");
  double_array_file_print(out, m_cn_d, dual_potential, "--raw");
}

int main(int argc, char ** argv)
{
  char * data_name, * m_inner_format, * m_inner_name, * m_format, * m_name,
       * output_format, * output_name;
  int d, size, status;
  int * m_cn;
  double * flow_rate, * dual_potential;
  double ** m_inner;
  FILE * data_file, * m_file, * output_file;
  struct matrix_sparse * m_cbd_dm1;
  struct matrix_sparse ** m_bd;
  struct mesh * m;
  struct diffusion_steady_state_discrete * data;

  cmc_command_line option_data_name, option_mesh_format,
    option_mesh_inner_format, option_mesh_inner_name, option_mesh_name,
    option_no_positional_arguments, option_output_format, option_output_name;

  cmc_command_line *(options[]) =
  {
    &option_mesh_format,
    &option_mesh_name,
    &option_mesh_inner_format,
    &option_mesh_inner_name,
    &option_data_name,
    &option_output_format,
    &option_output_name,
    &option_no_positional_arguments
  };

  cmc_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  cmc_command_line_set_option_string(
    &option_mesh_name, &m_name, "--mesh", NULL);

  cmc_command_line_set_option_string(
    &option_mesh_inner_format, &m_inner_format,
    "--mesh-inner-format", "--raw");

  cmc_command_line_set_option_string(
    &option_mesh_inner_name, &m_inner_name, "--mesh-inner", NULL);

  cmc_command_line_set_option_string(
    &option_data_name, &data_name, "--data", NULL);

  cmc_command_line_set_option_string(
    &option_output_format, &output_format, "--output-format", "--raw");

  cmc_command_line_set_option_string(
    &option_output_name, &output_name, "--output", NULL);
  option_output_name.minimal_number_of_arguments = 0;

  /* there are no positional arguments */
  cmc_command_line_set_option_no_arguments(
    &option_no_positional_arguments, NULL, NULL, NULL);

  size = (int) (sizeof(options) / sizeof(*options));
  status = 0;
  cmc_command_line_parse(options, &status, size, argc, argv);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    return status;
  }

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    goto end;
  }

  m = mesh_file_scan(m_file, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    fclose(m_file);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_bd = mesh_file_scan_boundary(m_file, m);
  if (m_bd == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_bd\n", stderr);
    fclose(m_file);
    goto m_free;
  }

  fclose(m_file);

  d = m->dim;
  m_cn = m->cn;

  m_cbd_dm1 = matrix_sparse_transpose(m_bd[d - 1]);
  if (m_cbd_dm1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_cbd_dm1\n", stderr);
    status = errno;
    goto m_bd_free;
  }

  m_inner = double_array2_file_scan_by_name(
    m_inner_name, d + 1, m_cn, m_inner_format);
  if (m_inner == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan inner products from file %s in format %s\n",
      m_inner_name, m_inner_format);
    status = errno;
    goto m_cbd_dm1_free;
  }

  data_file = fopen(data_name, "r");
  if (data_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem data file %s: %s\n", data_name, strerror(errno));
    status = errno;
    goto m_inner_free;
  }
  diffusion_steady_state_discrete_file_scan_raw(data_file, &data, &status);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    status = errno;
    goto m_inner_free;
  }
  fclose(data_file);

  flow_rate = (double *) malloc(sizeof(double) * m->cn[d - 1]);
  if (flow_rate == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[d - 1], "flow_rate");
    status = errno;
    goto data_free;
  }

  dual_potential = (double *) malloc(sizeof(double) * m->cn[d]);
  if (dual_potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[d], "dual_potential");
    status = errno;
    goto flow_rate_free;
  }

  diffusion_steady_state_discrete_mixed_weak_solve_1(
    flow_rate, dual_potential, m, m_cbd_dm1, m_inner[d - 1], m_inner[d], data);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find flow_rate and potential\n", stderr);
    status = errno;
    goto dual_potential_free;
  }
  if (output_name == NULL)
    print_solution(stdout, m->cn[d - 1], m->cn[d], flow_rate, dual_potential);
  else
  {
    output_file = fopen(output_name, "w");
    if (output_file == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot open output file %s: %s\n",
        output_name, strerror(errno));
      status = errno;
      goto dual_potential_free;
    }
    print_solution(output_file,
      m->cn[d - 1], m->cn[d], flow_rate, dual_potential);
    fclose(output_file);
  }

dual_potential_free:
  free(dual_potential);
flow_rate_free:
  free(flow_rate);
data_free:
  diffusion_steady_state_discrete_free(data);
m_inner_free:
  double_array2_free(m_inner, d + 1);
m_cbd_dm1_free:
  matrix_sparse_free(m_cbd_dm1);
m_bd_free:
  matrix_sparse_array_free(m_bd, d);
m_free:
  mesh_free(m);
end:
  return status;
}
