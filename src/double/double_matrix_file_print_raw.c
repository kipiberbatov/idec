#include "double_array_file_prin.h"
#include "double_matrix_file_print_raw.h"

/*
Print to a file an matrix of doubles in the form
  a[0][0] a[0][1] ... a[0][n - 1]
  ...
  a[m - 1][0] a[m - 1][1] ... a[m - 1][n - 1]
*/
void double_matrix_fprint_raw(FILE * out, int m, int n, const double * a)
{
  int i, ind;
  
  ind = 0;
  for (i = 0; i < m; ++i)
  {
    double_array_file_print(out, n, a + ind, "--raw");
    ind += n;
  }
}
