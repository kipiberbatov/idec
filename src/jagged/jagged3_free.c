#include <stdlib.h>
#include "jagged.h"

void jagged3_free(jagged3 * arr)
{
  free(arr->a3);
  free(arr->a2);
  free(arr->a1);
  free(arr);
}
