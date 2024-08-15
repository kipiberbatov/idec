##################################### mode #####################################
MODE := release

############### general preprocessor, compiler and linker flags ################
CPPFLAGS := -MMD -MP
CFLAGS := -O2 -Wall -Wfatal-errors
LDFLAGS := -lm

######################### OS-dependent file extensions #########################
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

########################### modules and dependencies ###########################
MODULES := array algebra region mesh shared graphics
# array:
# algebra: array
# region: array
# mesh: region algebra
# shared:
# graphics: mesh shared

############################ names of source files #############################
_src_array := $(wildcard code/c/src/array/*.c)
_src_algebra := $(wildcard code/c/src/algebra/*.c)
_src_region := $(wildcard code/c/src/region/*.c)
_src_mesh := $(wildcard code/c/src/mesh/*.c)
_src_shared := $(wildcard code/c/src/shared/*.c)
_src_graphics := $(wildcard code/c/src/graphics/*.c)

############################ names of object files #############################
_obj_array := $(patsubst code/c/src/array/%.c,\
  build/$(MODE)/obj/%$(.OBJ), $(_src_array))

_obj_algebra := $(patsubst code/c/src/algebra/%.c,\
  build/$(MODE)/obj/%$(.OBJ), $(_src_algebra))

_obj_region := $(patsubst code/c/src/region/%.c,\
  build/$(MODE)/obj/%$(.OBJ), $(_src_region))

_obj_mesh := $(patsubst code/c/src/mesh/%.c,\
  build/$(MODE)/obj/%$(.OBJ), $(_src_mesh))

_obj_shared := $(patsubst code/c/src/shared/%.c,\
  build/$(MODE)/obj/%$(.OBJ), $(_src_shared))

_obj_graphics := $(patsubst code/c/src/graphics/%.c,\
  build/$(MODE)/obj/%$(.OBJ), $(_src_graphics))

######################### names of header dependencies #########################
_dep_array := $(patsubst code/c/src/array/%.c,\
  build/$(MODE)/obj/%.d, $(_src_array))

_dep_algebra := $(patsubst code/c/src/algebra/%.c,\
  build/$(MODE)/obj/%.d, $(_src_algebra))

_dep_region := $(patsubst code/c/src/region/%.c,\
  build/$(MODE)/obj/%.d, $(_src_region))

_dep_mesh := $(patsubst code/c/src/mesh/%.c,\
  build/$(MODE)/obj/%.d, $(_src_mesh))

_dep_shared := $(patsubst code/c/src/shared/%.c,\
  build/$(MODE)/obj/%.d, $(_src_shared))

_dep_graphics := $(patsubst code/c/src/graphics/%.c,\
  build/$(MODE)/obj/%.d, $(_src_graphics))

# _dep_array := $(patsubst code/c/src/array/%.c,\
#   build/$(MODE)/dep/%.d, $(_src_array))

# _dep_algebra := $(patsubst code/c/src/algebra/%.c,\
#   build/$(MODE)/dep/%.d, $(_src_algebra))

# _dep_region := $(patsubst code/c/src/region/%.c,\
#   build/$(MODE)/dep/%.d, $(_src_region))

# _dep_mesh := $(patsubst code/c/src/mesh/%.c,\
#   build/$(MODE)/dep/%.d, $(_src_mesh))

# _dep_shared := $(patsubst code/c/src/shared/%.c,\
#   build/$(MODE)/dep/%.d, $(_src_shared))

# _dep_graphics := $(patsubst code/c/src/graphics/%.c,\
#   build/$(MODE)/dep/%.d, $(_src_graphics))

############################# names of main files ##############################
_main_array := $(wildcard code/c/main/array/*.c)
_main_algebra := $(wildcard code/c/main/algebra/*.c)
_main_region := $(wildcard code/c/main/region/*.c)
_main_mesh := $(wildcard code/c/main/mesh/*.c)
_main_graphics := $(wildcard code/c/main/graphics/*.c)

########################## names of executable files ###########################
_bin_array := $(patsubst code/c/main/array/main_%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_array))

_bin_algebra := $(patsubst code/c/main/algebra/main_%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_algebra))

_bin_region := $(patsubst code/c/main/region/main_%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_region))

_bin_mesh := $(patsubst code/c/main/mesh/main_%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_mesh))

_bin_graphics := $(patsubst code/c/main/graphics/main_%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_graphics))

#################### (public) include files for executables ####################
_include_array := -iquote code/c/include/array
_include_algebra := $(_include_array) -iquote code/c/include/algebra
_include_region := $(_include_array) -iquote code/c/include/region
_include_mesh := $(_include_algebra)\
  -iquote code/c/include/region -iquote code/c/include/mesh
_include_shared := $(_include_mesh) -iquote code/c/include/shared
_include_graphics := $(_include_mesh) -iquote code/c/include/graphics
# $(shell pkg-config --cflags gtk+-3.0) is included when calling the compiler


############# (public and private) include files for object files ##############
_include_src_array := $(_include_array) -iquote code/c/src/array
_include_src_algebra := $(_include_algebra) -iquote code/c/src/algebra
_include_src_region := $(_include_region) -iquote code/c/src/region
_include_src_mesh := $(_include_mesh) -iquote code/c/src/mesh
_include_src_shared := $(_include_shared) -iquote code/c/src/shared
_include_src_graphics := $(_include_graphics) -iquote code/c/src/graphics

############################# library dependencies ############################# 
_libs_array := build/$(MODE)/lib/libarray$(.LIB)
_libs_algebra := build/$(MODE)/lib/libalgebra$(.LIB) $(_libs_array)
_libs_region := build/$(MODE)/lib/libregion$(.LIB) $(_libs_array)
_libs_mesh := build/$(MODE)/lib/libmesh$(.LIB)\
  build/$(MODE)/lib/libregion$(.LIB) $(_libs_algebra)
_libs_graphics := build/$(MODE)/lib/libgraphics$(.LIB) $(_libs_mesh)

############################### all-type targets ###############################
.PHONY: all
all: obj lib bin demo

############################# object file targets ##############################
.PHONY: obj obj_array obj_algebra obj_region obj_mesh obj_shared obj_graphics
obj: $(patsubst %, obj_%, $(MODULES))
obj_array: $(_obj_array)
obj_algebra: $(_obj_algebra)
obj_region: $(_obj_region)
obj_mesh: $(_obj_mesh)
obj_shared: $(_obj_shared)
obj_graphics: $(_obj_graphics)

######################### header dependencies targets ##########################
# .PHONY: dep dep_array dep_algebra dep_region dep_mesh dep_shared dep_graphics
# dep: obj $(patsubst %, dep_%, $(MODULES))
# dep_array: $(_dep_array)
# dep_algebra: $(_dep_algebra)
# dep_region: $(_dep_region)
# dep_mesh: $(_dep_mesh)
# dep_shared: $(_dep_shared)
# dep_graphics: $(_dep_graphics)

############################### library targets ################################
.PHONY: lib lib_array lib_algebra lib_region lib_mesh lib_shared lib_graphics
lib: obj $(patsubst %, lib_%, $(MODULES))
lib_array: build/$(MODE)/lib/libarray$(.LIB)
lib_algebra: build/$(MODE)/lib/libalgebra$(.LIB)
lib_region: build/$(MODE)/lib/libregion$(.LIB)
lib_mesh: build/$(MODE)/lib/libmesh$(.LIB)
lib_shared: build/$(MODE)/lib/libshared$(.DLL)
lib_graphics: build/$(MODE)/lib/libgraphics$(.LIB)

############################## executable targets ##############################
.PHONY: bin bin_array bin_algebra bin_region bin_mesh bin_shared bin_graphics
bin: lib $(patsubst %, bin_%, array algebra region mesh graphics)
bin_array: $(_bin_array)
bin_algebra: $(_bin_algebra)
bin_region: $(_bin_region)
bin_mesh: $(_bin_mesh)
bin_shared: $(_bin_shared)
bin_graphics: $(_bin_graphics)

#################### targets by modules -- called on demand ####################
.PHONY: array algebra region mesh shared graphics
array: obj_array lib_array bin_array demo_array
algebra: obj_algebra lib_algebra bin_algebra demo_algebra
region: obj_region lib_region bin_region demo_region
mesh: obj_mesh lib_mesh bin_mesh demo_mesh
graphics: obj_graphics lib_graphics bin_graphics demo_graphics
shared: obj_shared lib_shared

########################## preparing build directory ###########################
build:
	mkdir -p $@

build/$(MODE): | build
	mkdir -p $@

######################### preprocessing and compiling ##########################
build/$(MODE)/obj: | build/$(MODE)
	mkdir -p $@

$(_obj_array): build/$(MODE)/obj/%$(.OBJ): code/c/src/array/%.c\
  | build/$(MODE)/obj
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_array) -c $<

$(_obj_algebra): build/$(MODE)/obj/%$(.OBJ): code/c/src/algebra/%.c\
    | build/$(MODE)/obj
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_algebra) -c $<

$(_obj_region): build/$(MODE)/obj/%$(.OBJ): code/c/src/region/%.c\
    | build/$(MODE)/obj
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_region) -c $<

$(_obj_mesh): build/$(MODE)/obj/%$(.OBJ): code/c/src/mesh/%.c\
    | build/$(MODE)/obj
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_mesh) -c $<

$(_obj_shared): build/$(MODE)/obj/%$(.OBJ): code/c/src/shared/%.c\
    | build/$(MODE)/obj
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_shared) -c $<

$(_obj_graphics): build/$(MODE)/obj/%$(.OBJ): code/c/src/graphics/%.c\
    | build/$(MODE)/obj
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(_include_src_graphics)\
	  $(shell pkg-config --cflags gtk+-3.0) -c $<

############################# header dependencies ##############################
# build/$(MODE)/dep: | build/$(MODE)
# 	mkdir -p $@

# $(_dep_array): build/$(MODE)/dep/%.d: build/$(MODE)/obj/%.o | build/$(MODE)/dep
# 	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep

# $(_dep_algebra): build/$(MODE)/dep/%.d: build/$(MODE)/obj/%.o\
#   | build/$(MODE)/dep
# 	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep

# $(_dep_region): build/$(MODE)/dep/%.d: build/$(MODE)/obj/%.o | build/$(MODE)/dep
# 	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep

# $(_dep_mesh): build/$(MODE)/dep/%.d: build/$(MODE)/obj/%.o | build/$(MODE)/dep
# 	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep

# $(_dep_shared): build/$(MODE)/dep/%.d: build/$(MODE)/obj/%.o | build/$(MODE)/dep
# 	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep

# $(_dep_graphics): build/$(MODE)/dep/%.d: build/$(MODE)/obj/%.o\
#   | build/$(MODE)/dep
# 	mv $(patsubst %.o, %.d, $<) build/$(MODE)/dep

# -include build/$(MODE)/dep/*.d

-include build/$(MODE)/obj/*.d

################################## archiving ###################################
build/$(MODE)/lib: | build/$(MODE)
	mkdir -p $@

build/$(MODE)/lib/libarray$(.LIB): $(_obj_array) | build/$(MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/libalgebra$(.LIB): $(_obj_algebra) | build/$(MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/libregion$(.LIB): $(_obj_region) | build/$(MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/libmesh$(.LIB): $(_obj_mesh) | build/$(MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/libgraphics$(.LIB): $(_obj_graphics) | build/$(MODE)/lib
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/libshared$(.DLL):\
  $(_obj_shared) $(_obj_algebra) $(_obj_array) | build/$(MODE)/lib
	$(CC) -o $@ -fPIC -shared $^

################################### linking ####################################
build/$(MODE)/bin: | build/$(MODE)
	-mkdir -p $@

$(_bin_array): build/$(MODE)/bin/%$(.EXE):\
 code/c/main/array/main_%.c $(_libs_array) | build/$(MODE)/bin
	$(CC) -o $@ $(CPPFLAGS) $(_include_array) $(CFLAGS) $< $(_libs_array)\
	  $(LDFLAGS)

$(_bin_algebra): build/$(MODE)/bin/%$(.EXE):\
  code/c/main/algebra/main_%.c $(_libs_algebra) | build/$(MODE)/bin
	$(CC) -o $@ $(CPPFLAGS) $(_include_algebra) $(CFLAGS) $<\
	  $(_libs_algebra) $(LDFLAGS)

$(_bin_region): build/$(MODE)/bin/%$(.EXE):\
  code/c/main/region/main_%.c $(_libs_region) | build/$(MODE)/bin
	$(CC) -o $@ $(CPPFLAGS) $(_include_region) $(CFLAGS) $< $(_libs_region)\
	  $(LDFLAGS)

$(_bin_mesh): build/$(MODE)/bin/%$(.EXE):\
  code/c/main/mesh/main_%.c $(_libs_mesh) | build/$(MODE)/bin
	$(CC) -o $@ $(CPPFLAGS) $(_include_mesh) $(CFLAGS) $< $(_libs_mesh)\
	  $(LDFLAGS)

$(_bin_graphics): build/$(MODE)/bin/%$(.EXE):\
  code/c/main/graphics/main_%.c $(_libs_graphics)\
  | build/$(MODE)/bin
	$(CC) -o $@ $(CPPFLAGS) $(_include_graphics)\
	  $(shell pkg-config --cflags gtk+-3.0) $(CFLAGS) $<\
	  $(shell pkg-config --libs gtk+-3.0) $(_libs_graphics) $(LDFLAGS)

-include build/$(MODE)/bin/*.d

################################ running demos #################################
build/$(MODE)/demo: | build/$(MODE)
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
	-$(RM) $(_obj_array) $(_dep_array)

.PHONY: lib_array_clean
lib_array_clean:
	-$(RM) build/$(MODE)/lib/libarray$(.LIB)

.PHONY: bin_array_clean
bin_array_clean:
	-$(RM) $(_bin_array)

.PHONY: array_clean
array_clean: obj_array_clean

.PHONY: array_distclean
array_distclean: lib_array_clean bin_array_clean demo_array_clean

# algebra
.PHONY: obj_algebra_clean
obj_algebra_clean:
	-$(RM) $(_obj_algebra) $(_dep_algebra)

.PHONY: lib_algebra_clean
lib_algebra_clean:
	-$(RM) build/$(MODE)/lib/libalgebra$(.LIB)

.PHONY: bin_algebra_clean
bin_algebra_clean:
	-$(RM) $(_bin_algebra)

.PHONY: algebra_clean
algebra_clean: obj_algebra_clean

.PHONY: algebra_distclean
algebra_distclean: lib_algebra_clean bin_algebra_clean demo_algebra_clean

# region
.PHONY: obj_region_clean
obj_region_clean:
	-$(RM) $(_obj_region) $(_dep_region)

.PHONY: lib_region_clean
lib_region_clean:
	-$(RM) build/$(MODE)/lib/libregion$(.LIB)

.PHONY: bin_region_clean
bin_region_clean:
	-$(RM) $(_bin_region)

.PHONY: region_clean
region_clean: obj_region_clean

.PHONY: region_distclean
region_distclean: lib_region_clean bin_region_clean demo_region_clean

# mesh
.PHONY: obj_mesh_clean
obj_mesh_clean:
	-$(RM) $(_obj_mesh)

.PHONY: lib_mesh_clean
lib_mesh_clean:
	-$(RM) build/$(MODE)/lib/libmesh$(.LIB)

.PHONY: bin_mesh_clean
bin_mesh_clean:
	-$(RM) $(_bin_mesh)

.PHONY: mesh_clean
mesh_clean: obj_mesh_clean

.PHONY: mesh_distclean
mesh_distclean: lib_mesh_clean bin_mesh_clean demo_mesh_clean

# graphics
.PHONY: obj_graphics_clean
obj_graphics_clean:
	-$(RM) $(_obj_graphics) $(_dep_graphics)

.PHONY: lib_graphics_clean
lib_graphics_clean:
	-$(RM) build/$(MODE)/lib/libgraphics$(.LIB)

.PHONY: bin_graphics_clean
bin_graphics_clean:
	-$(RM) $(_bin_graphics)

.PHONY: graphics_clean
graphics_clean: obj_graphics_clean

.PHONY: graphics_distclean
graphics_distclean: lib_graphics_clean bin_graphics_clean demo_graphics_clean

# shared
.PHONY: obj_shared_clean
obj_shared_clean:
	-$(RM) $(_obj_shared) $(_dep_shared)

.PHONY: lib_shared_clean
lib_shared_clean:
	-$(RM) build/$(MODE)/lib/libshared$(.LIB)

.PHONY: shared_clean
shared_clean: obj_shared_clean

.PHONY: shared_distclean
shared_distclean: lib_shared_clean

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
