#include <cairo.h>

#include "mesh.h"

typedef struct heat_flow heat_flow;

int heat_flow_size(void);

int * heat_flow_get_index(heat_flow * a);

int heat_flow_total_steps(heat_flow * a);

void heat_flow_set(
  heat_flow * a, int * i, int n, mesh * m, double * u, int total_colors);

heat_flow *
heat_flow_new(int * i, int n, mesh * m, double * u, int total_colors);

void
gtk_spacetime_pde(cairo_t * cr, double width, double height, heat_flow * a);
