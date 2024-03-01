#include "array_fprint.h"
#include "jagged_private.h"

void jagged3_fprint_curly(FILE * out, const jagged3 * arr)
{
  array_fprint3(out, arr->a0, arr->a1, arr->a2, arr->a3);
  fputc('\n', out);
}
