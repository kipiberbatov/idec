#include <errno.h>
#include <stdlib.h>
#include "int.h"

int int_sscan(const char * s)
{
  int a, correct;
  
  correct = sscanf(s, "%d", &a);
  if (correct <= 0)
  {
    errno = EINVAL;
    if (correct == 0)
      fputs("int_sscan - not a valid integer\n", stderr);
    else
      fputs("int_sscan - empty string\n", stderr);
    return -1;
  }
  return a;
}
