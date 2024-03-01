#ifndef _double_array_file_print_curly_h_
#define _double_array_file_print_curly_h_

#include <stdio.h>

/*
Print to a file an array of doubles in the form {a[0],a[1],...,a[n-1]}.
*/
void double_array_file_print_curly(FILE * out, int n, const double * a);

#endif /* _double_array_file_print_curly_h_ */
