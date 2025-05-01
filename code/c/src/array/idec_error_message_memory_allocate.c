#include <stdio.h>

#include "color.h"
#include "idec_error_message.h"

void idec_error_message_memory_allocate(const char * name)
{
  fprintf(stderr,
    "cannot allocate memory for variable %s%s%s\n",
    color_variable, name, color_none);
}
