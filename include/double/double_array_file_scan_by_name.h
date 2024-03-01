#ifndef _double_array_file_scan_by_name_h_
#define _double_array_file_scan_by_name_h_

/*
Scan an array of doubles from a file given by its name.
Return a pointer to an array of type double.
If the reading is unsuccessful, return NULL and set errno to EINVAL.
*/
double * double_array_file_scan_by_name(
  const char * name,
  int n,
  const char * format);

#endif /* _double_array_file_scan_by_name_h_ */
