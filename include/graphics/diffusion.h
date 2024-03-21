#include <cairo.h>
#include "mesh.h"
#include "painter.h"

typedef struct diffusion diffusion;

int diffusion_size(void);

int * diffusion_get_index(diffusion * a);
int * diffusion_get_index_void(void * a);
int diffusion_get_total_steps(const diffusion * a);
int diffusion_get_total_steps_void(const void * a);
mesh * diffusion_get_mesh(diffusion * a);
double * diffusion_get_new_coordinates(diffusion * a);
double diffusion_get_point_size(const diffusion * a);
double * diffusion_get_values(diffusion * a);
double diffusion_min_value(const diffusion * a);
double diffusion_max_value(const diffusion * a);
int diffusion_get_total_colors(const diffusion * a);

painter diffusion_get_painter(diffusion * a);

void diffusion_set(
  diffusion * a,
  int * i,
  int n,
  mesh * m,
  double * new_coordinates,
  double point_size,
  double * u,
  int total_colors,
  painter paint);

void diffusion_draw(cairo_t * cr, double width, double height, diffusion * a);
void diffusion_draw_void(cairo_t * cr, double width, double height, void * a);
