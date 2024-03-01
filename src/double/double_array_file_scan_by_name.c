#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "double_array_file_scan.h"
#include "double_array_file_scan_by_name.h"

/*
Scan an array of doubles from a file given by its name.
Return a pointer to an array of type double.
If the reading is unsuccessful, return NULL and set errno to EINVAL.
*/
double * double_array_file_scan_by_name(
  const char * name,
  int n,
  const char * format)
{
  FILE * in;
  double * a = NULL;
  
  /* try opening a file by the given name */
  in = fopen(name, "r");
  if (errno)
  {
    fprintf(stderr, "Error in %s - cannot open file %s\n", __func__, name);
    fprintf(stderr, " (%s)\n", strerror(errno));
    goto end;
  }
  
  /* try scanning the result */
  a = double_array_file_scan(in, n, format);
  if (errno)
  {
    fprintf(
      stderr,
      "Error in %s: cannot scan in format %s\n",
      __func__,
      format
    );
    goto in_close;
  }

in_close:
  fclose(in);
end:
  return a;
}
