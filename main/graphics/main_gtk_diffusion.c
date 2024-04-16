#include <alloca.h>
#include <errno.h>
#include <stdlib.h>

#include <gtk/gtk.h>

#include "double.h"
#include "diffusion.h"
#include "image.h"
#include "int.h"
#include "mesh.h"
#include "paint_rgb.h"
#include "gtk_draw.h"
#include "gtk_run.h"

static int gtk_draw_diffusion(GtkWidget * widget, cairo_t * cr, void * data)
{
  gtk_draw(
    widget,
    cr,
    data,
    diffusion_draw_void,
    diffusion_get_index_void,
    diffusion_get_total_steps_void,
    diffusion_increment_index_void
  );
  return FALSE;
}

int main(int argc, char ** argv)
{
  char * m_format, * u_format;
  char * m_filename, * u_filename;
  int i, n, steps, total_colors;
  unsigned int speed;
  double height, point_size, width;
  double * new_coordinates, * u;
  mesh * m;
  diffusion * a;
  const char title[80] = "Heat flow in 2D";
  
  errno = 0;
  
  if (argc != 6)
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
  
  total_colors = 10000;
  
  a = (diffusion *) alloca(diffusion_size());
  diffusion_set(a,
    i, n, m, new_coordinates, point_size, u, total_colors, paint_rgb);
  
  speed = 100;
  
  gtk_init(&argc, &argv);
  
  gtk_run(gtk_draw_diffusion, (diffusion *) a, width, height, speed, title);
  
  gtk_main();
  
  errno = 0;
  
  free(new_coordinates);
u_free:
  free(u);
m_free:
  mesh_free(m);
end:
  return errno;
}
