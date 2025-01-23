#include <cairo.h>

#include "mesh.h"

typedef struct diffusion diffusion;

void gtk_spacetime_pde(
  cairo_t * cr, int * status, double width, double height, diffusion * a);
