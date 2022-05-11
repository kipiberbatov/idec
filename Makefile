################################################################################
################################# main makefile ################################
################################################################################

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
  .DYN := .dll
  .LIB := .lib 
  .OBJ := .obj
else
  .EXE :=
  .LIB := .a
  .OBJ := .o
  UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
  .DYN := .so
endif
ifeq ($(UNAME_S), Darwin)
  .DYN := .dylib
endif
endif

########################### high-level dependencies ############################
# array:
# algebra: array
# region: array
# mesh: region algebra
# graphics: mesh

################################# $(CC) flags ##################################
MODULES := array algebra region mesh

CPPFLAGS := -MMD -MP
CFLAGS := -O2 -Wall

ARRAY_INC_EXE := -iquote include/array
ARRAY_INC := $(ARRAY_INC_EXE) -iquote src/array

ALGEBRA_INC_EXE := $(ARRAY_INC_EXE) -iquote include/algebra
ALGEBRA_INC := $(ALGEBRA_INC_EXE) -iquote src/algebra

REGION_INC_EXE := $(ARRAY_INC_EXE) -iquote include/region
REGION_INC := $(REGION_INC_EXE) -iquote src/region

MESH_INC_EXE := $(ALGEBRA_INC_EXE) -iquote include/region -iquote include/mesh
MESH_INC := $(MESH_INC_EXE) -iquote src/mesh

ARRAY_LDLIBS := lib/libarray$(.LIB)
ALGEBRA_LDLIBS := lib/libalgebra$(.LIB) $(ARRAY_LDLIBS)
REGION_LDLIBS := lib/libregion$(.LIB) $(ARRAY_LDLIBS)
MESH_LDLIBS := lib/libmesh$(.LIB) lib/libregion$(.LIB) $(ALGEBRA_LDLIBS) 

############################### all-type targets ###############################
.PHONY: all
all: build_all lib_all bin_all demo_all

# array
.PHONY: array
array: build_array lib_array bin_array demo_array

# algebra
.PHONY: algebra
algebra: build_algebra lib_algebra bin_algebra demo_algebra

# region
.PHONY: region
region: build_region lib_region bin_region demo_region

# mesh
.PHONY: mesh
mesh: build_mesh lib_mesh bin_mesh demo_mesh

######################### preprocessing and compiling ##########################
build:
	$(MKDIR) -p $@

# array
ARRAY_OBJ_NAMES := $(wildcard src/array/*$(.SRC))
ARRAY_OBJ :=\
  $(patsubst src/array/%$(.SRC), build/%$(.OBJ), $(ARRAY_OBJ_NAMES))

.PHONY: build_array
build_array: build $(ARRAY_OBJ)

$(ARRAY_OBJ): build/%$(.OBJ): src/array/%$(.SRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(ARRAY_INC) -c $< -o $@

# algebra
ALGEBRA_OBJ_NAMES := $(wildcard src/algebra/*$(.SRC))
ALGEBRA_OBJ :=\
  $(patsubst src/algebra/%$(.SRC), build/%$(.OBJ), $(ALGEBRA_OBJ_NAMES))

.PHONY: build_algebra
build_algebra: build $(ALGEBRA_OBJ)

$(ALGEBRA_OBJ): build/%$(.OBJ): src/algebra/%$(.SRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(ALGEBRA_INC) -c $< -o $@

# region
REGION_OBJ_NAMES := $(wildcard src/region/*$(.SRC))
REGION_OBJ :=\
  $(patsubst src/region/%$(.SRC), build/%$(.OBJ), $(REGION_OBJ_NAMES))

.PHONY: build_region
build_region: build $(REGION_OBJ)

$(REGION_OBJ): build/%$(.OBJ): src/region/%$(.SRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(REGION_INC) -c $< -o $@

# mesh
MESH_OBJ_NAMES := $(wildcard src/mesh/*$(.SRC))
MESH_OBJ :=\
  $(patsubst src/mesh/%$(.SRC), build/%$(.OBJ), $(MESH_OBJ_NAMES))

.PHONY: build_mesh
build_mesh: build $(MESH_OBJ)

$(MESH_OBJ): build/%$(.OBJ): src/mesh/%$(.SRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(MESH_INC) -c $< -o $@

# all
.PHONY: build_all
build_all: $(patsubst %, build_%, $(MODULES))

############################# header dependencies ##############################
-include build/*$(.DEP)

# array
ARRAY_HEADER_DEP :=\
  $(patsubst build/%$(.OBJ), build/%$(.DEP), $(ARRAY_OBJ_NAMES))

# algebra
ALGEBRA_HEADER_DEP :=\
  $(patsubst build/%$(.OBJ), build/%$(.DEP), $(ALGEBRA_OBJ_NAMES))

# region
REGION_HEADER_DEP :=\
  $(patsubst build/%$(.OBJ), build/%$(.DEP), $(REGION_OBJ_NAMES))

# mesh
MESH_HEADER_DEP :=\
  $(patsubst build/%$(.OBJ), build/%$(.DEP), $(MESH_OBJ_NAMES))

################################## archiving ###################################
lib: build
	$(MKDIR) -p $@

# array
.PHONY: lib_array
lib_array: lib lib/libarray$(.LIB)

lib/libarray$(.LIB): $(ARRAY_OBJ)
	$(AR) $(ARFLAGS) $@ $^

# algebra
.PHONY: lib_algebra
lib_algebra: lib lib/libalgebra$(.LIB)

lib/libalgebra$(.LIB): $(ALGEBRA_OBJ)
	$(AR) $(ARFLAGS) $@ $^

# region
.PHONY: lib_region
lib_region: lib lib/libregion$(.LIB)

lib/libregion$(.LIB): $(REGION_OBJ)
	$(AR) $(ARFLAGS) $@ $^

# mesh
.PHONY: lib_mesh
lib_mesh: lib lib/libmesh$(.LIB)

lib/libmesh$(.LIB): $(MESH_OBJ)
	$(AR) $(ARFLAGS) $@ $^

# all
.PHONY: lib_all
lib_all: $(patsubst %, lib_%, $(MODULES))

################################### linking ####################################
bin: lib
	-$(MKDIR) -p $@

# array
ARRAY_EXE_NAMES := $(wildcard main/array/*$(.SRC))
ARRAY_EXE :=\
  $(patsubst main/array/main_%$(.SRC), bin/%$(.EXE), $(ARRAY_EXE_NAMES))

.PHONY: bin_array
bin_array: bin $(ARRAY_EXE)

$(ARRAY_EXE): bin/%$(.EXE): main/array/main_%$(.SRC) $(ARRAY_LDLIBS)
	$(CC) $(CFLAGS) $(ARRAY_INC_EXE) $(CCFLAGS) $< $(ARRAY_LDLIBS) -o $@

# algebra
ALGEBRA_EXE_NAMES := $(wildcard main/algebra/*$(.SRC))
ALGEBRA_EXE :=\
  $(patsubst main/algebra/main_%$(.SRC), bin/%$(.EXE), $(ALGEBRA_EXE_NAMES))

.PHONY: bin_algebra
bin_algebra: bin $(ALGEBRA_EXE)

$(ALGEBRA_EXE): bin/%$(.EXE): main/algebra/main_%$(.SRC) $(ALGEBRA_LDLIBS)
	$(CC) $(CFLAGS) $(ALGEBRA_INC_EXE) $(CCFLAGS) $< $(ALGEBRA_LDLIBS) -o $@

# region
REGION_EXE_NAMES := $(wildcard main/region/*$(.SRC))
REGION_EXE :=\
  $(patsubst main/region/main_%$(.SRC), bin/%$(.EXE), $(REGION_EXE_NAMES))

.PHONY: bin_region
bin_region: bin $(REGION_EXE)

$(REGION_EXE): bin/%$(.EXE): main/region/main_%$(.SRC) $(REGION_LDLIBS)
	$(CC) $(CFLAGS) $(REGION_INC_EXE) $(CCFLAGS) $< $(REGION_LDLIBS) -o $@

# mesh
MESH_EXE_NAMES := $(wildcard main/mesh/*$(.SRC))
MESH_EXE :=\
  $(patsubst main/mesh/main_%$(.SRC), bin/%$(.EXE), $(MESH_EXE_NAMES))

.PHONY: bin_mesh
bin_mesh: bin $(MESH_EXE)

$(MESH_EXE): bin/%$(.EXE): main/mesh/main_%$(.SRC) $(MESH_LDLIBS)
	$(CC) $(CFLAGS) $(MESH_INC_EXE) $(CCFLAGS) $< $(MESH_LDLIBS) -o $@

# all
.PHONY: bin_all
bin_all: $(patsubst %, bin_%, $(MODULES))

############################## object dependencies #############################
# at the moment executables depend on libraries and a change in one object file
# could lead to a massive relinking of executables and reruning of demos

# at the moment this list is empty
-include bin/*$(.DEP)

# array
ARRAY_OBJ_DEP :=\
  $(patsubst bin/%$(.EXE), bin/%$(.DEP), $(ARRAY_EXE_NAMES))

# algebra
ALGEBRA_OBJ_DEP :=\
  $(patsubst bin/%$(.EXE), bin/%$(.DEP), $(ALGEBRA_EXE_NAMES))

# region
REGION_OBJ_DEP :=\
  $(patsubst bin/%$(.EXE), bin/%$(.DEP), $(REGION_EXE_NAMES))

# mesh
MESH_OBJ_DEP :=\
  $(patsubst bin/%$(.EXE), bin/%$(.DEP), $(MESH_EXE_NAMES))

################################ running demos #################################
-include demo/array/demo_array.mk
-include demo/algebra/demo_algebra.mk
-include demo/region/demo_region.mk
-include demo/mesh/demo_mesh.mk

.PHONY: demo_all
demo_all: $(patsubst %, demo_%, $(MODULES))

################################### cleaning ###################################
# array
.PHONY: build_array_clean
build_array_clean:
	-$(RM) $(ARRAY_OBJ) $(ARRAY_HEADER_DEP)

.PHONY: lib_array_clean
lib_array_clean:
	-$(RM) lib/libarray$(.LIB)

.PHONY: bin_array_clean
bin_array_clean:
	-$(RM) $(ARRAY_EXE) $(ARRAY_OBJ_DEP)

.PHONY: array_clean
array_clean: build_array_clean

.PHONY: array_distclean
array_distclean: lib_array_clean bin_array_clean demo_array_clean

# algebra
.PHONY: build_algebra_clean
build_algebra_clean:
	-$(RM) $(ALGEBRA_OBJ) $(ALGEBRA_HEADER_DEP)

.PHONY: lib_algebra_clean
lib_algebra_clean:
	-$(RM) lib/libalgebra$(.LIB)

.PHONY: bin_algebra_clean
bin_algebra_clean:
	-$(RM) $(ALGEBRA_EXE) $(ALGEBRA_OBJ_DEP)

.PHONY: algebra_clean
algebra_clean: build_algebra_clean

.PHONY: algebra_distclean
algebra_distclean: lib_algebra_clean bin_algebra_clean demo_algebra_clean

# region
.PHONY: build_region_clean
build_region_clean:
	-$(RM) $(REGION_OBJ) $(REGION_HEADER_DEP)

.PHONY: lib_region_clean
lib_region_clean:
	-$(RM) lib/libregion$(.LIB)

.PHONY: bin_region_clean
bin_region_clean:
	-$(RM) $(REGION_EXE) $(REGION_OBJ_DEP)

.PHONY: region_clean
region_clean: build_region_clean

.PHONY: region_distclean
region_distclean: lib_region_clean bin_region_clean demo_region_clean

# mesh
.PHONY: build_mesh_clean
build_mesh_clean:
	-$(RM) $(MESH_OBJ) $(MESH_HEADER_DEP)

.PHONY: lib_mesh_clean
lib_mesh_clean:
	-$(RM) lib/libmesh$(.LIB)

.PHONY: bin_mesh_clean
bin_mesh_clean:
	-$(RM) $(MESH_EXE) $(MESH_OBJ_DEP)

.PHONY: mesh_clean
mesh_clean: build_mesh_clean

.PHONY: mesh_distclean
mesh_distclean: lib_mesh_clean bin_mesh_clean demo_mesh_clean

# all
.PHONY: build_clean
build_clean:
	-$(RM) -r build

.PHONY: lib_clean
lib_clean:
	-$(RM) -r lib

.PHONY: bin_clean
bin_clean:
	-$(RM) -r bin

# demo_<module>_clean is found in -include demo/<module>/demo_<module>.mk
.PHONY: demo_clean
demo_clean: $(patsubst %, demo_%_clean, $(MODULES))

.PHONY: clean
clean: build_clean

.PHONY: distclean
distclean: clean lib_clean bin_clean demo_clean
