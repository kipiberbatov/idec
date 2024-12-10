#include <stdio.h>

#include "idec_error_message.h"

void idec_error_message_malloc(size_t size, const char * name)
{
  fprintf(stderr, "cannot allocate %ld bytes of memory for %s\n", size, name);
}
