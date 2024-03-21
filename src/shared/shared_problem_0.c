#include "double.h"
#include "diffusion_data.h"

static double initial(const double * x)
{
  return x[0] * x[0] + x[1] * x[1];
}

static double source(const double * x)
{
  return -4;
}

static int boundary_dirichlet(const double * x)
{
  double tolerance = 0.0000001;
  return double_equal(x[1], 0, tolerance) || double_equal(x[1], 1, tolerance);
}

static double g_dirichlet(const double * x)
{
  return x[0] * x[0] + x[1] * x[1];
}

static int boundary_neumann(const double * x)
{
  double tolerance = 0.0000001;
  return double_equal(x[0], 0, tolerance) || double_equal(x[0], 1, tolerance);
}

static double g_neumann(const double * x)
{
  return 0;
}

const diffusion_data diffusion_problem_0 =
{
  .initial = initial,
  .source = source,
  .boundary_dirichlet = boundary_dirichlet,
  .g_dirichlet = g_dirichlet,
  .boundary_neumann = boundary_neumann,
  .g_neumann = g_neumann
};
