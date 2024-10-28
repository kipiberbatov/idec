build/$(MODE)/demo/pdf: | build/$(MODE)/demo
	mkdir -p $@

build/$(MODE)/demo/pdf/fill.pdf:\
  build/$(MODE)/bin/pdf_fill | build/$(MODE)/demo/pdf
	$< 100 $@

include code/make/demo/pdf_mesh.mk
include code/make/demo/pdf_diffusion.mk

_demo_pdf :=\
  build/$(MODE)/demo/pdf/fill.pdf $(_demo_pdf_mesh) $(_demo_pdf_diffusion)\

.PHONY: demo_pdf demo_pdf_clean demo_pdf_distclean

demo_pdf: $(_demo_pdf)

demo_pdf_clean:
	-$(RM) $(_demo_pdf)

demo_pdf_distclean:
	-$(RM) -r build/$(MODE)/demo/pdf
