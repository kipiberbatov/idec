#include "array_file_print.h"
#include "jagged_private.h"

void jagged4_file_print_curly(FILE * out, const jagged4 * arr)
{
  array_file_print4(out, arr->a0, arr->a1, arr->a2, arr->a3, arr->a4);
  fputc('\n', out);
}
