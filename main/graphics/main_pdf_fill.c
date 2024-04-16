/* system headers */
#include <alloca.h>
#include <errno.h>
#include <stdio.h>

/* external headers */
#include <cairo.h>
#include <cairo-pdf.h>

/* internal headers */
#include "fill.h"
#include "int.h"
#include "paint_rgb.h"
#include "pdf_write_to_file.h"

int main(int argc, char ** argv)
{
  int i, n;
  double height, width;
  fill * a;
  char * out_filename;
  
  errno = 0;
  
  if (argc != 3)
  {
    fprintf(stderr, 
      "Error during execution of function %s in file %s on line %d: "
      "number of command-line arguments must be 3\n",
      __func__, __FILE__,__LINE__);
    errno = EINVAL;
    return errno;
  }
  
  i = 0;
  
  n = int_sscan(argv[1]);
  if (errno)
  {
    fprintf(stderr,
      "Error during execution of function %s in file %s on line %d: "
      "unable to scan number of time steps\n",
       __func__, __FILE__,__LINE__);
    return errno;
  }
  
  width = 500;
  height = 500;
  
  a = (fill *) alloca(fill_size());
  fill_set(a, i, n, paint_rgb);
  
  out_filename = argv[2];
  pdf_write_to_file(
    out_filename,
    width,
    height,
    (void *) a,
    fill_draw_void,
    fill_get_index_void,
    fill_get_total_steps_void,
    fill_increment_index_void);
  
  return 0;
}
