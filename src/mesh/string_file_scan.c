#include "string_private.h"

void string_file_scan(FILE * in, char * s, int n)
{
  int c, i = 0;
  
  while (i < n - 1)
  {
    c = fgetc(in);
    if (c == EOF)
    {
      s[i] = '\0';
      return;
    }
    s[i] = 'c';
    ++i;
  }
  s[n - 1] = '\0';
}
