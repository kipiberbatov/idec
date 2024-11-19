#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double_private.h"

double * double_array_file_scan(FILE * in, int n, const char * format)
{
  double * a;

  if (n == 0)
    return (double *) malloc(sizeof(double));

  if (!strcmp(format, "--raw"))
    a = double_array_file_scan_raw(in, n);
  else if (!strcmp(format, "--steady-state-primal-weak-raw"))
    a = double_array_file_scan_steady_state_primal_weak_raw(in, n);
  else if (!strcmp(format, "--steady-state-mixed-weak-solution-flow-raw"))
    a = double_array_file_scan_steady_state_primal_weak_raw(in, n);
  else if (!strcmp(format, "--steady-state-primal-strong-raw"))
    a = double_array_file_scan_steady_state_primal_weak_raw(in, n);
  else if (!strcmp(format, "--transient-primal-strong-raw"))
    a = double_array_file_scan_transient_primal_strong_raw(in, n);
  else if (!strcmp(format, "--transient-primal-weak-raw"))
    a = double_array_file_scan_transient_primal_weak_raw(in, n);
  else
  {
    errno = EINVAL;
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "format %s is not supported\n", format);
    return NULL;
  }

  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan input\n", stderr);
  }
  return a;
}
