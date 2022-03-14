#include <errno.h>
#include <string.h>
#include "cs.h"

int main(int argc, char * argv[])
{
  int d;
  char * format, * list;
  cs ** a, ** b;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  format = argv[1];
  list = argv[2];
  d = atoi(argv[3]);
  a = cs_fscan_array(in, d);
  if (errno)
  {
    perror("Unsuccessful scanning of first operator");
    goto a_free;
  }
  b = cs_fscan_array(in, d);
  if (errno)
  {
    perror("Unsuccessful scanning of second operator");
    goto b_free;
  }
  cs_laplacian_fprint(out, d, a, b, format);
  if (errno)
  {
    perror("Unsuccessful calculation or printing of Lalplacian");
    goto b_free;
  }
b_free:
  cs_free_array(b, d);
a_free:
  cs_free_array(a, d);
  return errno;
}
