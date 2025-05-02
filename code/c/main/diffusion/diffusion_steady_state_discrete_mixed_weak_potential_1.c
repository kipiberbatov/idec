#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "diffusion_steady_state_discrete.h"
#include "diffusion_steady_state_discrete_file_scan_raw.h"
#include "diffusion_steady_state_discrete_free.h"
#include "double_array.h"
#include "double_array2.h"
#include "idec_command_line.h"
#include "idec_error_message.h"
#include "int.h"
#include "mesh_qc.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_vol_format, * m_vol_name, * m_format, * m_name,
       * output_format, * output_name, * solution_name;
  int d, m_cn_dm1, m_cn_d, size, status;
  int * m_cn;
  double * flow_rate, * potential, * dual_potential;
  double ** m_vol;
  FILE * data_file, * m_file, * output_file, * solution_file;
  struct mesh * m;
  struct diffusion_steady_state_discrete * data;

  idec_command_line option_data_name, option_mesh_format, option_mesh_name,
    option_mesh_vol_format, option_mesh_vol_name, option_solution_name,
    option_no_positional_arguments, option_output_format, option_output_name;

  idec_command_line *(options[]) =
  {
    &option_mesh_format,
    &option_mesh_name,
    &option_mesh_vol_format,
    &option_mesh_vol_name,
    &option_data_name,
    &option_solution_name,
    &option_output_format,
    &option_output_name,
    &option_no_positional_arguments
  };

  idec_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  idec_command_line_set_option_string(
    &option_mesh_name, &m_name, "--mesh", NULL);

  idec_command_line_set_option_string(
    &option_mesh_vol_format, &m_vol_format,
    "--mesh-measures-format", "--raw");

  idec_command_line_set_option_string(
    &option_mesh_vol_name, &m_vol_name, "--mesh-measures", NULL);

  idec_command_line_set_option_string(
    &option_data_name, &data_name, "--data", NULL);

  idec_command_line_set_option_string(
    &option_solution_name, &solution_name, "--solution", NULL);

  idec_command_line_set_option_string(
    &option_output_format, &output_format, "--output-format", "--raw");

  idec_command_line_set_option_string(
    &option_output_name, &output_name, "--output", NULL);
  option_output_name.minimal_number_of_arguments = 0;

  /* there are no positional arguments */
  idec_command_line_set_option_no_arguments(
    &option_no_positional_arguments, NULL, NULL, NULL);

  size = (int) (sizeof(options) / sizeof(*options));
  status = 0;
  idec_command_line_parse(options, &status, size, argc, argv);
  if (status)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    return status;
  }

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    status = errno;
    goto end;
  }

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    status = errno;
    goto end;
  }

  d = m->dim;
  m_cn = m->cn;

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    status = errno;
    goto m_free;
  }

  m_vol = double_array2_file_scan_by_name(
    m_vol_name, d + 1, m_cn, m_vol_format);
  if (m_vol == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan cells' measures from file %s in format %s\n",
      m_vol_name, m_vol_format);
    status = errno;
    goto m_free;
  }

  data_file = fopen(data_name, "r");
  if (data_file == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem data file %s: %s\n", data_name, strerror(errno));
    status = errno;
    goto m_vol_free;
  }
  diffusion_steady_state_discrete_file_scan_raw(data_file, &data, &status);
  if (status)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    goto m_vol_free;
  }
  fclose(data_file);

  solution_file = fopen(solution_name, "r");
  if (solution_file == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem solution file %s: %s\n",
      solution_name, strerror(errno));
    status = errno;
    goto data_free;
  }
  m_cn_dm1 = int_file_scan(solution_file);
  m_cn_d = int_file_scan(solution_file);

  flow_rate = double_array_file_scan(solution_file, m_cn_dm1, "--raw");
  if (flow_rate == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan flow_rate from file in format --raw %s\n", solution_name);
    fclose(solution_file);
    status = errno;
    goto data_free;
  }
  free(flow_rate);

  dual_potential = double_array_file_scan(solution_file, m_cn_d, "--raw");
  if (dual_potential == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan dual_potential from file in format --raw %s\n",
      solution_name);
    fclose(solution_file);
    status = errno;
    goto data_free;
  }
  fclose(solution_file);

  potential = (double *) malloc(sizeof(double) * m->cn[0]);
  if (potential == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * m->cn[0], "potential");
    status = errno;
    goto dual_potential_free;
  }

  mesh_qc_hodge_star_d(potential, m, m_vol[d], dual_potential);
  double_array_assemble_from_sparse_array(
    potential, data->boundary_dirichlet_0, data->g_dirichlet);

  if (output_name == NULL)
    double_array_file_print(stdout, m->cn[0], potential, "--raw");
  else
  {
    output_file = fopen(output_name, "w");
    if (output_file == NULL)
    {
      idec_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot open output file %s: %s\n",
        output_name, strerror(errno));
      status = errno;
      goto dual_potential_free;
    }
    double_array_file_print(output_file, m->cn[0], potential, "--raw");
    fclose(output_file);
  }

  free(potential);
dual_potential_free:
  free(dual_potential);
data_free:
  diffusion_steady_state_discrete_free(data);
m_vol_free:
  double_array2_free(m_vol, d + 1);
m_free:
  mesh_free(m);
end:
  return status;
}
