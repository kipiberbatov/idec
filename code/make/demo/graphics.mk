include code/make/demo/graphics_gtk.mk
include code/make/demo/graphics_pdf.mk

build/$(BUILD_TYPE)/demo/graphics/frame.txt: build/$(BUILD_TYPE)/bin/frame
	$< > $@

_demo_graphics := $(_demo_graphics_gtk) $(_demo_graphics_pdf)\
  build/$(BUILD_TYPE)/demo/graphics/frame.txt

.PHONY: demo_graphics
demo_graphics: bin_graphics $(_demo_graphics)\
  | build/$(BUILD_TYPE)/demo/graphics

build/$(BUILD_TYPE)/demo/graphics: | build/$(BUILD_TYPE)/demo
	mkdir -p $@

.PHONY: demo_graphics_clean
demo_graphics_clean: demo_graphics_gtk_clean demo_graphics_pdf_clean
	-$(RM) build/$(BUILD_TYPE)/demo/graphics/frame.txt
	-$(RM) -r build/$(BUILD_TYPE)/demo/graphics
