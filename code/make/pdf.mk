build/$(MODE)/pdf: | build/$(MODE)
	mkdir -p $@

build/$(MODE)/pdf/filled_window_rainbow_100.pdf:\
  build/$(MODE)/bin/idec_graphics_filled_window$(.EXE)\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_filled_window$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_filled_window\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

include code/make/pdf/mesh.mk
include code/make/pdf/diffusion.mk

_pdf :=\
  build/$(MODE)/pdf/filled_window_rainbow_100.pdf\
  $(_pdf_mesh)\
  $(_pdf_diffusion)\

.PHONY: pdf pdf_clean pdf_distclean

pdf: $(_pdf)

pdf_clean:
	-$(RM) $(_pdf)

pdf_distclean:
	-$(RM) -r build/$(MODE)/pdf
