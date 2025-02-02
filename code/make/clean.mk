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
array_distclean: array_clean lib_array_clean bin_array_clean txt_array_clean

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
  txt_algebra_clean

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
  txt_region_clean

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
mesh_distclean: mesh_clean lib_mesh_clean bin_mesh_clean txt_mesh_clean

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
  txt_diffusion_clean

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
  txt_graphics_clean

# shared
.PHONY: obj_shared_clean
obj_shared_clean:
	-$(RM) $(_obj_src_shared)

.PHONY: lib_shared_clean
lib_shared_clean:
	-$(RM) build/$(MODE)/lib/libshared$(.DLL)

.PHONY: shared_clean
shared_clean: obj_shared_clean

.PHONY: shared_distclean
shared_distclean: shared_clean lib_shared_clean

# animation
.PHONY: obj_animation_clean
obj_animation_clean:
	-$(RM) $(_obj_src_animation)

.PHONY: lib_animation_clean
lib_animation_clean:
	-$(RM) build/$(MODE)/lib/libanimation$(.DLL)

.PHONY: animation_clean
animation_clean: obj_animation_clean

.PHONY: animation_distclean
animation_distclean: animation_clean lib_animation_clean

# canvas
.PHONY: obj_canvas_clean
obj_canvas_clean:
	-$(RM) $(_obj_src_canvas)

.PHONY: lib_canvas_clean
lib_canvas_clean:
	-$(RM) build/$(MODE)/lib/libcanvas$(.DLL)

.PHONY: canvas_clean
canvas_clean: obj_canvas_clean

.PHONY: canvas_distclean
canvas_distclean: canvas_clean lib_canvas_clean

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

# txt_<module>_clean is found in -include txt/<module>/txt_<module>.mk
.PHONY: txt_clean
txt_clean:
	-$(RM) -r build/$(MODE)/txt

.PHONY: clean
clean: obj_clean
