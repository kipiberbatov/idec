#include <stdlib.h>
#include "vector_sparse.h"

void vector_sparse_free(vector_sparse * a)
{
  free(a->values);
  free(a->positions);
  free(a);
}
