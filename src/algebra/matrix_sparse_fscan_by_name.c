#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_sparse.h"

matrix_sparse * matrix_sparse_fscan_by_name(
  const char * name, const char * format)
{
  FILE * in;
  matrix_sparse * a = NULL;

  in = fopen(name, "r");
  if (errno)
  {
    perror(name);
    goto end;
  }
  a = matrix_sparse_fscan(in, format);
  if (errno)
  {
    fprintf(stderr, "Cannot scan matrix in format %s: %s\n",
            format, strerror(errno));
    goto in_close;
  }
in_close:
  fclose(in);
end:
  return a;
}

matrix_sparse ** matrix_sparse_fscan_by_name_array(
  const char * name, int n, const char * format)
{
  int i;
  matrix_sparse ** a;
  
  a = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * n);
  if (errno)
  {
    perror("Cannot allocate memory for list of sparse matrices");
    goto end;
  }
  for (i = 0; i < n; ++i)
  {
    a[i] = matrix_sparse_fscan_by_name(name, format);
    if (errno)
    {
      fprintf(stderr, "Cannot scan by name matrix a[%d]: %s",
              i, strerror(errno));
      goto a_free;
    }
  }
  return a;
  
  /* cleaning if an error occurs */
a_free:
  matrix_sparse_free_array(a, i);
end:
  return NULL;
}
