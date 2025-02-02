#include <stdio.h>

#include <cairo.h>
#include <cairo-pdf.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_animation_generic_data.h"

static void idec_cairo_render_snapshot_to_pageable_cairo_context(
  cairo_t * cr, int * status, const struct idec_animation * animation)
{
  animation->draw_snapshot((void *) cr, status, animation);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw to Cairo context\n", stderr);
    return;
  }
  cairo_show_page(cr);
  *status = cairo_status(cr);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot render with Cairo: %s\n",
      cairo_status_to_string(*status));
    return;
  }
}

static void idec_cairo_render_to_pageable_cairo_surface(
  cairo_surface_t * surface, struct idec_animation * animation, int * status)
{
  int i, n;
  struct idec_animation_generic_data * generic_data;
  cairo_t * cr;

  generic_data = animation->generic_data;
  n = generic_data->total_steps;
  i = generic_data->new_index;
  while (i < n)
  {
    cr = cairo_create(surface);
    *status = cairo_status(cr);
    if (*status)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot create Cairo context from Cairo surface: %s\n",
        cairo_status_to_string(*status));
      return;
    }

    idec_cairo_render_snapshot_to_pageable_cairo_context(cr, status, animation);
    if (*status)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot render snapshot %s%d%s to Cairo context\n",
        color_variable, i, color_none);
      return;
    }

    generic_data->old_index = i;
    animation->update_new_index(&(generic_data->new_index));
    i = generic_data->new_index;
    cairo_destroy(cr);
  }
}

static void idec_cairo_render_to_pdf(
  struct idec_animation * animation, int * status, const char * filename)
{
  double height, width;
  cairo_surface_t * surface;

  width = animation->generic_data->width;
  height = animation->generic_data->height;

  surface = cairo_pdf_surface_create(filename, width, height);
  *status = cairo_surface_status(surface);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot create Cairo PDF surface from filename %s%s%s: %s\n",
      color_variable, filename, color_none,
      cairo_status_to_string(*status));
    return;
  }

  idec_cairo_render_to_pageable_cairo_surface(surface, animation, status);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw animation to PDF Cairo surface\n", stderr);
    return;
  }
  cairo_surface_destroy(surface);
}

void idec_cairo_pdf_animation(
  struct idec_animation * animation,
  int * status,
  int argc,
  char ** argv,
  const char * filename)
{
  if (filename == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("empty filenames are not allowed\n", stderr);
    *status = 1;
    return;
  }

  idec_cairo_render_to_pdf(animation, status, filename);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot draw animation to PDF file %s%s%s\n",
      color_variable, filename, color_none);
    return;
  }
}
