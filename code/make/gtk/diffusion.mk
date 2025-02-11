.PHONY: gtk_diffusion gtk_diffusion_clean gtk_diffusion_distclean

build/$(MODE)/gtk/diffusion: | build/$(MODE)/gtk
	mkdir -p $@

include code/make/gtk/diffusion/transient.mk

_gtk_diffusion := $(_gtk_diffusion_transient)

gtk_diffusion: $(_gtk_diffusion)

gtk_diffusion_clean:
	-$(RM) $(_gtk_diffusion)

gtk_diffusion_distclean:
	-$(RM) -r build/$(MODE)/gtk/diffusion
