#include <errno.h>
#include <string.h>
#include "jagged_private.h"

void jagged2_file_print(FILE * out, const jagged2 * arr, const char * format)
{
  int i;
  
  for (i = 0; i < JAGGED2_file_print_format_total; ++i)
    if (!strcmp(format, jagged2_file_print_format[i]))
    {
      jagged2_file_print_function[i](out, arr);
      if (errno)
      {
        perror("jagged2_file_print - cannot print arr to out");
        return;
      }
      return;
    }
  errno = EINVAL;
  perror(format);
}
