#include "cmc_string.h"

void cmc_string_file_print_void(FILE * out, const void * x)
{
  fputs(*((const char **) x), out);
}
