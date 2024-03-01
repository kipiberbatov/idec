#ifndef _double_array2_file_scan_h_
#define _double_array2_file_scan_h_

#include <stdio.h>

/*
Read from a file in a specified format.
Return a pointer to an array of arrays of type double.
The result res is of size a0 and each of res[i] is of size a1[i].
If the reading is unsuccessful, return NULL and set errno to EINVAL.

Supported formats:
  --raw
*/
double * double_array2_file_scan(
  FILE * in,
  int a0,
  const int * a1,
  const char * format);

#endif /* _double_array2_file_scan_h_ */
