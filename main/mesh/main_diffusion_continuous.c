#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "double.h"
#include "diffusion_continuous.h"
#include "int.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * error, * data_name, * lib_name;
  char * m_format, * m_laplacian_0_format, * m_laplacian_0_name, * m_name;
  double ** result;

  mesh * m;
  matrix_sparse * m_laplacian_0;
  void * lib_handle;
  const diffusion_continuous * data;
  int i, number_of_steps;
  double time_step;
  
  if (argc != 8)
  {
    errno = EINVAL;
    fputs("main - the number of command-line arguments must be 6\n", stderr);
    goto end;
  }
  
  m_format = argv[1];
  m_name = argv[2];
  m = mesh_fscan_by_name(m_name, m_format);
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
  
  m_laplacian_0_format = argv[3];
  m_laplacian_0_name = argv[4];
  
  m_laplacian_0 = 
    matrix_sparse_fscan_by_name(m_laplacian_0_name, m_laplacian_0_format);
  if (errno)
  {
    fputs("main - cannot calculate m_laplacian[0]\n", stderr);
    goto m_free;
  }
  matrix_sparse_scalar_multiply(m_laplacian_0, -1);

  
#ifdef __linux__
  lib_name ="lib/libshared.so";
#elif __APPLE__
  lib_name ="lib/libshared.dylib";
#endif
  lib_handle = dlopen(lib_name, RTLD_LAZY);
  if (!lib_handle)
  {
    fputs("main - cannot open libshared\n", stderr);
    goto m_laplacian_0_free;
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

  time_step = double_sscan(argv[6]);
  if (errno)
  {
    fprintf(stderr, "Error in %s: cannot scan time_step\n", __func__);
    goto m_laplacian_0_free;
  }

  number_of_steps = int_sscan(argv[7]);
  if (errno)
  {
    fprintf(stderr, "Error in %s: cannot scan number_of_steps\n", __func__);
    goto m_laplacian_0_free;
  }
  
  result = diffusion_continuous_solve_trapezoidal_method(
    m,
    m_laplacian_0,
    data,
    time_step,
    number_of_steps);
  if (errno)
  {
    fputs("main - cannot calculate x\n", stderr);
    goto m_laplacian_0_free;
  }

  for (i = 0; i <= number_of_steps; ++i)
  {
    double_array_fprint(stdout, m->cn[0], result[i], "--raw");
    fputs("\n", stdout);
  }

  for (i = number_of_steps; i >= 0; --i)
    free(result[i]);
  free(result);
lib_close:
  dlclose(lib_name);
m_laplacian_0_free:
  matrix_sparse_free(m_laplacian_0);
m_free:
  mesh_free(m);
end:
  return errno;
}