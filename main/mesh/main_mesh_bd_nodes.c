#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "mesh.h"

int main(int argc, char * argv[])
{
  char * m_format, * m_name, * out_format;
  FILE * m_file;
  mesh * m;
  jagged1 * m_bd_nodes;
  
  if (argc != 4)
  {
    errno = EINVAL;
    fputs("main - the number of command-line arguments must be 4\n", stderr);
    goto end;
  }
  
  m_name = argv[1];
  m_file = fopen(m_name, "r");
  if (errno)
  {
    fprintf(stderr, "main - cannot open the content of m_file: %s\n",
            strerror(errno));
    goto end;
  }
  
  m_format = argv[2];
  m = mesh_fscan(m_file, m_format);
  if (errno)
  {
    fputs("main - cannot scan m\n", stderr);
    fclose(m_file);
    goto end;
  }
  fclose(m_file);
  
  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("main - cannot calculate m->fc\n", stderr);
    goto m_free;
  }
  
  out_format = argv[3];
  m_bd_nodes = mesh_bd_nodes(m);
  if (errno)
  {
    fputs("main - cannot calculate m_bd_nodes\n", stderr);
    goto m_free;
  }
  
  jagged1_fprint(stdout, m_bd_nodes, out_format);

  jagged1_free(m_bd_nodes);
m_free:
  mesh_free(m);
end:
  return errno;
}
