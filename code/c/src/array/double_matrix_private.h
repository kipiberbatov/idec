#ifndef _double_matrix_private_h
#define _double_matrix_private_h

#include <stdio.h>

/************************** double_matrix_file_scan ***************************/
double * double_matrix_file_scan_raw(FILE * in, int m, int n);

/************************** double_matrix_file_print **************************/
void double_matrix_file_print_raw(FILE * out, int m, int n, const double * a);
void double_matrix_file_print_curly(FILE * out, int m, int n, const double * a);

#endif /* _double_matrix_private_h */
