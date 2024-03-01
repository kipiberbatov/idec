#ifndef _double_array_file_scan_h_
#define _double_array_file_scan_h_

#include <stdio.h>

/*
Read from a file in a specified format up to a specified length.
Return a pointer to an array of type double.
If the reading is unsuccessful, return NULL and set errno to EINVAL.

Supported formats:
  --raw
*/
double * double_array_file_scan(FILE * in, int n, const char * format);

#endif /* _double_array_file_scan_h_ */
