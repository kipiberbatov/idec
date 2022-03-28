#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "array_indexed.h"
#include "int.h"
#include "jagged.h"

int main()
{
  int n;
  jagged1 * arr = NULL;
  array_indexed a;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  
  arr = jagged1_fscan(in, "--raw");
  if (errno)
  {
    fputs("main - cannot scan arr\n", stderr);
    goto end;
  }
  
  n = arr->a0;
  
  a.positions = (int *) malloc(sizeof(int) * n);
  if (errno)
  {
    fputs("main - cannot allocate memory for a.positions\n", stderr);
    goto arr_free;
  }
  int_array_assign_identity(a.positions, n);
  
  a.values = (int *) malloc(sizeof(int) * n);
  if (errno)
  {
    fputs("main - cannot allocate memory for a.values\n", stderr);
    goto a_positions_free;
  }
  memcpy(a.values, arr->a1, sizeof(int) * n);
  
  array_indexed_merge_sort(&a, n);
  if (errno)
  {
    fputs("main - cannot merge sort a\n", stderr);
    goto a_values_free;
  }
  
  fprintf(stdout, "%d\n", arr->a0);
  int_array_fprint(out, n, a.values, "--raw");

a_values_free:
  free(a.values);
a_positions_free:
  free(a.positions);
arr_free:
  jagged1_free(arr);
end:
  return errno;
}
