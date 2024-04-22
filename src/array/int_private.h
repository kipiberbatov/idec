#ifndef _int_private_h
#define _int_private_h

#include "int.h"

/****************************** int_array_file_scan *******************************/
int * int_array_file_scan_raw(FILE * in, int n);

/****************************** int_array_file_print ******************************/
void int_array_file_print_raw(FILE * out, int n, const int * a);
void int_array_file_print_curly(FILE * out, int n, const int * a);

#endif /* _int_private_h */
