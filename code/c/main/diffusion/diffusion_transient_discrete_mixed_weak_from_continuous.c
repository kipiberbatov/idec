#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "color.h"
#include "double.h"
#include "diffusion_transient_discrete_mixed_weak.h"
#include "idec_command_line.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * data_continuous_name, * error, * lib_name, * m_cbd_star_name,
       * m_format, * m_name, * m_vol_format, * m_vol_name;
  int d, size, status;
  int * m_cn;
  double ** m_vol;
  void * lib_handle;
  FILE * m_cbd_star_file;
  struct mesh * m;
  struct matrix_sparse ** m_cbd_star;
  const struct diffusion_transient_continuous * data_continuous;
  struct diffusion_transient_discrete_mixed_weak * data_discrete;

  idec_command_line no_positional_arguments, option_input_data, option_lib,
                    option_mesh, option_mesh_format,
                    option_mesh_coboundary_star, option_mesh_vol,
                    option_mesh_vol_format;

  idec_command_line *(options[]) =
  {
    &option_mesh_format,
    &option_mesh,
    &option_mesh_coboundary_star,
    &option_mesh_vol_format,
    &option_mesh_vol,
    &option_input_data,
    &option_lib,
    &no_positional_arguments
  };

  idec_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  idec_command_line_set_option_string(&option_mesh, &m_name, "--mesh", NULL);

  idec_command_line_set_option_string(&option_mesh_coboundary_star,
    &m_cbd_star_name, "--mesh-coboundary-star", NULL);

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

  m_cbd_star_file = fopen(m_cbd_star_name, "r");
  if (m_cbd_star_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open adjoint coboundary file %s: %s\n",
      m_cbd_star_name, strerror(errno));
    goto m_free;
  }

  m_cbd_star = mesh_file_scan_boundary(m_cbd_star_file, m);
  if (m_cbd_star == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan m_cbd_star\n", stderr);
    fclose(m_cbd_star_file);
    goto m_free;
  }
  fclose(m_cbd_star_file);

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
    goto m_cbd_star_free;
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

  *(const void **) (&data_continuous) = dlsym(lib_handle, data_continuous_name);
  error = dlerror();
  if (error)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    goto lib_close;
  }

  data_discrete = diffusion_transient_discrete_mixed_weak_from_continuous(
    m, m_vol[d - 1], m_vol[d], m_cbd_star[d - 1], data_continuous);
  if (data_discrete == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot discretize continuous data %s\n", stderr);
    goto lib_close;
  }

  diffusion_transient_discrete_mixed_weak_file_print_raw(
    stdout, data_discrete);

  diffusion_transient_discrete_mixed_weak_free(data_discrete);
lib_close:
  dlclose(lib_handle);
m_vol_free:
  double_array2_free(m_vol, d + 1);
m_cbd_star_free:
  matrix_sparse_array_free(m_cbd_star, d);
m_free:
  mesh_free(m);
end:
  return errno;
}
