#ifndef _double_matrix_h
#define _double_matrix_h

#include <stdio.h>

double * double_matrix_file_scan(FILE * in, int m, int n, const char * format);

double * double_matrix_file_scan_by_name(
  const char * name, int m, int n, const char * format);

void double_matrix_file_print(
  FILE * out, int m, int n, const double * a, const char * format);

#endif /* _double_matrix_h */
