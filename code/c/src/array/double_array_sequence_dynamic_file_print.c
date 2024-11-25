#include "double.h"

void double_array_sequence_dynamic_file_print(
  FILE * out,
  const double_array_sequence_dynamic * a)
{
  int dimension, i, length;
  double ** values;

  length = a->length;
  dimension = a->dimension;
  values = a->values;

  fprintf(out, "%d\n%d\n", length, dimension);
  if (length == 0)
    return;
  for (i = 0; i < length; ++i)
    double_array_file_print(out, dimension, values[i], "--raw");
}
