#ifndef VECTOR_SPARSE_PRIVATE_H
#define VECTOR_SPARSE_PRIVATE_H

#include "vector_sparse.h"
#include "cs.h"

/**************************** vector_sparse_wrapper ***************************/
void vector_sparse_to_cs(cs * a0, const vector_sparse * a);
void vector_sparse_from_cs(vector_sparse * a, const cs * a0);

/**************************** vector_sparse_file_scan *****************************/
vector_sparse * vector_sparse_file_scan_raw(FILE * in);

#define VECTOR_SPARSE_file_scan_format_total 1

static const char *
vector_sparse_file_scan_format[VECTOR_SPARSE_file_scan_format_total] =
  {
    "--raw"
  };

typedef vector_sparse * (*vector_sparse_file_scan_function_type)(FILE *);

static const vector_sparse_file_scan_function_type
vector_sparse_file_scan_function[VECTOR_SPARSE_file_scan_format_total] =
  {
    vector_sparse_file_scan_raw
  };

/**************************** vector_sparse_file_print ****************************/
void vector_sparse_file_print_only_values(FILE * out, const vector_sparse * a);
void vector_sparse_file_print_raw(FILE * out, const vector_sparse * a);
void vector_sparse_file_print_annotated(FILE * out, const vector_sparse * a);
void vector_sparse_file_print_curly(
  FILE * out, const vector_sparse * a);
void vector_sparse_file_print_mathematica_sparse(
  FILE * out, const vector_sparse * a);

#define VECTOR_SPARSE_file_print_format_total 5

static const char *
vector_sparse_file_print_format[VECTOR_SPARSE_file_print_format_total] =
  {
    "--only-values",
    "--raw",
    "--annotated",
    "--curly",
    "--mathematica-sparse"
  };

typedef void (*vector_sparse_file_print_function_type)(
  FILE *, const vector_sparse *);

static const vector_sparse_file_print_function_type
vector_sparse_file_print_function[VECTOR_SPARSE_file_print_format_total] =
  {
    vector_sparse_file_print_only_values,
    vector_sparse_file_print_raw,
    vector_sparse_file_print_annotated,
    vector_sparse_file_print_curly,
    vector_sparse_file_print_mathematica_sparse
  };

#endif /* VECTOR_SPARSE_PRIVATE_H */
