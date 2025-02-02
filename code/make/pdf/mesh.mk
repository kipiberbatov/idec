build/$(MODE)/pdf/mesh: | build/$(MODE)/pdf
	mkdir -p $@

_pdf_mesh :=\
  build/$(MODE)/pdf/mesh/brick_2d_10_edge_skeleton.pdf\
  build/$(MODE)/pdf/mesh/brick_2d_10_forman_edge_skeleton.pdf\
  build/$(MODE)/pdf/mesh/circular_4_3_edge_skeleton.pdf\
  build/$(MODE)/pdf/mesh/circular_4_3_forman_edge_skeleton.pdf\
  build/$(MODE)/pdf/mesh/circular_18_10_edge_skeleton.pdf\
  build/$(MODE)/pdf/mesh/circular_18_10_forman_edge_skeleton.pdf\
  build/$(MODE)/pdf/mesh/pentagon_edge_skeleton.pdf\
  build/$(MODE)/pdf/mesh/pentagon_forman_edge_skeleton.pdf\
  build/$(MODE)/pdf/mesh/2d_10_grains_edge_skeleton.pdf\
  build/$(MODE)/pdf/mesh/2d_10_grains_forman_edge_skeleton.pdf\

build/$(MODE)/pdf/mesh/brick_2d_10_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/mesh/brick_2d_10_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/mesh/circular_4_3_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/mesh/circular_4_3_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/mesh/circular_18_10_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/mesh/circular_18_10_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/mesh/pentagon_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  data/mesh/pentagon.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/mesh/pentagon_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/mesh/2d_10_grains_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  data/mesh/2d_10_grains.tess\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh-format=tess\
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/mesh/2d_10_grains_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

.PHONY: pdf_mesh pdf_mesh_clean pdf_mesh_distclean

pdf_mesh: $(_pdf_mesh)

pdf_mesh_clean:
	-$(RM) $(_pdf_mesh)

pdf_mesh_distclean:
	-$(RM) -r build/$(MODE)/pdf/mesh
