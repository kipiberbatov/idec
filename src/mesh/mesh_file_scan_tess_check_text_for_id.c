#include <string.h>

#include "mesh_file_scan_tess_private.h"
#include "string_private.h"

void mesh_file_scan_tess_check_text_for_id(FILE * in, int * error)
{
  const char str[] = "\n  *id\n   ";
  char buffer[sizeof(str)];
  
  string_file_scan(in, buffer, sizeof(buffer));
  if (strcmp(buffer, str))
  {
    *error = 1;
    fputs("8-th line of .tess file must be '  *id\n", stderr);
  }
}
