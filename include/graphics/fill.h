#include <stdlib.h>

#include <cairo.h>
#include "painter.h"

typedef struct fill fill;

size_t fill_size(void);

int * fill_get_index(fill * a);
int * fill_get_index_void(void * a);

int fill_get_total_steps(const fill * a);
int fill_get_total_steps_void(const void * a);

painter fill_get_paint(fill * a);

void fill_set(fill * a, int * i, int n, painter paint);

void fill_draw(cairo_t * cr, double width, double height, fill * a);
void fill_draw_void(cairo_t * cr, double width, double height, void * a);
