#ifndef CS_PRIVATE_H
#define CS_PRIVATE_H

#include "cs.h"

void cs_fprint_only_values(FILE * out, const cs * a);
void cs_fprint_raw(FILE * out, const cs * a);
void cs_fprint_annotated(FILE * out, const cs * a);
void cs_fprint_matrix_form_raw(FILE * out, const cs * a);
void cs_fprint_matrix_form_curly(FILE * out, const cs * a);
void cs_fprint_mathematica_sparse(FILE * out, const cs * a);

#endif /* CS_PRIVATE_H */
