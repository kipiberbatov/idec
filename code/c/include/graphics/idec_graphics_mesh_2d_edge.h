#ifndef _idec_graphics_mesh_2d_edge_h
#define _idec_graphics_mesh_2d_edge_h

struct idec_graphics_mesh_2d_edge
{
  int total_colors;
  int color_index;
  double width;
  void * data;
  void (*set_color)(void *, int *, int, int);
  void (*draw_curve)(void *, int *, const void *);
};

#endif /* _idec_graphics_mesh_2d_edge_h */
