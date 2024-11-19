#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double.h"

double * double_matrix_file_scan_by_name(
  const char * name, int m, int n, const char * format)
{
  FILE * in;
  double * a = NULL;

  in = fopen(name, "r");
  if (in == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open file %s: %s\n", name, strerror(errno));
    goto end;
  }

  a = double_matrix_file_scan(in, m, n, format);
  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan matrix a from file %s in format %s\n",
      name, format);
    goto in_close;
  }

in_close:
  fclose(in);
end:
  return a;
}
