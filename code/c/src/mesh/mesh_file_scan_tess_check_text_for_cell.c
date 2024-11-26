#include <string.h>

#include "color.h"
#include "mesh_file_scan_tess_private.h"
#include "string_private.h"

void mesh_file_scan_tess_check_text_for_cell(FILE * in, int * error)
{
  const char str[] = " standard\n **cell\n  ";
  char buffer[sizeof(str)];

  string_file_scan(in, buffer, sizeof(buffer));
  if (strcmp(buffer, str))
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "expected\n\n%s\n\n", str);
    fprintf(stderr, "Instead, we have\n\n%s\n\n", buffer);
    *error = 1;
    return;
  }
}
