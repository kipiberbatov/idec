#include "double.h"
#include "diffusion_continuous.h"

static double pi_0(const double * x)
{
  return 1;
}

static double pi_1(const double * x)
{
  return 1.;
}

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

const diffusion_continuous diffusion_continuous_p3 =
{
  pi_0,
  pi_1,
  initial,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  g_neumann
};
