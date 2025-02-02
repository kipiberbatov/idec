_txt_graphics := build/$(MODE)/txt/graphics/frame.txt

.PHONY: txt_graphics
txt_graphics: bin_graphics $(_txt_graphics)\
  | build/$(MODE)/txt/graphics

build/$(MODE)/txt/graphics: | build/$(MODE)/txt
	mkdir -p $@

build/$(MODE)/txt/graphics/frame.txt: build/$(MODE)/bin/frame\
  | build/$(MODE)/txt/graphics
	$< > $@

.PHONY: txt_graphics_clean
txt_graphics_clean:
	-$(RM) $(_txt_graphics)
	-$(RM) -r build/$(MODE)/txt/graphics
