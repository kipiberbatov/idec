#include <string.h>

#include "mesh_file_scan_tess_private.h"
#include "string_private.h"

void mesh_file_scan_tess_check_text_for_face(FILE * in, int * error)
{
  const char str[] = "\n **face\n ";
  char buffer[sizeof(str)];

  string_file_scan(in, buffer, sizeof(buffer));
  if (strcmp(buffer, str))
  {
    *error = 1;
    fprintf(stderr, "Face field is not presented %s\n", str);
  }
}
