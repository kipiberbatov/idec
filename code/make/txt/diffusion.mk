.PHONY: txt_diffusion txt_diffusion_clean txt_diffusion_distclean

build/$(MODE)/txt/diffusion: | build/$(MODE)/txt
	mkdir -p $@

include code/make/txt/diffusion/steady_state.mk
include code/make/txt/diffusion/transient.mk

_txt_diffusion := $(_txt_diffusion_steady_state) $(_txt_diffusion_transient)

txt_diffusion: $(_txt_diffusion)

txt_diffusion_clean:
	-$(RM) $(_txt_diffusion)

txt_diffusion_distclean:
	-$(RM) -r build/$(MODE)/txt/diffusion
