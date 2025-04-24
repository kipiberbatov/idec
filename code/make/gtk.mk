.PHONY: gtk gtk_clean gtk_distclean

build/$(MODE)/gtk: | build/$(MODE)
	mkdir -p $@

TIMELAPSE = 100
CLOSE_AUTOMATICALLY = 0

include code/make/gtk/filled_window.mk
include code/make/gtk/diffusion.mk

_gtk :=\
  $(_gtk_filled_window)\
  $(_gtk_diffusion_transient)\

gtk: $(_gtk)

gtk_clean:
	-$(RM) $(_gtk)

gtk_distclean:
	-$(RM) -r build/$(MODE)/gtk
