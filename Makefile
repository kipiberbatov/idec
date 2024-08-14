################################################################################
################################# main makefile ################################
################################################################################

#################################### paths #####################################
BUILD_MODE := release

################################### commands ###################################
# AR := ar
# CC := cc
# RM := rm -f
MKDIR := mkdir

############################### file extensions ################################
.DEP := .d
.INCLUDE := .h
.SRC := .c
ifeq ($(OS), Windows_NT)
  .EXE := .exe
  .DLL := .dll
  .LIB := .lib
  .OBJ := .obj
else
  .EXE :=
  .LIB := .a
  .OBJ := .o
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S), Linux)
    .DLL := .so
  endif
  ifeq ($(UNAME_S), Darwin)
    .DLL := .dylib
  endif
endif

########################### high-level dependencies ############################
# array:
# algebra: array
# region: array
# mesh: region algebra
# graphics: mesh

################################# $(CC) flags ##################################
MODULES := array algebra region mesh graphics shared

CPPFLAGS := -MMD -MP
CFLAGS := -O2 -Wall -Wfatal-errors
CFLAGS_DEBUG := -g -O0 -Wall -Wfatal-errors
LDFLAGS := -lm

ARRAY_INC_EXE := -iquote code/c/include/array
ARRAY_INC := $(ARRAY_INC_EXE) -iquote code/c/src/array

ALGEBRA_INC_EXE := $(ARRAY_INC_EXE) -iquote code/c/include/algebra
ALGEBRA_INC := $(ALGEBRA_INC_EXE) -iquote code/c/src/algebra

REGION_INC_EXE := $(ARRAY_INC_EXE) -iquote code/c/include/region
REGION_INC := $(REGION_INC_EXE) -iquote code/c/src/region

MESH_INC_EXE := $(ALGEBRA_INC_EXE) -iquote code/c/include/region\
                                   -iquote code/c/include/mesh
MESH_INC := $(MESH_INC_EXE) -iquote code/c/src/mesh

# GRAPHICS_INC_EXE := $(MESH_INC_EXE) -iquote code/c/include/graphics\
#    $(shell pkg-config --cflags gtk+-3.0)
# GRAPHICS_INC := $(GRAPHICS_INC_EXE) -iquote code/c/src/graphics

GRAPHICS_INC_EXE := $(MESH_INC_EXE) -iquote code/c/include/graphics
GRAPHICS_INC := $(GRAPHICS_INC_EXE) -iquote code/c/src/graphics

SHARED_INC_EXE := $(MESH_INC_EXE) -iquote code/c/include/shared
SHARED_INC := $(SHARED_INC_EXE) -iquote code/c/src/shared

ARRAY_LDLIBS := build/$(BUILD_MODE)/lib/libarray$(.LIB)
ALGEBRA_LDLIBS := build/$(BUILD_MODE)/lib/libalgebra$(.LIB) $(ARRAY_LDLIBS)
REGION_LDLIBS := build/$(BUILD_MODE)/lib/libregion$(.LIB) $(ARRAY_LDLIBS)
MESH_LDLIBS := build/$(BUILD_MODE)/lib/libmesh$(.LIB)\
  build/$(BUILD_MODE)/lib/libregion$(.LIB) $(ALGEBRA_LDLIBS)
GRAPHICS_LDLIBS := build/$(BUILD_MODE)/lib/libgraphics$(.LIB) $(MESH_LDLIBS)
SHARED_LDLIBS := build/$(BUILD_MODE)/lib/libshared$(.DLL) $(MESH_LDLIBS)

############################### all-type targets ###############################
.PHONY: all
all: obj lib bin demo

# array
.PHONY: array
array: obj_array lib_array bin_array demo_array

# algebra
.PHONY: algebra
algebra: obj_algebra lib_algebra bin_algebra demo_algebra

# region
.PHONY: region
region: obj_region lib_region bin_region demo_region

# mesh
.PHONY: mesh
mesh: obj_mesh lib_mesh bin_mesh demo_mesh

# graphics
.PHONY: graphics
graphics: obj_graphics lib_graphics bin_graphics demo_graphics

# shared
.PHONY: shared
shared: obj_shared lib_shared

########################## preparing build directory ###########################
build:
	$(MKDIR) -p $@

build/$(BUILD_MODE): | build
	$(MKDIR) -p $@

######################### preprocessing and compiling ##########################
build/$(BUILD_MODE)/obj: | build/$(BUILD_MODE)
	$(MKDIR) -p $@

# array
ARRAY_OBJ_NAMES := $(wildcard code/c/src/array/*$(.SRC))
ARRAY_OBJ := $(patsubst code/c/src/array/%$(.SRC),\
  build/$(BUILD_MODE)/obj/%$(.OBJ), $(ARRAY_OBJ_NAMES))

.PHONY: obj_array
obj_array: $(ARRAY_OBJ)

$(ARRAY_OBJ): build/$(BUILD_MODE)/obj/%$(.OBJ): code/c/src/array/%$(.SRC)\
  | build/$(BUILD_MODE)/obj
	$(CC) $(CPPFLAGS) $(CFLAGS) $(ARRAY_INC) -c $< -o $@

# algebra
ALGEBRA_OBJ_NAMES := $(wildcard code/c/src/algebra/*$(.SRC))
ALGEBRA_OBJ := $(patsubst code/c/src/algebra/%$(.SRC),\
  build/$(BUILD_MODE)/obj/%$(.OBJ), $(ALGEBRA_OBJ_NAMES))

.PHONY: obj_algebra
obj_algebra: $(ALGEBRA_OBJ)

$(ALGEBRA_OBJ): build/$(BUILD_MODE)/obj/%$(.OBJ): code/c/src/algebra/%$(.SRC)\
    | build/$(BUILD_MODE)/obj
	$(CC) $(CPPFLAGS) $(CFLAGS) $(ALGEBRA_INC) -c $< -o $@

# region
REGION_OBJ_NAMES := $(wildcard code/c/src/region/*$(.SRC))
REGION_OBJ := $(patsubst code/c/src/region/%$(.SRC),\
  build/$(BUILD_MODE)/obj/%$(.OBJ), $(REGION_OBJ_NAMES))

.PHONY: obj_region
obj_region: $(REGION_OBJ)

$(REGION_OBJ): build/$(BUILD_MODE)/obj/%$(.OBJ): code/c/src/region/%$(.SRC)\
    | build/$(BUILD_MODE)/obj
	$(CC) $(CPPFLAGS) $(CFLAGS) $(REGION_INC) -c $< -o $@

# mesh
MESH_OBJ_NAMES := $(wildcard code/c/src/mesh/*$(.SRC))
MESH_OBJ := $(patsubst code/c/src/mesh/%$(.SRC),\
  build/$(BUILD_MODE)/obj/%$(.OBJ), $(MESH_OBJ_NAMES))

.PHONY: obj_mesh
obj_mesh: $(MESH_OBJ)

$(MESH_OBJ): build/$(BUILD_MODE)/obj/%$(.OBJ): code/c/src/mesh/%$(.SRC)\
    | build/$(BUILD_MODE)/obj
	$(CC) $(CPPFLAGS) $(CFLAGS) $(MESH_INC) -c $< -o $@

# graphics
GRAPHICS_OBJ_NAMES := $(wildcard code/c/src/graphics/*$(.SRC))
GRAPHICS_OBJ := $(patsubst code/c/src/graphics/%$(.SRC),\
  build/$(BUILD_MODE)/obj/%$(.OBJ), $(GRAPHICS_OBJ_NAMES))

.PHONY: obj_graphics
obj_graphics: $(GRAPHICS_OBJ)

$(GRAPHICS_OBJ): build/$(BUILD_MODE)/obj/%$(.OBJ): code/c/src/graphics/%$(.SRC)\
    | build/$(BUILD_MODE)/obj
	$(CC) $(CPPFLAGS) $(CFLAGS) $(GRAPHICS_INC)\
	  $(shell pkg-config --cflags gtk+-3.0) -c $< -o $@

# shared
SHARED_OBJ_NAMES := $(wildcard code/c/src/shared/*$(.SRC))
SHARED_OBJ := $(patsubst code/c/src/shared/%$(.SRC),\
  build/$(BUILD_MODE)/obj/%$(.OBJ), $(SHARED_OBJ_NAMES))

.PHONY: obj_shared
obj_shared: $(SHARED_OBJ)

$(SHARED_OBJ): build/$(BUILD_MODE)/obj/%$(.OBJ): code/c/src/shared/%$(.SRC)\
    | build/$(BUILD_MODE)/obj
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SHARED_INC) -c $< -o $@

# all
.PHONY: obj
obj: $(patsubst %, obj_%, $(MODULES))

############################# header dependencies ##############################
-include build/$(BUILD_MODE)/obj/*$(.DEP)

# array
ARRAY_HEADER_DEP := $(patsubst code/c/src/array/%$(.SRC),\
  build/$(BUILD_MODE)/obj/%$(.DEP), $(ARRAY_OBJ_NAMES))

# algebra
ALGEBRA_HEADER_DEP := $(patsubst code/c/src/algebra/%$(.SRC),\
  build/$(BUILD_MODE)/obj/%$(.DEP), $(ALGEBRA_OBJ_NAMES))

# region
REGION_HEADER_DEP :=\
  $(patsubst code/c/src/region/%$(.SRC), build/$(BUILD_MODE)/obj/%$(.DEP),\
    $(REGION_OBJ_NAMES))

# mesh
MESH_HEADER_DEP := $(patsubst code/c/src/mesh/%$(.SRC),\
  build/$(BUILD_MODE)/obj/%$(.DEP), $(MESH_OBJ_NAMES))

# graphics
GRAPHICS_HEADER_DEP := $(patsubst code/c/src/graphics/%$(.SRC),\
  build/$(BUILD_MODE)/obj/%$(.DEP), $(GRAPHICS_OBJ_NAMES))

# shared
SHARED_HEADER_DEP := $(patsubst code/c/src/shared/%$(.SRC),\
  build/$(BUILD_MODE)/obj/%$(.DEP), $(SHARED_OBJ_NAMES))

################################## archiving ###################################
build/$(BUILD_MODE)/lib: | build/$(BUILD_MODE)
	$(MKDIR) -p $@

# array
.PHONY: lib_array
lib_array: build/$(BUILD_MODE)/lib/libarray$(.LIB)

build/$(BUILD_MODE)/lib/libarray$(.LIB): $(ARRAY_OBJ)\
  | build/$(BUILD_MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

# algebra
.PHONY: lib_algebra
lib_algebra: build/$(BUILD_MODE)/lib/libalgebra$(.LIB)

build/$(BUILD_MODE)/lib/libalgebra$(.LIB): $(ALGEBRA_OBJ)\
  | build/$(BUILD_MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

# region
.PHONY: lib_region
lib_region: build/$(BUILD_MODE)/lib/libregion$(.LIB)

build/$(BUILD_MODE)/lib/libregion$(.LIB):\
 $(REGION_OBJ) | build/$(BUILD_MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

# mesh
.PHONY: lib_mesh
lib_mesh: build/$(BUILD_MODE)/lib/libmesh$(.LIB)

build/$(BUILD_MODE)/lib/libmesh$(.LIB): $(MESH_OBJ) | build/$(BUILD_MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

# graphics
.PHONY: lib_graphics
lib_graphics: build/$(BUILD_MODE)/lib/libgraphics$(.LIB)\
  | build/$(BUILD_MODE)/lib

build/$(BUILD_MODE)/lib/libgraphics$(.LIB): $(GRAPHICS_OBJ)\
  | build/$(BUILD_MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

#shared
.PHONY: lib_shared
lib_shared: build/$(BUILD_MODE)/lib/libshared$(.DLL)

build/$(BUILD_MODE)/lib/libshared$(.DLL):\
  $(SHARED_OBJ) $(ALGEBRA_OBJ) $(ARRAY_OBJ) | build/$(BUILD_MODE)/lib
	$(CC) -o $@ -fPIC -shared $^

# all
.PHONY: lib
lib: $(patsubst %, lib_%, $(MODULES))

################################### bining ####################################
build/$(BUILD_MODE)/bin: | build/$(BUILD_MODE)
	-$(MKDIR) -p $@

# array
ARRAY_EXE_NAMES := $(wildcard code/c/main/array/*$(.SRC))
ARRAY_EXE := $(patsubst code/c/main/array/main_%$(.SRC),\
  build/$(BUILD_MODE)/bin/%$(.EXE), $(ARRAY_EXE_NAMES))

.PHONY: bin_array
bin_array: $(ARRAY_EXE)

$(ARRAY_EXE): build/$(BUILD_MODE)/bin/%$(.EXE):\
 code/c/main/array/main_%$(.SRC) $(ARRAY_LDLIBS) | build/$(BUILD_MODE)/bin
	$(CC) -o $@ $(CFLAGS) $(ARRAY_INC_EXE) $(CCFLAGS) $< $(ARRAY_LDLIBS)\
	  $(LDFLAGS)

# algebra
ALGEBRA_EXE_NAMES := $(wildcard code/c/main/algebra/*$(.SRC))
ALGEBRA_EXE := $(patsubst code/c/main/algebra/main_%$(.SRC),\
  build/$(BUILD_MODE)/bin/%$(.EXE), $(ALGEBRA_EXE_NAMES))

.PHONY: bin_algebra
bin_algebra: $(ALGEBRA_EXE)

$(ALGEBRA_EXE): build/$(BUILD_MODE)/bin/%$(.EXE):\
  code/c/main/algebra/main_%$(.SRC) $(ALGEBRA_LDLIBS) | build/$(BUILD_MODE)/bin
	$(CC) -o $@ $(CFLAGS) $(ALGEBRA_INC_EXE) $(CCFLAGS) $<\
	  $(ALGEBRA_LDLIBS) $(LDFLAGS)

# region
REGION_EXE_NAMES := $(wildcard code/c/main/region/*$(.SRC))
REGION_EXE := $(patsubst code/c/main/region/main_%$(.SRC),\
  build/$(BUILD_MODE)/bin/%$(.EXE), $(REGION_EXE_NAMES))

.PHONY: bin_region
bin_region: $(REGION_EXE)

$(REGION_EXE): build/$(BUILD_MODE)/bin/%$(.EXE):\
  code/c/main/region/main_%$(.SRC) $(REGION_LDLIBS) | build/$(BUILD_MODE)/bin
	$(CC) -o $@ $(CFLAGS) $(REGION_INC_EXE) $(CCFLAGS) $< $(REGION_LDLIBS)\
	  $(LDFLAGS)

# mesh
MESH_EXE_NAMES := $(wildcard code/c/main/mesh/*$(.SRC))
MESH_EXE := $(patsubst code/c/main/mesh/main_%$(.SRC),\
  build/$(BUILD_MODE)/bin/%$(.EXE), $(MESH_EXE_NAMES))

.PHONY: bin_mesh
bin_mesh: $(MESH_EXE)

$(MESH_EXE): build/$(BUILD_MODE)/bin/%$(.EXE):\
  code/c/main/mesh/main_%$(.SRC) $(MESH_LDLIBS) | build/$(BUILD_MODE)/bin
	$(CC) -o $@ $(CFLAGS) $(MESH_INC_EXE) $(CCFLAGS) $< $(MESH_LDLIBS)\
	  $(LDFLAGS)

# graphics
GRAPHICS_EXE_NAMES := $(wildcard code/c/main/graphics/*$(.SRC))
GRAPHICS_EXE := $(patsubst code/c/main/graphics/main_%$(.SRC),\
  build/$(BUILD_MODE)/bin/%$(.EXE), $(GRAPHICS_EXE_NAMES))

.PHONY: bin_graphics
bin_graphics: $(GRAPHICS_EXE)

$(GRAPHICS_EXE): build/$(BUILD_MODE)/bin/%$(.EXE):\
  code/c/main/graphics/main_%$(.SRC) $(GRAPHICS_LDLIBS)\
  | build/$(BUILD_MODE)/bin
	$(CC) -o $@ $(CFLAGS) $(GRAPHICS_INC_EXE)\
	  $(shell pkg-config --cflags gtk+-3.0) $(CCFLAGS) $<\
	  $(shell pkg-config --libs gtk+-3.0) $(GRAPHICS_LDLIBS) $(LDFLAGS)

# all
.PHONY: bin
bin: $(patsubst %, bin_%, array algebra region mesh graphics)
# bin: $(patsubst %, bin_%, $(MODULES))

############################## object dependencies #############################
# at the moment executables depend on libraries and a change in one object file
# could lead to a massive rebining of executables and redemoing of demos

# at the moment this list is empty
-include build/$(BUILD_MODE)/bin/*$(.DEP)

# array
ARRAY_OBJ_DEP := $(patsubst build/$(BUILD_MODE)/bin/%$(.EXE),\
  build/$(BUILD_MODE)/bin/%$(.DEP), $(ARRAY_EXE_NAMES))

# algebra
ALGEBRA_OBJ_DEP := $(patsubst build/$(BUILD_MODE)/bin/%$(.EXE),\
  build/$(BUILD_MODE)/bin/%$(.DEP), $(ALGEBRA_EXE_NAMES))

# region
REGION_OBJ_DEP := $(patsubst build/$(BUILD_MODE)/bin/%$(.EXE),\
  build/$(BUILD_MODE)/bin/%$(.DEP), $(REGION_EXE_NAMES))

# mesh
MESH_OBJ_DEP := $(patsubst build/$(BUILD_MODE)/bin/%$(.EXE),\
  build/$(BUILD_MODE)/bin/%$(.DEP), $(MESH_EXE_NAMES))

# graphics
GRAPHICS_OBJ_DEP := $(patsubst build/$(BUILD_MODE)/bin/%$(.EXE),\
  build/$(BUILD_MODE)/bin/%$(.DEP), $(GRAPHICS_EXE_NAMES))

# graphics
SHARED_OBJ_DEP := $(patsubst build/$(BUILD_MODE)/bin/%$(.EXE),\
  build/$(BUILD_MODE)/bin/%$(.DEP), $(SHARED_EXE_NAMES))

################################ running demos #################################
build/$(BUILD_MODE)/demo: | build/$(BUILD_MODE)
	mkdir -p $@

-include code/make/demo/array.mk
-include code/make/demo/algebra.mk
-include code/make/demo/region.mk
-include code/make/demo/mesh.mk
-include code/make/demo/graphics.mk

.PHONY: demo
demo: $(patsubst %, demo_%, array algebra mesh region)

############### create documentation and publish it as a website ###############
-include code/make/docs/latex.mk
-include code/make/website.mk

################################### cleaning ###################################
# array
.PHONY: obj_array_clean
obj_array_clean:
	-$(RM) $(ARRAY_OBJ) $(ARRAY_HEADER_DEP)

.PHONY: lib_array_clean
lib_array_clean:
	-$(RM) build/$(BUILD_MODE)/lib/libarray$(.LIB)

.PHONY: bin_array_clean
bin_array_clean:
	-$(RM) $(ARRAY_EXE) $(ARRAY_OBJ_DEP)

.PHONY: array_clean
array_clean: obj_array_clean

.PHONY: array_distclean
array_distclean: lib_array_clean bin_array_clean demo_array_clean

# algebra
.PHONY: obj_algebra_clean
obj_algebra_clean:
	-$(RM) $(ALGEBRA_OBJ) $(ALGEBRA_HEADER_DEP)

.PHONY: lib_algebra_clean
lib_algebra_clean:
	-$(RM) build/$(BUILD_MODE)/lib/libalgebra$(.LIB)

.PHONY: bin_algebra_clean
bin_algebra_clean:
	-$(RM) $(ALGEBRA_EXE) $(ALGEBRA_OBJ_DEP)

.PHONY: algebra_clean
algebra_clean: obj_algebra_clean

.PHONY: algebra_distclean
algebra_distclean: lib_algebra_clean bin_algebra_clean demo_algebra_clean

# region
.PHONY: obj_region_clean
obj_region_clean:
	-$(RM) $(REGION_OBJ) $(REGION_HEADER_DEP)

.PHONY: lib_region_clean
lib_region_clean:
	-$(RM) build/$(BUILD_MODE)/lib/libregion$(.LIB)

.PHONY: bin_region_clean
bin_region_clean:
	-$(RM) $(REGION_EXE) $(REGION_OBJ_DEP)

.PHONY: region_clean
region_clean: obj_region_clean

.PHONY: region_distclean
region_distclean: lib_region_clean bin_region_clean demo_region_clean

# mesh
.PHONY: obj_mesh_clean
obj_mesh_clean:
	-$(RM) $(MESH_OBJ) $(MESH_HEADER_DEP)

.PHONY: lib_mesh_clean
lib_mesh_clean:
	-$(RM) build/$(BUILD_MODE)/lib/libmesh$(.LIB)

.PHONY: bin_mesh_clean
bin_mesh_clean:
	-$(RM) $(MESH_EXE) $(MESH_OBJ_DEP)

.PHONY: mesh_clean
mesh_clean: obj_mesh_clean

.PHONY: mesh_distclean
mesh_distclean: lib_mesh_clean bin_mesh_clean demo_mesh_clean

# graphics
.PHONY: obj_graphics_clean
obj_graphics_clean:
	-$(RM) $(GRAPHICS_OBJ) $(GRAPHICS_HEADER_DEP)

.PHONY: lib_graphics_clean
lib_graphics_clean:
	-$(RM) build/$(BUILD_MODE)/lib/libgraphics$(.LIB)

.PHONY: bin_graphics_clean
bin_graphics_clean:
	-$(RM) $(GRAPHICS_EXE) $(GRAPHICS_OBJ_DEP)

.PHONY: graphics_clean
graphics_clean: obj_graphics_clean

.PHONY: graphics_distclean
graphics_distclean: lib_graphics_clean bin_graphics_clean demo_graphics_clean

# shared
.PHONY: obj_shared_clean
obj_shared_clean:
	-$(RM) $(SHARED_OBJ) $(SHARED_HEADER_DEP)

.PHONY: lib_shared_clean
lib_shared_clean:
	-$(RM) build/$(BUILD_MODE)/lib/libshared$(.LIB)

# .PHONY: bin_shared_clean
# bin_shared_clean:
# 	-$(RM) $(SHARED_EXE) $(SHARED_OBJ_DEP)

.PHONY: shared_clean
shared_clean: obj_shared_clean

.PHONY: shared_distclean
shared_distclean: lib_shared_clean #bin_shared_clean demo_shared_clean

# all
.PHONY: obj_clean
obj_clean:
	-$(RM) -r build/$(BUILD_MODE)/obj

.PHONY: lib_clean
lib_clean:
	-$(RM) -r build/$(BUILD_MODE)/lib

.PHONY: bin_clean
bin_clean:
	-$(RM) -r build/$(BUILD_MODE)/bin

# demo_<module>_clean is found in -include demo/<module>/demo_<module>.mk
.PHONY: demo_clean
demo_clean: $(patsubst %, demo_%_clean, array algebra region mesh graphics)
	-$(RM) -r demo
# demo_clean: $(patsubst %, demo_%_clean, $(MODULES))

.PHONY: clean
clean: obj_clean

.PHONY: distclean
distclean: # clean lib_clean bin_clean demo_clean
	-$(RM) -r build
