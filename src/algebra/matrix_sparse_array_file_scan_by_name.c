#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "matrix_sparse.h"

matrix_sparse ** matrix_sparse_array_file_scan_by_name(
  const char * name, int n, const char * format)
{
  int i;
  matrix_sparse ** a;
  FILE * a_file;

  a_file = fopen(name, "r");
  if (errno)
  {
    fprintf(stderr,
      "matrix_sparse_array_file_scan_by_name: cannot open file: %s\n",
      strerror(errno));
    return NULL;
  }
  
  a = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * n);
  if (errno)
  {
    fputs(
      "matrix_sparse_array_file_scan_by_name: cannot allocate memory for a\n",
      stderr);
    return NULL;
  }
  for (i = 0; i < n; ++i)
  {
    a[i] = matrix_sparse_file_scan(a_file, format);
    if (errno)
    {
      fprintf(stderr,
        "matrix_sparse_array_file_scan_by_name: cannot scan a[%d]\n", i);
      matrix_sparse_array_free(a, i);
      fclose(a_file);
      return NULL;
    }
  }
  fclose(a_file);
  return a;
}
