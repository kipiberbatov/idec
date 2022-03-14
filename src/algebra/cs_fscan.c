#include "cs.h"
#include "double.h"
#include "int.h"

cs * cs_fscan(FILE * in)
{
  cs * a;
  
  a = (cs *) malloc(sizeof(cs));
  /* NULL_ppointer check */
  a->nzmax = int_fscan(in);
  a->m = int_fscan(in);
  a->n = int_fscan(in);
  a->p = int_fscan_array(in, a->n + 1);
  /* NULL_ppointer check */
  a->i = int_fscan_array(in, a->nzmax);
  /* NULL_ppointer check */
  a->x = double_fscan_array(in, a->nzmax);
  /* NULL_ppointer check */
  a->nz = int_fscan(in);
  return a;
}

cs ** cs_fscan_array(FILE * in, int a0)
{
  int i;
  cs ** arr;
  
  arr = (cs **) malloc(a0 * sizeof(cs *));
  /* NULL_ppointer check */
  for (i = 0; i < a0; ++i)
  {
    arr[i] = cs_fscan(in);
    /* NULL_ppointer check */
  }
  return arr;
}