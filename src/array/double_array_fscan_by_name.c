#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double.h"

double * double_array_fscan_by_name(
  const char * name, int n, const char * format)
{
  FILE * in;
  double * a = NULL;

  in = fopen(name, "r");
  if (errno)
  {
    fprintf(stderr, "double_array_fscan_by_name - cannot open file %s: %s\n",
            name, strerror(errno));
    goto end;
  }
  
  a = double_array_fscan(in, n, format);
  if (errno)
  {
    fprintf(stderr, "double_array_fscan_by_name - cannot scan a ");
    fprintf(stderr, "in format %s: %s\n", format, strerror(errno));
    goto in_close;
  }

in_close:
  fclose(in);
end:
  return a;
}
