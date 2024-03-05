#include <math.h>
#include "spacetime_pde.h"

/*
Solve the following problem:
Given a mesh M for the unit square, and the discrete Laplacian, solve:
  . du/dt = -Laplacian(u) + f    in the interior nodes of M
  . u = g_d                      at the boundary nodes of M
  . u(0) = initial               at all nodes of M
For this example it is assumed that f and g_d are time independent.
An artificial example with
  u(t, x, y) = exp(-2 * pi^2) sin(pi x) sin(pi y)
is taken.
This corresponds to f = 0, g_d = 0, initial = sin(pi x) sin(pi y).
*/

static double f(const double * x)
{
  return 0;
}

static double g_d(const double * x)
{
  return 0;
}

static double initial(const double * x)
{
  return sin(M_PI * x[0]) * sin(M_PI * x[1]);
}

int main(int argc, char * argv[])
{
  return spacetime_pde_heat_equation_runner(argc, argv, f, g_d, initial);
}
