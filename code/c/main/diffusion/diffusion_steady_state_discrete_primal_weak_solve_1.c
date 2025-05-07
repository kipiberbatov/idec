#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "diffusion_steady_state_discrete.h"
#include "diffusion_steady_state_discrete_primal_weak_solve_1.h"
#include "diffusion_steady_state_discrete_file_scan_raw.h"
#include "diffusion_steady_state_discrete_free.h"
#include "double_array.h"
#include "double_array2.h"
#include "idec_command_line.h"
#include "idec_error_message.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_inner_format, * m_inner_name, * m_format, * m_name,
       * output_format, * output_name;
  int size, status;
  int * m_cn;
  double * potential;
  double ** m_inner;
  FILE * data_file, * output_file;
  struct mesh * m;
  struct diffusion_steady_state_discrete * data;

  idec_command_line option_data_name, option_mesh_format,
    option_mesh_inner_format, option_mesh_inner_name, option_mesh_name,
    option_no_positional_arguments, option_output_format, option_output_name;

  idec_command_line *(options[]) =
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

  idec_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  idec_command_line_set_option_string(
    &option_mesh_name, &m_name, "--mesh", NULL);

  idec_command_line_set_option_string(
    &option_mesh_inner_format, &m_inner_format,
    "--mesh-inner-format", "--raw");

  idec_command_line_set_option_string(
    &option_mesh_inner_name, &m_inner_name, "--mesh-inner", NULL);

  idec_command_line_set_option_string(
    &option_data_name, &data_name, "--data", NULL);

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

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    status = errno;
    goto end;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    status = errno;
    goto m_free;
  }

  m_cn = m->cn;

  m_inner = double_array2_file_scan_by_name(
    m_inner_name, 2, m_cn, m_inner_format);
  if (m_inner == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan inner products from file %s in format %s\n",
      m_inner_name, m_inner_format);
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
    goto m_inner_free;
  }
  diffusion_steady_state_discrete_file_scan_raw(data_file, &data, &status);
  if (status)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    status = errno;
    goto m_inner_free;
  }
  fclose(data_file);

  diffusion_steady_state_discrete_primal_weak_solve_1(&potential, &status,
    m, m_inner[1], data);
  if (status)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find potential\n", stderr);
    goto data_free;
  }

  if (output_name == NULL)
    double_array_file_print(stdout, m_cn[0], potential, "--raw");
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
      goto potential_free;
    }
    double_array_file_print(output_file, m_cn[0], potential, "--raw");
    fclose(output_file);
  }

potential_free:
  free(potential);
data_free:
  diffusion_steady_state_discrete_free(data);
m_inner_free:
  double_array2_free(m_inner, 2);
m_free:
  mesh_free(m);
end:
  return status;
}
