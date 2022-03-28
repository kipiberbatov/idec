#include <stdlib.h>
#include "jagged.h"

void jagged4_free(jagged4 * arr)
{
  free(arr->a4);
  free(arr->a3);
  free(arr->a2);
  free(arr->a1);
  free(arr);
}
