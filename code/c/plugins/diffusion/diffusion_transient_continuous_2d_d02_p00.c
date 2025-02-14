#include "diffusion_transient_continuous.h"

static double pi_0(const double * x)
{
  return 4.;
}

static double kappa_1(const double * x)
{
  return 6.;
}

static double initial(const double * x)
{
  if (x[0] == 0. && (0. <= x[1] && x[1] <= 15.))
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
  return (x[0] == 0 || x[0] == 20.) && (0. <= x[1] && x[1] <= 15.);
}

static double g_dirichlet(const double * x)
{
  if (x[0] == 0. && (0. <= x[1] && x[1] <= 15.))
    return 100.;
  else if (x[0] == 20. && (0. <= x[1] && x[1] <= 15.))
    return 0.;
  return -100;
}

static int boundary_neumann(const double * x)
{
  return ((x[1] == 0. || x[1] == 15.) && (0. <= x[0] && x[0] <= 20.));
}

static double g_neumann(const double * x)
{
  return 0;
}

const struct diffusion_transient_continuous
diffusion_transient_continuous_2d_d02_p00 =
{
  pi_0,
  kappa_1,
  initial,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  g_neumann
};
