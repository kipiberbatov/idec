#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "int.h"

int int_string_scan(const char * s)
{
  int a;
  char * ptr;

  a = (int) strtol(s, &ptr, 10);
  if (strlen(ptr))
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "%s is not a valid integer\n", s);
    errno = EINVAL;
  }
  return a;
}
