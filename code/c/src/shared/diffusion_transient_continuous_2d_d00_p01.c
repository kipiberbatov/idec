#include "diffusion_transient_continuous.h"

static double pi_0(const double * x)
{
  return 4.;
}

static double pi_1(const double * x)
{
  return 6.;
}

static double initial(const double * x)
{
  if (x[0] == 0. && (0. <= x[1] && x[1] <= 1.))
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
  else /* x[0] == 1. */
    return 0.;
}

static int boundary_neumann(const double * x)
{
  return ((x[1] == 0. || x[1] == 1.) && (0. < x[0] && x[0] < 1.));
}

static double g_neumann(const double * x)
{
  return 0;
}

const diffusion_transient_continuous
diffusion_transient_continuous_2d_d00_p01 =
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