#ifndef _double_matrix_file_scan_raw_h_
#define _double_matrix_file_scan_raw_h_

#include <stdio.h>

/*
Scan a matrix of doubles stored as blank space separated values.
Return NULL if the scan is unsuccessful.
*/
double * double_matrix_file_scan_raw(FILE * in, int m, int n);

#endif /* _double_matrix_file_scan_raw_h_ */
