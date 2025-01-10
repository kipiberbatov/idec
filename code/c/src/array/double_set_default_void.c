#include "double.h"

void double_set_default_void(void * argument, const void * default_argument)
{
  *(double *) argument = *(const double *) default_argument;
}
