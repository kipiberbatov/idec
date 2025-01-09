#include "int.h"

void int_file_print_void(FILE * out, const void * x)
{
  fprintf(out, "%d", *((const int *) x));
}
