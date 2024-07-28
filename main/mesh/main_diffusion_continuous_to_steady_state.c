#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "diffusion_continuous.h"
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
  const diffusion_continuous * data;
  double time_step;

  if (argc != 7)
  {
    errno = EINVAL;
    fputs("main - the number of command-line arguments must be 8\n", stderr);
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  m = mesh_file_scan_by_name(m_name, m_format);
  if (errno)
  {
    fputs("main - cannot scan m\n", stderr);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("main - cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_cbd_0_name = argv[3];

  m_cbd_0 = matrix_sparse_file_scan_by_name(m_cbd_0_name, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m_cbd_0\n", stderr);
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
    fputs("main - cannot scan m_cbd_star_1\n", stderr);
    fclose(m_cbd_star_1_file);
    goto m_cbd_0_free;
  }
  fclose(m_cbd_star_1_file);


#ifdef __linux__
  lib_name ="lib/libshared.so";
#elif __APPLE__
  lib_name ="lib/libshared.dylib";
#endif
  lib_handle = dlopen(lib_name, RTLD_LAZY);
  if (!lib_handle)
  {
    fputs("main - cannot open libshared\n", stderr);
    goto m_cbd_star_1_free;
  }
  /* clear any existing errors */
  dlerror();

  data_name = argv[5];
  data = (const diffusion_continuous *) dlsym(lib_handle, data_name);
  error = dlerror();
  if (error)
  {
    fputs(error, stderr);
    fputs("\n", stderr);
    goto lib_close;
  }

  time_step = double_string_scan(argv[6]);
  if (errno)
  {
    fprintf(stderr, "Error in %s: cannot scan time_step\n", __func__);
    goto lib_close;
  }

  result = diffusion_continuous_solve_trapezoidal_method_to_steady_state(
    m,
    m_cbd_0,
    m_cbd_star_1,
    data,
    time_step,
    0.004);
  if (errno)
  {
    fputs("main - cannot calculate x\n", stderr);
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
