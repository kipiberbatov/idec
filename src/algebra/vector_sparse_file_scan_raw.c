#include <errno.h>
#include <stdlib.h>
#include "double.h"
#include "int.h"
#include "vector_sparse_private.h"

static int all_values_in_range(
  int a_length, int a_nonzero_max, const int * a_positions)
{
  int i;
  
  for (i = 0; i < a_nonzero_max; ++i)
    if (a_positions[i] < 0 || a_positions[i] >= a_length)
      return 0;
  return 1;
}

static int all_values_different(int a_nonzero_max, const int * a_positions)
{
  int i, j;
  
  for (i = 0; i < a_nonzero_max - 1; ++i)
    for (j = i + 1; j < a_nonzero_max; ++j)
      if (a_positions[i] == a_positions[j])
        return 0;
  return 1;
}

static int vector_sparse_positions_possible(
  int a_length, int a_nonzero_max, const int * a_positions)
{
  if (!all_values_in_range(a_length, a_nonzero_max, a_positions))
    return 0;
  if (!all_values_different(a_nonzero_max, a_positions))
    return 0;
  return 1;
}

vector_sparse * vector_sparse_file_scan_raw(FILE * in)
{
  vector_sparse * a;
  
  a = (vector_sparse *) malloc(sizeof(vector_sparse));
  if (errno)
  {
    perror("vector_sparse_file_scan_raw - cannot allocate memory for a");
    goto end;
  }
  
  a->length = int_file_scan(in);
  if (errno)
  {
    perror("vector_sparse_file_scan_raw - cannot scan a->length");
    goto a_free;
  }
  if (a->length <= 0)
  {
    errno = EINVAL;
    perror("vector_sparse_file_scan_raw - a->length is nonpositive");
    goto a_free;
  }
  
  a->nonzero_max = int_file_scan(in);
  if (errno)
  {
    perror("vector_sparse_file_scan_raw - cannot scan a->nonzero_max");
    goto a_free;
  }
  if (a->nonzero_max <= 0 || a->nonzero_max > a->length)
  {
    errno = EINVAL;
    perror("vector_sparse_file_scan_raw - a->nonzero_max is out of domain");
    goto a_free;
  }
  
  a->positions = int_array_file_scan(in, a->nonzero_max, "--raw");
  if (errno)
  {
    perror("vector_sparse_file_scan_raw - cannot scan a->positions");
    goto a_free;
  }
  if(!vector_sparse_positions_possible(a->length, a->nonzero_max, a->positions))
  {
    errno = EINVAL;
    perror("vector_sparse_file_scan_raw - a->positions is impossible");
    goto a_positions_free;
  }
  
  a->values = double_array_file_scan(in, a->nonzero_max, "--raw");
  if (errno)
  {
    perror("vector_sparse_file_scan_raw - cannot scan a->values");
    goto a_positions_free;
  }
  
  return a;
  
  /* cleaning if an error occurs */
a_positions_free:
  free(a->positions);
a_free:
  free(a);
end:
  return NULL;
}
