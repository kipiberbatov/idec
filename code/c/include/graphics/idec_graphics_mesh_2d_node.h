#ifndef _idec_graphics_mesh_2d_node_h
#define _idec_graphics_mesh_2d_node_h

struct idec_graphics_mesh_2d_node
{
  int total_colors;
  int color_index;
  double * coordinates;
  double size;
  void (*set_color)(void *, int *, int, int);
};

#endif /* _idec_graphics_mesh_2d_node_h */
