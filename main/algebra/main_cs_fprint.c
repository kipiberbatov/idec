#include <errno.h>
#include <string.h>
#include "cs.h"

static void cs_fprint_fscan(FILE * out, FILE * in, char * format)
{
  cs * a;
  
  a = cs_fscan(in);
  if (errno)
  {
    perror("Unsuccessful matrix scanning during matrix printing calculation");
    goto a_free;
  }
  cs_fprint(out, a, format);
  if (errno)
  {
    perror("Unsuccessful matrix printing");
    goto a_free;
  }
a_free:
  free(a);
}

static void cs_fprint_array_fscan(FILE * out, FILE * in, char * format, int d)
{
  int p;
  
  for (p = 0; p < d; ++p)
  {
    cs_fprint_fscan(out, in, format);
    if (errno)
    {
      fprintf(stderr, "During the printing of the %d-th matrix", p);
      perror("");
    }
    if (p < d - 1)
      fputc('\n', out);
  }
}

int main(int argc, char * argv[])
{
  char * format, * list;
  int d;
  
  format = argv[1];
  if (argc == 4)
  {
    list = argv[2];
    if (!strcmp(list, "list"))
    {
      errno = EINVAL;
      perror(list);
      return errno;
    }
    d = atoi(argv[3]);
    cs_fprint_array_fscan(stdout, stdin, format, d);
    return 0;
  }
  cs_fprint_fscan(stdout, stdin, format);
  return 0;
}
