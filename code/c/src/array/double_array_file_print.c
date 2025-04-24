#include <errno.h>
#include <string.h>

#include "color.h"
#include "double_array.h"
#include "double_array_private.h"

void double_array_file_print(
  FILE * out, int n, const double * a, const char * format)
{
  if (!strcmp(format, "--raw"))
    double_array_file_print_raw(out, n, a);
  else if (!strcmp(format, "--curly"))
    double_array_file_print_curly(out, n, a);
  else
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "format %s is not supported\n", format);
    errno = EINVAL;
  }
}
