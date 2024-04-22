#include <errno.h>
#include <stdlib.h>
#include "jagged.h"

jagged1 * jagged1_complement(int n, const jagged1 * arr)
{
  int i, ind;
  jagged1 * res;
  
  res = (jagged1 *) malloc(sizeof(jagged1));
  if (errno)
  {
    perror("jagged1_complement : cannot allocate memory for res");
    goto end;
  }
  
  res->a0 = n - arr->a0;
  
  res->a1 = (int *) malloc(sizeof(int) * res->a0);
  if (errno)
  {
    perror("jagged1_complement : cannot allocate memory for res->a1");
    goto res_free;
  }
  
  ind = 0;
  for (i = 0; i < n; ++i)
  {
    if (!jagged1_member(arr, i))
    {
      res->a1[ind] = i;
      ++ind;
    }
  }
  
  return res;
  
  /* cleaning if an error occurs */
res_free:
  free(res);
end:
  return NULL;
}
