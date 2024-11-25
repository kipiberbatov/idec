#include <errno.h>
#include <stdlib.h>

#include "color.h"
#include "double.h"
#include "int.h"

double_array_sequence_dynamic *
double_array_sequence_dynamic_file_scan(FILE * in)
{
  size_t type_size;
  int dimension, i, j, length;
  double ** values;
  double_array_sequence_dynamic * a;

  type_size = sizeof(double_array_sequence_dynamic);
  a = (double_array_sequence_dynamic *) malloc(type_size);
  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot allocate %ld bytes of memory for a\n", type_size);
    goto end;
  }

  length = int_file_scan(in);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan length\n", stderr);
    goto a_free;
  }

  dimension = int_file_scan(in);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan dimension\n", stderr);
    goto a_free;
  }

  values = malloc(sizeof(double) * length);
  if (values == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for values\n",
      sizeof(double) * length);
    goto a_free;
  }

  for (i = 0; i < length; ++i)
  {
    values[i] = double_array_file_scan(in, dimension, "--raw");
    if (errno)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan values[%d]\n", i);
      goto values_free;
    }
  }
  a->length = length;
  a->dimension = dimension;
  a->capacity = length;
  a->values = values;
  return a;

  /* cleaning if an error occurs */
values_free:
  for (j = i - 1; j >= 0; --j)
    free(values[j]);
  free(values);
a_free:
  free(a);
end:
  return NULL;
}
