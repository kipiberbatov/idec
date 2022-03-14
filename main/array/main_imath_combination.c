#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "imath.h"
#include "list.h"

static void list_fprint(FILE * out, int d, const int * a)
{
  int i;
  
  for (i = 0; i < d - 1; ++i)
    fprintf(out, "%d ", a[i]);
  fprintf(out, "%d\n", a[i]);
}

static void imath_combination_fprint(FILE * out, int m, int n)
{
  int prod, i;
  int * a;
  
  prod = imath_binom(m, n);
  a = (int *) malloc(n * sizeof(int));
  if (errno)
  {
    perror("Cannot allocate memory for combinations");
    return;
  }
  for (i = 0; i < n; ++i)
    a[i] = i;
  i = 0;
  while(i < prod - 1)
  {
    list_fprint(out, n, a);
    imath_combination_next(a, m, n);
    ++i;
  }
  list_fprint(out, n, a);
  free(a);
}

int main(int argc, char * argv[])
{
  int m, n;
  
  m = atoi(argv[1]);
  n = atoi(argv[2]);
  imath_combination_fprint(stdout, m, n);
  if (errno)
  {
    perror("Error during printing combinations");
    goto end;
  }
end:
  return errno;
}
