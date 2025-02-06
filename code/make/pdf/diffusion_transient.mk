include code/make/pdf/diffusion_transient_continuous_2d_d00_p00.mk
include code/make/pdf/diffusion_transient_continuous_2d_d00_p01.mk
include code/make/pdf/diffusion_transient_continuous_2d_d00_p04.mk

_pdf_diffusion_transient :=\
  $(_pdf_diffusion_transient_continuous_2d_d00_p00)\
  $(_pdf_diffusion_transient_continuous_2d_d00_p01)\
  $(_pdf_diffusion_transient_continuous_2d_d00_p04)\

.PHONY: pdf_diffusion_transient pdf_diffusion_transient_clean

pdf_diffusion_transient: $(_pdf_diffusion_transient)

pdf_diffusion_transient_clean:
	-$(RM) $(_pdf_diffusion_transient)
