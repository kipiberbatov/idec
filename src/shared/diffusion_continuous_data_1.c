#include "diffusion_continuous.h"

static double pi_0(const double * x)
{
  return 4;
}

static double initial(const double * x)
{
  if (x[0] == 0.)
    return 100.;
  else
    return 0.;
}

static double source(const double * x)
{
  return 0;
}

static int boundary_dirichlet(const double * x)
{
  return (x[0] == 0. || x[0] == 1.) && (0. <= x[1] && x[1] <= 1.);
}

static double g_dirichlet(const double * x)
{
  if (x[0] == 0.)
    return 100.;
  else
    return 0.;
}

static int boundary_neumann(const double * x)
{
  return (x[1] == 0. || x[1] == 1.) && (0. < x[0] && x[0] < 1.);
}

static double g_neumann(const double * x)
{
  return 0;
}

const diffusion_continuous diffusion_continuous_data_1 =
{
  pi_0,
  initial,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  g_neumann
};
