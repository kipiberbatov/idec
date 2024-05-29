#include <string.h>

#include "mesh_file_scan_tess_private.h"
#include "string_private.h"

void mesh_file_scan_tess_check_text_for_cell(FILE * in, int * error)
{
  const char str[] = " standard\n **cell\n  ";
  char buffer[sizeof(str)];
  
  string_file_scan(in, buffer, strlen(str) + 1);
  if (strcmp(buffer, str))
  {
    *error = 1;
    fputs("Lines 5 and 6 are not right\n", stderr);
  }
}
