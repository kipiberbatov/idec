#ifndef _double_array2_file_scan_by_name_h_
#define _double_array2_file_scan_by_name_h_

/*
Scan an array of arrays of doubles from a file given by its name.
Return a pointer to pointer of type double (array of arrays).
If the reading is unsuccessful, return NULL and set errno to EINVAL.
*/
double ** double_array2_file_scan_by_name(
  const char * name,
  int a0,
  const int * a1,
  const char * format);

#endif /* _double_array2_file_scan_by_name_h_ */
