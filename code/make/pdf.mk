.PHONY: pdf pdf_clean pdf_distclean

build/$(MODE)/pdf: | build/$(MODE)
	mkdir -p $@

include code/make/pdf/filled_window.mk
include code/make/pdf/colorbar.mk
include code/make/pdf/mesh.mk
include code/make/pdf/diffusion.mk

_pdf :=\
  $(_pdf_filled_window)\
  $(_pdf_colorbar)\
  $(_pdf_mesh)\
  $(_pdf_diffusion)\

pdf: $(_pdf)

pdf_clean:
	-$(RM) $(_pdf)

pdf_distclean:
	-$(RM) -r build/$(MODE)/pdf
