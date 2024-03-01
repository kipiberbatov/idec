#ifndef _double_array_file_print_h_
#define _double_array_file_print_h_

#include <stdio.h>

/*
Write an array of doubles of size n to a file in a specified format.
If the writing is unsuccessful, set errno to EINVAL.

Supported formats:
  --raw
  --curly
*/
void double_array_file_print(
  FILE * out,
  int n,
  const double * a,
  const char * format);

#endif /* _double_array_file_print_h_ */
