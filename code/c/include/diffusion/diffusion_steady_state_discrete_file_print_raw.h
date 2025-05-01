#ifndef _diffusion_steady_state_discrete_file_print_raw_h
#define _diffusion_steady_state_discrete_file_print_raw_h

#include <stdio.h>

struct diffusion_steady_state_discrete;

void diffusion_steady_state_discrete_file_print_raw(
  FILE * out,
  const struct diffusion_steady_state_discrete * data);

#endif /* _diffusion_steady_state_discrete_file_print_raw_h */
