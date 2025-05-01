#include "boundary_scalar_field_discretize.h"
#include "boundary_pseudoscalar_field_discretize.h"
#include "de_rham.h"
#include "diffusion_steady_state_discrete_pre_processing.h"
#include "mesh.h"
#include "unsigned_approximation.h"

static void de_rham_d(
  double * x,
  const mesh * m,
  const double * m_vol_d,
  double (*f)(const double *))
{
  de_rham_nonzero(x, m, m->dim, m_vol_d, f);
}

static void get_boundary_dirichlet_dm1(
    struct jagged1 ** boundary_dirichlet_dm1,
    int * status,
    const struct mesh * m,
    const struct jagged1 * m_boundary_dm1,
    int (*boundary_dirichlet_continuous)(const double *))
{
  *boundary_dirichlet_dm1
  = mesh_boundary_hyperfaces_from_constraint(m, boundary_dirichlet_continuous);
  if (*boundary_dirichlet_dm1 == NULL)
  {
    *status = 1;
    return;
  }
}

static void get_g_dirichlet(
  double * g_dirichlet,
  const struct mesh * m,
  const struct jagged1 * boundary_dirichlet_0,
  double (*g_dirichlet_continuous)(const double *))
{
  boundary_scalar_field_discretize(
    g_dirichlet,
    m->dim_embedded,
    m->coord,
    boundary_dirichlet_0,
    g_dirichlet_continuous);
}

void get_g_neumann(
  double * g_neumann,
  const struct mesh * m,
  const double * m_vol_dm1,
  const struct jagged1 * boundary_neumann_dm1,
  double (*g_neumann_continuous)(const double *))
{
  boundary_pseudoscalar_field_discretize(
    g_neumann, m, m_vol_dm1, boundary_neumann_dm1, g_neumann_continuous);
}

struct diffusion_steady_state_discrete_pre_processing
diffusion_steady_state_discrete_pre_processing_standard =
{
  unsigned_approximation_of_scalar_field_on_hyperfaces,
  unsigned_approximation_of_scalar_field_on_1_cells,
  de_rham_d,
  get_boundary_dirichlet_dm1,
  get_g_dirichlet,
  get_g_neumann
};
