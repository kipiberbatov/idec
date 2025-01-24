#ifndef _idec_filled_window_h
#define _idec_filled_window_h

/*
Structure for drawing animation of a filled window of given 'width' and 'height'
with 'total_colors' from a color scheme, specified elewhere.
*/
struct idec_filled_window
{
  /* immutable once set */
  int width;
  int height;
  int total_colors;

  /* mutable on each iteration of animation drawing */
  int old_index;
  int new_index;
};

#endif /* _idec_filled_window_h */
