#ifndef _double_matrix_file_scan_h_
#define _double_matrix_file_scan_h_

#include <stdio.h>

/*
Read from a file in a specified format up to a specified length.
Return a pointer to a flattened matrix of type double.
If the reading is unsuccessful, return NULL and set errno to EINVAL.

Supported formats:
  --raw
*/
double * double_matrix_file_scan(FILE * in, int m, int n, const char * format);

#endif /* _double_matrix_file_scan_h_ */
