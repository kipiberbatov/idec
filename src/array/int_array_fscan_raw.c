#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "int_private.h"

int * int_array_file_scan_raw(FILE * in, int n)
{
  int i;
  int * a;
  
  a = (int *) malloc(sizeof(int) * n);
  if (errno)
  {
    perror("int_array_file_scan_raw - cannot allocate memory for array");
    return NULL;
  }
  for (i = 0; i < n; ++i)
  {
    a[i] = int_file_scan(in);
    if (errno)
    {
      fprintf(stderr,
              "int_array_file_scan_raw - unsuccessfull scanning of a[%d]: %s\n",
              i, strerror(errno));
      free(a);
      return NULL;
    }
  }
  return a;
}
