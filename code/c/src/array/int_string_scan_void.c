#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "int.h"

void int_string_scan_void(void * result, int * status, const char * s)
{
  char * ptr;

  if (*s == 0)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("empty string is not a valid integer\n", stderr);
    *status = 1;
  }

  *((int *) result) = (int) strtol(s, &ptr, 10);
  if (strlen(ptr))
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "%s%s%s is not a valid integer\n",
      color_variable, s, color_none);
    *status = 1;
  }
}
