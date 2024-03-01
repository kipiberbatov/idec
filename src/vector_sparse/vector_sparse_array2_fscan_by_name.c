#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "vector_sparse.h"

vector_sparse *** vector_sparse_array2_fscan_by_name(
  const char * name, int a0, const int * a1, const char * format)
{
  int i;
  vector_sparse *** a;
  
  a = (vector_sparse ***) malloc(sizeof(vector_sparse **) * a0);
  if (errno)
  {
    perror("vector_sparse_array2_fscan_by_name - cannot allocate memory for a");
    return NULL;
  }
  for (i = 0; i < a0; ++i)
  {
    a[i] = vector_sparse_array_fscan_by_name(name, a1[i], format);
    if (errno)
    {
      fprintf(stderr, "vector_sparse_array_fscan_by_name - cannot scan ");
      fprintf(stderr, "a[%d]: %s\n", i, strerror(errno));
      vector_sparse_array2_free(a, i, a1);
      return NULL;
    }
  }
  return a;
}
