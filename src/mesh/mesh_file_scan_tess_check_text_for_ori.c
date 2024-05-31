#include <string.h>

#include "mesh_file_scan_tess_private.h"
#include "string_private.h"

void mesh_file_scan_tess_check_text_for_ori(FILE * in, int * error)
{
  const char str[] = "\n  *ori\n   quaternion:active\n";
  char buffer[sizeof(str)];
  
  string_file_scan(in, buffer, sizeof(buffer));
  if (strcmp(buffer, str))
  {
    *error = 1;
    fprintf(stderr, "Error: expected\n\n%s\n\n", str);
    fprintf(stderr, "Instead, we have\n\n%s\n\n", buffer);
    return;
  }
}
