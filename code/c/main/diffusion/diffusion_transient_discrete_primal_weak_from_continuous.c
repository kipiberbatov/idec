#include <errno.h>
#include <stdlib.h>

#include <dlfcn.h>

#include "color.h"
#include "double.h"
#include "diffusion_transient_discrete_primal_weak.h"
#include "idec_command_line.h"

int main(int argc, char ** argv)
{
  char * data_continuous_name, * error, * lib_name, * m_format, * m_name,
       * m_vol_format, * m_vol_name;
  int d, size, status;
  int * m_cn;
  double ** m_vol;
  void * lib_handle;
  mesh * m;
  const diffusion_transient_continuous * data_continuous;
  diffusion_transient_discrete_primal_weak * data_discrete;

  idec_command_line no_positional_arguments, option_input_data, option_lib,
                    option_mesh, option_mesh_format, option_mesh_vol,
                    option_mesh_vol_format;

  idec_command_line *(options[]) =
  {
    &option_mesh_format,
    &option_mesh,
    &option_mesh_vol_format,
    &option_mesh_vol,
    &option_input_data,
    &option_lib,
    &no_positional_arguments
  };

  idec_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  idec_command_line_set_option_string(&option_mesh, &m_name, "--mesh", NULL);

  idec_command_line_set_option_string(
    &option_mesh_vol_format, &m_vol_format, "--mesh-volumes-format", "--raw");

  idec_command_line_set_option_string(
    &option_mesh_vol, &m_vol_name, "--mesh-volumes", NULL);

  idec_command_line_set_option_string(
    &option_input_data, &data_continuous_name, "--input-data", NULL);

  idec_command_line_set_option_string(
    &option_lib, &lib_name, "--dynamic-library", NULL);

  /* there are no positional arguments */
  idec_command_line_set_option_no_arguments(
    &no_positional_arguments, NULL, NULL, NULL);

  size = (int) (sizeof(options) / sizeof(*options));
  status = 0;
  idec_command_line_parse(options, &status, size, argc, argv);
  if (status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    return status;
  }

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    goto end;
  }

  d = m->dim;
  m_cn = m->cn;

  m_vol = double_array2_file_scan_by_name(
    m_vol_name, d + 1, m_cn, m_vol_format);
  if (m_vol == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan measures m_vol from file %s in format %s\n",
      m_vol_name, m_vol_format);
    goto m_free;
  }

  lib_handle = dlopen(lib_name, RTLD_LAZY);
  if (lib_handle == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open dynamic library %s\n", lib_name);
    goto m_vol_free;
  }
  /* clear any existing errors */
  dlerror();

  data_continuous = (const diffusion_transient_continuous *) dlsym(
    lib_handle, data_continuous_name);
  error = dlerror();
  if (error)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    goto lib_close;
  }

  data_discrete = diffusion_transient_discrete_primal_weak_from_continuous(
    m, m_vol[d - 1], m_vol[d], data_continuous);
  if (data_discrete == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot discretize continuous data %s\n", stderr);
    goto lib_close;
  }

  diffusion_transient_discrete_primal_weak_file_print_raw(
    stdout, data_discrete);

  diffusion_transient_discrete_primal_weak_free(data_discrete);
lib_close:
  dlclose(lib_handle);
m_vol_free:
  double_array2_free(m_vol, d + 1);
m_free:
  mesh_free(m);
end:
  return errno;
}
