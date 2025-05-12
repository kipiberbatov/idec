#ifndef _cmc_string_h
#define _cmc_string_h

#include <stdio.h>

void cmc_string_string_scan_void(void * result, int * status, const char * s);

void cmc_string_file_print_void(FILE * out, const void * x);

void
cmc_string_set_default_void(void * argument, const void * default_argument);

#endif /* _cmc_string_h */
