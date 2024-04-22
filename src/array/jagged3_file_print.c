#include <errno.h>
#include <string.h>
#include "jagged_private.h"

void jagged3_file_print(FILE * out, const jagged3 * arr, const char * format)
{
  int i;
  
  for (i = 0; i < JAGGED3_file_print_format_total; ++i)
    if (!strcmp(format, jagged3_file_print_format[i]))
    {
      jagged3_file_print_function[i](out, arr);
      if (errno)
      {
        perror("jagged3_file_print - cannot print arr to out");
        return;
      }
      return;
    }
  errno = EINVAL;
  perror(format);
}
