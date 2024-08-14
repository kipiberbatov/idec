#include "array_file_print.h"
#include "jagged_private.h"

void jagged3_file_print_curly(FILE * out, const jagged3 * arr)
{
  array_file_print3(out, arr->a0, arr->a1, arr->a2, arr->a3);
  fputc('\n', out);
}
