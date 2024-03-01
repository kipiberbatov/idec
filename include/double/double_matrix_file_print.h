#ifndef _double_matrix_file_print_h_
#define _double_matrix_file_print_h_

#include <stdio.h>

/*
Write a matrix of doubles of size m * n to a file in a specified format.

Supported formats:
  --raw
  --curly
*/
void double_matrix_file_print(
  FILE * out,
  int m,
  int n,
  const double * a,
  const char * format);

#endif /* _double_matrix_file_print_h_ */
