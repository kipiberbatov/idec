#ifndef _double_private_h
#define _double_private_h

#include "double.h"

/***************************** double_array_file_scan *****************************/
double * double_array_file_scan_raw(FILE * in, int n);

/**************************** double_array_file_print *****************************/
void double_array_file_print_raw(FILE * out, int n, const double * a);
void double_array_file_print_curly(FILE * out, int n, const double * a);

/**************************** double_array2_file_scan *****************************/
double ** double_array2_file_scan_raw(FILE * in, int a0, const int * a1);

/**************************** double_matrix_file_scan *****************************/
double * double_matrix_file_scan_raw(FILE * in, int m, int n);

/**************************** double_matrix_file_print ****************************/
void double_matrix_file_print_raw(FILE * out, int m, int n, const double * a);
void double_matrix_file_print_curly(FILE * out, int m, int n, const double * a);

#endif /* _double_private_h */
