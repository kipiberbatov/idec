#include <stdlib.h>
#include "jagged.h"

void jagged1_free(jagged1 * arr)
{
  free(arr->a1);
  free(arr);
}
