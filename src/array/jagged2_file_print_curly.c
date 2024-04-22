#include "array_file_print.h"
#include "jagged_private.h"

void jagged2_file_print_curly(FILE * out, const jagged2 * arr)
{
  array_file_print2(out, arr->a0, arr->a1, arr->a2);
  fputc('\n', out);
}
