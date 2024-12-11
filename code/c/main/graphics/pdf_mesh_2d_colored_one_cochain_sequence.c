/* system headers */
#include <errno.h>
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
#include "points_array_minimal_distance.h"

int main(int argc, char ** argv)
{
  char * m_format, * m_name, * number_of_steps_name, * out_name, * u_format,
       * u_name;
  int i, n, number_of_steps, total_colors;
  double height, width;
  double * new_coordinates, * u;
  FILE * m_file;
  matrix_sparse * m_bd_1;
  mesh * m;
  mesh_2d_colored_one_cochain_sequence a;
  margin window_margin;
  frame_mesh_data data;
  frame window_frame;

  errno = 0;

#define ARGC 7
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
  number_of_steps_name = argv[3];
  u_format = argv[4];
  u_name = argv[5];
  out_name = argv[6];

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    goto end;
  }
  m = mesh_file_scan(m_file, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan mesh m from file %s in format %s\n",
      m_name, m_format);
    fclose(m_file);
    goto end;
  }

  m_bd_1 = mesh_file_scan_boundary_p(m_file, m, 1);
  if (m_bd_1 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m_bd_1 m from file %s\n", m_name);
    fclose(m_file);
    goto m_free;
  }
  fclose(m_file);

  number_of_steps = int_string_scan(number_of_steps_name);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan number of steps from string %s\n", number_of_steps_name);
    goto m_free;
  }
  if (number_of_steps < 0)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of steps is %d but it must be at least 0\n", number_of_steps);
    goto m_free;
  }
  n = number_of_steps + 1;

  u = double_matrix_file_scan_by_name(u_name, n, m->cn[1], u_format);
  if (u == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan sequence of cochain values in format %s\n",
      u_format);
    goto m_bd_1_free;
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

  i = 0;
  total_colors = 1000;

  a.is_mesh_edge_skeleton = 0;
  a.index = i;
  a.total_steps = n;
  a.m = m;
  a.bd_1 = m_bd_1->values;
  a.values = u;

  a.total_colors = total_colors;
  a.new_coordinates = new_coordinates;
  a.point_size = points_array_minimal_distance(m->cn[0], new_coordinates);
  a.line_width = data.line_width;
  a.min_value = double_array_absolute_min(n * m->cn[1], u);
  a.max_value = double_array_absolute_max(n * m->cn[1], u);
  a.paint = paint_rgb;

  out_name = argv[6];
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
m_bd_1_free:
  matrix_sparse_free(m_bd_1);
m_free:
  mesh_free(m);
end:
  return errno;
}
