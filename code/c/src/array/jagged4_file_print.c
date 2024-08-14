#include <errno.h>
#include <string.h>
#include "jagged_private.h"

void jagged4_file_print(FILE * out, const jagged4 * arr, const char * format)
{
  if (!strcmp(format, "--raw"))
    jagged4_file_print_raw(out, arr);
  else if (!strcmp(format, "--curly"))
    jagged4_file_print_curly(out, arr);
  else
  {
    errno = EINVAL;
    fprintf(stderr, "jagged4_file_print - format %s is not supported\n", format);
  }
}
