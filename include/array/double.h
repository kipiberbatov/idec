#ifndef DOUBLE_H
#define DOUBLE_H

#include <stdio.h>

/********************************* double_free ********************************/
void double_free_array2(double ** arr, int n);

/******************************** double_fscan ********************************/
double double_fscan(FILE * in);
double * double_fscan_array(FILE * in, int n);
double ** double_fscan_array2(FILE * in, int a0, int * a1);
double * double_fscan_matrix(FILE * in, int rows, int cols);

/******************************** double_fprint *******************************/
void double_fprint_array(FILE * out, int n, const double * a);

void double_fprint_array_annotated(
  FILE * out, int n, const double * a, const char * name);

void double_fprint_array_raw(FILE * out, int n, const double * a);

void double_fprint_array2_annotated(
  FILE * out, int m_dim, const int * n, double ** a, const char * name);

void double_fprint_matrix(FILE * out, int m, int n, const double * a);

void double_fprint_matrix_raw(FILE * out, int m, int n, const double * a);

void double_fprint_matrix_annotated(
  FILE * out, int m, int n, const double * a, const char * name);

#endif /* DOUBLE_H */
