#include <errno.h>
#include <string.h>

#include "double_matrix_file_print.h"
#include "double_matrix_file_print_curly.h"
#include "double_matrix_file_print_raw.h"

/*
Write a matrix of doubles of size m * n to a file in a specified format.
If the format is not supported, set errno to EINVAL.

Supported formats:
  --raw
  --curly
*/
void double_matrix_file_print(
  FILE * out,
  int m,
  int n,
  const double * a,
  const char * format)
{
  /* check format "--raw" */
  if (!strcmp(format, "--raw"))
  {
    double_matrix_file_print_raw(out, m, n, a);
    return;
  }

  /* check format "--curly" */
  if (!strcmp(format, "--curly"))
  {
    double_matrix_file_print_curly(out, m, n, a);
    return;
  }
  
  /* the program will get there only if the format is not supported */
  errno = EINVAL;
  fprintf(
    stderr,
    "Error in %s: format %s is not supported\n",
    __func__,
    format
  );
}
