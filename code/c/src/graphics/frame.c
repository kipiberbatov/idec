#include "frame.h"
#include "points_array_minimal_distance.h"

/* rectangle for eclosing original mesh coordinates */
typedef struct rectangle
{
  double east;
  double west;
  double south;
  double north;
} rectangle;

static double
rectangle_intrinsic_for_set_of_points_west(int n, const double * p)
{
  int i;
  double west, x;

  west = p[0];
  for (i = 1; i < n; ++i)
  {
    x = p[2 * i];
    if (x < west)
      west = x;
  }
  return west;
}

static double
rectangle_intrinsic_for_set_of_points_east(int n, const double * p)
{
  int i;
  double east, x;

  east = p[0];
  for (i = 1; i < n; ++i)
  {
    x = p[2 * i];
    if (x > east)
      east = x;
  }
  return east;
}

static double
rectangle_intrinsic_for_set_of_points_south(int n, const double * p)
{
  int i;
  double south, x;

  south = p[1];
  for (i = 1; i < n; ++i)
  {
    x = p[2 * i + 1];
    if (x < south)
      south = x;
  }
  return south;
}

static double
rectangle_intrinsic_for_set_of_points_north(int n, const double * p)
{
  int i;
  double north, x;

  north = p[1];
  for (i = 1; i < n; ++i)
  {
    x = p[2 * i + 1];
    if (x > north)
      north = x;
  }
  return north;
}

static void
rectangle_intrinsic_for_set_of_points(rectangle * a, int n, const double * p)
{
  a->west = rectangle_intrinsic_for_set_of_points_west(n, p);
  a->east = rectangle_intrinsic_for_set_of_points_east(n, p);
  a->south = rectangle_intrinsic_for_set_of_points_south(n, p);
  a->north = rectangle_intrinsic_for_set_of_points_north(n, p);
}

typedef struct image_map
{
  frame extrinsic;
  double scaling;
} image_map;

void frame_drawing_region(
  frame * drawing_region,
  double width,
  double height,
  const margin * window_margin)
{
  drawing_region->left = window_margin->left;
  drawing_region->right = width - window_margin->left;
  drawing_region->top = window_margin->top;
  drawing_region->bottom = height - window_margin->bottom;
}

static void frame_internal(
  image_map * im,
  const rectangle * a,
  const frame * drawing_region)
{
  double a_x, a_y, q, r_x, r_y, u;

  a_x = a->east - a->west;
  a_y = a->north - a->south;

  r_x = drawing_region->right - drawing_region->left;
  r_y = drawing_region->bottom - drawing_region->top;

  u = a_x * r_y - a_y * r_x;
  if (u > 0)
  {
    im->scaling = r_x / a_x;
    q = u / (2 * a_x);
    im->extrinsic.left = drawing_region->left;
    im->extrinsic.right = drawing_region->right;
    im->extrinsic.top = drawing_region->top + q;
    im->extrinsic.bottom = drawing_region->bottom - q;
  }
  else
  {
    im->scaling = r_y / a_y;
    q = - u / (2 * a_y);
    im->extrinsic.left = drawing_region->left + q;
    im->extrinsic.right = drawing_region->right - q;
    im->extrinsic.top = drawing_region->top;
    im->extrinsic.bottom = drawing_region->bottom;
  }
}

static void frame_for_mesh_drawing(
  frame * c,
  double minimal_distance,
  const image_map * im,
  double reduction)
{
  double b_x, b_y, rho, sigma_x, sigma_y;
  frame b;

  b = im->extrinsic;
  b_x = b.right - b.left;
  b_y = b.bottom - b.top;
  rho = im->scaling * minimal_distance;
  if (b_x < b_y)
  {
    sigma_x = rho / reduction;
    sigma_y = sigma_x * (b_y / b_x);
  }
  else
  {
    sigma_y = rho / reduction;
    sigma_x = sigma_y * (b_x / b_y);
  }
  c->left = b.left + sigma_x;
  c->right = b.right - sigma_x;
  c->top = b.top + sigma_y;
  c->bottom = b.bottom - sigma_y;
}

static void frame_new_coordinates(
  double * new_coordinates,
  const rectangle * a,
  const frame * c,
  int n,
  const double * points,
  double reduction)
{
  int i;
  double a_x, c_x, d_x, d_y, mu;

  a_x = a->east - a->west;
  c_x = c->right - c->left;
  mu = c_x / a_x;
  d_x = c->left - a->west * mu;
  d_y = c->bottom + a->south * mu;

  for (i = 0; i < n; ++i)
  {
    new_coordinates[2 * i] = mu * points[2 * i] + d_x;
    new_coordinates[2 * i + 1] = - mu * points[2 * i + 1] + d_y;
  }
}

void frame_internal_info_for_set_of_points(
  frame_mesh_data * data,
  int n,
  const double * points,
  double width,
  double height,
  const margin * window_margin)
{
  double minimal_distance, reduction, rho;
  rectangle a;
  frame c, drawing_region;
  image_map im;

  rectangle_intrinsic_for_set_of_points(&a, n, points);
  frame_drawing_region(&drawing_region, width, height, window_margin);
  minimal_distance = points_array_minimal_distance(n, points);
  frame_internal(&im, &a, &drawing_region);
  reduction = 4;
  frame_for_mesh_drawing(&c, minimal_distance, &im, reduction);
  frame_new_coordinates(data->coordinates, &a, &c, n, points, reduction);
  rho = im.scaling * minimal_distance;
  data->point_size = rho / reduction;
  data->line_width = rho / reduction;
}
