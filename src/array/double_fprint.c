#include "double.h"

void double_fprint_array(FILE * out, int n, const double * a)
{
  int i;
  
  fputc('{', out);
  for (i = 0; i < n - 1; ++i)
    fprintf(out, "%g,", a[i]);
  if (n)
    fprintf(out, "%g", a[i]);
  fputc('}', out);
}

void double_fprint_array_annotated(
  FILE * out, int n, const double * a, const char * name)
{
  fputs(name, out);
  fputs(" = ", out);
  double_fprint_array(out, n, a);
  fputs("\n", out);
}

void double_fprint_array_raw(FILE * out, int n, const double * a)
{
  int i;
  
  for (i = 0; i < n - 1; ++i)
    fprintf(out, "%g ", a[i]);
  if (n)
    fprintf(out, "%g\n", a[i]);
}

void double_fprint_array2_annotated(
  FILE * out, int m_dim, const int * n, double ** a, const char * name)
{
  int p;
  
  fputs(name, out);
  fputs(":\n", out);
  for (p = 0; p <= m_dim; ++p)
  {
    fputs(name, out);
    fprintf(out, "[%d] = ", p);
    double_fprint_array(out, n[p], a[p]);
    fputs("\n", out);
  }
}

void double_fprint_matrix(FILE * out, int m, int n, const double * a)
{
  int i, ind;
  
  fputc('{', out);
  ind = 0;
  for (i = 0; i < m - 1; ++i)
  {
    double_fprint_array(out, n, a + ind);
    fputc(',', out);
    ind += n;
  }
  if (m > 0)
    double_fprint_array(out, n, a + ind);
  fputc('}', out);
}

void double_fprint_matrix_raw(FILE * out, int m, int n, const double * a)
{
  int i, ind;
  
  ind = 0;
  for (i = 0; i < m; ++i)
  {
    double_fprint_array_raw(out, n, a + ind);
    ind += n;
  }
}

void double_fprint_matrix_annotated(
  FILE * out, int m, int n, const double * a, const char * name)
{
  fputs(name, out);
  fputs(" = ", out);
  double_fprint_matrix(out, m, n, a);
  fputs("\n", out);
}
