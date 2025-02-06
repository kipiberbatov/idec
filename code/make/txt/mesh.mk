.PHONY: txt_mesh txt_mesh_clean txt_mesh_distclean

build/$(MODE)/txt/mesh: | build/$(MODE)/txt
	mkdir -p $@

-include code/make/txt/mesh/brick_2d_1.mk
-include code/make/txt/mesh/brick_2d_2.mk
-include code/make/txt/mesh/brick_2d_4.mk
-include code/make/txt/mesh/brick_2d_5.mk
-include code/make/txt/mesh/brick_2d_10.mk
-include code/make/txt/mesh/two_triangles.mk
-include code/make/txt/mesh/triangle_and_square.mk
-include code/make/txt/mesh/pentagon.mk
-include code/make/txt/mesh/square.mk
-include code/make/txt/mesh/2d_10_grains.mk
-include code/make/txt/mesh/circular_4_3.mk
-include code/make/txt/mesh/circular_18_10.mk
-include code/make/txt/mesh/brick_3d_1.mk
-include code/make/txt/mesh/brick_3d_2.mk
-include code/make/txt/mesh/brick_3d_5.mk
-include code/make/txt/mesh/brick_3d_10.mk
-include code/make/txt/mesh/brick_3d_25.mk # not used in default build
-include code/make/txt/mesh/square_pyramid.mk
-include code/make/txt/mesh/brick_4d_2.mk
-include code/make/txt/mesh/high_dimensions.mk # not used in default build
	
_txt_mesh_brick_2d:=\
  $(_txt_mesh_brick_2d_1)\
  $(_txt_mesh_brick_2d_2)\
  $(_txt_mesh_brick_2d_4)\
  $(_txt_mesh_brick_2d_5)\
  $(_txt_mesh_brick_2d_10)\

.PHONY: txt_mesh_brick_2d txt_mesh_brick_2d_clean

txt_mesh_brick_2d: $(_txt_mesh_brick_2d)

txt_mesh_brick_2d_clean:
	-$(RM) $(_txt_mesh_brick_2d)

_txt_mesh_circular:=\
  $(_txt_mesh_circular_4_3)\
  $(_txt_mesh_circular_18_10)\

.PHONY: txt_mesh_circular txt_mesh_circular_clean

txt_mesh_circular: $(_txt_mesh_circular)

txt_mesh_circular_clean:
	-$(RM) $(_txt_mesh_circular)

_txt_mesh_brick_3d:=\
  $(_txt_mesh_brick_3d_1)\
  $(_txt_mesh_brick_3d_2)\
  $(_txt_mesh_brick_3d_5)\
  $(_txt_mesh_brick_3d_10)\

.PHONY: txt_mesh_brick_3d txt_mesh_brick_3d_clean

txt_mesh_brick_3d: $(_txt_mesh_brick_3d)

txt_mesh_brick_3d_clean:
	-$(RM) $(_txt_mesh_brick_3d)

_txt_mesh_brick_regular_4d := $(_txt_mesh_brick_regular_4d_2)

.PHONY: txt_mesh_brick_4d txt_mesh_brick_4d_clean

txt_mesh_brick_4d: $(_txt_mesh_brick_4d)

txt_mesh_brick_4d_clean:
	-$(RM) $(_txt_mesh_brick_4d)

_txt_mesh_brick :=\
  $(_txt_mesh_brick_2d)\
  $(_txt_mesh_brick_3d)\
  $(_txt_mesh_brick_4d)\

.PHONY: txt_mesh_brick txt_mesh_brick_clean

txt_mesh_brick: $(_txt_mesh_brick)

txt_mesh_brick_clean:
	-$(RM) $(_txt_mesh_brick)

_txt_mesh :=\
  $(_txt_mesh_brick)\
  $(_txt_mesh_two_triangles)\
  $(_txt_mesh_triangle_and_square)\
  $(_txt_mesh_pentagon)\
  $(_txt_mesh_square)\
  $(_txt_mesh_2d_10_grains)\
  $(_txt_mesh_circular)\
  $(_txt_mesh_square_pyramid)\

txt_mesh: bin_mesh $(_txt_mesh)

txt_mesh_clean:
	-$(RM) $(_txt_mesh)

txt_mesh_distclean:
	-$(RM) -r build/$(MODE)/txt/mesh
