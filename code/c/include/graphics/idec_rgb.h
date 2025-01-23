#ifndef _idec_rgb_h
#define _idec_rgb_h

typedef struct idec_rgb
{
  double red;
  double green;
  double blue;
} idec_rgb;

void
idec_rgb_set_from_scheme_rainbow(idec_rgb * color, int * status, int i, int n);

#endif /* _idec_rgb_h */
