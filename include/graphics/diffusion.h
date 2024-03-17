#include "mesh.h"

typedef struct diffusion diffusion;

int diffusion_size(void);

int * diffusion_get_index(diffusion * a);
int diffusion_total_steps(diffusion * a);
mesh * diffusion_get_mesh(diffusion * a);
double * diffusion_get_values(diffusion * a);
double diffusion_min_value(const diffusion * a);
double diffusion_max_value(const diffusion * a);
int diffusion_get_total_colors(const diffusion * a);

void diffusion_set(
  diffusion * a, int * i, int n, mesh * m, double * u, int total_colors);

diffusion *
diffusion_new(int * i, int n, mesh * m, double * u, int total_colors);
