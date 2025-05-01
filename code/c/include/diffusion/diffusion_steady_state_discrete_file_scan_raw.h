#ifndef _diffusion_steady_state_discrete_file_scan_raw_h
#define _diffusion_steady_state_discrete_file_scan_raw_h

#include <stdio.h>

struct diffusion_steady_state_discrete;

void diffusion_steady_state_discrete_file_scan_raw(
  FILE * out,
  struct diffusion_steady_state_discrete ** result,
  int * status);

#endif /* _diffusion_steady_state_discrete_file_scan_raw_h */
