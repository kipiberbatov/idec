#ifndef _double_array2_private_h
#define _double_array2_private_h

#include <stdio.h>

/************************** double_array2_file_scan ***************************/
double ** double_array2_file_scan_raw(FILE * in, int a0, const int * a1);

/************************** double_array2_file_print **************************/
void
double_array2_file_print_raw(FILE * out, int a0, const int * a1, double ** a2);

#endif /* _double_array2_private_h */
