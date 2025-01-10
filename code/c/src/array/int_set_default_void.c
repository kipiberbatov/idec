#include "int.h"

void int_set_default_void(void * argument, const void * default_argument)
{
  *(int *) argument = *(const int *) default_argument;
}
