#include <stdlib.h>

#include "double.h"

void double_array_sequence_dynamic_free(double_array_sequence_dynamic * a)
{
  int i, length;
  double ** values;

  length = a->length;
  values = a->values;

  for (i = length - 1; i >= 0; --i)
    free(values[i]);
  free(values);
  free(a);
}
