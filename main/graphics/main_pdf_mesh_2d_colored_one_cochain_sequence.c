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
#include "frame.h"
#include "int.h"
#include "mesh.h"
#include "mesh_2d_colored_one_cochain_sequence.h"
#include "paint_rgb.h"
#include "pdf_write_to_file.h"

int main(int argc, char ** argv)
{
  char * m_format, * u_format;
  char * m_filename, * u_filename;
  int i, n, steps, total_colors;
  double height, width;
  double * new_coordinates, * u;
  mesh * m;
  mesh_2d_colored_one_cochain_sequence a;
  char * out_filename;
  margin window_margin;
  frame_mesh_data data;
  frame window_frame;

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

  i = 0;

  m_format = argv[1];
  m_filename = argv[2];
  m = mesh_file_scan_by_name(m_filename, m_format);
  if (errno)
  {
    fprintf(stderr,
      "Error during execution of function %s in file %s on line %d: "
      "could not generate input mesh\n",
      __func__, __FILE__,__LINE__);
    goto end;
  }

  steps = int_string_scan(argv[3]);
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
  u = double_matrix_file_scan_by_name(u_filename, n, m->cn[1], u_format);
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
  window_margin.left = 50;
  window_margin.right = 50;
  window_margin.top = 50;
  window_margin.bottom = 50;
  data.coordinates = new_coordinates;
  frame_internal_info_for_set_of_points(
    &window_frame,
    &data,
    m->cn[0],
    m->coord,
    width,
    height,
    &window_margin);

  total_colors = 1000;

  a.index = i;
  a.total_steps = n;
  a.m = m;
  a.values = u;

  a.total_colors = total_colors;
  a.new_coordinates = new_coordinates;
  a.line_width = data.line_width;
  a.min_value = double_array_min(n * m->cn[1], u);
  a.max_value = double_array_max(n * m->cn[1], u);
  a.paint = paint_rgb;

  out_filename = argv[6];
  pdf_write_to_file(
    out_filename,
    width,
    height,
    (void *) &a,
    mesh_2d_colored_one_cochain_sequence_snapshot_cairo_draw_void,
    mesh_2d_colored_one_cochain_sequence_get_index_void,
    mesh_2d_colored_one_cochain_sequence_get_total_steps_void,
    mesh_2d_colored_one_cochain_sequence_increment_index_void);

  free(new_coordinates);
u_free:
  free(u);
m_free:
  mesh_free(m);
end:
  return errno;
}
