#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "vector_sparse_private.h"

vector_sparse * vector_sparse_fscan(FILE * in, const char * format)
{
  int i;
  vector_sparse * a;
  
  for (i = 0; i < VECTOR_SPARSE_FSCAN_FORMAT_TOTAL; ++i)
    if (!strcmp(format, vector_sparse_fscan_format[i]))
    {
      a = vector_sparse_fscan_function[i](in);
      if (errno)
      {
        perror("vector_sparse_fscan - cannot scan a");
        return NULL;
      }
      return a;
    }
  errno = EINVAL;
  fprintf(stderr, "vector_sparse_fscan - format %s is not supported: %s\n",
          format, strerror(errno));
  return NULL;
}
