#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "double.h"
#include "diffusion.h"

struct diffusion
{
  int * i;
  int n;
  mesh * m;
  double * u;
  double min_value;
  double max_value;
  int total_colors;
};

int diffusion_size(void)
{
  return (int) sizeof(diffusion);
}

int * diffusion_get_index(diffusion * a)
{
  return a->i;
}

int diffusion_total_steps(diffusion * a)
{
  return a->n;
}

mesh * diffusion_get_mesh(diffusion * a)
{
  return a->m;
}

double * diffusion_get_values(diffusion * a)
{
  return a->u;
}

double diffusion_min_value(const diffusion * a)
{
  return a->min_value;
}

double diffusion_max_value(const diffusion * a)
{
  return a->max_value;
}

int diffusion_get_total_colors(const diffusion * a)
{
  return a->total_colors;
}

void diffusion_set(
  diffusion * a, int * i, int n, mesh * m, double * u, int total_colors)
{
  a->i = i;
  a->n = n;
  a->m = m;
  a->u = u;
  a->total_colors = total_colors;
  a->min_value = double_array_min(n * m->cn[0], u);
  a->max_value = double_array_max(n * m->cn[0], u);
}

diffusion *
diffusion_new(int * i, int n, mesh * m, double * u, int total_colors)
{
  diffusion * a;
  
  a = malloc(sizeof(diffusion));
  if (errno)
  {
    fprintf(stderr, 
      "Error during execution of function %s in file %s on line %d: "
      "cannot allocate memory for het flow structure\n",
      __func__, __FILE__,__LINE__);
   return NULL;
  }
  
  diffusion_set(a, i, n, m, u, total_colors);
  return a;
}
