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

static void imath_cartesian_product_fprint(FILE * out, int d, const int * n)
{
  int prod, i;
  int * a;
  
  prod = list_product(n, 0, d);
  a = (int *) calloc(d, sizeof(int));
  if (errno)
  {
    perror("Cannot allocate memory for tuples");
    return;
  }
  i = 0;
  while(i < prod - 1)
  {
    list_fprint(out, d, a);
    imath_cartesian_product_next(a, d, n);
    ++i;
  }
  list_fprint(out, d, a);
  free(a);
}

int main(int argc, char * argv[])
{
  int d, p;
  int * n;
  
  d = argc - 1;
  n = (int *) malloc(d * sizeof(int));
  if (errno)
  {
    perror("Cannot allocate memory for dimensions");
    goto end;
  }
  for (p = 0; p < d; ++p)
    n[p] = atoi(argv[1 + p]);
  imath_cartesian_product_fprint(stdout, d, n);
  if (errno)
  {
    perror("Error during tuplles printing");
    goto n_free;
  }
n_free:
  free(n);
end:
  return errno;
}
