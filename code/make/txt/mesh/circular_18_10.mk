.PHONY: txt_mesh_circular_18_10 txt_mesh_circular_18_10_clean

_txt_mesh_circular_18_10 :=\
  build/$(MODE)/txt/mesh/circular_18_10.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_cbd.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_vol.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_inner.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_hodge.txt\

build/$(MODE)/txt/mesh/circular_18_10.txt:\
  build/$(MODE)/bin/mesh_circular$(.EXE) | build/$(MODE)/txt/mesh
	$< 4 3 > $@

build/$(MODE)/txt/mesh/circular_18_10_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --circular --raw > $@

build/$(MODE)/txt/mesh/circular_18_10_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/circular_18_10_forman_vol.txt:\
  build/$(MODE)/bin/mesh_measures$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  | build/$(MODE)/txt/mesh
	$<\
  --mesh=$(word 2, $^)\
  --mesh-measures-function=circular-forman\
  > $@

build/$(MODE)/txt/mesh/circular_18_10_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/circular_18_10_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/circular_18_10_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/circular_18_10_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_inner.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

txt_mesh_circular_18_10: $(_txt_mesh_circular_18_10)

txt_mesh_circular_18_10_clean:
	-$(RM) $(_txt_mesh_circular_18_10)
