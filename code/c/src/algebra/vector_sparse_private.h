#ifndef _vector_sparse_private_h
#define _vector_sparse_private_h

#include "vector_sparse.h"

/**************************** vector_sparse_file_scan *****************************/
vector_sparse * vector_sparse_file_scan_raw(FILE * in);

/**************************** vector_sparse_file_print ****************************/
void vector_sparse_file_print_only_values(FILE * out, const vector_sparse * a);
void vector_sparse_file_print_raw(FILE * out, const vector_sparse * a);
void vector_sparse_file_print_annotated(FILE * out, const vector_sparse * a);
void vector_sparse_file_print_curly(FILE * out, const vector_sparse * a);
void vector_sparse_file_print_mathematica_sparse(
  FILE * out, const vector_sparse * a);

#endif /* _vector_sparse_private_h */
