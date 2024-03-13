#ifndef _rgb_h
#define _rgb_h

typedef struct rgb
{
  double red;
  double green;
  double blue;
} rgb;

void rgb_color(rgb * color, int i, int n);

#endif /* _rgb_h */
