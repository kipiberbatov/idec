##################################### mode #####################################
MODE := release

############### general preprocessor, compiler and linker flags ################
CPPFLAGS := -MMD -MP
CFLAGS := -O2 -Wall -Wfatal-errors -Werror
LDLIBS := -lm

######################### OS-dependent file extensions #########################
# Windows extensions are fine but the project cannot be built on Windows
ifeq ($(OS), Windows_NT)
  .EXE := .exe
  .DLL := .dll
  .LIB := .lib
  .OBJ := .obj
else
  .EXE :=
  .LIB := .a
  .OBJ := .o
  .DEP := .d
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S), Linux)
    .DLL := .so
  endif
  ifeq ($(UNAME_S), Darwin)
    .DLL := .dylib
  endif
endif

########################### modules and dependencies ###########################
MODULES := array algebra region mesh diffusion shared graphics
# array:
# algebra: array
# region: array
# mesh: region algebra
# diffusion: mesh
# shared:
# graphics: mesh shared

############################ names of source files #############################
_src_array := $(wildcard code/c/src/array/*.c)
_src_algebra := $(wildcard code/c/src/algebra/*.c)
_src_region := $(wildcard code/c/src/region/*.c)
_src_mesh := $(wildcard code/c/src/mesh/*.c)
_src_diffusion := $(wildcard code/c/src/diffusion/*.c)
_src_shared := $(wildcard code/c/src/shared/*.c)
_src_graphics := $(wildcard code/c/src/graphics/*.c)

############################# names of main files ##############################
_main_array := $(wildcard code/c/main/array/*.c)
_main_algebra := $(wildcard code/c/main/algebra/*.c)
_main_region := $(wildcard code/c/main/region/*.c)
_main_mesh := $(wildcard code/c/main/mesh/*.c)
_main_diffusion := $(wildcard code/c/main/diffusion/*.c)
_main_shared :=
_main_graphics := $(wildcard code/c/main/graphics/*.c)

######################### names of source object files #########################
_obj_src_array := $(patsubst code/c/src/array/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_array))

_obj_src_algebra := $(patsubst code/c/src/algebra/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_algebra))

_obj_src_region := $(patsubst code/c/src/region/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_region))

_obj_src_mesh := $(patsubst code/c/src/mesh/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_mesh))

_obj_src_diffusion := $(patsubst code/c/src/diffusion/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_diffusion))

_obj_src_shared := $(patsubst code/c/src/shared/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_shared))

_obj_src_graphics := $(patsubst code/c/src/graphics/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_graphics))

########################## names of main object files ##########################
_obj_main_array := $(patsubst code/c/main/array/%.c,\
  build/$(MODE)/obj/main/%$(.OBJ), $(_main_array))

_obj_main_algebra := $(patsubst code/c/main/algebra/%.c,\
  build/$(MODE)/obj/main/%$(.OBJ), $(_main_algebra))

_obj_main_region := $(patsubst code/c/main/region/%.c,\
  build/$(MODE)/obj/main/%$(.OBJ), $(_main_region))

_obj_main_mesh := $(patsubst code/c/main/mesh/%.c,\
  build/$(MODE)/obj/main/%$(.OBJ), $(_main_mesh))

_obj_main_diffusion := $(patsubst code/c/main/diffusion/%.c,\
  build/$(MODE)/obj/main/%$(.OBJ), $(_main_diffusion))

_obj_main_shared :=

_obj_main_graphics := $(patsubst code/c/main/graphics/%.c,\
  build/$(MODE)/obj/main/%$(.OBJ), $(_main_graphics))

################### names of source header dependency files ####################
_dep_src_array := $(patsubst code/c/src/array/%.c,\
  build/$(MODE)/dep/src/%$(.DEP), $(_src_array))

_dep_src_algebra := $(patsubst code/c/src/algebra/%.c,\
  build/$(MODE)/dep/src/%$(.DEP), $(_src_algebra))

_dep_src_region := $(patsubst code/c/src/region/%.c,\
  build/$(MODE)/dep/src/%$(.DEP), $(_src_region))

_dep_src_mesh := $(patsubst code/c/src/mesh/%.c,\
  build/$(MODE)/dep/src/%$(.DEP), $(_src_mesh))

_dep_src_diffusion := $(patsubst code/c/src/diffusion/%.c,\
  build/$(MODE)/dep/src/%$(.DEP), $(_src_diffusion))

_dep_src_shared := $(patsubst code/c/src/shared/%.c,\
  build/$(MODE)/dep/src/%$(.DEP), $(_src_shared))

_dep_src_graphics := $(patsubst code/c/src/graphics/%.c,\
  build/$(MODE)/dep/src/%$(.DEP), $(_src_graphics))

#################### names of main header dependency files #####################
_dep_main_array := $(patsubst code/c/main/array/%.c,\
  build/$(MODE)/dep/main/%$(.DEP), $(_main_array))

_dep_main_algebra := $(patsubst code/c/main/algebra/%.c,\
  build/$(MODE)/dep/main/%$(.DEP), $(_main_algebra))

_dep_main_region := $(patsubst code/c/main/region/%.c,\
  build/$(MODE)/dep/main/%$(.DEP), $(_main_region))

_dep_main_mesh := $(patsubst code/c/main/mesh/%.c,\
  build/$(MODE)/dep/main/%$(.DEP), $(_main_mesh))

_dep_main_diffusion := $(patsubst code/c/main/diffusion/%.c,\
  build/$(MODE)/dep/main/%$(.DEP), $(_main_diffusion))

_dep_main_shared :=

_dep_main_graphics := $(patsubst code/c/main/graphics/%.c,\
  build/$(MODE)/dep/main/%$(.DEP), $(_main_graphics))

########################## names of executable files ###########################
_bin_array := $(patsubst code/c/main/array/%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_array))

_bin_algebra := $(patsubst code/c/main/algebra/%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_algebra))

_bin_region := $(patsubst code/c/main/region/%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_region))

_bin_mesh := $(patsubst code/c/main/mesh/%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_mesh))

_bin_diffusion := $(patsubst code/c/main/diffusion/%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_diffusion))

_bin_shared :=

_bin_graphics := $(patsubst code/c/main/graphics/%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_graphics))

################# include directories for compiling main files #################
_include_main_array := -iquote code/c/include/array
_include_main_algebra := $(_include_main_array) -iquote code/c/include/algebra
_include_main_region := $(_include_main_array) -iquote code/c/include/region
_include_main_mesh := $(_include_main_algebra)\
  -iquote code/c/include/region -iquote code/c/include/mesh
_include_main_diffusion := $(_include_main_mesh)\
  -iquote code/c/include/diffusion
_include_main_shared :=
_include_main_graphics := $(_include_main_mesh) -iquote code/c/include/graphics
# $(shell pkg-config --cflags gtk+-3.0) is included when calling the compiler


################ include directories for compiling source files ################
_include_src_array := $(_include_main_array) -iquote code/c/src/array
_include_src_algebra := $(_include_main_algebra) -iquote code/c/src/algebra
_include_src_region := $(_include_main_region) -iquote code/c/src/region
_include_src_mesh := $(_include_main_mesh) -iquote code/c/src/mesh
_include_src_diffusion := $(_include_main_diffusion)\
  -iquote code/c/src/diffusion
_include_src_shared := $(_include_main_diffusion)
_include_src_graphics := $(_include_main_graphics) -iquote code/c/src/graphics

############################# library dependencies #############################
_libs_array := build/$(MODE)/lib/libarray$(.LIB)
_libs_algebra := build/$(MODE)/lib/libalgebra$(.LIB) $(_libs_array)
_libs_region := build/$(MODE)/lib/libregion$(.LIB) $(_libs_array)
_libs_mesh := build/$(MODE)/lib/libmesh$(.LIB)\
  build/$(MODE)/lib/libregion$(.LIB) $(_libs_algebra)
_libs_diffusion := build/$(MODE)/lib/libdiffusion$(.LIB) $(_libs_mesh)
_libs_shared :=
_libs_graphics := build/$(MODE)/lib/libgraphics$(.LIB) $(_libs_mesh)
# $(shell pkg-config --libs gtk+-3.0) is included when calling the linker

############################### all-type targets ###############################
.PHONY: all
all: obj dep lib bin demo

############################# object file targets ##############################
.PHONY: obj obj_src obj_main
obj: obj_src obj_main

# object files from source files
.PHONY: $(patsubst %, obj_src_%, $(MODULES))
obj_src: $(patsubst %, obj_src_%, $(MODULES))
obj_src_array: $(_obj_src_array)
obj_src_algebra: $(_obj_src_algebra)
obj_src_region: $(_obj_src_region)
obj_src_mesh: $(_obj_src_mesh)
obj_src_diffusion: $(_obj_src_diffusion)
obj_src_shared: $(_obj_src_shared)
obj_src_graphics: $(_obj_src_graphics)

# object files from main files
.PHONY: $(patsubst %, obj_%, $(MODULES))
obj_main: $(patsubst %, obj_%, $(MODULES))
obj_main_array: $(_obj_main_array)
obj_main_algebra: $(_obj_main_algebra)
obj_main_region: $(_obj_main_region)
obj_main_mesh: $(_obj_main_mesh)
obj_main_diffusion: $(_obj_main_diffusion)
obj_main_shared:
obj_main_graphics: $(_obj_main_graphics)

########################## header dependency targets ###########################
.PHONY: dep dep_src dep_main
dep: dep_src dep_main

# header dependencies of source files
.PHONY: $(patsubst %, dep_src_%, $(MODULES))
dep_src: $(patsubst %, dep_src_%, $(MODULES))
dep_src_array: $(_dep_src_array)
dep_src_algebra: $(_dep_src_algebra)
dep_src_region: $(_dep_src_region)
dep_src_mesh: $(_dep_src_mesh)
dep_src_diffusion: $(_dep_src_diffusion)
dep_src_shared: $(_dep_src_shared)
dep_src_graphics: $(_dep_src_graphics)

# header dependencies of main files
.PHONY: $(patsubst %, dep_%, $(MODULES))
dep_main: $(patsubst %, dep_%, $(MODULES))
dep_main_array: $(_dep_main_array)
dep_main_algebra: $(_dep_main_algebra)
dep_main_region: $(_dep_main_region)
dep_main_mesh: $(_dep_main_mesh)
dep_main_diffusion: $(_dep_main_diffusion)
dep_main_shared:
dep_main_graphics: $(_dep_main_graphics)

############################### library targets ################################
.PHONY: lib $(patsubst %, lib_%, $(MODULES))
lib: obj_src $(patsubst %, lib_%, $(MODULES))
lib_array: build/$(MODE)/lib/libarray$(.LIB)
lib_algebra: build/$(MODE)/lib/libalgebra$(.LIB)
lib_region: build/$(MODE)/lib/libregion$(.LIB)
lib_mesh: build/$(MODE)/lib/libmesh$(.LIB)
lib_diffusion: build/$(MODE)/lib/libdiffusion$(.LIB)
lib_shared: build/$(MODE)/lib/libshared$(.DLL)
lib_graphics: build/$(MODE)/lib/libgraphics$(.LIB)

############################## executable targets ##############################
.PHONY: $(patsubst %, bin_%, $(MODULES))
bin: obj_main lib $(patsubst %, bin_%, $(MODULES))
bin_array: $(_bin_array)
bin_algebra: $(_bin_algebra)
bin_region: $(_bin_region)
bin_mesh: $(_bin_mesh)
bin_diffusion: $(_bin_diffusion)
bin_shared:
bin_graphics: $(_bin_graphics)

#################### targets by modules -- called on demand ####################
.PHONY: $(MODULES)
array: $(patsubst %, %_array, obj_src obj_main lib bin demo)
algebra: $(patsubst %, %_algebra, obj_src obj_main lib bin demo)
region: $(patsubst %, %_region, obj_src obj_main lib bin demo)
mesh: $(patsubst %, %_mesh, obj_src obj_main lib bin demo)
diffusion: $(patsubst %, %_diffusion, obj_src obj_main lib bin demo)
shared: obj_src_shared lib_shared
graphics: $(patsubst %, %_graphics, obj_src obj_main lib bin demo)

########################## preparing build directory ###########################
build:
	mkdir -p $@

build/$(MODE): | build
	mkdir -p $@

######################### preprocessing and compiling ##########################
build/$(MODE)/obj: | build/$(MODE)
	mkdir -p $@

# compiling source files
build/$(MODE)/obj/src: | build/$(MODE)/obj
	mkdir -p $@

$(_obj_src_array): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/array/%.c\
  | build/$(MODE)/obj/src
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_array) -c $<

$(_obj_src_algebra): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/algebra/%.c\
    | build/$(MODE)/obj/src
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_algebra) -c $<

$(_obj_src_region): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/region/%.c\
    | build/$(MODE)/obj/src
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_region) -c $<

$(_obj_src_mesh): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/mesh/%.c\
    | build/$(MODE)/obj/src
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_mesh) -c $<

$(_obj_src_diffusion): build/$(MODE)/obj/src/%$(.OBJ):\
  code/c/src/diffusion/%.c | build/$(MODE)/obj/src
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_diffusion) -c $<

$(_obj_src_shared): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/shared/%.c\
    | build/$(MODE)/obj/src
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_shared) -c $<

$(_obj_src_graphics): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/graphics/%.c\
    | build/$(MODE)/obj/src
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_graphics)\
	  $(shell pkg-config --cflags gtk+-3.0) -c $<

# in case `dep_src` is not called
# -include build/$(MODE)/obj/src/*$(.DEP)

# compiling main files
build/$(MODE)/obj/main: | build/$(MODE)/obj
	mkdir -p $@

$(_obj_main_array): build/$(MODE)/obj/main/%$(.OBJ): code/c/main/array/%.c\
  | build/$(MODE)/obj/main
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_main_array) -c $<

$(_obj_main_algebra): build/$(MODE)/obj/main/%$(.OBJ):\
   code/c/main/algebra/%.c | build/$(MODE)/obj/main
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_main_algebra) -c $<

$(_obj_main_region): build/$(MODE)/obj/main/%$(.OBJ):\
   code/c/main/region/%.c | build/$(MODE)/obj/main
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_main_region) -c $<

$(_obj_main_mesh): build/$(MODE)/obj/main/%$(.OBJ): code/c/main/mesh/%.c\
  | build/$(MODE)/obj/main
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_main_mesh) -c $<

$(_obj_main_diffusion): build/$(MODE)/obj/main/%$(.OBJ):\
  code/c/main/diffusion/%.c | build/$(MODE)/obj/main
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_main_diffusion) -c $<

$(_obj_main_graphics): build/$(MODE)/obj/main/%$(.OBJ):\
   code/c/main/graphics/%.c | build/$(MODE)/obj/main
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_main_graphics)\
	  $(shell pkg-config --cflags gtk+-3.0) -c $<

# in case `dep_main` is not called
# -include build/$(MODE)/obj/main/*$(.DEP)

########################### move header dependencies ###########################
build/$(MODE)/dep: | build/$(MODE)
	mkdir -p $@

# move header dependencies of source files
build/$(MODE)/dep/src: | build/$(MODE)/dep
	mkdir -p $@

$(_dep_src_array): build/$(MODE)/dep/src/%.d: build/$(MODE)/obj/src/%.o\
  | build/$(MODE)/dep/src
	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep/src

$(_dep_src_algebra): build/$(MODE)/dep/src/%.d: build/$(MODE)/obj/src/%.o\
  | build/$(MODE)/dep/src
	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep/src

$(_dep_src_region): build/$(MODE)/dep/src/%.d: build/$(MODE)/obj/src/%.o\
  | build/$(MODE)/dep/src
	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep/src

$(_dep_src_mesh): build/$(MODE)/dep/src/%.d: build/$(MODE)/obj/src/%.o\
  | build/$(MODE)/dep/src
	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep/src

$(_dep_src_diffusion): build/$(MODE)/dep/src/%.d: build/$(MODE)/obj/src/%.o\
  | build/$(MODE)/dep/src
	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep/src

$(_dep_src_shared): build/$(MODE)/dep/src/%.d: build/$(MODE)/obj/src/%.o\
  | build/$(MODE)/dep/src
	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep/src

$(_dep_src_graphics): build/$(MODE)/dep/src/%.d: build/$(MODE)/obj/src/%.o\
  | build/$(MODE)/dep/src
	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep/src

-include build/$(MODE)/dep/src/*$(.DEP)

# move header dependencies of main files
build/$(MODE)/dep/main: | build/$(MODE)/dep
	mkdir -p $@

$(_dep_main_array): build/$(MODE)/dep/main/%.d: build/$(MODE)/obj/main/%.o\
  | build/$(MODE)/dep/main
	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep/main

$(_dep_main_algebra): build/$(MODE)/dep/main/%.d: build/$(MODE)/obj/main/%.o\
  | build/$(MODE)/dep/main
	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep/main

$(_dep_main_region): build/$(MODE)/dep/main/%.d: build/$(MODE)/obj/main/%.o\
  | build/$(MODE)/dep/main
	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep/main

$(_dep_main_mesh): build/$(MODE)/dep/main/%.d: build/$(MODE)/obj/main/%.o\
  | build/$(MODE)/dep/main
	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep/main

$(_dep_main_diffusion): build/$(MODE)/dep/main/%.d: build/$(MODE)/obj/main/%.o\
  | build/$(MODE)/dep/main
	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep/main

$(_dep_main_graphics): build/$(MODE)/dep/main/%.d: build/$(MODE)/obj/main/%.o\
  | build/$(MODE)/dep/main
	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep/main

-include build/$(MODE)/dep/main/*$(.DEP)

################################## archiving ###################################
build/$(MODE)/lib: | build/$(MODE)
	mkdir -p $@

build/$(MODE)/lib/libarray$(.LIB): $(_obj_src_array) | build/$(MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/libalgebra$(.LIB): $(_obj_src_algebra) | build/$(MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/libregion$(.LIB): $(_obj_src_region) | build/$(MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/libmesh$(.LIB): $(_obj_src_mesh) | build/$(MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/libdiffusion$(.LIB): $(_obj_src_diffusion) | build/$(MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/libgraphics$(.LIB): $(_obj_src_graphics) | build/$(MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/libshared$(.DLL):\
  $(_obj_src_shared) $(_obj_src_mesh) $(_obj_src_region) $(_obj_src_algebra) $(_obj_src_array)\
  | build/$(MODE)/lib
	$(CC) -o $@ -fPIC -shared $^

################################### linking ####################################
build/$(MODE)/bin: | build/$(MODE)
	-mkdir -p $@

$(_bin_array): build/$(MODE)/bin/%$(.EXE): build/$(MODE)/obj/main/%$(.OBJ)\
  $(_libs_array) | build/$(MODE)/bin
	$(CC) -o $@ $< $(_libs_array) $(LDLIBS)

$(_bin_algebra): build/$(MODE)/bin/%$(.EXE): build/$(MODE)/obj/main/%$(.OBJ)\
  $(_libs_algebra) | build/$(MODE)/bin
	$(CC) -o $@ $< $(_libs_algebra) $(LDLIBS)

$(_bin_region): build/$(MODE)/bin/%$(.EXE): build/$(MODE)/obj/main/%$(.OBJ)\
  $(_libs_region) | build/$(MODE)/bin
	$(CC) -o $@ $< $(_libs_region) $(LDLIBS)

$(_bin_mesh): build/$(MODE)/bin/%$(.EXE): build/$(MODE)/obj/main/%$(.OBJ)\
  $(_libs_mesh) | build/$(MODE)/bin
	$(CC) -o $@ $< $(_libs_mesh) $(LDLIBS)

$(_bin_diffusion): build/$(MODE)/bin/%$(.EXE): build/$(MODE)/obj/main/%$(.OBJ)\
  $(_libs_diffusion) | build/$(MODE)/bin
	$(CC) -o $@ $< $(_libs_diffusion) $(LDLIBS)

_external_libs_gtk = $(shell pkg-config --libs gtk+-3.0)

$(_bin_graphics): build/$(MODE)/bin/%$(.EXE): build/$(MODE)/obj/main/%$(.OBJ)\
  $(_libs_graphics) | build/$(MODE)/bin
	$(CC) -o $@ $< $(_libs_graphics) $(_external_libs_gtk) $(LDLIBS)

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

############### create documentation and publish it as a website ###############
-include code/make/docs/latex.mk
-include code/make/website.mk

################################### cleaning ###################################
# array
.PHONY: obj_array_clean
obj_array_clean:
	-$(RM) $(_obj_src_array) $(_obj_main_array)

.PHONY: lib_array_clean
lib_array_clean:
	-$(RM) build/$(MODE)/lib/libarray$(.LIB)

.PHONY: bin_array_clean
bin_array_clean:
	-$(RM) $(_bin_array)

.PHONY: array_clean
array_clean: obj_array_clean

.PHONY: array_distclean
array_distclean: array_clean lib_array_clean bin_array_clean demo_array_clean

# algebra
.PHONY: obj_algebra_clean
obj_algebra_clean:
	-$(RM) $(_obj_src_algebra) $(_obj_main_algebra)

.PHONY: lib_algebra_clean
lib_algebra_clean:
	-$(RM) build/$(MODE)/lib/libalgebra$(.LIB)

.PHONY: bin_algebra_clean
bin_algebra_clean:
	-$(RM) $(_bin_algebra)

.PHONY: algebra_clean
algebra_clean: obj_algebra_clean

.PHONY: algebra_distclean
algebra_distclean: algebra_clean lib_algebra_clean bin_algebra_clean\
  demo_algebra_clean

# region
.PHONY: obj_region_clean
obj_region_clean:
	-$(RM) $(_obj_src_region) $(_obj_main_region)

.PHONY: lib_region_clean
lib_region_clean:
	-$(RM) build/$(MODE)/lib/libregion$(.LIB)

.PHONY: bin_region_clean
bin_region_clean:
	-$(RM) $(_bin_region)

.PHONY: region_clean
region_clean: obj_region_clean

.PHONY: region_distclean
region_distclean: region_clean lib_region_clean bin_region_clean\
  demo_region_clean

# mesh
.PHONY: obj_mesh_clean
obj_mesh_clean:
	-$(RM) $(_obj_src_mesh) $(_obj_main_mesh)

.PHONY: lib_mesh_clean
lib_mesh_clean:
	-$(RM) build/$(MODE)/lib/libmesh$(.LIB)

.PHONY: bin_mesh_clean
bin_mesh_clean:
	-$(RM) $(_bin_mesh)

.PHONY: mesh_clean
mesh_clean: obj_mesh_clean

.PHONY: mesh_distclean
mesh_distclean: mesh_clean lib_mesh_clean bin_mesh_clean demo_mesh_clean

# diffusion
.PHONY: obj_diffusion_clean
obj_diffusion_clean:
	-$(RM) $(_obj_src_diffusion) $(_obj_main_diffusion)

.PHONY: lib_diffusion_clean
lib_diffusion_clean:
	-$(RM) build/$(MODE)/lib/libdiffusion$(.LIB)

.PHONY: bin_diffusion_clean
bin_diffusion_clean:
	-$(RM) $(_bin_diffusion)

.PHONY: diffusion_clean
diffusion_clean: obj_diffusion_clean

.PHONY: diffusion_distclean
diffusion_distclean: diffusion_clean lib_diffusion_clean bin_diffusion_clean\
  demo_diffusion_clean

# graphics
.PHONY: obj_graphics_clean
obj_graphics_clean:
	-$(RM) $(_obj_src_graphics) $(_obj_main_graphics)

.PHONY: lib_graphics_clean
lib_graphics_clean:
	-$(RM) build/$(MODE)/lib/libgraphics$(.LIB)

.PHONY: bin_graphics_clean
bin_graphics_clean:
	-$(RM) $(_bin_graphics)

.PHONY: graphics_clean
graphics_clean: obj_graphics_clean

.PHONY: graphics_distclean
graphics_distclean: graphics_clean lib_graphics_clean bin_graphics_clean\
  demo_graphics_clean

# shared
.PHONY: obj_shared_clean
obj_shared_clean:
	-$(RM) $(_obj_src_shared)

.PHONY: lib_shared_clean
lib_shared_clean:
	-$(RM) build/$(MODE)/lib/libshared$(.LIB)

.PHONY: shared_clean
shared_clean: obj_shared_clean

.PHONY: shared_distclean
shared_distclean: shared_clean lib_shared_clean

# all
.PHONY: obj_clean
obj_clean:
	-$(RM) -r build/$(MODE)/obj

.PHONY: lib_clean
lib_clean:
	-$(RM) -r build/$(MODE)/lib

.PHONY: bin_clean
bin_clean:
	-$(RM) -r build/$(MODE)/bin

# demo_<module>_clean is found in -include demo/<module>/demo_<module>.mk
.PHONY: demo_clean
demo_clean: 
	-$(RM) -r build/$(MODE)/demo

.PHONY: clean
clean: obj_clean

.PHONY: distclean
distclean:
	-$(RM) -r build
