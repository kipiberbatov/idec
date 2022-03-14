#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_sparse_private.h"

matrix_sparse * matrix_sparse_fscan(FILE * in, const char * format)
{
  int i;
  matrix_sparse * a;
  
  for (i = 0; i < FSCAN_FORMATS_TOTAL; ++i)
    if (!strcmp(format, fscan_formats[i]))
    {
      a = fscanners[i](in);
      if (errno)
      {
        perror("Unsuccessful matrix scanning");
        return NULL;
      }
      return a;
    }
  errno = EINVAL;
  perror(format);
  return NULL;
}

matrix_sparse ** matrix_sparse_fscan_array(
  FILE * in, int n, const char * format)
{
  int i;
  matrix_sparse ** a;
  
  a = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * n);
  if (errno)
  {
    perror("Cannot allocate memory for list of sparse matrices");
    return NULL;
  }
  for (i = 0; i < n; ++i)
  {
    a[i] = matrix_sparse_fscan(in, format);
    if (errno)
    {
      fprintf(stderr, "Cannot scan matrix a[%d]: %s", i, strerror(errno));
      matrix_sparse_free_array(a, i);
      return NULL;
    }
  }
  return a;
}
