build/$(MODE)/demo/pdf: | build/$(MODE)/demo
	mkdir -p $@

build/$(MODE)/demo/pdf/filled_window_default.pdf:\
  build/$(MODE)/bin/idec_filled_window$(.EXE)\
  build/$(MODE)/obj/src/idec_cairo_canvas_functions_filled_window$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_canvas_functions_filled_window\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

include code/make/demo/pdf_mesh.mk
include code/make/demo/pdf_diffusion.mk

_demo_pdf :=\
  build/$(MODE)/demo/pdf/filled_window_default.pdf\
  $(_demo_pdf_mesh)\
  $(_demo_pdf_diffusion)\

.PHONY: demo_pdf demo_pdf_clean demo_pdf_distclean

demo_pdf: $(_demo_pdf)

demo_pdf_clean:
	-$(RM) $(_demo_pdf)

demo_pdf_distclean:
	-$(RM) -r build/$(MODE)/demo/pdf
