#include "idec_string.h"

void idec_string_file_print_void(FILE * out, const void * x)
{
  fputs(*((const char **) x), out);
}
