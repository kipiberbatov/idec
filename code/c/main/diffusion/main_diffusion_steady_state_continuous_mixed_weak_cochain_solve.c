#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "double.h"
#include "diffusion_steady_state_continuous.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * error, * data_name, * lib_name, * m_inner_name, * m_name, * m_vol_name;
  int d;
  int * m_cn;
  double * flux = NULL, * temperature = NULL;
  double ** m_inner, ** m_vol;
  FILE * m_file;
  matrix_sparse * m_cbd_dm1;
  matrix_sparse ** m_bd;
  mesh * m;
  void * lib_handle;
  const diffusion_steady_state_continuous * data;

  if (argc != 6)
  {
    errno = EINVAL;
    fputs("Runtime error stack trace:\n", stderr);
    fputs("  main: the number of command-line arguments must be 8\n", stderr);
    goto end;
  }

  m_name = argv[1];
  m_vol_name = argv[2];
  m_inner_name = argv[3];
  lib_name = argv[4];
  data_name = argv[5];

  m_file = fopen(m_name, "r");
  if (errno)
  {
    fprintf(stderr, "Cannot open mesh file: %s\n", strerror(errno));
    goto end;
  }

  m = mesh_file_scan(m_file, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m\n", stderr);
    fclose(m_file);
    goto end;
  }

  m_bd = mesh_file_scan_boundary(m_file, m);
  if (errno)
  {
    fputs("main - cannot scan m_bd\n", stderr);
    fclose(m_file);
    goto m_free;
  }

  fclose(m_file);

  d = m->dim;
  m_cn = m->cn;

  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("  main: cannot calculate m->fc\n", stderr);
    goto m_bd_free;
  }

  m_cbd_dm1 = matrix_sparse_transpose(m_bd[d - 1]);
  if (errno)
  {
    fputs("  main: cannot calculate m_cbd[d - 1]\n", stderr);
    goto m_bd_free;
  }
  
  m_vol = double_array2_file_scan_by_name(m_vol_name, d + 1, m_cn, "--raw");
  if (errno)
  {
    fputs("  main: cannot scan m_vol\n", stderr);
    goto m_cbd_dm1_free;
  }

  m_inner = double_array2_file_scan_by_name(m_inner_name, d + 1, m_cn, "--raw");
  if (errno)
  {
    fputs("  main: cannot scan m_vol\n", stderr);
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

  data
  = (const diffusion_steady_state_continuous *) dlsym(lib_handle, data_name);
  error = dlerror();
  if (error)
  {
    fputs(error, stderr);
    fputs("\n", stderr);
    goto lib_close;
  }

  diffusion_steady_state_continuous_mixed_weak_cochain_solve(
    flux, temperature,
    m, m_cbd_dm1, m_vol[d - 1], m_vol[d], m_inner[d - 1], data);
  if (errno)
  {
    fputs("  main: cannot calculate result\n", stderr);
    goto lib_close;
  }

  // double_array_file_print(stdout, m->cn[0], result, "--raw");

lib_close:
  dlclose(lib_name);
m_inner_free:
  double_array2_free(m_inner, d + 1);
m_vol_free:
  double_array2_free(m_vol, d + 1);
m_cbd_dm1_free:
  matrix_sparse_free(m_cbd_dm1);
m_bd_free:
  matrix_sparse_array_free(m_bd, d);
m_free:
  mesh_free(m);
end:
  return errno;
}
