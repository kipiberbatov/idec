#include <errno.h>
#include <stdlib.h>
#include "int.h"

int int_fscan(FILE * in)
{
  int a, correct;
  
  correct = fscanf(in, "%d", &a);
  if (correct <= 0)
  {
    errno = EINVAL;
    if (correct == 0)
      fputs("int_fscan - not a valid integer\n", stderr);
    else
      fputs("int_fscan - there is no number to scan\n", stderr);
    return -1;
  }
  return a;
}
