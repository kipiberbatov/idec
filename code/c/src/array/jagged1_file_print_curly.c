#include "array_file_print.h"
#include "jagged_private.h"

void jagged1_file_print_curly(FILE * out, const jagged1 * arr)
{
  array_file_print1(out, arr->a0, arr->a1);
  fputc('\n', out);
}
