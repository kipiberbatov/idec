#include "region.h"
#include "region_private.h"

double region_measure(const region * r)
{
  switch (r->type)
  {
  case region_type_point_2d:
    return point_2d_measure((const point_2d *) r->data);
  case region_type_line_2d:
    return line_2d_measure((const line_2d *) r->data);
  case region_type_triangle_2d:
    return triangle_2d_measure((const triangle_2d *) r->data);
  case region_type_simplex:
    return simplex_measure((const simplex *) r->data);
  case region_type_quasi_cube:
    return quasi_cube_measure((const quasi_cube *) r->data);
  }
  return 0.;
}
