#include <errno.h>
#include <string.h>
#include "int_private.h"

void int_array_file_print(FILE * out, int n, const int * a, const char * format)
{
  int i;
  
  for (i = 0; i < INT_ARRAY_file_print_format_total; ++i)
    if (!strcmp(format, int_array_file_print_format[i]))
    {
      int_array_file_print_function[i](out, n, a);
      if (errno)
      {
        perror("int_array_file_print - printing failed");
        return;
      }
      return;
    }
  errno = EINVAL;
  fprintf(stderr, "int_array_file_print - format %s is not supported: %s\n",
          format, strerror(errno));
  return;
}
