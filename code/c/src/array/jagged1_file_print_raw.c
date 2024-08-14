#include "int.h"
#include "jagged_private.h"

void jagged1_file_print_raw(FILE * out, const jagged1 * arr)
{
  fprintf(out, "%d\n", arr->a0);
  int_array_file_print(out, arr->a0, arr->a1, "--raw");
}
