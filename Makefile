################################ default target ################################
.PHONY: all
all: obj lib bin txt

##################################### mode #####################################
MODE := release

########################## preparing build directory ###########################
build:
	mkdir -p $@

build/$(MODE): | build
	mkdir -p $@

############### generating object files, libraries and binaries ################
-include code/make/c_compile.mk

######################## running text-outputting demos #########################
-include code/make/txt.mk

######################### running PDF-outputting demos #########################
-include code/make/pdf.mk

############################ running GTK animations ############################
-include code/make/gtk.mk

################### creating a PDF documentation using LaTeX ###################
-include code/make/docs.mk

############### creating a website linking to PDF documentation ################
-include code/make/website.mk

################################### cleaning ###################################
-include code/make/clean.mk

########################## removing built artifacts ############################
.PHONY: distclean
distclean:
	-$(RM) -r build
