#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double.h"

double ** double_array2_file_scan_by_name(
  const char * name, int a0, const int * a1, const char * format)
{
  FILE * in;
  double ** a = NULL;

  in = fopen(name, "r");
  if (in == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open file %s: %s\n", name, strerror(errno));
    goto end;
  }

  a = double_array2_file_scan(in, a0, a1, format);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan file %s\n", name);
    goto in_close;
  }

in_close:
  fclose(in);
end:
  return a;
}
