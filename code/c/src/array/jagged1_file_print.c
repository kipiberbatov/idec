#include <errno.h>
#include <string.h>
#include "jagged_private.h"

void jagged1_file_print(FILE * out, const jagged1 * arr, const char * format)
{
  if (!strcmp(format, "--raw"))
    jagged1_file_print_raw(out, arr);
  else if (!strcmp(format, "--curly"))
    jagged1_file_print_curly(out, arr);
  else
  {
    errno = EINVAL;
    fprintf(stderr, "jagged1_file_print - format %s is not supported\n", format);
  }
}
