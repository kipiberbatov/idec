#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_sparse.h"

matrix_sparse ** matrix_sparse_array_file_scan_by_name(
  const char * name, int n, const char * format)
{
  int i;
  matrix_sparse ** a;
  
  a = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * n);
  if (errno)
  {
    fputs("matrix_sparse_array_file_scan_by_name - cannot allocate memory for a\n",
          stderr);
    return NULL;
  }
  for (i = 0; i < n; ++i)
  {
    a[i] = matrix_sparse_file_scan_by_name(name, format);
    if (errno)
    {
      fprintf(stderr, "matrix_sparse_array_file_scan_by_name - cannot scan ");
      fprintf(stderr, "a[%d]: %s\n", i, strerror(errno));
      matrix_sparse_array_free(a, i);
      return NULL;
    }
  }
  return a;
}
