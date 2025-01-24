#ifndef _idec_animation_generic_data_h
#define _idec_animation_generic_data_h

struct idec_animation_generic_data
{
  /* immutable once set */
  double width;
  double height;
  int total_steps;

  /* mutable on each iteration of animation drawing */
  int old_index;
  int new_index;
};

#endif /* _idec_animation_generic_data_h */
