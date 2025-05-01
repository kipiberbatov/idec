#include <stdlib.h>

#include "idec_memory.h"

void idec_memory_free(void * data)
{
  free(data);
}
