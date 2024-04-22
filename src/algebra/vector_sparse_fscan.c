#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "vector_sparse_private.h"

vector_sparse * vector_sparse_file_scan(FILE * in, const char * format)
{
  int i;
  vector_sparse * a;
  
  for (i = 0; i < VECTOR_SPARSE_file_scan_format_total; ++i)
    if (!strcmp(format, vector_sparse_file_scan_format[i]))
    {
      a = vector_sparse_file_scan_function[i](in);
      if (errno)
      {
        perror("vector_sparse_file_scan - cannot scan a");
        return NULL;
      }
      return a;
    }
  errno = EINVAL;
  fprintf(stderr, "vector_sparse_file_scan - format %s is not supported: %s\n",
          format, strerror(errno));
  return NULL;
}
