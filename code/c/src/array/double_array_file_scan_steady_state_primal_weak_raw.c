#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double_private.h"
#include "int.h"

double * double_array_file_scan_steady_state_primal_weak_raw(FILE * in, int n)
{
  int x;
  double * a = NULL;

  x = int_file_scan(in);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan number_of_cells_1\n", stderr);
    return NULL;
  }

  x = int_file_scan(in);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan number_of_cells_d\n", stderr);
    return NULL;
  }
  
  /* doing useless work to convince the compiler that variable 'x' is used */
  x = 0;
  if (x == 0)
    a = double_array_file_scan_raw(in, n);
  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan array of length %d\n", n);
    return NULL;
  }

  return a;
}
