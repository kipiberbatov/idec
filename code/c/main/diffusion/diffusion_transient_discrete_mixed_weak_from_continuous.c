#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "color.h"
#include "double.h"
#include "diffusion_transient_discrete_mixed_weak.h"

int main(int argc, char ** argv)
{
  char * data_continuous_name, * error, * lib_name, * m_cbd_star_name,
       * m_format, * m_name, * m_vol_format, * m_vol_name;
  int d;
  int * m_cn;
  double ** m_vol;
  void * lib_handle;
  FILE * m_cbd_star_file;
  mesh * m;
  matrix_sparse ** m_cbd_star;
  const diffusion_transient_continuous * data_continuous;
  diffusion_transient_discrete_mixed_weak * data_discrete;

#define ARGC 8
  if (argc != ARGC)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of command-line arguments must be %d; instead it is %d\n",
      ARGC, argc);
    errno = EINVAL;
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  m_cbd_star_name = argv[3];
  m_vol_format = argv[4];
  m_vol_name = argv[5];
  lib_name = argv[6];
  data_continuous_name = argv[7];

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

  data_continuous = (const diffusion_transient_continuous *) dlsym(
    lib_handle, data_continuous_name);
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
  dlclose(lib_name);
m_vol_free:
  double_array2_free(m_vol, d + 1);
m_cbd_star_free:
  matrix_sparse_array_free(m_cbd_star, d);
m_free:
  mesh_free(m);
end:
  return errno;
}
