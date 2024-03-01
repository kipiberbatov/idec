#include <stdlib.h>
#include "jagged.h"

void jagged2_free(jagged2 * arr)
{
  free(arr->a2);
  free(arr->a1);
  free(arr);
}
