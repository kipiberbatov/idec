#include "frame.h"
#include "points_array_minimal_distance.h"

/* rectangle for eclosing original mesh coordinates */
typedef struct rectangle rectangle;
struct rectangle {double east, west, south, north;};

static void rectangle_intrinsic_for_set_of_points(rectangle * a,
  int n, const double * p)
{
  int i;
  double x, tmp;

  /* west */
  tmp = p[0];
  for (i = 1; i < n; ++i)
  {
    x = p[2 * i];
    if (x < tmp)
      tmp = x;
  }
  a->west = tmp;

  /* east */
  tmp = p[0];
  for (i = 1; i < n; ++i)
  {
    x = p[2 * i];
    if (x > tmp)
      tmp = x;
  }
  a->east = tmp;

  /* south */
  tmp = p[1];
  for (i = 1; i < n; ++i)
  {
    x = p[2 * i + 1];
    if (x < tmp)
      tmp = x;
  }
  a->south = tmp;

  /* north */
  tmp = p[1];
  for (i = 1; i < n; ++i)
  {
    x = p[2 * i + 1];
    if (x > tmp)
      tmp = x;
  }
  a->north = tmp;
}

void frame_internal_info_for_set_of_points(
  frame * window_frame,
  frame_mesh_data * data,
  int n,
  const double * points,
  double width,
  double height,
  const margin * window_margin)
{
  rectangle a;
  frame b, c, r;
  int i;
  double lambda, mu, tau, rho, sigma_x, sigma_y, q;
  double a_x, a_y, b_x, b_y, c_x, d_x, d_y, r_x, r_y, u;
  double reduction = 4;
  double * data_coordinates;

  tau = points_array_minimal_distance(n, points);

  rectangle_intrinsic_for_set_of_points(&a, n, points);
  a_x = a.east - a.west;
  a_y = a.north - a.south;

  r.left = window_margin->left;
  r.right = width - window_margin->left;
  r.top = window_margin->top;
  r.bottom = height - window_margin->bottom;
  r_x = r.right - r.left;
  r_y = r.bottom - r.top;

  u = a_x * r_y - a_y * r_x;
  if (u > 0)
  {
    lambda = r_x / a_x;
    q = u / (2 * a_x);
    b.left = r.left;
    b.right = r.right;
    b.top = r.top + q;
    b.bottom = r.bottom - q;
  }
  else
  {
    lambda = r_y / a_y;
    q = - u / (2 * a_y);
    b.left = r.left + q;
    b.right = r.right - q;
    b.top = r.top;
    b.bottom = r.bottom;
  }
  b_x = b.right - b.left;
  b_y = b.bottom - b.top;

  rho = tau * lambda;

  data->point_size = rho / reduction;
  data->line_width = rho / reduction;
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
  c.left = b.left + sigma_x;
  c.right = b.right - sigma_x;
  c.top = b.top + sigma_y;
  c.bottom = b.bottom - sigma_y;
  c_x = c.right - c.left;

  mu = c_x / a_x;
  d_x = c.left - a.west * mu;
  d_y = c.bottom + a.south * mu;

  data_coordinates = data->coordinates;
  for (i = 0; i < n; ++i)
  {
    data_coordinates[2 * i] = mu * points[2 * i] + d_x;
    data_coordinates[2 * i + 1] = - mu * points[2 * i + 1] + d_y;
  }
  window_frame->left = b.left;
  window_frame->right = b.right;
  window_frame->top = b.top;
  window_frame->bottom = b.bottom;
}
