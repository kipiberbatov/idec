#include <errno.h>
#include <stdlib.h>

#include <dlfcn.h>

#include "double.h"
#include "diffusion_steady_state_continuous.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * error, * data_name, * lib_name;
  char * m_format, * m_name;
  char * m_inner_name;
  char * m_vol_name;
  double * result;

  double ** m_inner, ** m_vol;
  mesh * m;
  void * lib_handle;
  const diffusion_steady_state_continuous * data;

  if (argc != 7)
  {
    errno = EINVAL;
    fputs("Runtime error stack trace:\n", stderr);
    fputs("  main: the number of command-line arguments must be 8\n", stderr);
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  m = mesh_file_scan_by_name(m_name, m_format);
  if (errno)
  {
    fputs("  main: cannot scan m\n", stderr);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("  main: cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_vol_name = argv[3];
  m_vol = double_array2_file_scan_by_name(
    m_vol_name, m->dim + 1, m->cn, "--raw");
  if (errno)
  {
    fputs("  main: cannot scan m_vol\n", stderr);
    goto m_free;
  }

  m_inner_name = argv[4];
  m_inner = double_array2_file_scan_by_name(
    m_inner_name, m->dim + 1, m->cn, "--raw");
  if (errno)
  {
    fputs("  main: cannot scan m_vol\n", stderr);
    goto m_vol_free;
  }

  lib_name = argv[5];
  lib_handle = dlopen(lib_name, RTLD_LAZY);
  if (!lib_handle)
  {
    fputs("Runtime error stack trace:\n", stderr);
    fputs("  main: cannot open libshared\n", stderr);
    goto m_inner_free;
  }
  /* clear any existing errors */
  dlerror();

  data_name = argv[6];
  data = (const diffusion_steady_state_continuous *)
    dlsym(lib_handle, data_name);
  error = dlerror();
  if (error)
  {
    fputs(error, stderr);
    fputs("\n", stderr);
    goto lib_close;
  }

  result = diffusion_steady_state_continuous_primal_weak_solve(
    m, m_vol[m->dim - 1], m_inner[1], data);
  if (errno)
  {
    fputs("  main: cannot calculate result\n", stderr);
    goto lib_close;
  }

  double_array_file_print(stdout, m->cn[0], result, "--raw");

  free(result);
lib_close:
  dlclose(lib_name);
m_inner_free:
  double_array2_free(m_inner, m->dim + 1);
m_vol_free:
  double_array2_free(m_vol, m->dim + 1);
m_free:
  mesh_free(m);
end:
  return errno;
}
