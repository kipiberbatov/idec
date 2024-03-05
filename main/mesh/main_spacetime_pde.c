#include "spacetime_pde.h"

/*
Solve the following problem:
Given a mesh M for the unit square, and the discrete Laplacian, solve:
  . du/dt = -Laplacian(u) + f    in the interior nodes of M
  . u = g_d                      at the boundary nodes of M
  . u(0) = initial               at all nodes of M
For this example it is assumed that f and g_d are time independent.
An artificial example with u(t, x_0, x_1) = x_0^2 + x_1^2 is taken.
This corresponds to f(x_0, x_1) = -4.
*/

static double f(const double * x)
{
  return -4;
}

static double g_d(const double * x)
{
  return x[0] * x[0] + x[1] * x[1];
}

static double initial(const double * x)
{
  return x[0] * x[0] + x[1] * x[1];
}

int main(int argc, char * argv[])
{
  return spacetime_pde_heat_equation_runner(argc, argv, f, g_d, initial);
}
