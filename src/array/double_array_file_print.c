#include <errno.h>
#include <string.h>
#include "double_private.h"

void double_array_file_print(
  FILE * out, int n, const double * a, const char * format)
{
  if (!strcmp(format, "--raw"))
    double_array_file_print_raw(out, n, a);
  else if (!strcmp(format, "--curly"))
    double_array_file_print_curly(out, n, a);
  else
  {
    errno = EINVAL;
    fprintf(stderr,
      "double_array_file_print - format %s is not supported\n", format);
  }
}
