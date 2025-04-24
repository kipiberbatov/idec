#include <stdlib.h>

#include "color.h"
#include "double.h"
#include "double_private.h"
#include "idec_error_message.h"

double ** double_array2_file_scan_raw(FILE * in, int a0, const int * a1)
{
  int i;
  double ** a;

  a = (double **) malloc(sizeof(double *) * a0);
  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double *) * a0, "a");
    return NULL;
  }
  for (i = 0; i < a0; ++i)
  {
    a[i] = double_array_file_scan(in, a1[i], "--raw");
    if (a[i] == NULL)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan a[%d] in format --raw\n", i);
      double_array2_free(a, i);
      return NULL;
    }
  }
  return a;
}
