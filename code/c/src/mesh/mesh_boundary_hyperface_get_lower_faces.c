#include "idec_error_message.h"
#include "idec_memory.h"
#include "int.h"
#include "mesh.h"

static void generate_duplicates(
  int * duplicates_a1,
  const struct jagged1 * boundary_subset,
  const struct jagged2 * m_cf_dm1_p,
  int subfaces_per_cell)
{
  int boundary_subset_a0, i, i_local, index, j;
  int * boundary_subset_a1;
  struct jagged1 m_cf_dm1_p_i;

  boundary_subset_a0 = boundary_subset->a0;
  boundary_subset_a1 = boundary_subset->a1;

  index = 0;
  for (i_local = 0; i_local < boundary_subset_a0; ++i_local)
  {
    i = boundary_subset_a1[i_local];
    jagged2_part1(&m_cf_dm1_p_i, m_cf_dm1_p, i);
    for (j = 0; j < subfaces_per_cell; ++j)
    {
      duplicates_a1[index] = m_cf_dm1_p_i.a1[j];
      ++index;
    }
  }
}

void mesh_boundary_hyperface_get_lower_faces(
  struct jagged1 ** skeleton_p,
  int * status,
  const struct mesh * m,
  const struct jagged1 * boundary_subset,
  int p)
{
  int dm1, subfaces_per_cell;
  struct jagged1 duplicates;
  struct jagged2 m_cf_dm1_p;

  dm1 = m->dim - 1;
  mesh_cf_part2(&m_cf_dm1_p, m, dm1, p);
  subfaces_per_cell = (1 << (dm1 - p)) * int_binomial(dm1, p);

  duplicates.a0 = boundary_subset->a0 * subfaces_per_cell;
  idec_memory_allocate(
    (void **) &(duplicates.a1), status, sizeof(int) * duplicates.a0);
  if (*status)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_memory_allocate("duplicates");
    return;
  }

  generate_duplicates(
    duplicates.a1, boundary_subset, &m_cf_dm1_p, subfaces_per_cell);

  *skeleton_p = jagged1_delete_duplicates(&duplicates);
  if (*skeleton_p == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_cannot_calculate("*skeleton_p");
    *status = 1;
    idec_memory_free(duplicates.a1);
    return;
  }
  idec_memory_free(duplicates.a1);
}
