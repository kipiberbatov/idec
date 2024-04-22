#include <errno.h>
#include <stdlib.h>
#include "int.h"

int int_file_scan(FILE * in)
{
  int a, correct;
  
  correct = fscanf(in, "%d", &a);
  if (correct <= 0)
  {
    errno = EINVAL;
    if (correct == 0)
      fputs("int_file_scan - not a valid integer\n", stderr);
    else
      fputs("int_file_scan - there is no number to scan\n", stderr);
    return -1;
  }
  return a;
}
