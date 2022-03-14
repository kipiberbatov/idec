#include <stdlib.h>
#include "region.h"

region * region_new(region_names_list r_name, void * r_object)
{
  region * r;
  r = (region *) malloc(sizeof(region));
  /* NULL pointer check */
  r->name = r_name;
  r->object = r_object;
  return r;
}

void region_free(region * r)
{
  switch (r->name)
  {
  case POINT:
    point_free((point *) r->object);
    break;
  case LINE:
    line_free((line *) r->object);
    break;
  case TRIANGLE:
    triangle_free((triangle *) r->object);
    break;
  }
  free(r);
}

double region_measure(region * r)
{
  switch (r->name)
  {
  case POINT:
    return point_measure((point *) r->object);
  case LINE:
    return line_measure((line *) r->object);
  case TRIANGLE:
    return triangle_measure((triangle *) r->object);
  }
  return 0.;
}
