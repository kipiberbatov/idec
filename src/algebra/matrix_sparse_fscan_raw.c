#include <errno.h>
#include <stdlib.h>
#include "double.h"
#include "int.h"
#include "matrix_sparse_private.h"

matrix_sparse * matrix_sparse_fscan_raw(FILE * in)
{
  matrix_sparse * a;
  
  a = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (errno)
  {
    perror("Cannot allocate memory for matrix_sparse");
    return NULL;
  }
  a->rows = int_fscan(in);
  if (errno)
  {
    perror("Problem with scanning rows");
    free(a);
    return NULL;
  }
  /* check if a->rows > 0 */
  a->cols = int_fscan(in);
  if (errno)
  {
    perror("Problem with scanning columns");
    free(a);
    return NULL;
  }
  /* check if a->cols > 0 */
  a->cols_total = int_fscan_array(in, a->cols + 1);
  if (errno)
  {
    perror("Problem with scanning cols_total");
    free(a);
    return NULL;
  }
  /* check if such a matrix is possible */
  a->row_indices = int_fscan_array(in, a->cols_total[a->cols]);
  if (errno)
  {
    perror("Problem with scanning cols_total");
    free(a->cols_total);
    free(a);
    return NULL;
  }
  /* check if such a matrix is possible */
  a->values = double_fscan_array(in, a->cols_total[a->cols]);
  if (errno)
  {
    perror("Problem with scanning cols_total");
    free(a->row_indices);
    free(a->cols_total);
    free(a);
    return NULL;
  }
  return a;
}
