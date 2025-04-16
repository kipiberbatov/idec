#include <stdio.h>
#include <string.h>

#include "color.h"
#include "mesh_measures.h"

struct mesh;

void mesh_measures(double *** m_measures, int * status,
  const struct mesh * m, const char * method)
{
  void (*measurer)(double *** m_measures, int * status, const struct mesh * m);

  if (!strcmp(method, "default"))
    measurer = mesh_measures_default;
  else if (!strcmp(method, "simplicial-or-quasi-cubical"))
    measurer = mesh_measures_simplicial_or_quasi_cubical;
  else if (!strcmp(method, "circular-forman"))
    measurer = mesh_measures_circular_forman;
  else if (!strcmp(method, "hemisphere-forman"))
    measurer = mesh_measures_hemisphere_forman;
  else
    measurer = NULL;

  if (measurer == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "method %s is not supported\n", method);
    *status = 1;
    return;
  }

  measurer(m_measures, status, m);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate m_measures using method %s\n", method);
  }
}
