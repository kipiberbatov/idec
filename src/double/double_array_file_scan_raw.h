#ifndef _double_array_file_scan_raw_h_
#define _double_array_file_scan_raw_h_

#include <stdio.h>

/*
Scan an array of doubles stored as blank space separated values.
Return NULL if the scan is unsuccessful and set errno to EINVAL.
*/
double * double_array_file_scan_raw(FILE * in, int n);

#endif /* _double_array_file_scan_raw_h_ */
