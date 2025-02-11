.PHONY: svg svg_clean svg_distclean

build/$(MODE)/svg: | build/$(MODE)
	mkdir -p $@

build/$(MODE)/svg/filled_window_rainbow_100.svg:\
  build/$(MODE)/bin/idec_graphics_filled_window$(.EXE)\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_filled_window$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_filled_window\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_svg_animation\
  --output=$@

include code/make/svg/mesh.mk

_svg :=\
  build/$(MODE)/svg/filled_window_rainbow_100.svg\
  $(_svg_mesh)\

svg: $(_svg)

svg_clean:
	-$(RM) $(_svg)

svg_distclean:
	-$(RM) -r build/$(MODE)/svg
