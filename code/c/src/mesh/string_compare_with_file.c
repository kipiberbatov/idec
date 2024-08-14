#include "string_private.h"

int string_compare_with_file(FILE * in, int n, const char * s)
{
  int c, i = 0;

  while (i < n)
  {
    c = fgetc(in);
    if (c == EOF)
      return -2;
    if (c < s[i])
      return -1;
    if (c > s[i])
      return 1;
    ++i;
  }
  return 0;
}
