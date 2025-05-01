#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "idec_error_message.h"
#include "idec_memory.h"

void idec_memory_allocate(void ** data, int * status, size_t size)
{
  *data = malloc(size);
  if (*data == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %s%ld%s bytes of memory\n",
      color_variable, size, color_none);
    *status = ENOMEM;
  }
}
