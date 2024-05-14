include make/demo/graphics_gtk.mk
include make/demo/graphics_pdf.mk

demo/graphics/frame.txt: bin/frame
	$< > $@

_demo_graphics := $(_demo_graphics_gtk) $(_demo_graphics_pdf) demo/graphics/frame.txt

.PHONY: demo_graphics
demo_graphics: bin_graphics $(_demo_graphics) | demo/graphics

demo/graphics: | demo
	mkdir -p $@

.PHONY: demo_graphics_clean
demo_graphics_clean: demo_graphics_gtk_clean demo_graphics_pdf_clean
	-$(RM) demo/graphics/frame.txt
	-$(RM) -r demo/graphics
