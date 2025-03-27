#ifndef _idec_graphics_mesh_2d_edge_h
#define _idec_graphics_mesh_2d_edge_h

struct idec_graphics_mesh_2d_edge
{
  void * data;
  double width;
  void * color;
  void (*draw_curve)(void *, int *, const void *);
};

#endif /* _idec_graphics_mesh_2d_edge_h */
