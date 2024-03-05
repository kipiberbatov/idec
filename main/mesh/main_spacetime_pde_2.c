#include <math.h>
#include "spacetime_pde.h"

/*
Solve the following problem:
Given a mesh M for the unit square, and the discrete Laplacian, solve:
  . du/dt = -Laplacian(u) + f    in the interior nodes of M
  . u = g_d                      at the boundary nodes of M
  . u(0) = initial               at all nodes of M
In this example:
  . we have zero degrees everywhere except at the central node where it is 100
  . we maintain zero degrees at the boundary
After a finite amount of time the temperature will be zero degrees everywhere.
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
  if (fabs(x[0] - 0.5) < 0.00001 && fabs(x[1] - 0.5) < 0.00001)
    return 100;
  return 0;
}

int main(int argc, char * argv[])
{
  return spacetime_pde_heat_equation_runner(argc, argv, f, g_d, initial);
}
