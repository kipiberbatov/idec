#include <errno.h>
#include "forman.h"

static mesh * forman_mesh_file_scan(FILE * in, const char * format)
{
  mesh * m, * m_forman = NULL;
  
  m = mesh_file_scan(in, format);
  if (errno)
  {
    fputs("forman_mesh_file_scan - cannot scan m\n", stderr);
    goto end;
  }
  
  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("forman_mesh_file_scan - cannot calculate m->fc\n", stderr);
    goto m_free;
  }
  
  m_forman = forman(m);
  if (errno)
  {
    fputs("forman_mesh_file_scan - cannot calculate m->fc\n", stderr);
    goto m_free;
  }
  
m_free:
  mesh_free(m);
end:
  return m_forman;
}

int main(int argc, char ** argv)
{
  mesh * m_forman;

  if (argc != 2)
  {
    fputs("main - number of command line arguments should be 1\n", stderr);
    return errno;
  }
  
  m_forman = forman_mesh_file_scan(stdin, argv[1]);
  if (errno)
  {
    fputs("main - cannot calculate m_forman\n", stderr);
    return errno;
  }
  
  mesh_file_print(stdout, m_forman, "--raw");
  mesh_free(m_forman);
  return 0;
}
