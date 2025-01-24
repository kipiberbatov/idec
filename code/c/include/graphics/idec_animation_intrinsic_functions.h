#ifndef _idec_animation_intrinsic_functions_h
#define _idec_animation_intrinsic_functions_h

struct idec_animation_intrinsic_functions
{
  double (*get_width)(const void *);
  double (*get_height)(const void *);
  int (*get_total_steps)(const void *);
  int * (*get_old_index_address)(const void *);
  int * (*get_new_index_address)(const void *);
  void (*update_new_index)(void *);
};

#endif /* _idec_animation_intrinsic_functions_h */
