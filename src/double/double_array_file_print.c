#include <errno.h>
#include <string.h>

#include "double_array_file_print.h"
#include "double_array_file_print_curly.h"
#include "double_array_file_print_raw.h"

/*
Write an array of doubles of size n to a file in a specified format.
If the format is not supported, set errno to EINVAL.

Supported formats:
  --raw
  --curly
*/
void double_array_file_print(
  FILE * out,
  int n,
  const double * a,
  const char * format)
{
  /* check format "--raw" */
  if (!strcmp(format, "--raw"))
  {
    double_array_file_print_raw(out, n, a);
    return;
  }

  /* check format "--curly" */
  if (!strcmp(format, "--curly"))
  {
    double_array_file_print_curly(out, n, a);
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
