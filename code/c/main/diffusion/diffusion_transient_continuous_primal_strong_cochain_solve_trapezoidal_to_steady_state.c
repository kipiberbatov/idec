#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "color.h"
#include "diffusion_transient_continuous.h"
#include "int.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * error, * data_name, * lib_name;
  char * m_format, * m_name;
  char * m_cbd_0_name;
  char * m_cbd_star_1_name;
  FILE * m_cbd_star_1_file;
  double_array_sequence_dynamic * result;

  mesh * m;
  matrix_sparse * m_cbd_0, * m_cbd_star_1;
  void * lib_handle;
  const diffusion_transient_continuous * data;
  double time_step;

  if (argc != 8)
  {
    errno = EINVAL;
    color_error_position(__FILE__, __LINE__);
    fputs("the number of command-line arguments must be 8\n", stderr);
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  m = mesh_file_scan_by_name(m_name, m_format);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan m\n", stderr);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_cbd_0_name = argv[3];

  m_cbd_0 = matrix_sparse_file_scan_by_name(m_cbd_0_name, "--raw");
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan m_cbd_0\n", stderr);
    goto m_free;
  }

  m_cbd_star_1_name = argv[4];

  m_cbd_star_1_file = fopen(m_cbd_star_1_name, "r");
  if (errno)
  {
    fprintf(stderr, "Cannot open file %s\n", m_cbd_star_1_name);
    goto m_cbd_0_free;
  }
  m_cbd_star_1 = mesh_file_scan_boundary_p(m_cbd_star_1_file, m, 1);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan m_cbd_star_1\n", stderr);
    fclose(m_cbd_star_1_file);
    goto m_cbd_0_free;
  }
  fclose(m_cbd_star_1_file);


  lib_name = argv[5];
  lib_handle = dlopen(lib_name, RTLD_LAZY);
  if (!lib_handle)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot open libshared\n", stderr);
    goto m_cbd_star_1_free;
  }
  /* clear any existing errors */
  dlerror();

  data_name = argv[6];
  data = (const diffusion_transient_continuous *) dlsym(lib_handle, data_name);
  error = dlerror();
  if (error)
  {
    fputs(error, stderr);
    fputs("\n", stderr);
    goto lib_close;
  }

  time_step = double_string_scan(argv[7]);
  if (errno)
  {
    fprintf(stderr, "Error in %s: cannot scan time_step\n", __func__);
    goto lib_close;
  }

  result = diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal_to_steady_state(
    m,
    m_cbd_0,
    m_cbd_star_1,
    data,
    time_step,
    0.004);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate x\n", stderr);
    goto lib_close;
  }
  double_array_sequence_dynamic_file_print(stdout, result);

  double_array_sequence_dynamic_free(result);
lib_close:
  dlclose(lib_name);
m_cbd_star_1_free:
  matrix_sparse_free(m_cbd_star_1);
m_cbd_0_free:
  matrix_sparse_free(m_cbd_0);
m_free:
  mesh_free(m);
end:
  return errno;
}
