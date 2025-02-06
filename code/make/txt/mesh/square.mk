.PHONY: txt_mesh_square txt_mesh_square_clean

_txt_mesh_square := \
  build/$(MODE)/txt/mesh/square_2.txt\
  build/$(MODE)/txt/mesh/square_4.txt\
  build/$(MODE)/txt/mesh/square_8.txt\
  build/$(MODE)/txt/mesh/square_8_cbd.txt\
  build/$(MODE)/txt/mesh/square_8_vol.txt\
  build/$(MODE)/txt/mesh/square_8_inner.txt\
  build/$(MODE)/txt/mesh/square_8_cbd_star.txt\
  build/$(MODE)/txt/mesh/square_8_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/square_8_hodge.txt\

build/$(MODE)/txt/mesh/square_2.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  data/mesh/square.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/square_4.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/square_2.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/square_8.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/square_4.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/square_8_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/square_8.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/square_8_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/square_8.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/square_8_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/square_8.txt\
  build/$(MODE)/txt/mesh/square_8_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/square_8_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/square_8.txt\
  build/$(MODE)/txt/mesh/square_8_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/square_8_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/square_8.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/square_8_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/square_8.txt\
  build/$(MODE)/txt/mesh/square_8_inner.txt\
  build/$(MODE)/txt/mesh/square_8_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

txt_mesh_square: $(_txt_mesh_square)

txt_mesh_square_clean:
	-$(RM) $(_txt_mesh_square)
