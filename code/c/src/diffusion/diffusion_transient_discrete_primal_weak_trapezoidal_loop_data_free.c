#include <stdlib.h>

#include "diffusion_transient_discrete_primal_weak_trapezoidal_loop_data.h"

void diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_free(
  diffusion_transient_discrete_primal_weak_trapezoidal_loop_data * input)
{
  matrix_sparse_free(input->rhs);
  matrix_sparse_free(input->lhs);
  free(input->free_part);
  free(input);
}
