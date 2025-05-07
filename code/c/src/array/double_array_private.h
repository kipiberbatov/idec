#ifndef _double_array_private_h
#define _double_array_private_h

#include <stdio.h>

/*************************** double_array_file_scan ***************************/
double * double_array_file_scan_raw(FILE * in, int n);
double * double_array_file_scan_steady_state_primal_weak_raw(FILE * in, int n);
double * double_array_file_scan_transient_primal_strong_raw(FILE * in, int n);
double * double_array_file_scan_transient_primal_weak_raw(FILE * in, int n);
double *
double_array_file_scan_steady_state_dual_conductivity_raw(FILE * in, int n);

/************************** double_array_file_print ***************************/
void double_array_file_print_raw(FILE * out, int n, const double * a);
void double_array_file_print_curly(FILE * out, int n, const double * a);

#endif /* _double_array_private_h */
