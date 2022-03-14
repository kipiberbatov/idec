#include <stdlib.h>
#include "int.h"

int int_fscan(FILE * in)
{
  int a;
  
  fscanf(in, "%d", &a);
  return a;
}

int * int_fscan_array(FILE * in, int n)
{
  int i;
  int * a;
  
  a = (int *) malloc(n * sizeof(int));
  /* NULL pointer check */
  for (i = 0; i < n; ++i)
  {
    fscanf(in, "%d", a + i);
    /* successfull scanning check */
  }
  return a;
}
