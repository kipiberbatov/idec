#ifndef _double_array2_h
#define _double_array2_h

#include <stdio.h>

void double_array2_free(double ** arr, int n);

double ** double_array2_file_scan(
  FILE * in, int a0, const int * a1, const char * format);

double ** double_array2_file_scan_by_name(
  const char * name, int a0, const int * a1, const char * format);

void double_array2_file_print(FILE * out, int * status,
  int a0, const int * a1, double ** a2, const char * format);

#endif /* _double_array2_h */
