#include "double.h"

void double_file_print_void(FILE * out, const void * x)
{
  fprintf(out, "%g", *((const double *) x));
}
