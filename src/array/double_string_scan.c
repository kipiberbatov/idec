#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "int.h"

double double_string_scan(const char * s)
{
  double a;
  char * ptr;

  a = strtod(s, &ptr);
  if (strlen(ptr))
  {
    errno = EINVAL;
    fprintf(stderr,
    "Error during execution of function %s in file %s on line %d: "
    "%s is not a valid floating point number\n",
    __func__, __FILE__, __LINE__, s);
  }
  return a;
}
