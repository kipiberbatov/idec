#ifndef _double_string_scan_h_
#define _double_string_scan_h_

/*
Read from a constant string and return a number of type double.
If the reading is unsuccessful, return -1 and set errno to EINVAL.
*/
double double_string_scan(const char * s);

#endif /* _double_string_scan_h_ */
