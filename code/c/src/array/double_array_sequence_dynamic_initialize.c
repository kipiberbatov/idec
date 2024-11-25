#include <stdlib.h>

#include "color.h"
#include "double.h"

double_array_sequence_dynamic * double_array_sequence_dynamic_initialize(int n)
{
  size_t type_size;
  double_array_sequence_dynamic * a;

  type_size = sizeof(double_array_sequence_dynamic);
  a = (double_array_sequence_dynamic *) malloc(type_size);
  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot allocate %ld bytes of memory for a\n", type_size);
    goto end;
  }

  a->capacity = 8;
  a->length = 1;
  a->dimension = n;

  a->values = malloc(sizeof(double *) * a->capacity);
  if (a->values == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for a->values\n",
      sizeof(double *) * a->capacity);
    goto a_free;
  }

  a->values[0] = (double *) malloc(sizeof(double) * n);
  if (a->values[0] == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for a->values\n",
      sizeof(double) * n);
    goto a_values_free;
  }
  return a;

  /* cleaning if an error occurs */
a_values_free:
  free(a->values);
a_free:
  free(a);
end:
  return NULL;
}
