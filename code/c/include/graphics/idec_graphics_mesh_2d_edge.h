#ifndef _idec_graphics_mesh_2d_edge_h
#define _idec_graphics_mesh_2d_edge_h

struct idec_graphics_mesh_2d_edge
{
  int total_colors;
  int color_index;
  double e0[2];
  double e1[2];
  double width;
  void (*set_color)(void *, int *, int, int);
};

#endif /* _idec_graphics_mesh_2d_edge_h */
