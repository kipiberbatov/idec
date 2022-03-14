#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "array_indexed.h"
#include "int.h"
#include "jagged.h"

static void array_set_to_identity(int * a, int n)
{
  int i;
  
  for (i = 0; i < n; ++i)
    a[i] = i;
}

int main()
{
  int n;
  jagged1 * arr = NULL;
  array_indexed a;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  arr = jagged1_fscan_raw(in);
  if (errno)
  {
    perror("Problem in array scanning");
    goto arr_free;
  }
  n = arr->a0;
  a.positions = (int *) malloc(n * sizeof(int));
  if (errno)
  {
    perror("Cannot allocate memory for a.positions");
    goto arr_free;
  }
  a.values = (int *) malloc(n * sizeof(int));
  if (errno)
  {
    perror("Cannot allocate memory for a.values");
    goto a_positions_free;
  }
  array_set_to_identity(a.positions, n);
  memcpy(a.values, arr->a1, n * sizeof(int));
  array_indexed_merge_sort(&a, n);
  if (errno)
  {
    perror("Unsuccessful merge sort");
    goto a_values_free;
  }
  fprintf(stdout, "%d\n", arr->a0);
  int_fprint_array_raw(out, n, a.values);
a_values_free:
  free(a.values);
a_positions_free:
  free(a.positions);
arr_free:
  jagged1_free(arr);
  return errno;
}
