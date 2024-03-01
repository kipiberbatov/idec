#ifndef _double_file_scan_h_
#define _double_file_scan_h_

#include <stdio.h>

/*
Read from a file and return a number of type double.
If the reading is unsuccessful, return -1 and set errno to EINVAL.
*/
double double_file_scan(FILE * in);

#endif /* _double_file_scan_h_ */
