#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "double.h"
#include "diffusion_transient_continuous.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * data_name, * error, * lib_name, * m_format, * m_inner_format,
       * m_inner_name, * m_name, * m_vol_format, * m_vol_name,
       * tolerance_name, * time_step_name;
  int d, i;
  double time_step, tolerance;
  double_array_sequence_dynamic * result;
  double ** m_inner, ** m_vol;
  void * lib_handle;
  mesh * m;
  const diffusion_transient_continuous * data;

#define ARGC 11
  if (argc != ARGC)
  {
    fprintf(stderr,
      "%s:%d: number of command line arguments should be %d, not %d\n",
      __FILE__, __LINE__, ARGC, argc);
    fputs("Your command line arguments:\n", stderr);
    for (i = 0; i < argc; ++i)
      fprintf(stderr, "%d: %s\n", i, argv[i]);
    return EINVAL;
  }

  m_format = argv[1];
  m_name = argv[2];
  m_vol_format = argv[3];
  m_vol_name = argv[4];
  m_inner_format = argv[5];
  m_inner_name = argv[6];
  lib_name = argv[7];
  data_name = argv[8];
  time_step_name = argv[9];
  tolerance_name = argv[10];

  m = mesh_file_scan_by_name(m_name, m_format);
  if (errno)
  {
    fputs("  main: cannot scan m\n", stderr);
    goto end;
  }
  d = m->dim;

  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("  main: cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_vol = double_array2_file_scan_by_name(
    m_vol_name, d + 1, m->cn, m_vol_format);
  if (errno)
  {
    fprintf(stderr, "%s:%d: cannot scan m_vol from file %s in format %s\n",
      __FILE__, __LINE__, m_vol_name, m_vol_format);
    goto m_free;
  }

  m_inner = double_array2_file_scan_by_name(
    m_inner_name, d + 1, m->cn, m_inner_format);
  if (errno)
  {
    fprintf(stderr, "%s:%d: cannot scan m_inner from file %s in format %s\n",
      __FILE__, __LINE__, m_inner_name, m_inner_format);
    goto m_vol_free;
  }

  lib_handle = dlopen(lib_name, RTLD_LAZY);
  if (!lib_handle)
  {
    fputs("Runtime error stack trace:\n", stderr);
    fputs("  main: cannot open libshared\n", stderr);
    goto m_inner_free;
  }
  /* clear any existing errors */
  dlerror();

  data = (const diffusion_transient_continuous *) dlsym(lib_handle, data_name);
  error = dlerror();
  if (error)
  {
    fputs(error, stderr);
    fputs("\n", stderr);
    goto lib_close;
  }

  time_step = double_string_scan(time_step_name);
  if (errno)
  {
    fputs("  main: cannot scan time_step\n", stderr);
    goto lib_close;
  }

  if (time_step <= 0)
  {
    fputs("  main: error: time step must be a positive real number\n", stderr);
    goto lib_close;
  }

  tolerance = double_string_scan(tolerance_name);
  if (errno)
  {
    fputs("  main: cannot scan tolerance\n", stderr);
    goto lib_close;
  }

  if (tolerance <= 0)
  {
    fputs("  main: error: tolerance must be a positive real number\n", stderr);
    goto lib_close;
  }


  result
  = diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal_to_steady_state(
    m,
    m_vol[d - 1],
    m_vol[d],
    m_inner[0],
    m_inner[1],
    data,
    time_step,
    tolerance);
  if (errno)
  {
    fputs("  main: cannot calculate result\n", stderr);
    goto lib_close;
  }

  double_array_sequence_dynamic_file_print(stdout, result);

  double_array_sequence_dynamic_free(result);
lib_close:
  dlclose(lib_name);
m_inner_free:
  double_array2_free(m_inner, d + 1);
m_vol_free:
  double_array2_free(m_vol, d + 1);
m_free:
  mesh_free(m);
end:
  return errno;
}
