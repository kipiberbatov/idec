/* system headers */
#include <alloca.h>
#include <errno.h>
#include <stdio.h>

/* external headers */
#include <cairo.h>
#include <cairo-pdf.h>

/* internal headers */
#include "color.h"
#include "fill.h"
#include "idec_error_message.h"
#include "int.h"
#include "paint_rgb.h"
#include "pdf_write_to_file.h"

int main(int argc, char ** argv)
{
  char * n_name, * out_name;
  int i, n;
  double height, width;
  fill * a;

#define ARGC 3
  if (argc != ARGC)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    errno = EINVAL;
    return errno;
  }

  errno = 0;

  n_name = argv[1];
  out_name = argv[2];

  i = 0;
  n = int_string_scan(n_name);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan number of colors from string %s\n", n_name);
    return errno;
  }
  if (n < 1)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of colors is %d but it must be at least 1\n", n);
    return errno;
  }
  width = 500;
  height = 500;

  a = (fill *) alloca(fill_size());
  fill_set(a, i, n, paint_rgb);

  pdf_write_to_file(
    out_name,
    width,
    height,
    (void *) a,
    fill_draw_void,
    fill_get_index_void,
    fill_get_total_steps_void,
    fill_increment_index_void);

  return 0;
}
