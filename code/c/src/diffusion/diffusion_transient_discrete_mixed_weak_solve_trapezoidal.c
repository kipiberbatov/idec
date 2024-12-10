#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "diffusion_transient_discrete_mixed_weak_solve_trapezoidal_next.h"
#include "idec_error_message.h"

static void loop(
  double * flow,
  double * dual_potential,
  double * y,
  double * flow_reduced,
  const diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data * input,
  int number_of_steps)
{
  int i, m_cn_dm1, m_cn_d;

  m_cn_d = input->data->number_of_cells_d;
  m_cn_dm1 = input->data->number_of_cells_dm1;

  for (i = 0; i < number_of_steps; ++i)
  {
    diffusion_transient_discrete_mixed_weak_solve_trapezoidal_next(
      flow + m_cn_dm1 * (i + 1),
      dual_potential + m_cn_d * (i + 1),
      y,
      flow_reduced,
      flow + m_cn_dm1 * i,
      dual_potential + m_cn_d * i,
      input);
  }
}

void diffusion_transient_discrete_mixed_weak_solve_trapezoidal(
  double * flow,
  double * dual_potential,
  const mesh * m,
  const matrix_sparse * m_cbd_dm1,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const diffusion_transient_discrete_mixed_weak * data,
  double time_step,
  int number_of_steps)
{
  int d, m_cn_dm1, m_cn_dm1_bar, m_cn_d;
  double * flow_reduced, * y;
  diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data * input;
  
  d = m->dim;
  m_cn_dm1 = m->cn[d - 1];
  m_cn_dm1_bar = m_cn_dm1 - data->boundary_neumann_dm1->a0;
  m_cn_d = m->cn[d];

  input
  = diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_initialize(
    m, m_cbd_dm1, m_inner_dm1, m_inner_d, data, time_step);
  if (input == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot initialize constant input for loop\n", stderr);
    return;
  }

  y = (double *) malloc(sizeof(double) * m_cn_d);
  if (y == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * m_cn_d, "y");
    goto input_free;
  }

  flow_reduced = (double *) malloc(sizeof(double) * m_cn_dm1_bar);
  if (flow_reduced == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * m_cn_dm1_bar, "flow_reduced");
    goto y_free;
  }

  /* initialization */
  memcpy(flow, data->initial_flow, sizeof(double) * m_cn_dm1);
  memcpy(dual_potential, data->initial_dual_potential, sizeof(double) * m_cn_d);

  loop(flow, dual_potential, y, flow_reduced, input, number_of_steps);

  free(flow_reduced);
y_free:
  free(y);
input_free:
  diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_free(input);
}
