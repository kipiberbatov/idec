#include <errno.h>
#include "int.h"
#include "jagged_private.h"

void jagged3_fprint_raw(FILE * out, const jagged3 * arr)
{
  int arr_a2_size, arr_a3_size;
  
  fprintf(out, "%d\n", arr->a0);
  int_array_fprint(out, arr->a0, arr->a1, "--raw");
  arr_a2_size = int_array_total_sum(arr->a0, arr->a1);
  int_array_fprint(out, arr_a2_size, arr->a2, "--raw");
  arr_a3_size = int_array_total_sum(arr_a2_size, arr->a3);
  int_array_fprint(out, arr_a3_size, arr->a3, "--raw");
}
