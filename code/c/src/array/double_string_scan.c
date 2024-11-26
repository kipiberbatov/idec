#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double.h"

double double_string_scan(const char * s)
{
  double a;
  char * ptr;

  a = strtod(s, &ptr);
  if (strlen(ptr))
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "%s is not a valid 64-bit float\n", s);
    errno = EINVAL;
  }
  return a;
}
