.PHONY: gtk gtk_clean gtk_distclean

build/$(MODE)/gtk: | build/$(MODE)
	mkdir -p $@

TIMELAPSE = 100
CLOSE_AUTOMATICALLY = 0

build/$(MODE)/gtk/filled_window_rainbow_100.log:\
  build/$(MODE)/bin/idec_graphics_filled_window$(.EXE)\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_filled_window$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_filled_window\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_gtk_animation\
  --title=filled_window\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

include code/make/gtk/diffusion.mk

_gtk :=\
  build/$(MODE)/gtk/filled_window_rainbow_100.log\
  $(_gtk_diffusion_transient)

gtk: $(_gtk)

gtk_clean:
	-$(RM) $(_gtk)

gtk_distclean:
	-$(RM) -r build/$(MODE)/gtk
