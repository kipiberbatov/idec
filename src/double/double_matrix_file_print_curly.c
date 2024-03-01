#include "double_array_file_print.h"
#include "double_matrix_file_print_curly.h"

/*
Print to a file an matrix of doubles in the form
  {{a[0][0],a[0][1],...,a[0][n - 1]},
  ...
  {a[m - 1][0],a[m - 1][1],a[m - 1][n - 1]}}
*/
void double_matrix_file_print_curly(FILE * out, int m, int n, const double * a)
{
  int i, ind;
  
  fputc('{', out);
  ind = 0;
  for (i = 0; i < m - 1; ++i)
  {
    double_array_file_print(out, n, a + ind, "--curly");
    fputc(',', out);
    ind += n;
  }
  if (m > 0)
    double_array_file_print(out, n, a + ind, "--curly");
  fputc('}', out);
}
