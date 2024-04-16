#include <cairo.h>

void pdf_draw(
	cairo_t * cr,
	double width,
	double height,
	void * a,
	void (*draw)(cairo_t *, double, double, void *));
