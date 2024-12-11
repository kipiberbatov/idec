#ifndef _diffusion_transient_discrete_mixed_weak_solve_trapezoidal_next_h
#define _diffusion_transient_discrete_mixed_weak_solve_trapezoidal_next_h

#include "diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data.h"

void diffusion_transient_discrete_mixed_weak_solve_trapezoidal_next(
  double * flow_next,
  double * dual_potential_next,
  double * y,
  double * flow_reduced,
  const double * flow_current,
  const double * dual_potential_current,
  const diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data * input);

#endif /* _diffusion_transient_discrete_mixed_weak_solve_trapezoidal_next_h */