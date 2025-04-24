#ifndef _double_array_sequence_dynamic_h
#define _double_array_sequence_dynamic_h

#include <stdio.h>

typedef struct double_array_sequence_dynamic
{
  int capacity;
  int length;
  int dimension;
  double ** values;
} double_array_sequence_dynamic;

void double_array_sequence_dynamic_free(double_array_sequence_dynamic * a);

void double_array_sequence_dynamic_file_print(
  FILE * out,
  const double_array_sequence_dynamic * a);

double_array_sequence_dynamic *
double_array_sequence_dynamic_file_scan(FILE * in);

double_array_sequence_dynamic *
double_array_sequence_dynamic_file_scan_by_name(const char * name);

void double_array_sequence_dynamic_resize(double_array_sequence_dynamic * a);

double_array_sequence_dynamic * double_array_sequence_dynamic_initialize(int n);

#endif /* _double_array_sequence_dynamic_h */
