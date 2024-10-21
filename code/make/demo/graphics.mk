include code/make/demo/graphics_gtk.mk
include code/make/demo/graphics_pdf.mk

build/$(MODE)/demo/graphics/frame.txt: build/$(MODE)/bin/frame\
  | build/$(MODE)/demo/graphics
	$< > $@

_demo_graphics := $(_demo_gtk) $(_demo_pdf)\
  build/$(MODE)/demo/graphics/frame.txt

.PHONY: demo_graphics
demo_graphics: bin_graphics $(_demo_graphics)\
  | build/$(MODE)/demo/graphics

build/$(MODE)/demo/graphics: | build/$(MODE)/demo
	mkdir -p $@

.PHONY: demo_graphics_clean
demo_graphics_clean: demo_gtk_clean demo_pdf_clean
	-$(RM) build/$(MODE)/demo/graphics/frame.txt
	-$(RM) -r build/$(MODE)/demo/graphics
