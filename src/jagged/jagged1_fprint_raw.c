#include "int.h"
#include "jagged_private.h"

void jagged1_fprint_raw(FILE * out, const jagged1 * arr)
{
  fprintf(out, "%d\n", arr->a0);
  int_array_fprint(out, arr->a0, arr->a1, "--raw");
}
