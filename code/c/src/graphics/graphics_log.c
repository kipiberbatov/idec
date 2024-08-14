#include <errno.h>
#include <time.h>

#include "graphics_log.h"

void graphics_log(FILE * out, int argc, char ** argv)
{
  int i;
  time_t rawtime;
  struct tm * p;

  time(&rawtime);
  p = gmtime(&rawtime);

  fputs("The following command was run:\n", out);
  for (i = 0; i < argc; ++i)
    fprintf(out, "%s ", argv[i]);
  fputc('\n', out);
  fprintf(out, "Program exited at %02d.%02d.%d %02d:%02d:%02d UTC\n",
    p->tm_mday, p->tm_mon + 1, p->tm_year + 1900,
    p->tm_hour, p->tm_min, p->tm_sec);
  fprintf(out, "Exit status: %d\n", errno);
}
