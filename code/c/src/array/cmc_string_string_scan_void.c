#include "cmc_string.h"

void cmc_string_string_scan_void(void * result, int * status, const char * s)
{
  *((const char **) result) = s;
}
