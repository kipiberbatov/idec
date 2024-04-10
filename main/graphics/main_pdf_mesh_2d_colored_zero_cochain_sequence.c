/* system headers */
#include <alloca.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* external headers */
#include <cairo.h>
#include <cairo-pdf.h>

/* internal headers */
#include "double.h"
#include "drawer.h"
#include "image.h"
#include "int.h"
#include "mesh.h"
#include "mesh_2d_colored.h"
#include "paint_rgb.h"
#include "pdf_write_to_file.h"

int main(int argc, char * argv[])
{
  char * m_format, * u_format;
  char * m_filename, * u_filename;
  int begin, n, steps, total_colors;
  int * i;
  double height, point_size, width;
  double * new_coordinates, * u;
  mesh * m;
  //diffusion * a;
  mesh_2d_colored_zero_cochain_sequence a;
  char * out_filename;
  
  errno = 0;
  
  if (argc != 7)
  {
    fprintf(stderr, 
      "Error during execution of function %s in file %s on line %d: "
      "number of command-line arguments must be 6\n",
      __func__, __FILE__,__LINE__);
    errno = EINVAL;
    goto end;
  }
  
  begin = 0;
  i = &begin;
  
  m_format = argv[1];
  m_filename = argv[2];
  m = mesh_fscan_by_name(m_filename, m_format);
  if (errno)
  {
    fprintf(stderr,
      "Error during execution of function %s in file %s on line %d: "
      "could not generate input mesh\n",
      __func__, __FILE__,__LINE__);
    goto end;
  }
  
  steps = int_sscan(argv[3]);
  if (errno)
  {
    fprintf(stderr,
      "Error during execution of function %s in file %s on line %d: "
      "unable to scan number of time steps\n",
       __func__, __FILE__,__LINE__);
    goto m_free;
  }
  n = steps + 1;
  
  u_format = argv[4];
  u_filename = argv[5];
  u = double_matrix_fscan_by_name(u_filename, n, m->cn[0], u_format);
  if (errno)
  {
    fprintf(stderr,
      "Error during execution of function %s in file %s on line %d: "
      "could not generate values\n",
       __func__, __FILE__,__LINE__);
    goto m_free;
  }
  
  new_coordinates = (double *) malloc(sizeof(double) * 2 * m->cn[0]);
  if (errno)
  {
    fprintf(stderr,
      "Error during execution of function %s in file %s on line %d: "
      "could not generate values\n",
       __func__, __FILE__,__LINE__);
    goto u_free;
  }
  
  width = 500;
  height = 500;
  image_new_coordinates(new_coordinates, m, width, height);
  point_size = image_point_size(width, height);
  
  total_colors = 1000;
  
  // a = (diffusion *) alloca(diffusion_size());
  // diffusion_set(a,
  //   i, n, m, new_coordinates, point_size, u, total_colors, paint_rgb);
  a.index = i;
  a.total_steps = n;
  a.m = m;
  a.values = u;
  
  a.total_colors = total_colors;
  a.new_coordinates = new_coordinates;
  a.point_size = point_size;
  a.min_value = double_array_min(n * m->cn[0], u);
  a.max_value = double_array_max(n * m->cn[0], u);
  a.paint = paint_rgb;
  
  out_filename = argv[6];
  pdf_write_to_file(
    out_filename,
    width,
    height,
    &a,
    mesh_2d_colored_zero_cochain_sequence_snapshot_cairo_draw_void,
    mesh_2d_colored_zero_cochain_sequence_get_index_void,
    mesh_2d_colored_zero_cochain_sequence_get_total_steps_void);
  
  free(new_coordinates);
u_free:
  free(u);
m_free:
  mesh_free(m);
end:
  return errno;
}
