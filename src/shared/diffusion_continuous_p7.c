#include <math.h>

#include "diffusion_continuous.h"

static double pi_0(const double * x)
{
  return 4.;
}

static double pi_1(const double * x)
{
  return 6.;
}

#define EPSILON .0000001

static int double_almost_zero(double a)
{
  return a < EPSILON && -a < EPSILON;
}

// static int double_in_open_0_1(double a)
// {
//   return -EPSILON < a && a < 1 + EPSILON;
// }

static double initial(const double * x)
{
  if (double_almost_zero(x[0]) && (0. <= x[1] && x[1] <= 15.))
    return 100.;
  else
    return 0.;
}

static double source(const double * x)
{
  return 0;
}

// static int boundary_dirichlet(const double * x)
// {
//   return (x[0] == 0. || x[0] == 1.) && (0. < x[1] && x[1] < 1.);
// }

// static double g_dirichlet(const double * x)
// {
//   if (x[0] == 0. && (0. < x[1] && x[1] < 1.))
//     return 100.;
//   else
//     return 0.;
// }

// static int boundary_neumann(const double * x)
// {
//   return (x[1] == 0. || x[1] == 1.) && (0. <= x[0] && x[0] <= 1.);
// }

// static double g_neumann(const double * x)
// {
//   return 0;
// }

static int boundary_dirichlet(const double * x)
{
  return (x[0] == 0.) && (0. <= x[1] && x[1] <= 15.);
}

static double g_dirichlet(const double * x)
{
  return 100.;
}

static int boundary_neumann(const double * x)
{
  return ((x[1] == 0. || x[1] == 15.) && (0. < x[0] && x[0] < 20.));
}

static double g_neumann(const double * x)
{
  return 0;
}

const diffusion_continuous diffusion_continuous_p7 =
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
