#include <errno.h>
#include <string.h>

#include "color.h"
#include "double_private.h"

double * double_matrix_file_scan(FILE * in, int m, int n, const char * format)
{
  double * a;

  if (!strcmp(format, "--raw"))
    a = double_matrix_file_scan_raw(in, m, n);
  else if (!strcmp(format, "--steady-state-mixed-weak-solution-flow-raw"))
    a = double_array_file_scan_steady_state_primal_weak_raw(in, m * n);
  else
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "format %s is not supported\n", format);
    errno = EINVAL;
    return NULL;
  }

  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan input matrix\n", stderr);
  }
  return a;
}
