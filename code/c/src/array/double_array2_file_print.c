#include <string.h>

#include "color.h"
#include "double.h"

static void double_array2_file_print_raw(FILE * out,
  int a0, const int * a1, double ** a2)
{
  int i;

  for (i = 0; i < a0; ++i)
    double_array_file_print(out, a1[i], a2[i], "--raw");
}

void double_array2_file_print(FILE * out, int * status,
  int a0, const int * a1, double ** a2, const char * format)
{
  if (!strcmp(format, "raw"))
    double_array2_file_print_raw(out, a0, a1, a2);
  else
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "format %s is not supported\n", format);
    *status = 1;
  }
}
