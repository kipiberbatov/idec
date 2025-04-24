#include "double_array_private.h"
#include "double_array2_private.h"

void
double_array2_file_print_raw(FILE * out, int a0, const int * a1, double ** a2)
{
  int i;

  for (i = 0; i < a0; ++i)
    double_array_file_print_raw(out, a1[i], a2[i]);
}
