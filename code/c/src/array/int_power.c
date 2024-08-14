#include "int.h"

int int_power(int a, int n)
{
  int flag, result, tmp;

  if (n == 0)
    return 1;
  result = 1;
  tmp = a;
  while (n > 1)
  {
    flag = n % 2;
    if (flag)
      result *= tmp;
    tmp *= tmp;
    n /= 2;
  }
  result *= tmp;
  return result;
}
