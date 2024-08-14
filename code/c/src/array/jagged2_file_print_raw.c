#include "int.h"
#include "jagged_private.h"

void jagged2_file_print_raw(FILE * out, const jagged2 * arr)
{
  int arr_a2_size;

  fprintf(out, "%d\n", arr->a0);
  int_array_file_print(out, arr->a0, arr->a1, "--raw");
  arr_a2_size = int_array_total_sum(arr->a0, arr->a1);
  int_array_file_print(out, arr_a2_size, arr->a2, "--raw");
}
