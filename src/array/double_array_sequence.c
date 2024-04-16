#include <errno.h>
#include <stdlib.h>

#include "double.h"
#include "int.h"

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
    double_array_fprint(out, dimension, values[i], "--raw");
}

double_array_sequence_dynamic *
double_array_sequence_dynamic_file_scan(FILE * in)
{
  double_array_sequence_dynamic * a;
  int dimension, i, length;
  double ** values;

  a = (double_array_sequence_dynamic *) malloc(
    sizeof(double_array_sequence_dynamic));
  length = int_fscan(in);
  dimension = int_fscan(in);
  values = malloc(sizeof(double) * length);
  for (i = 0; i < length; ++i)
    values[i] = double_array_fscan(in, dimension, "--raw");
  a->length = length;
  a->dimension = dimension;
  a->capacity = length;
  a->values = values;
  return a;
}
