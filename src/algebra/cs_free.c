#include "cs.h"

void cs_free2(cs * a)
{
  free(a->p);
  free(a->i);
  free(a->x);
  free(a);
}

void cs_free_array(cs ** a, int n)
{
  int i;
  for (i = 0; i < n; ++i)
    cs_free2(a[i]);
  free(a);
}

void cs_free_shared(cs * a)
{
  free(a->x);
  free(a);
}

void cs_free_shared_array(cs ** a, int n)
{
  int i;
  for (i = 0; i < n; ++i)
    cs_free_shared(a[i]);
  free(a);
}
