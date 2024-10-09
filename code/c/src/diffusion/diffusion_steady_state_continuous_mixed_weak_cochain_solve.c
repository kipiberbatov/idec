#include <errno.h>
#include <stdlib.h>

#include "color.h"
#include "double.h"
#include "diffusion_steady_state_continuous.h"
#include "diffusion_steady_state_discrete_mixed_weak.h"
#include "mesh_qc.h"

void diffusion_steady_state_continuous_mixed_weak_cochain_solve(
  double * flux,
  double * temperature_on_cells,
  const mesh * m,
  const matrix_sparse * m_cbd_dm1,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const diffusion_steady_state_continuous * data_continuous)
{
  diffusion_steady_state_discrete_mixed_weak * data_discrete;
  double * temperature;

  data_discrete = diffusion_steady_state_discrete_mixed_weak_from_continuous(
    m, m_vol_dm1, m_vol_d, data_continuous);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot discretize continuous data\n", stderr);
    return;
  }

  diffusion_steady_state_discrete_mixed_weak_solve(
    flux,
    temperature_on_cells,
    m,
    m_cbd_dm1,
    m_inner_dm1,
    m_inner_d,
    data_discrete);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot solve discretized problem\n", stderr);
    goto data_discrete_free;
  }

  temperature = (double *) malloc(sizeof(double) * m->cn[0]);
  if (temperature == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for temperature\n", stderr);
    goto data_discrete_free;
  }
  mesh_qc_hodge_star_d(temperature, m, m_vol_d, temperature_on_cells);
  fprintf(stderr, "\n%stemperature:%s\n", color_red, color_none);
  double_array_file_print(stderr, m->cn[0], temperature, "--curly");
  fputc('\n', stderr);
  
  double_array_assemble_from_sparse_array(
    temperature,
    data_discrete->boundary_dirichlet_0,
    data_discrete->g_dirichlet_0);
  fprintf(stderr, "\n%stemperature:%s\n", color_red, color_none);
  double_array_file_print(stderr, m->cn[0], temperature, "--curly");
  fputc('\n', stderr);

  free(temperature);
data_discrete_free:
  diffusion_steady_state_discrete_mixed_weak_free(data_discrete);
}
