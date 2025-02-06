build/$(MODE)/pdf/diffusion: | build/$(MODE)/pdf
	mkdir -p $@

include code/make/pdf/diffusion/steady_state.mk
include code/make/pdf/diffusion/transient.mk

.PHONY: pdf_diffusion pdf_diffusion_clean pdf_diffusion_distclean

_pdf_diffusion := $(_pdf_diffusion_steady_state) $(_pdf_diffusion_transient)

pdf_diffusion: $(_pdf_diffusion)

pdf_diffusion_clean:
	-$(RM) $(_pdf_diffusion)

pdf_diffusion_distclean:
	-$(RM) -r build/$(MODE)/pdf/diffusion
