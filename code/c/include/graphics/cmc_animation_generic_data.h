#ifndef _cmc_animation_generic_data_h
#define _cmc_animation_generic_data_h

struct cmc_animation_generic_data
{
  /* immutable once set */
  double width;
  double height;
  int total_steps;

  /* mutable on each iteration of animation drawing */
  int old_index;
  int new_index;
};

#endif /* _cmc_animation_generic_data_h */
