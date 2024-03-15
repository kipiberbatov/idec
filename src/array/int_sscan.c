#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "int.h"

int int_sscan(const char * s)
{
  int a;
  char * ptr;

  a = (int) strtol(s, &ptr, 10);
  if (strlen(ptr))
  {
    errno = EINVAL;
    fprintf(stderr,
    "Error during execution of function %s in file %s on line %d: "
    "%s is not a valid integer\n",
    __func__, __FILE__, __LINE__, s);
  }
  return a;
}
