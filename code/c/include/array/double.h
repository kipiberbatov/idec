#ifndef _double_h
#define _double_h

#include <stdio.h>

double double_file_scan(FILE * in);

double double_string_scan(const char * s);

void double_string_scan_void(void * result, int * status, const char * s);

void double_file_print_void(FILE * out, const void * x);

void double_set_default_void(void * argument, const void * default_argument);

int double_equal(double x, double y, double tolerance);

#endif /* _double_h */
