#include "idec_string.h"

void
idec_string_set_default_void(void * argument, const void * default_argument)
{
  *(const char **) argument = (const char *) default_argument;
}
