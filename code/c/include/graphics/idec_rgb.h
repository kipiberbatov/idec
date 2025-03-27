#ifndef _idec_rgb_h
#define _idec_rgb_h

struct idec_rgb
{
  double red;
  double green;
  double blue;
};

void idec_rgb_set_from_scheme_rainbow(
  struct idec_rgb * color, int * status, int i, int n);

void idec_rgb_set_from_scheme_rainbow_no_checks(
  struct idec_rgb * color, int i, int n);

void idec_rgb_check_color_scheme_rainbow(int * status, int n);

void idec_rgb_allocate_color(struct idec_rgb ** color, int * status);

#endif /* _idec_rgb_h */
