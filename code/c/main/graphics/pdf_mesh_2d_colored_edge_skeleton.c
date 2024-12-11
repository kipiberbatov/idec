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
#include "color.h"
#include "double.h"
#include "frame.h"
#include "idec_error_message.h"
#include "int.h"
#include "mesh.h"
#include "mesh_2d_colored_one_cochain_sequence.h"
#include "paint_rgb.h"
#include "pdf_write_to_file.h"

int main(int argc, char ** argv)
{
  char * m_format, * m_name, * out_name;
  int i, total_colors;
  double height, width;
  double * new_coordinates, * u;
  mesh * m;
  mesh_2d_colored_one_cochain_sequence a;
  margin window_margin;
  frame_mesh_data data;
  frame window_frame;

  errno = 0;

#define ARGC 4
  if (argc != ARGC)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    errno = EINVAL;
    goto end;
  }

  i = 0;

  m_format = argv[1];
  m_name = argv[2];
  out_name = argv[3];

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan mesh m from file %s in format %s\n",
      m_name, m_format);
    goto end;
  }

  u = (double *) calloc(m->cn[1], sizeof(double));
  if (u == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * m->cn[1], "u");
    goto m_free;
  }

  new_coordinates = (double *) malloc(sizeof(double) * 2 * m->cn[0]);
  if (new_coordinates == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * 2 * m->cn[0], "new_coordinates");
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

  total_colors = 10;

  a.is_mesh_edge_skeleton = 1;
  a.index = i;
  a.total_steps = 1;
  a.m = m;
  a.bd_1 = NULL;
  a.values = u;

  a.total_colors = total_colors;
  a.new_coordinates = new_coordinates;
  a.point_size = -1;
  a.line_width = data.line_width;
  a.min_value = -1;
  a.max_value = 1;
  a.paint = paint_rgb;

  pdf_write_to_file(
    out_name,
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
