#include "array_fprint.h"
#include "jagged_private.h"

void jagged2_fprint_curly(FILE * out, const jagged2 * arr)
{
  array_fprint2(out, arr->a0, arr->a1, arr->a2);
  fputc('\n', out);
}
