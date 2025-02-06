build/$(MODE)/gtk/diffusion: | build/$(MODE)/gtk
	mkdir -p $@

include code/make/gtk/diffusion_transient_continuous_2d_d00_p00.mk
include code/make/gtk/diffusion_transient_continuous_2d_d00_p01.mk
include code/make/gtk/diffusion_transient_continuous_2d_d00_p04.mk

_gtk_diffusion_transient :=\
  $(_gtk_diffusion_transient_continuous_2d_d00_p00)\
  $(_gtk_diffusion_transient_continuous_2d_d00_p01)\
  $(_gtk_diffusion_transient_continuous_2d_d00_p04)\

.PHONY: gtk_diffusion_transient gtk_diffusion_transient_clean

gtk_diffusion_transient: $(_gtk_diffusion_transient)

gtk_diffusion_transient_clean:
	-$(RM) $(_gtk_diffusion_transient)
