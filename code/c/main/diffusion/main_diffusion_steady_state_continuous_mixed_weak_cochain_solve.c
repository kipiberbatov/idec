#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "color.h"
#include "double.h"
#include "diffusion_steady_state_continuous.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * error, * data_name, * lib_name, * m_inner_name, * m_name, * m_vol_name;
  int d;
  int * m_cn;
  double * flux, * temperature_on_cells;
  double ** m_inner, ** m_vol;
  FILE * m_file;
  matrix_sparse * m_cbd_dm1;
  matrix_sparse ** m_bd;
  mesh * m;
  void * lib_handle;
  const diffusion_steady_state_continuous * data;

  if (argc != 6)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of command-line arguments must be 6; instead it is %d\n",
      argc);
    errno = EINVAL;
    goto end;
  }

  m_name = argv[1];
  m_vol_name = argv[2];
  m_inner_name = argv[3];
  lib_name = argv[4];
  data_name = argv[5];

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    goto end;
  }

  m = mesh_file_scan(m_file, "--raw");
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan mesh m in format 'raw'\n", stderr);
    fclose(m_file);
    goto end;
  }

  m_bd = mesh_file_scan_boundary(m_file, m);
  if (m_bd == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan m_bd\n", stderr);
    fclose(m_file);
    goto m_free;
  }

  fclose(m_file);

  d = m->dim;
  m_cn = m->cn;

  m_cbd_dm1 = matrix_sparse_transpose(m_bd[d - 1]);
  if (m_cbd_dm1 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_bd_free;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_cbd_dm1_free;
  }
  
  m_vol = double_array2_file_scan_by_name(m_vol_name, d + 1, m_cn, "--raw");
  if (m_vol == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan m_vol\n", stderr);
    goto m_bd_free;
  }

  m_inner = double_array2_file_scan_by_name(m_inner_name, d + 1, m_cn, "--raw");
  if (m_inner == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan m_inner\n", stderr);
    goto m_vol_free;
  }

  lib_handle = dlopen(lib_name, RTLD_LAZY);
  if (lib_handle == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open dynamic library %s\n", lib_name);
    goto m_inner_free;
  }
  /* clear any existing errors */
  dlerror();

  data
  = (const diffusion_steady_state_continuous *) dlsym(lib_handle, data_name);
  error = dlerror();
  if (error)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    goto lib_close;
  }

  flux = (double *) malloc(sizeof(double) * m->cn[d - 1]);
  if (flux == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for flux\n", stderr);
    goto lib_close;
  }

  temperature_on_cells = (double *) malloc(sizeof(double) * m->cn[d]);
  if (temperature_on_cells == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for temperature_on_cells\n", stderr);
    goto flux_free;
  }

  diffusion_steady_state_continuous_mixed_weak_cochain_solve(
    flux, temperature_on_cells,
    m, m_cbd_dm1, m_vol[d - 1], m_vol[d], m_inner[d - 1], m_inner[d], data);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot find flux and temperature\n", stderr);
    goto temperature_on_cells_free;
  }

  fprintf(stderr, "\n%sflux:%s\n", color_red, color_none);
  double_array_file_print(stderr, m->cn[d - 1], flux, "--curly");
  fputc('\n', stderr);

  fprintf(stderr, "\n%stemperature on cells:%s\n", color_red, color_none);
  double_array_file_print(stderr, m->cn[d], temperature_on_cells, "--curly");
  fputc('\n', stderr);

temperature_on_cells_free:
  free(temperature_on_cells);
flux_free:
  free(flux);
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
