#include <math.h>

#include "diffusion_steady_state_continuous.h"

#define A 5.

static double pi_1(const double * x)
{
  return 6.;
}

static double source(const double * x)
{
  return 0;
}

static int boundary_dirichlet(const double * x)
{
  return (fabs(x[0] + x[1] + A) < 0.0001 && -A <= x[0] && x[0] <= 0.)
    || (fabs(x[0] + x[1] - A) < 0.0001 && 0. <= x[0] && x[0] <= A);
}

static double g_dirichlet(const double * x)
{
  if (fabs(x[0] + x[1] + A) < 0.0001)
    return 100.;
  else
    return 0.;
}

static int boundary_neumann(const double * x)
{
  return (fabs(x[1] - x[0] - A) < 0.0001 && -A <= x[0] && x[0] <= 0.)
    || (fabs(x[1] - x[0] + A) < 0.0001 && 0. <= x[0] && x[0] <= A);
}

static double g_neumann(const double * x)
{
  return 0;
}

const diffusion_steady_state_continuous
diffusion_steady_state_continuous_2d_d01_p00 =
{
  pi_1,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  g_neumann
};
