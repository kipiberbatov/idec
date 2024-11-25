#include <stdlib.h>

#include "color.h"
#include "double.h"

void double_array_sequence_dynamic_resize(double_array_sequence_dynamic * a)
{
  double ** tmp;

  tmp = (double **) realloc(a->values, sizeof(double *) * 2 * a->capacity);
  if (tmp == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot reallocate %ld bytes of memory for tmp\n",
      sizeof(double *) * 2 * a->capacity);
    return;
  }
  a->values = tmp;
  a->capacity *= 2;
}
