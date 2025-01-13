#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double.h"

void double_string_scan_void(void * result, int * status, const char * s)
{
  char * ptr;

  *((double *) result) = (double) strtod(s, &ptr);
  if (strlen(ptr))
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "%s%s%s is not a valid floating point number\n",
      color_variable, s, color_none);
    *status = 1;
  }
}
