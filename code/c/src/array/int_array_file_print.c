#include <errno.h>
#include <string.h>
#include "int_private.h"

void int_array_file_print(
  FILE * out, int n, const int * a, const char * format)
{
  if (!strcmp(format, "--raw"))
    int_array_file_print_raw(out, n, a);
  else if (!strcmp(format, "--curly"))
    int_array_file_print_curly(out, n, a);
  else
  {
    errno = EINVAL;
    fprintf(stderr,
      "int_array_file_print - format %s is not supported\n", format);
  }
}
