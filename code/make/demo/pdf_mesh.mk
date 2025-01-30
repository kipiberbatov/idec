build/$(MODE)/demo/pdf/mesh: | build/$(MODE)/demo/pdf
	mkdir -p $@

_demo_pdf_mesh :=\
  build/$(MODE)/demo/pdf/mesh/brick_2d_10_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/brick_2d_10_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/circular_4_3_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/circular_4_3_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/circular_18_10_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/circular_18_10_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/pentagon_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/pentagon_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/2d_10_grains_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/2d_10_grains_forman_edge_skeleton.pdf\

build/$(MODE)/demo/pdf/mesh/brick_2d_10_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_10.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/mesh/brick_2d_10_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/mesh/circular_4_3_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/mesh/circular_4_3_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/mesh/circular_18_10_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/circular_18_10.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/mesh/circular_18_10_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/circular_18_10_forman.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/mesh/pentagon_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  data/mesh/pentagon.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/mesh/pentagon_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/pentagon_forman.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/mesh/2d_10_grains_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  data/mesh/2d_10_grains.tess\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/mesh\
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

build/$(MODE)/demo/pdf/mesh/2d_10_grains_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/mesh\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

.PHONY: demo_pdf_mesh demo_pdf_mesh_clean demo_pdf_mesh_distclean

demo_pdf_mesh: $(_demo_pdf_mesh)

demo_pdf_mesh_clean:
	-$(RM) $(_demo_pdf_mesh)

demo_pdf_mesh_distclean:
	-$(RM) -r build/$(MODE)/demo/pdf/mesh
