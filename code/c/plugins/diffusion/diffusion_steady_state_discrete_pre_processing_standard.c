#include "boundary_pseudoscalar_field_discretize.h"
#include "de_rham.h"
#include "diffusion_steady_state_discrete_pre_processing.h"
#include "mesh.h"
#include "unsigned_approximation.h"

struct diffusion_steady_state_discrete_pre_processing
diffusion_steady_state_discrete_pre_processing_standard =
{
  unsigned_approximation_of_scalar_field_on_hyperfaces,
  unsigned_approximation_of_scalar_field_on_1_cells,
  de_rham_top_dimension,
  mesh_boundary_hyperfaces_from_constraint_1,
  de_rham_boundary_0,
  boundary_pseudoscalar_field_discretize
};
