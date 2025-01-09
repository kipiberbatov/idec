#include "idec_string.h"

void idec_string_string_scan_void(void * result, int * status, const char * s)
{
  *((const char **) result) = s;
}
