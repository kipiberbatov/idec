#ifndef _idec_string_h
#define _idec_string_h

#include <stdio.h>

void idec_string_string_scan_void(void * result, int * status, const char * s);

void idec_string_file_print_void(FILE * out, const void * x);

void
idec_string_set_default_void(void * argument, const void * default_argument);

#endif /* _idec_string_h */
