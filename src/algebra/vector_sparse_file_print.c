#include <errno.h>
#include <string.h>
#include "vector_sparse_private.h"

void vector_sparse_file_print(
  FILE * out, const vector_sparse * a, const char * format)
{
  int i;
  
  for (i = 0; i < VECTOR_SPARSE_file_print_format_total; ++i)
    if (!strcmp(format, vector_sparse_file_print_format[i]))
    {
      vector_sparse_file_print_function[i](out, a);
      if (errno)
      {
        perror("vector_sparse_file_print - cannot print a");
        return;
      }
      return;
    }
  errno = EINVAL;
  fprintf(stderr, "vector_sparse_file_print - format %s is not supported: %s\n",
          format, strerror(errno));
  return;
}
