#include <stdio.h>

#include "color.h"
#include "mesh_measures.h"
#include "mesh_qc.h"

void mesh_measures_default(
  double *** m_measures, int * status, const struct mesh * m)
{
  *m_measures = mesh_qc_vol(m);
  if (*m_measures == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m_measures\n", stderr);
    *status = 1;
  }
}
