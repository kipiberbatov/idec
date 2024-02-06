#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "array_indexed.h"
#include "double.h"
#include "int.h"
#include "vector_sparse.h"

void vector_sparse_rearrange(vector_sparse * b)
{
  double * b_values_new;
  array_indexed a;
  
  a.positions = (int *) malloc(sizeof(int) * b->nonzero_max);
  if (errno)
  {
    perror("vector_sparse_rearrange - cannnot allocate memory for a.positions");
    goto end;
  }
  
  int_array_assign_identity(a.positions, b->nonzero_max);
  a.values = b->positions;
  
  array_indexed_merge_sort(&a, b->nonzero_max);
  if (errno)
  {
    perror("vector_sparse_rearrange - cannnot merge sort a");
    goto a_positions_free;
  }
  
  b_values_new = (double *) malloc(sizeof(double) * b->nonzero_max);
  if (errno)
  {
    perror("vector_sparse_rearrange - cannnot allocate memory for b_values_new");
    goto a_positions_free;
  }
  
  double_array_substitute(b_values_new, b->nonzero_max, b->values, a.positions);
  memcpy(b->values, b_values_new, sizeof(double) * b->nonzero_max);
  
  free(b_values_new);
a_positions_free:
  free(a.positions);
end:
  return;
}
