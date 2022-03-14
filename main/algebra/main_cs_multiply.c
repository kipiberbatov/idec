#include <errno.h>
#include <string.h>
#include "cs.h"

// static void cs_multiply_fprint(
//   FILE * out, const cs * a, const cs * b, const char * format)
// {
//   cs * res;
//   res = cs_multiply(a, b);
//   if (errno)
//   {
//     perror("Cannot multiply matrices");
//     goto res_free;
//   }
//   cs_fprint(out, res, format);
//   if (errno)
//   {
//     perror("Cannot multiply matrices");
//     goto res_free;
//   }
// res_free:
//   cs_free(res);
// end:
//   return;
// }

static void cs_multiply_fprint(
  FILE * out, cs ** a, cs ** b, int d, const char * format)
{
  int p;
  cs * res;
  
  for (p = 0; p < d; ++p)
  {
    res = cs_multiply(a[p], b[p]);
    if (errno)
    {
      perror("Cannot multiply matrices");
      cs_free(res);
      return;
    }
    cs_fprint(out, res, format);
    if (errno)
    {
      perror("Cannot print matrix");
      cs_free(res);
      return;
    }
    cs_free(res);
  }
}

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
    perror("Cannot scan left multiplier");
    goto a_free;
  }
  b = cs_fscan_array(in, d);
  if (errno)
  {
    perror("Cannot scan right multiplier");
    goto b_free;
  }
//   res = cs_multiply(a[0], b[0]);
//   if (errno)
//   {
//     perror("Cannot multiply matrices");
//     goto res_free;
//   }
//   cs_fprint(out, res, "--raw");
//   if (errno)
//   {
//     perror("Cannot print matrix");
//     goto res_free;
//   }
// res_free:
//   cs_free(res);
  cs_multiply_fprint(out, a, b, d, format);
  if (errno)
  {
    perror("Cannot print matrix");
    goto b_free;
  }
b_free:
  cs_free_array(b, d);
a_free:
  cs_free_array(a, d);
  return errno;
}

// int main(int argc, char * argv[])
// {
//   char * format;
//   cs * a, * b, * res;
//   FILE * in, * out;
//
//   out = stdout;
//   in = stdin;
//   a = cs_fscan(in);
//   if (errno)
//   {
//     perror("Cannot scan left multiplier");
//     cs_free(a);
//     goto end;
//   }
//   b = cs_fscan(in);
//   if (errno)
//   {
//     perror("Cannot scan right multiplier");
//     cs_free(b);
//     cs_free(a);
//     goto end;
//   }
//   res = cs_multiply(a, b);
//   if (errno)
//   {
//     perror("Cannot multiply matrices");
//     cs_free(res);
//     cs_free(b);
//     cs_free(a);
//     goto end;
//   }
//   cs_free(b);
//   cs_free(a);
//   format = argv[1];
//   cs_fprint(out, res, format);
//   if (errno)
//   {
//     perror("Cannot multiply matrices");
//     goto res_free;
//   }
// res_free:
//   cs_free(res);
// end:
//   return errno;
// }
