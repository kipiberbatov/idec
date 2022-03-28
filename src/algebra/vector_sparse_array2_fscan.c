#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "vector_sparse.h"

vector_sparse *** vector_sparse_array2_fscan(
  FILE * in, int a0, int * a1, const char * format)
{
  int i;
  vector_sparse *** arr;
  
  arr = (vector_sparse ***) malloc(sizeof(vector_sparse **) * a0);
  if (errno)
  {
    perror("vector_sparse_array2_fscan - cannot allocate memory for arr");
    return NULL;
  }
  for (i = 0; i < a0; ++i)
  {
    arr[i] = vector_sparse_array_fscan(in, a1[i], format);
    if (errno)
    {
      fprintf(stderr, "vector_sparse_array2_fscan - cannot scan arr[%d]: %s\n",
              i, strerror(errno));
      vector_sparse_array2_free(arr, i, a1);
      return NULL;
    }
  }
  return arr;
}
