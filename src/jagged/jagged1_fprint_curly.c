#include "array_fprint.h"
#include "jagged_private.h"

void jagged1_fprint_curly(FILE * out, const jagged1 * arr)
{
  array_fprint1(out, arr->a0, arr->a1);
  fputc('\n', out);
}
