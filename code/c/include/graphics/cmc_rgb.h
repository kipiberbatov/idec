#ifndef _cmc_rgb_h
#define _cmc_rgb_h

struct cmc_rgb
{
  double red;
  double green;
  double blue;
};

extern void (* const * cmc_rgb_color_scheme_rainbow_regions)(
  struct cmc_rgb *, int, int);

extern const int cmc_rgb_color_scheme_rainbow_regions_size;

void cmc_rgb_set_from_scheme_rainbow(
  struct cmc_rgb * color, int * status, int i, int n);

void cmc_rgb_set_from_scheme_rainbow_no_checks(
  struct cmc_rgb * color, int i, int n);

void cmc_rgb_check_color_scheme_rainbow(int * status, int n);

void cmc_rgb_allocate_color(struct cmc_rgb ** color, int * status);

void cmc_rgb_get_color_rgb(struct cmc_rgb * rgb_color, const void * color);

#endif /* _cmc_rgb_h */
