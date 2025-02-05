build/$(MODE)/svg/mesh: | build/$(MODE)/svg
	mkdir -p $@

_svg_mesh :=\
  build/$(MODE)/svg/mesh/brick_2d_10_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/brick_2d_10_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/circular_4_3_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/circular_4_3_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/circular_18_10_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/circular_18_10_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/pentagon_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/pentagon_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/2d_10_grains_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/2d_10_grains_forman_edge_skeleton.svg\

build/$(MODE)/svg/mesh/brick_2d_10_edge_skeleton.svg:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/brick_2d_10_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/circular_4_3_edge_skeleton.svg:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/circular_4_3_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/circular_18_10_edge_skeleton.svg:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/circular_18_10_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/pentagon_edge_skeleton.svg:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  data/mesh/pentagon.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/pentagon_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/2d_10_grains_edge_skeleton.svg:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  data/mesh/2d_10_grains.tess\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$< \
  --mesh-format=tess\
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/2d_10_grains_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_svg_animation\
  --output=$@

.PHONY: svg_mesh svg_mesh_clean svg_mesh_distclean

svg_mesh: $(_svg_mesh)

svg_mesh_clean:
	-$(RM) $(_svg_mesh)

svg_mesh_distclean:
	-$(RM) -r build/$(MODE)/svg/mesh
