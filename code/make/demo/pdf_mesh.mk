build/$(MODE)/demo/pdf/mesh: | build/$(MODE)/demo/pdf
	mkdir -p $@

_demo_pdf_mesh :=\
  build/$(MODE)/demo/pdf/mesh/circular_4_3_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/circular_4_3_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/circular_17_10_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/circular_17_10_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/pentagon_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/pentagon_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/brick_2d_1_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/brick_2d_10_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/2d_10_grains_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/2d_10_grains_forman_edge_skeleton.pdf\

build/$(MODE)/demo/pdf/mesh/circular_4_3_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_4_3.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/circular_4_3_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_4_3_forman.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/circular_17_10_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_17_10.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/circular_17_10_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_17_10_forman.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/pentagon_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  data/mesh/mesh_pentagon.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/pentagon_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_pentagon_forman.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/brick_2d_1_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/brick_2d_10_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/2d_10_grains_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  data/mesh/mesh_2d_10_grains.tess\
  | build/$(MODE)/demo/pdf/mesh
	$< --tess $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/2d_10_grains_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@	

.PHONY: demo_pdf_mesh demo_pdf_mesh_clean demo_pdf_mesh_distclean

demo_pdf_mesh: $(_demo_pdf_mesh)

demo_pdf_mesh_clean:
	-$(RM) $(_demo_pdf_mesh)

demo_pdf_mesh_distclean:
	-$(RM) -r build/$(MODE)/demo/pdf/mesh