#include <errno.h>
#include <string.h>
#include "cs_private.h"
#include "double.h"
#include "int.h"

void cs_fprint_only_values(FILE * out, const cs * a)
{
  fprintf(out, "%d\n%d\n", a->m, a->n);
  double_fprint_array_raw(out, a->nzmax, a->x);
}

void cs_fprint_raw(FILE * out, const cs * a)
{
  fprintf(out, "%d\n", a->nzmax);
  fprintf(out, "%d\n", a->m);
  fprintf(out, "%d\n", a->n);
  int_fprint_array_raw(out, (a->n + 1), a->p);
  int_fprint_array_raw(out, a->nzmax, a->i);
  double_fprint_array_raw(out, a->nzmax, a->x);
  fprintf(out, "%d\n", a->nz);
}

void cs_fprint_annotated(FILE * out, const cs * a)
{
  int a_m, a_n, a_nz, a_nzmax, j, p;
  int * a_i, * a_p ;
  double * a_x;
  
  a_m = a->m; a_n = a->n; a_p = a->p; a_i = a->i; a_x = a->x;
  a_nzmax = a->nzmax; a_nz = a->nz;
  if (a_nz < 0)
  {
    fprintf(out, "%d-by-%d, number of nonzero values: %d\n", a_m, a_n, a_nzmax);
    for (j = 0; j < a_n; ++j)
    {
      fprintf(out, "    col %d : locations %d to %d\n",
              j, a_p[j], a_p[j + 1] - 1);
      for (p = a_p[j]; p < a_p[j + 1]; ++p)
      {
        fprintf(out, "      %d : %g\n", a_i[p], a_x[p]);
      }
    }
  }
  else
  {
    fprintf(out, "triplet: %d-by-%d, number of nonzero values: %d\n",
            a_m, a_n, a_nzmax);
    for (p = 0 ; p < a_nz ; p++)
    {
      fprintf(out, "    %d %d : %g\n", a_i[p], a_p[p], a_x[p]);
    }
  }
}

void cs_fprint_matrix_form_raw(FILE * out, const cs * a)
{
  int a_m, a_n, i, j;
  
  a_m = a->m;
  a_n = a->n;
  for (i = 0; i < a_m; ++i)
  {
    for(j = 0; j < a_n - 1; ++ j)
      fprintf(out, "%g ", cs_part(a, i, j));
    fprintf(out, "%g\n", cs_part(a, i, j));
  }
}

void cs_fprint_matrix_form_curly(FILE * out, const cs * a)
{
  int a_m, a_n, i, j;
  
  a_m = a->m;
  a_n = a->n;
  fputc('{', out);
  for (i = 0; i < a_m - 1; ++i)
  {
    fputc('{', out);
    for(j = 0; j < a_n - 1; ++ j)
      fprintf(out, "%g,", cs_part(a, i, j));
    fprintf(out, "%g},\n", cs_part(a, i, j));
  }
  fputc('{', out);
  for(j = 0; j < a_n - 1; ++ j)
    fprintf(out, "%g,", cs_part(a, i, j));
  fprintf(out, "%g}}\n", cs_part(a, i, j));
}

static void rule_fprint(FILE * out, int i, int j, double x)
{
  fprintf(out, "{%d,%d}->%g", i, j, x);
}

void cs_fprint_mathematica_sparse(FILE * out, const cs * a)
{
  int a_m, a_n, i, i_loc, j;
  int * a_p, * a_i;
  double x;
  double * a_x;
  
  a_m = a->m; a_n = a->n; a_p = a->p; a_i = a->i; a_x = a->x;
  fputs("SparseArray[{", out);
  for (j = 0; j < a_n; ++j)
  {
    for (i_loc = a_p[j]; i_loc < a_p[j + 1]; ++i_loc)
    {
      i = a_i[i_loc];
      x = a_x[i_loc];
      rule_fprint(out, i + 1, j + 1, x);
      if (i_loc < a_p[a_n] - 1)
        fputc(',', out);
    }
  }
  fprintf(out, "},{%d,%d}]\n", a_m, a_n);
}

void cs_fprint(FILE * out, const cs * a, const char * format)
{
  if (!strcmp(format, "--only-values"))
  {
    cs_fprint_only_values(out, a);
    if (errno)
    {
      perror("Unsuccessful matrix printing");
      return;
    }
  }
  else if (!strcmp(format, "--raw"))
  {
    cs_fprint_raw(out, a);
    if (errno)
    {
      perror("Unsuccessful matrix printing");
      return;
    }
  }
  else if (!strcmp(format, "--annotated"))
  {
    cs_fprint_annotated(out, a);
    if (errno)
    {
      perror("Unsuccessful matrix printing");
      return;
    }
  }
  else if (!strcmp(format, "--matrix-form-raw"))
  {
    cs_fprint_matrix_form_raw(out, a);
    if (errno)
    {
      perror("Unsuccessful matrix printing");
      return;
    }
  }
  else if (!strcmp(format, "--matrix-form-curly"))
  {
    cs_fprint_matrix_form_curly(out, a);
    if (errno)
    {
      perror("Unsuccessful matrix printing");
      return;
    }
  }
  else if (!strcmp(format, "--mathematica-sparse"))
  {
    cs_fprint_mathematica_sparse(out, a);
    if (errno)
    {
      perror("Unsuccessful matrix printing");
      return;
    }
  }
  else
  {
    errno = EINVAL;
    perror(format);
    return;
  }
}

void cs_fprint_array(FILE * out, int n, cs ** a, const char * format)
{
  int i;

  for (i = 0; i < n; ++i)
  {
    cs_fprint(out, a[i], format);
    if (errno)
    {
      perror("During matrix printing");
      return;
    }
    if (i < n - 1)
      fputc('\n', out);
  }
}
