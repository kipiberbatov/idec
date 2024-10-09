#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "diffusion_steady_state_discrete_mixed_weak.h"
#include "double.h"
#include "int.h"
#include "mesh_qc.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_vol_format, * m_vol_name, * m_format, * m_name,
       * solution_name;
  int d, m_cn_dm1, m_cn_d;
  int * m_cn;
  double * flux, * temperature, * temperature_on_cells;
  double ** m_vol;
  FILE * data_file, * m_file, * solution_file;
  mesh * m;
  diffusion_steady_state_discrete_mixed_weak * data;

#define ARGC 7
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
  m_vol_format = argv[3];
  m_vol_name = argv[4];
  data_name = argv[5];
  solution_name = argv[6];

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    goto end;
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

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_vol = double_array2_file_scan_by_name(
    m_vol_name, d + 1, m_cn, m_vol_format);
  if (m_vol == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan cells' measures from file %s in format %s\n",
      m_vol_name, m_vol_format);
    goto m_free;
  }

  data_file = fopen(data_name, "r");
  if (data_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem data file %s: %s\n", data_name, strerror(errno));
    goto m_vol_free;
  }
  data = diffusion_steady_state_discrete_mixed_weak_file_scan_raw(data_file);
  if (data == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    goto m_vol_free;
  }
  fclose(data_file);

  solution_file = fopen(solution_name, "r");
  if (solution_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem solution file %s: %s\n",
      solution_name, strerror(errno));
    goto data_free;
  }
  m_cn_dm1 = int_file_scan(solution_file);
  m_cn_d = int_file_scan(solution_file);

  flux = double_array_file_scan(solution_file, m_cn_dm1, "--raw");
  if (flux == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan flux from file in format 'raw' %s\n", solution_name);
    fclose(solution_file);
    goto data_free;
  }

  temperature_on_cells = double_array_file_scan(solution_file, m_cn_d, "--raw");
  if (temperature_on_cells == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan temperature_on_cells from file in format 'raw' %s\n",
      solution_name);
    fclose(solution_file);
    goto flux_free;
  }
  fclose(solution_file);

  temperature = (double *) malloc(sizeof(double) * m->cn[0]);
  if (temperature == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for temperature\n", stderr);
    goto temperature_on_cells_free;
  }

  mesh_qc_hodge_star_d(temperature, m, m_vol[d], temperature_on_cells);
  double_array_assemble_from_sparse_array(
    temperature, data->boundary_dirichlet_0, data->g_dirichlet_0);

  fprintf(stdout, "%d\n", m->cn[0]);
  double_array_file_print(stdout, m->cn[0], temperature, "--raw");

  free(temperature);
temperature_on_cells_free:
  free(temperature_on_cells);
flux_free:
  free(flux);
data_free:
  diffusion_steady_state_discrete_mixed_weak_free(data);
m_vol_free:
  double_array2_free(m_vol, d + 1);
m_free:
  mesh_free(m);
end:
  return errno;
}
