#include "cs.h"

static int position(const int * a, int len, int element)
{
  int i;
  for (i = 0; i < len; ++i)
    if (element == a[i])
      return i;
  return -1;
}

double cs_part(const cs * a, int i, int j)
{
  int a_nz, begin, len, p;
  int * a_i, * a_p;
  double * a_x;
  
  a_p = a->p;
  a_i = a->i;
  a_x = a->x;
  a_nz = a->nz;
  if (a_nz < 0)
  {
    begin = a_p[j];
    len = a_p[j + 1] - begin;
    p = position(a_i + begin, len, i);
    if (p != -1)
      return a_x[begin + p];
  }
  return 0;
}
