#ifndef _double_matrix_file_print_raw_h_
#define _double_matrix_file_print_raw_h_

#include <stdio.h>

/*
Print to a file an matrix of doubles in the form
  a[0][0] a[0][1] ... a[0][n - 1]
  ...
  a[m - 1][0] a[m - 1][1] ... a[m - 1][n - 1]
*/
void double_matrix_file_print_raw(FILE * out, int m, int n, const double * a);

#endif /* _double_matrix_file_print_raw_h_ */
