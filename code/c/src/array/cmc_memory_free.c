#include <stdlib.h>

#include "cmc_memory.h"

void cmc_memory_free(void * data)
{
  free(data);
}
