#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double.h"

double ** double_array2_file_scan_by_name(
  const char * name, int a0, const int * a1, const char * format)
{
  int i;
  double ** a = NULL;
  FILE * in;

  in = fopen(name, "r");
  if (errno)
  {
    fprintf(stderr, "double_array2_file_scan_by_name: cannot open file %s: %s\n",
            name, strerror(errno));
    goto end;
  }
  
  a = (double **) malloc(sizeof(double *) * a0);
  if (errno)
  {
    fputs("double_array2_file_scan_by_name: cannot allocate memory for a\n",
          stderr);
    return NULL;
  }
  for (i = 0; i < a0; ++i)
  {
    a[i] = double_array_file_scan(in, a1[i], format);
    if (errno)
    {
      fprintf(stderr, "double_array2_file_scan_by_name - cannot scan ");
      fprintf(stderr, "a[%d]: %s\n", i, strerror(errno));
      double_array2_free(a, i);
      fclose(in);
      return NULL;
    }
  }
  fclose(in);
end:
  return a;
}
