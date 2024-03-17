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
#include "diffusion.h"
#include "image.h"
#include "int.h"
#include "mesh.h"
#include "rgb.h"

static void
pdf_draw_diffusion(cairo_t * cr, int width, int height, diffusion * a)
{
  cairo_save(cr);
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_paint(cr);
  cairo_restore(cr);
  diffusion_draw_snapshot(cr, width, height, a);
  cairo_show_page(cr);
}

static void surface_draw_diffusion(
  cairo_surface_t * surface,
  double width,
  double height,
  diffusion * a)
{
  cairo_t * cr;
  int n;
  int * i;
  
  i = diffusion_get_index(a);
  n = diffusion_total_steps(a);
  while (*i < n - 1)
  {
    cr = cairo_create(surface);
    pdf_draw_diffusion(cr, width, height, a);
    *i += 1;
    cairo_destroy(cr);
  }
}

static void
diffusion_write_to_file(
  const char * filename, double width, double height, diffusion * a)
{
  cairo_surface_t * surface;
  
  surface = cairo_pdf_surface_create(filename, width, height);
  surface_draw_diffusion(surface, width, height, a);
  cairo_surface_destroy(surface);
}

static void painter(cairo_t * cr, int ind, int total_colors)
{
  rgb color;
  rgb_color(&color, ind, total_colors);
  cairo_set_source_rgb(cr, color.red, color.green, color.blue);
}

int main(int argc, char * argv[])
{
  char * m_format, * u_format;
  char * m_filename, * u_filename;
  int begin, n, steps, total_colors;
  int * i;
  double height, point_size, width;
  double * new_coordinates, * u;
  mesh * m;
  diffusion * a;
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
  
  a = (diffusion *) alloca(diffusion_size());
  diffusion_set(a,
    i, n, m, new_coordinates, point_size, u, total_colors, painter);
  
  out_filename = argv[6];
  diffusion_write_to_file(out_filename, width, height, a);
  
  free(new_coordinates);
u_free:
  free(u);
m_free:
  mesh_free(m);
end:
  return errno;
}
