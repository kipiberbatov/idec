#include <errno.h>
#include <string.h>

#include "color.h"
#include "double.h"

double_array_sequence_dynamic *
double_array_sequence_dynamic_file_scan_by_name(const char * name)
{
  FILE * in;
  double_array_sequence_dynamic * a;

  in = fopen(name, "r");
  if (in == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open file %s: %s\n", name, strerror(errno));
    return NULL;
  }

  a = double_array_sequence_dynamic_file_scan(in);
  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan file %s\n", name);
    goto in_close;
  }

in_close:
  fclose(in);
  return a;
}
