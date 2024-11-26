#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "diffusion_transient_discrete_primal_weak_solve_trapezoidal_next.h"
#include "double.h"
#include "mesh_qc.h"

/*
$potential$ stores the final solution $y_0, ..., y_{number_of_steps}$.
$y_0$ is the initial condition.
Until error is less than $tolerance$:
  $rhs_final$ is updated using $y_i$ and used to find $y_{i + 1}$.
*/
static void loop(
  double_array_sequence_dynamic * potential,
  double * rhs_final,
  const diffusion_transient_discrete_primal_weak_trapezoidal_loop_data * input,
  double tolerance)
{
  int i, m_cn_0;
  double relative_norm;

  i = 0;
  m_cn_0 = input->rhs->rows;

  do
  {
    if (i == potential->capacity - 1)
    {
      double_array_sequence_dynamic_resize(potential);
      if (errno)
      {
        color_error_position(__FILE__, __LINE__);
        fprintf(stderr, "loop: cannot resize in iteration %d\n", i);
        return;
      }
    }

    potential->values[i + 1] = (double *) malloc(sizeof(double) * m_cn_0);
    if (potential->values[i + 1] == NULL)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr,
        "loop: cannot allocate %ld bytes of memory for potential->values[%d]\n",
        sizeof(double) * m_cn_0, i + 1);
      return;
    }

    diffusion_transient_discrete_primal_weak_solve_trapezoidal_next(
      potential->values[i + 1], rhs_final, potential->values[i], input);
    if (errno)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr, "loop: cannot calculate potential->values[%d]\n", i + 1);
      return;
    }

    relative_norm = double_array_pair_norm_uniform_relative(
      m_cn_0, potential->values[i], potential->values[i + 1]);
    ++potential->length;
    ++i;
  }
  while (relative_norm >= tolerance);
}

double_array_sequence_dynamic *
diffusion_transient_discrete_primal_weak_solve_trapezoidal_to_steady_state(
  const mesh * m,
  const double * m_inner_0,
  const double * m_inner_1,
  const diffusion_transient_discrete_primal_weak * data,
  double time_step,
  double tolerance)
{
  int m_cn_0;
  double * rhs_final;
  diffusion_transient_discrete_primal_weak_trapezoidal_loop_data * input;
  double_array_sequence_dynamic * potential = NULL;

  input =
  diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_initialize(
    m, m_inner_0, m_inner_1, data, time_step);
  if (input == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot initialize loop input\n", stderr);
    goto end;
  }

  m_cn_0 = m->cn[0];

  /* allocate memory for $rhs_final$ -> uppdated at each step of the loop */
  rhs_final = (double *) malloc(sizeof(double) * m_cn_0);
  if (rhs_final == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for rhs_final\n",
      sizeof(double) * m_cn_0);
    goto input_free;
  }

  potential = double_array_sequence_dynamic_initialize(m_cn_0);
  if (potential == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot initialize potential with size %d\n", m_cn_0);
    goto rhs_final_free;
  }

  /* the initial $potential->values[0]$ is the initial condition */
  memcpy(potential->values[0], data->initial, sizeof(double) * m_cn_0);

  /* The following elements of $potential$ (each of size $n$)
   * are calculated iteratively with $rhs_final$ updating at each step
   * (until error is less than tolerance).
   */
  loop(potential, rhs_final, input, tolerance);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("error in loop calculating final potential\n", stderr);
    double_array_sequence_dynamic_free(potential);
    potential = NULL;
    goto rhs_final_free;
  }

rhs_final_free:
  free(rhs_final);
input_free:
  diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_free(input);
end:
  return potential;
}
