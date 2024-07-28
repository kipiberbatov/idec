#include <errno.h>
#include <stdlib.h>
#include <string.h>

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
    double_array_file_print(out, dimension, values[i], "--raw");
}

double_array_sequence_dynamic *
double_array_sequence_dynamic_file_scan(FILE * in)
{
  size_t type_size;
  int dimension, i, j, length;
  double ** values;
  double_array_sequence_dynamic * a;

  type_size = sizeof(double_array_sequence_dynamic);
  a = (double_array_sequence_dynamic *) malloc(type_size);
  if (errno)
  {
    fputs("Cannot allocate memory for final result\n", stderr);
    goto end;
  }

  length = int_file_scan(in);
  if (errno)
  {
    fputs("Cannot scan length\n", stderr);
    goto a_free;
  }

  dimension = int_file_scan(in);
  if (errno)
  {
    fputs("Cannot scan dimension\n", stderr);
    goto a_free;
  }

  values = malloc(sizeof(double) * length);
  if (errno)
  {
    fputs("Cannot allocate memory for values\n", stderr);
    goto a_free;
  }

  for (i = 0; i < length; ++i)
  {
    values[i] = double_array_file_scan(in, dimension, "--raw");
    if (errno)
    {
      fprintf(stderr, "Cannot scan values[%d]\n", i);
      goto values_free;
    }
  }
  a->length = length;
  a->dimension = dimension;
  a->capacity = length;
  a->values = values;
  return a;

  /* Cleaning if an error occurs */
values_free:
  for (j = i - 1; j >= 0; --j)
    free(values[j]);
  free(values);
a_free:
  free(a);
end:
  return NULL;
}

double_array_sequence_dynamic *
double_array_sequence_dynamic_file_scan_by_name(const char * name)
{
  FILE * in;
  double_array_sequence_dynamic * a;

  in = fopen(name, "r");
  if (errno)
  {
    fprintf(stderr, "Cannot open file %s: %s\n", name, strerror(errno));
    return NULL;
  }

  a = double_array_sequence_dynamic_file_scan(in);
  if (errno)
  {
    fprintf(stderr, "Cannot scan file %s\n", name);
    goto in_close;
  }

in_close:
  fclose(in);
  return a;
}

void double_array_sequence_dynamic_resize(double_array_sequence_dynamic * a)
{
  double ** tmp;

  tmp = (double **) realloc(a->values, sizeof(double *) * 2 * a->capacity);
  if (errno)
  {
    fprintf(stderr, "Cannot allocate memory for temporary array\n");
    return;
  }
  a->values = tmp;
  a->capacity *= 2;
}

double_array_sequence_dynamic * double_array_sequence_dynamic_initialize(int n)
{
  size_t type_size;
  double_array_sequence_dynamic * a;

  type_size = sizeof(double_array_sequence_dynamic);
  a = (double_array_sequence_dynamic *) malloc(type_size);
  /* NULL pointer checking */
  a->capacity = 8;
  a->length = 1;
  a->dimension = n;
  a->values = malloc(sizeof(double *) * a->capacity);
  /* NULL pointer checking */
  a->values[0] = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */
  return a;
}
