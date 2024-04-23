#include "int.h"

void int_swap(int * a, int * b)
{
  int tmp;
  
  tmp = *a;
  *a = *b;
  *b = tmp;
}
