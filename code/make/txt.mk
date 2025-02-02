build/$(MODE)/txt: | build/$(MODE)
	mkdir -p $@

-include code/make/txt/array.mk
-include code/make/txt/algebra.mk
-include code/make/txt/region.mk
-include code/make/txt/mesh.mk
-include code/make/txt/diffusion.mk
-include code/make/txt/graphics.mk

.PHONY: txt
txt: $(patsubst %, txt_%, array algebra region mesh diffusion graphics)
