#include "cmc_string.h"

void
cmc_string_set_default_void(void * argument, const void * default_argument)
{
  *(const char **) argument = (const char *) default_argument;
}
