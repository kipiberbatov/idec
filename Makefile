################################ default target ################################
.PHONY: all
all: obj lib bin demo

##################################### mode #####################################
MODE := release

########################## preparing build directory ###########################
build:
	mkdir -p $@

build/$(MODE): | build
	mkdir -p $@

############### generating object files, libraries and binaries ################
-include code/make/c_compile.mk

################################ running demos #################################
build/$(MODE)/demo: | build/$(MODE)
	mkdir -p $@

-include code/make/demo/array.mk
-include code/make/demo/algebra.mk
-include code/make/demo/region.mk
-include code/make/demo/mesh.mk
-include code/make/demo/diffusion.mk
-include code/make/demo/graphics.mk

.PHONY: demo
demo: $(patsubst %, demo_%, array algebra region mesh diffusion)

########### creating a documentation and publishing it as a website ############
-include code/make/docs/latex.mk
-include code/make/website.mk

################################### cleaning ###################################
-include code/make/clean.mk

########################## removing built artifacts ############################
.PHONY: distclean
distclean:
	-$(RM) -r build
