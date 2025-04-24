.PHONY: svg svg_clean svg_distclean

build/$(MODE)/svg: | build/$(MODE)
	mkdir -p $@

include code/make/svg/filled_window.mk
include code/make/svg/mesh.mk

_svg :=\
  $(_svg_filled_window)\
  $(_svg_mesh)\

svg: $(_svg)

svg_clean:
	-$(RM) $(_svg)

svg_distclean:
	-$(RM) -r build/$(MODE)/svg
