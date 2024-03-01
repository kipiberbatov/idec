#ifndef VECTOR_SPARSE_PRIVATE_H
#define VECTOR_SPARSE_PRIVATE_H

#include "vector_sparse.h"
#include "cs.h"

/**************************** vector_sparse_wrapper ***************************/
void vector_sparse_to_cs(cs * a0, const vector_sparse * a);
void vector_sparse_from_cs(vector_sparse * a, const cs * a0);

/**************************** vector_sparse_fscan *****************************/
vector_sparse * vector_sparse_fscan_raw(FILE * in);

#define VECTOR_SPARSE_FSCAN_FORMAT_TOTAL 1

static const char *
vector_sparse_fscan_format[VECTOR_SPARSE_FSCAN_FORMAT_TOTAL] =
  {
    "--raw"
  };

typedef vector_sparse * (*vector_sparse_fscan_function_type)(FILE *);

static const vector_sparse_fscan_function_type
vector_sparse_fscan_function[VECTOR_SPARSE_FSCAN_FORMAT_TOTAL] =
  {
    vector_sparse_fscan_raw
  };

/**************************** vector_sparse_fprint ****************************/
void vector_sparse_fprint_only_values(FILE * out, const vector_sparse * a);
void vector_sparse_fprint_raw(FILE * out, const vector_sparse * a);
void vector_sparse_fprint_annotated(FILE * out, const vector_sparse * a);
void vector_sparse_fprint_curly(
  FILE * out, const vector_sparse * a);
void vector_sparse_fprint_mathematica_sparse(
  FILE * out, const vector_sparse * a);

#define VECTOR_SPARSE_FPRINT_FORMAT_TOTAL 5

static const char *
vector_sparse_fprint_format[VECTOR_SPARSE_FPRINT_FORMAT_TOTAL] =
  {
    "--only-values",
    "--raw",
    "--annotated",
    "--curly",
    "--mathematica-sparse"
  };

typedef void (*vector_sparse_fprint_function_type)(
  FILE *, const vector_sparse *);

static const vector_sparse_fprint_function_type
vector_sparse_fprint_function[VECTOR_SPARSE_FPRINT_FORMAT_TOTAL] =
  {
    vector_sparse_fprint_only_values,
    vector_sparse_fprint_raw,
    vector_sparse_fprint_annotated,
    vector_sparse_fprint_curly,
    vector_sparse_fprint_mathematica_sparse
  };

#endif /* VECTOR_SPARSE_PRIVATE_H */
