#ifndef _idec_graphics_mesh_2d_0_cochain_sequence_h
#define _idec_graphics_mesh_2d_0_cochain_sequence_h

/* used in conjunction with idec_animation_generic_data */
struct idec_graphics_mesh_2d_0_cochain_sequence
{
  int number_of_nodes;
  double * values;
  double * coordinates;
  double * point_sizes;
  double min_value;
  double max_value;
};

#endif /* _idec_graphics_mesh_2d_0_cochain_sequence_h */
