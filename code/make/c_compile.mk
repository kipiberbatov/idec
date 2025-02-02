############### general preprocessor, compiler and linker flags ################
CPPFLAGS := -MMD -MP
CFLAGS := -O2 -Wall -Wfatal-errors -Werror -fPIC
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
MODULES := array algebra region mesh diffusion graphics shared animation canvas
# array:
# algebra: array
# region: array
# mesh: region algebra
# diffusion: mesh
# graphics: mesh (dynamically on shared, and hence, on diffusion)
# shared: mesh (+ diffusion headers)
# canvas: [Cairo] (+ animation headers)
# animation: graphics Cairo GTK3

############################ names of source files #############################
_src_array := $(wildcard code/c/src/array/*.c)
_src_algebra := $(wildcard code/c/src/algebra/*.c)
_src_region := $(wildcard code/c/src/region/*.c)
_src_mesh := $(wildcard code/c/src/mesh/*.c)
_src_diffusion := $(wildcard code/c/src/diffusion/*.c)
_src_graphics := $(wildcard code/c/src/graphics/*.c)
_src_shared := $(wildcard code/c/src/shared/*.c)
_src_animation := $(wildcard code/c/src/animation/*.c)
_src_canvas := $(wildcard code/c/src/canvas/*.c)

############################# names of main files ##############################
_main_array := $(wildcard code/c/main/array/*.c)
_main_algebra := $(wildcard code/c/main/algebra/*.c)
_main_region := $(wildcard code/c/main/region/*.c)
_main_mesh := $(wildcard code/c/main/mesh/*.c)
_main_diffusion := $(wildcard code/c/main/diffusion/*.c)
_main_graphics := $(wildcard code/c/main/graphics/*.c)
_main_shared :=
_main_animation :=
_main_canvas :=

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

_obj_src_graphics := $(patsubst code/c/src/graphics/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_graphics))

_obj_src_shared := $(patsubst code/c/src/shared/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_shared))

_obj_src_animation := $(patsubst code/c/src/animation/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_animation))

_obj_src_canvas := $(patsubst code/c/src/canvas/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_canvas))

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

_obj_main_graphics := $(patsubst code/c/main/graphics/%.c,\
  build/$(MODE)/obj/main/%$(.OBJ), $(_main_graphics))

_obj_main_shared :=

_obj_main_animation :=

_obj_main_canvas :=

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

_bin_graphics := $(patsubst code/c/main/graphics/%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_graphics))

_bin_shared :=

_bin_animation :=

_bin_canvas :=

################# include directories for compiling main files #################
_include_main_array := -iquote code/c/include/array
_include_main_algebra := $(_include_main_array) -iquote code/c/include/algebra
_include_main_region := $(_include_main_array) -iquote code/c/include/region
_include_main_mesh := $(_include_main_algebra)\
  -iquote code/c/include/region -iquote code/c/include/mesh
_include_main_diffusion := $(_include_main_mesh)\
  -iquote code/c/include/diffusion
_include_main_graphics := $(_include_main_mesh) -iquote code/c/include/graphics
_include_main_shared :=
_include_main_animation :=
_include_main_canvas :=

################ include directories for compiling source files ################
_include_src_array := $(_include_main_array) -iquote code/c/src/array
_include_src_algebra := $(_include_main_algebra) -iquote code/c/src/algebra
_include_src_region := $(_include_main_region) -iquote code/c/src/region
_include_src_mesh := $(_include_main_mesh) -iquote code/c/src/mesh
_include_src_diffusion := $(_include_main_diffusion)\
  -iquote code/c/src/diffusion
_include_src_graphics := $(_include_main_graphics) -iquote code/c/src/graphics
_include_src_shared := $(_include_main_diffusion)
_include_src_animation := $(_include_main_graphics) -iquote code/c/src/animation
_include_src_canvas := $(_include_main_graphics)\
  -iquote code/c/include/animation -iquote code/c/src/canvas

############################# library dependencies #############################
_libs_array := build/$(MODE)/lib/libarray$(.LIB)
_libs_algebra := build/$(MODE)/lib/libalgebra$(.LIB) $(_libs_array)
_libs_region := build/$(MODE)/lib/libregion$(.LIB) $(_libs_array)
_libs_mesh := build/$(MODE)/lib/libmesh$(.LIB)\
  build/$(MODE)/lib/libregion$(.LIB) $(_libs_algebra)
_libs_diffusion := build/$(MODE)/lib/libdiffusion$(.LIB) $(_libs_mesh)
_libs_graphics := build/$(MODE)/lib/libgraphics$(.LIB) $(_libs_mesh)
_libs_shared :=
_libs_animation :=
_libs_canvas :=

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
obj_src_graphics: $(_obj_src_graphics)
obj_src_shared: $(_obj_src_shared)
obj_src_animation: $(_obj_src_animation)
obj_src_canvas: $(_obj_src_canvas)

# object files from main files
.PHONY: $(patsubst %, obj_main_%, $(MODULES))
obj_main: $(patsubst %, obj_main_%, $(MODULES))
obj_main_array: $(_obj_main_array)
obj_main_algebra: $(_obj_main_algebra)
obj_main_region: $(_obj_main_region)
obj_main_mesh: $(_obj_main_mesh)
obj_main_diffusion: $(_obj_main_diffusion)
obj_main_graphics: $(_obj_main_graphics)
obj_main_shared:
obj_main_animation:
obj_main_canvas:

############################### library targets ################################
.PHONY: lib $(patsubst %, lib_%, $(MODULES))
lib: obj_src $(patsubst %, lib_%, $(MODULES))
lib_array: build/$(MODE)/lib/libarray$(.LIB)
lib_algebra: build/$(MODE)/lib/libalgebra$(.LIB)
lib_region: build/$(MODE)/lib/libregion$(.LIB)
lib_mesh: build/$(MODE)/lib/libmesh$(.LIB)
lib_diffusion: build/$(MODE)/lib/libdiffusion$(.LIB)
lib_graphics: build/$(MODE)/lib/libgraphics$(.LIB)
lib_shared: build/$(MODE)/lib/libshared$(.DLL)
lib_animation: build/$(MODE)/lib/libanimation$(.DLL)
lib_canvas: build/$(MODE)/lib/libcanvas$(.DLL)

############################## executable targets ##############################
.PHONY: $(patsubst %, bin_%, $(MODULES))
bin: obj_main lib $(patsubst %, bin_%, $(MODULES))
bin_array: $(_bin_array)
bin_algebra: $(_bin_algebra)
bin_region: $(_bin_region)
bin_mesh: $(_bin_mesh)
bin_diffusion: $(_bin_diffusion)
bin_graphics: $(_bin_graphics)
bin_shared:
bin_animation:
bin_canvas:

#################### targets by modules -- called on demand ####################
.PHONY: $(MODULES)
array: $(patsubst %, %_array, obj_src obj_main lib bin txt)
algebra: $(patsubst %, %_algebra, obj_src obj_main lib bin txt)
region: $(patsubst %, %_region, obj_src obj_main lib bin txt)
mesh: $(patsubst %, %_mesh, obj_src obj_main lib bin txt)
diffusion: $(patsubst %, %_diffusion, obj_src obj_main lib bin txt)
graphics: $(patsubst %, %_graphics, obj_src obj_main lib bin txt)
shared: obj_src_shared lib_shared
animation: obj_src_animation lib_animation
canvas: obj_src_canvas lib_canvas

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

$(_obj_src_graphics): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/graphics/%.c\
    | build/$(MODE)/obj/src
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_graphics) -c $<

$(_obj_src_shared): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/shared/%.c\
    | build/$(MODE)/obj/src
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_shared) -c $<

$(_obj_src_animation): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/animation/%.c\
    | build/$(MODE)/obj/src
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_animation)\
	  $(shell pkg-config --cflags gtk+-3.0) -c $<

$(_obj_src_canvas): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/canvas/%.c\
    | build/$(MODE)/obj/src
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_canvas)\
	  $(shell pkg-config --cflags cairo) -c $<

# include header dependencies for object files from code/c/src
-include build/$(MODE)/obj/src/*$(.DEP)

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

$(_obj_main_graphics): build/$(MODE)/obj/main/%$(.OBJ):\
   code/c/main/graphics/%.c | build/$(MODE)/obj/main
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_main_graphics) -c $<

$(_obj_main_mesh): build/$(MODE)/obj/main/%$(.OBJ): code/c/main/mesh/%.c\
  | build/$(MODE)/obj/main
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_main_mesh) -c $<

$(_obj_main_diffusion): build/$(MODE)/obj/main/%$(.OBJ):\
  code/c/main/diffusion/%.c | build/$(MODE)/obj/main
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_main_diffusion) -c $<

# include header dependencies for object files from code/c/main
-include build/$(MODE)/obj/main/*$(.DEP)

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
  $(_obj_src_shared) $(_obj_src_mesh) $(_obj_src_region) $(_obj_src_algebra)\
  $(_obj_src_array)\
  | build/$(MODE)/lib
	$(CC) -o $@ -fPIC -shared $^ $(LDLIBS)

build/$(MODE)/lib/libanimation$(.DLL):\
  $(_obj_src_animation) | build/$(MODE)/lib
	$(CC) -o $@ -fPIC -shared $^ $(shell pkg-config --libs gtk+-3.0) $(LDLIBS)

build/$(MODE)/lib/libcanvas$(.DLL):\
  $(_obj_src_canvas)\
  $(_obj_src_graphics)\
  $(_obj_src_mesh)\
  $(_obj_src_region)\
  $(_obj_src_algebra)\
  $(_obj_src_array)\
  | build/$(MODE)/lib
	$(CC) -o $@ -fPIC -shared $^ $(shell pkg-config --libs cairo) $(LDLIBS)

################################### linking ####################################
build/$(MODE)/bin: | build/$(MODE)
	mkdir -p $@

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

$(_bin_graphics): build/$(MODE)/bin/%$(.EXE): build/$(MODE)/obj/main/%$(.OBJ)\
  $(_libs_graphics) | build/$(MODE)/bin
	$(CC) -o $@ $< $(_libs_graphics) $(LDLIBS)
