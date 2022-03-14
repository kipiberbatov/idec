.PHONY: demo_mesh
demo_mesh: bin demo_mesh_brick_regular

DEMO_MESH_BRICK_REGULAR :=\
  demo_mesh_brick_regular_2d\
  demo_mesh_brick_regular_3d\
  demo_mesh_brick_regular_4d\

.PHONY: demo_mesh_brick_regular
demo_mesh_brick_regular: $(DEMO_MESH_BRICK_REGULAR)

# d = 2
DEMO_MESH_BRICK_REGULAR_2D :=\
  demo_mesh_brick_regular_2d_1\
  demo_mesh_brick_regular_2d_2\
  demo_mesh_brick_regular_2d_4\
  demo_mesh_brick_regular_2d_10\

.PHONY: demo_mesh_brick_regular_2d
demo_mesh_brick_regular_2d: $(DEMO_MESH_BRICK_REGULAR_2D)
	
# d = 2, n = 1
DEMO_MESH_BRICK_REGULAR_2D_1 := \
  demo/mesh/mesh_brick_2d_1.txt\
  demo/mesh/mesh_brick_2d_1_vol.txt\
  demo/mesh/mesh_brick_2d_1_forman.txt\
  demo/mesh/mesh_brick_2d_1_forman_vol.txt\
  demo/mesh/mesh_brick_2d_1_forman_metric.txt\
  demo/mesh/mesh_brick_2d_1_forman_inner.txt\
  demo/mesh/mesh_brick_2d_1_forman_cbd_star.txt\
  demo/mesh/mesh_brick_2d_1_forman_laplacian.txt\
  demo/mesh/mesh_brick_2d_1_forman_hodge_coeff.txt\
  demo/mesh/mesh_brick_2d_1_forman_hodge.txt\
  demo/mesh/mesh_brick_2d_1_forman_node_curvature.txt\
  demo/mesh/mesh_brick_2d_1_forman_metric_corrected.txt\
  demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt\
  demo/mesh/mesh_brick_2d_1_forman_cbd_star_corrected.txt\
  demo/mesh/mesh_brick_2d_1_forman_laplacian_corrected.txt\
  demo/mesh/mesh_brick_2d_1_forman_hodge_corrected.txt\
  demo/mesh/mesh_brick_2d_1_forman_displacement.txt\
  demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt\
  demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt\
  demo/mesh/mesh_brick_2d_1_forman_elastcity_laplacian_1_1_1.txt\

.PHONY: demo_mesh_brick_regular_2d_1
demo_mesh_brick_regular_2d_1: $(DEMO_MESH_BRICK_REGULAR_2D_1)

demo/mesh/mesh_brick_2d_1.txt:\
	  bin/mesh_brick_regular$(.EXE)
	$< 2 1 > $@

demo/mesh/mesh_brick_2d_1_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_1.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman.txt:\
	  bin/forman_bd$(.EXE)\
	  demo/mesh/mesh_brick_2d_1.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_vol.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_1_forman_inner.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_1_forman_metric.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_1_forman_cbd_star.txt:\
	  bin/mesh_qc_cbd_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_inner.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_1_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_cbd_star.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_1_forman_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_hodge.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_inner.txt\
	  demo/mesh/mesh_brick_2d_1_forman_hodge_coeff.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_1_forman_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_1_forman_node_curvature.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_1_forman_metric_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_1_forman_cbd_star_corrected.txt:\
	  bin/mesh_qc_cbd_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_1_forman_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_cbd_star_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_1_forman_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt\
	  demo/mesh/mesh_brick_2d_1_forman_hodge_coeff.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_1_forman_displacement.txt:\
	  bin/mesh_displacement$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt:\
	  bin/mesh_qc_elasticity_cbd_star_1\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< 1 1 < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt:\
	  bin/mesh_qc_elasticity_cbd_star_2\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< 1 < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_1_forman_elastcity_laplacian_1_1_1.txt:\
	  bin/mesh_qc_laplacian\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt\
	  demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< 1 < tmp.txt > $@
	rm tmp.txt

# d = 2, n = 2
DEMO_MESH_BRICK_REGULAR_2D_2 := \
  demo/mesh/mesh_brick_2d_2.txt\
  demo/mesh/mesh_brick_2d_2_vol.txt\
  demo/mesh/mesh_brick_2d_2_forman.txt\
  demo/mesh/mesh_brick_2d_2_forman_bd.txt\
  demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  demo/mesh/mesh_brick_2d_2_forman_metric.txt\
  demo/mesh/mesh_brick_2d_2_forman_inner.txt\
  demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  demo/mesh/mesh_brick_2d_2_forman_laplacian.txt\
  demo/mesh/mesh_brick_2d_2_forman_hodge_coeff.txt\
  demo/mesh/mesh_brick_2d_2_forman_hodge.txt\
  demo/mesh/mesh_brick_2d_2_forman_node_curvature.txt\
  demo/mesh/mesh_brick_2d_2_forman_metric_corrected.txt\
  demo/mesh/mesh_brick_2d_2_forman_inner_corrected.txt\
  demo/mesh/mesh_brick_2d_2_forman_cbd_star_corrected.txt\
  demo/mesh/mesh_brick_2d_2_forman_laplacian_corrected.txt\
  demo/mesh/mesh_brick_2d_2_forman_laplacian_corrected_matrix_form.txt\
  demo/mesh/mesh_brick_2d_2_forman_hodge_corrected.txt\
  demo/mesh/mesh_brick_2d_2_forman_hodge_corrected_matrix_form.txt\
  demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected.txt\
  demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected_matrix_form.txt\
  demo/mesh/mesh_brick_2d_2_forman_hodge_laplacian_corrected.txt\

.PHONY: demo_mesh_brick_regular_2d_2
demo_mesh_brick_regular_2d_2: $(DEMO_MESH_BRICK_REGULAR_2D_2)

demo/mesh/mesh_brick_2d_2.txt:\
	  bin/mesh_brick_regular$(.EXE)
	$< 2 2 > $@

demo/mesh/mesh_brick_2d_2_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_2.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman.txt:\
	  bin/forman_bd$(.EXE)\
	  demo/mesh/mesh_brick_2d_2.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_bd.txt:\
	  bin/mesh_bd$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt
	$< --raw < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_cbd.txt:\
	  bin/mesh_cbd$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt
	$< --raw < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_vol.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_2_forman_inner.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_2_forman_metric.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt:\
	  bin/mesh_qc_cbd_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_inner.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_2_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_2_forman_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_hodge.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_inner.txt\
	  demo/mesh/mesh_brick_2d_2_forman_hodge_coeff.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_2_forman_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_2_forman_node_curvature.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_2_forman_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_2_forman_metric_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_2_forman_cbd_star_corrected.txt:\
	  bin/mesh_qc_cbd_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_inner_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_2_forman_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_cbd_star_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_2_forman_laplacian_corrected_matrix_form.txt:\
	  bin/cs_fprint$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman_laplacian_corrected.txt
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_inner_corrected.txt\
	  demo/mesh/mesh_brick_2d_2_forman_hodge_coeff.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_2_forman_hodge_corrected_matrix_form.txt:\
	  bin/cs_fprint$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman_hodge_corrected.txt
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected.txt:\
	  bin/mesh_qc_hodge_codifferential$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_hodge_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected_matrix_form.txt:\
	  bin/cs_fprint$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected.txt
	$< --matrix-form-curly -list 2 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_hodge_laplacian_corrected.txt:\
	  bin/cs_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
	  demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< --raw -list 2 < tmp.txt > $@
	rm tmp.txt

# demo/mesh/mesh_brick_2d_2_forman_hodge_laplacian_corrected.txt:\
# 	  bin/mesh_qc_laplacian$(.EXE)\
# 	  demo/mesh/mesh_brick_2d_2_forman.txt\
# 	  demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected.txt
# 	cat $(wordlist 2, $(words $^), $^) > tmp.txt
# 	$< < tmp.txt > $@
# 	rm tmp.txt
#
# demo/mesh/mesh_brick_2d_2_forman_hodge_laplacian_corrected_matrix_form.txt:\
# 	  bin/cs_fprint$(.EXE)\
# 	  demo/mesh/mesh_brick_2d_2_forman_hodge_laplacian_corrected.txt
# 	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

# d = 2, n = 4
DEMO_MESH_BRICK_REGULAR_2D_4 := \
  demo/mesh/mesh_brick_2d_4.txt\
  demo/mesh/mesh_brick_2d_4_bd.txt\
  demo/mesh/mesh_brick_2d_4_cbd.txt\
  demo/mesh/mesh_brick_2d_4_vol.txt\
  demo/mesh/mesh_brick_2d_4_node_curvature.txt\
  demo/mesh/mesh_brick_2d_4_metric_corrected.txt\
  demo/mesh/mesh_brick_2d_4_inner_corrected.txt\
  demo/mesh/mesh_brick_2d_4_cbd_star_corrected.txt\
  demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt\
  demo/mesh/mesh_brick_2d_4_laplacian_corrected_matrix_form.txt\
  demo/mesh/mesh_brick_2d_4_laplacian_corrected_mathematica_sparse.txt\
  demo/mesh/mesh_brick_2d_4_hodge_coeff.txt\
  demo/mesh/mesh_brick_2d_4_hodge_corrected.txt\
  demo/mesh/mesh_brick_2d_4_hodge_corrected_matrix_form.txt\
  demo/mesh/mesh_brick_2d_4_hodge_corrected_mathematica_sparse.txt\
  demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected.txt\
  demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected_matrix_form.txt\
  demo/mesh/mesh_brick_2d_4_hodge_laplacian_corrected.txt\
  demo/mesh/mesh_brick_2d_4_diffusion.txt\
  # demo/mesh/mesh_brick_2d_4_hodge_laplacian_corrected.txt
  # demo/mesh/mesh_brick_2d_4_hodge_laplacian_0_corrected.txt
  # demo/mesh/mesh_brick_2d_4_hodge_laplacian_corrected_matrix_form.txt

.PHONY: demo_mesh_brick_regular_2d_4
demo_mesh_brick_regular_2d_4: $(DEMO_MESH_BRICK_REGULAR_2D_4)

demo/mesh/mesh_brick_2d_4.txt:\
	  bin/mesh_brick_regular$(.EXE)
	$< 2 4 > $@

demo/mesh/mesh_brick_2d_4_bd.txt:\
	  bin/mesh_bd$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt
	$< --raw < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_cbd.txt:\
	  bin/mesh_cbd$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt
	$< --raw < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_vol.txt\
	  demo/mesh/mesh_brick_2d_4_node_curvature.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

# demo/mesh/mesh_brick_2d_4_metric_corrected.txt:\
# 	  bin/mesh_qc_metric$(.EXE)\
# 	  demo/mesh/mesh_brick_2d_4.txt\
# 	  demo/mesh/mesh_brick_2d_4_vol.txt
# 	cat $(wordlist 2, $(words $^), $^) > tmp.txt
# 	$< < tmp.txt > $@
# 	rm tmp.txt

demo/mesh/mesh_brick_2d_4_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_vol.txt\
	  demo/mesh/mesh_brick_2d_4_metric_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_4_cbd_star_corrected.txt:\
	  bin/mesh_qc_cbd_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_inner_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_cbd_star_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_4_laplacian_corrected_matrix_form.txt:\
	  bin/cs_fprint$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_laplacian_corrected_mathematica_sparse.txt:\
	  bin/cs_fprint$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt
	$< --mathematica-sparse -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_inner_corrected.txt\
	  demo/mesh/mesh_brick_2d_4_hodge_coeff.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_4_hodge_corrected_matrix_form.txt:\
	  bin/cs_fprint$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_hodge_corrected.txt
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_hodge_corrected_mathematica_sparse.txt:\
	  bin/cs_fprint$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_hodge_corrected.txt
	$< --mathematica-sparse -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected.txt:\
	  bin/mesh_qc_hodge_codifferential$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_hodge_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected_matrix_form.txt:\
	  bin/cs_fprint$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected.txt
	$< --matrix-form-curly -list 2 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_hodge_laplacian_corrected.txt:\
	  bin/cs_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_cbd.txt\
	  demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< --raw -list 2 < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_4_diffusion.txt:\
	  bin/cs_diffusion$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt\
	  demo/mesh/mesh_brick_2d_4_node_curvature.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< 2 5 0.1 < tmp.txt > $@
	rm tmp.txt

# demo/mesh/mesh_brick_2d_4_hodge_laplacian_0_corrected.txt:\
# 	  bin/cs_multiply$(.EXE)\
# 	  demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected.txt\
# 	  demo/mesh/mesh_brick_2d_4_cbd.txt
# 	cat $(wordlist 2, $(words $^), $^) > tmp.txt
# 	$< --raw -list 2 < tmp.txt > $@
# 	rm tmp.txt
#
# demo/mesh/mesh_brick_2d_4_hodge_laplacian_corrected.txt:\
# 	  bin/mesh_qc_laplacian$(.EXE)\
# 	  demo/mesh/mesh_brick_2d_4.txt\
# 	  demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected.txt
# 	cat $(wordlist 2, $(words $^), $^) > tmp.txt
# 	$< < tmp.txt > $@
# 	rm tmp.txt
#
# demo/mesh/mesh_brick_2d_4_hodge_laplacian_corrected_matrix_form.txt:\
# 	  bin/cs_fprint$(.EXE)\
# 	  demo/mesh/mesh_brick_2d_4_hodge_laplacian_corrected.txt
# 	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

# d = 2, n = 10
DEMO_MESH_BRICK_REGULAR_2D_10 := \
  demo/mesh/mesh_brick_2d_10.txt\
  demo/mesh/mesh_brick_2d_10_vol.txt\
  demo/mesh/mesh_brick_2d_10_forman.txt\
  demo/mesh/mesh_brick_2d_10_forman_vol.txt\
  demo/mesh/mesh_brick_2d_10_forman_metric.txt\
  demo/mesh/mesh_brick_2d_10_forman_inner.txt\
  demo/mesh/mesh_brick_2d_10_forman_cbd_star.txt\
  demo/mesh/mesh_brick_2d_10_forman_laplacian.txt\
  demo/mesh/mesh_brick_2d_10_forman_bd_layer_0_1_nodes.txt\
  demo/mesh/mesh_brick_2d_10_forman_laplacian_0_interior.txt\
  demo/mesh/mesh_brick_2d_10_forman_hodge_coeff.txt\
  demo/mesh/mesh_brick_2d_10_forman_hodge.txt\
  demo/mesh/mesh_brick_2d_10_forman_node_curvature.txt\
  demo/mesh/mesh_brick_2d_10_forman_metric_corrected.txt\
  demo/mesh/mesh_brick_2d_10_forman_inner_corrected.txt\
  demo/mesh/mesh_brick_2d_10_forman_cbd_star_corrected.txt\
  demo/mesh/mesh_brick_2d_10_forman_laplacian_corrected.txt\
  demo/mesh/mesh_brick_2d_10_forman_hodge_corrected.txt\

.PHONY: demo_mesh_brick_regular_2d_10
demo_mesh_brick_regular_2d_10: $(DEMO_MESH_BRICK_REGULAR_2D_10)

demo/mesh/mesh_brick_2d_10.txt:\
	  bin/mesh_brick_regular$(.EXE)
	$< 2 10 > $@

demo/mesh/mesh_brick_2d_10_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_10.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_10_forman.txt:\
	  bin/forman_bd$(.EXE)\
	  demo/mesh/mesh_brick_2d_10.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_10_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_10_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_vol.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_10_forman_inner.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_10_forman_metric.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_10_forman_cbd_star.txt:\
	  bin/mesh_qc_cbd_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_inner.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_10_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_cbd_star.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_10_forman_bd_layer_0_1_nodes.txt:\
	  bin/mesh_qc_bd_layer$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt
	$< < $(word 2, $^) > $@
	
demo/mesh/mesh_brick_2d_10_forman_laplacian_0_interior.txt:\
	  bin/mesh_qc_laplacian_0_interior$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman_bd_layer_0_1_nodes.txt\
	  demo/mesh/mesh_brick_2d_10_forman_laplacian.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_10_forman_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_10_forman_hodge.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_inner.txt\
	  demo/mesh/mesh_brick_2d_10_forman_hodge_coeff.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_10_forman_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_10_forman_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_10_forman_node_curvature.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_10_forman_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_10_forman_metric_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_10_forman_cbd_star_corrected.txt:\
	  bin/mesh_qc_cbd_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_inner_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_10_forman_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_cbd_star_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_2d_10_forman_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_inner_corrected.txt\
	  demo/mesh/mesh_brick_2d_10_forman_hodge_coeff.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

DEMO_MESH_BRICK_REGULAR_2 :=\
  $(DEMO_MESH_BRICK_REGULAR_2D_1)\
  $(DEMO_MESH_BRICK_REGULAR_2D_2)\
  $(DEMO_MESH_BRICK_REGULAR_2D_4)\
  $(DEMO_MESH_BRICK_REGULAR_2D_10)\

# d = 3
DEMO_MESH_BRICK_REGULAR_3D :=\
  demo_mesh_brick_regular_3d_1\
  demo_mesh_brick_regular_3d_2\
  demo_mesh_brick_regular_3d_5\

.PHONY: demo_mesh_brick_regular_3d
demo_mesh_brick_regular_3d: $(DEMO_MESH_BRICK_REGULAR_3D)

# d = 3, n = 1
DEMO_MESH_BRICK_REGULAR_3D_1 := \
  demo/mesh/mesh_brick_3d_1.txt\
  demo/mesh/mesh_brick_3d_1_vol.txt\
  demo/mesh/mesh_brick_3d_1_forman.txt\
  demo/mesh/mesh_brick_3d_1_forman_vol.txt\
  demo/mesh/mesh_brick_3d_1_forman_metric.txt\
  demo/mesh/mesh_brick_3d_1_forman_inner.txt\
  demo/mesh/mesh_brick_3d_1_forman_cbd_star.txt\
  demo/mesh/mesh_brick_3d_1_forman_laplacian.txt\
  demo/mesh/mesh_brick_3d_1_forman_hodge_coeff.txt\
  demo/mesh/mesh_brick_3d_1_forman_hodge.txt\
  demo/mesh/mesh_brick_3d_1_forman_node_curvature.txt\
  demo/mesh/mesh_brick_3d_1_forman_metric_corrected.txt\
  demo/mesh/mesh_brick_3d_1_forman_inner_corrected.txt\
  demo/mesh/mesh_brick_3d_1_forman_cbd_star_corrected.txt\
  demo/mesh/mesh_brick_3d_1_forman_laplacian_corrected.txt\
  demo/mesh/mesh_brick_3d_1_forman_hodge_corrected.txt\

.PHONY: demo_mesh_brick_regular_3d_1
demo_mesh_brick_regular_3d_1: $(DEMO_MESH_BRICK_REGULAR_3D_1)

demo/mesh/mesh_brick_3d_1.txt:\
	  bin/mesh_brick_regular$(.EXE)
	$< 3 1 > $@

demo/mesh/mesh_brick_3d_1_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_3d_1.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_1_forman.txt:\
	  bin/forman_bd$(.EXE)\
	  demo/mesh/mesh_brick_3d_1.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_1_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_1_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_vol.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_1_forman_inner.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_1_forman_metric.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_1_forman_cbd_star.txt:\
	  bin/mesh_qc_cbd_star$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_inner.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_1_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_cbd_star.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_1_forman_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_1_forman_hodge.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_inner.txt\
	  demo/mesh/mesh_brick_3d_1_forman_hodge_coeff.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_1_forman_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_1_forman_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_1_forman_node_curvature.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_1_forman_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_1_forman_metric_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_1_forman_cbd_star_corrected.txt:\
	  bin/mesh_qc_cbd_star$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_inner_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_1_forman_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_cbd_star_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_1_forman_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_inner_corrected.txt\
	  demo/mesh/mesh_brick_3d_1_forman_hodge_coeff.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

# d = 3, n = 2
DEMO_MESH_BRICK_REGULAR_3D_2 := \
  demo/mesh/mesh_brick_3d_2.txt\
  demo/mesh/mesh_brick_3d_2_vol.txt\
  demo/mesh/mesh_brick_3d_2_forman.txt\
  demo/mesh/mesh_brick_3d_2_forman_vol.txt\
  demo/mesh/mesh_brick_3d_2_forman_metric.txt\
  demo/mesh/mesh_brick_3d_2_forman_inner.txt\
  demo/mesh/mesh_brick_3d_2_forman_cbd_star.txt\
  demo/mesh/mesh_brick_3d_2_forman_laplacian.txt\
  demo/mesh/mesh_brick_3d_2_forman_hodge_coeff.txt\
  demo/mesh/mesh_brick_3d_2_forman_hodge.txt\
  demo/mesh/mesh_brick_3d_2_forman_node_curvature.txt\
  demo/mesh/mesh_brick_3d_2_forman_metric_corrected.txt\
  demo/mesh/mesh_brick_3d_2_forman_inner_corrected.txt\
  demo/mesh/mesh_brick_3d_2_forman_cbd_star_corrected.txt\
  demo/mesh/mesh_brick_3d_2_forman_laplacian_corrected.txt\
  demo/mesh/mesh_brick_3d_2_forman_hodge_corrected.txt\

.PHONY: demo_mesh_brick_regular_3d_2
demo_mesh_brick_regular_3d_2: $(DEMO_MESH_BRICK_REGULAR_3D_2)

demo/mesh/mesh_brick_3d_2.txt:\
	  bin/mesh_brick_regular$(.EXE)
	$< 3 2 > $@

demo/mesh/mesh_brick_3d_2_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_3d_2.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_2_forman.txt:\
	  bin/forman_bd$(.EXE)\
	  demo/mesh/mesh_brick_3d_2.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_2_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_2_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_vol.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_2_forman_inner.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_2_forman_metric.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_2_forman_cbd_star.txt:\
	  bin/mesh_qc_cbd_star$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_inner.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_2_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_cbd_star.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_2_forman_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_2_forman_hodge.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_inner.txt\
	  demo/mesh/mesh_brick_3d_2_forman_hodge_coeff.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_2_forman_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_2_forman_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_2_forman_node_curvature.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_2_forman_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_2_forman_metric_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_2_forman_cbd_star_corrected.txt:\
	  bin/mesh_qc_cbd_star$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_inner_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_2_forman_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_cbd_star_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_2_forman_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_inner_corrected.txt\
	  demo/mesh/mesh_brick_3d_2_forman_hodge_coeff.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

# d = 3, n = 5
DEMO_MESH_BRICK_REGULAR_3D_5 := \
  demo/mesh/mesh_brick_3d_5.txt\
  demo/mesh/mesh_brick_3d_5_vol.txt\
  demo/mesh/mesh_brick_3d_5_forman.txt\
  demo/mesh/mesh_brick_3d_5_forman_vol.txt\
  demo/mesh/mesh_brick_3d_5_forman_metric.txt\
  demo/mesh/mesh_brick_3d_5_forman_inner.txt\
  demo/mesh/mesh_brick_3d_5_forman_cbd_star.txt\
  demo/mesh/mesh_brick_3d_5_forman_laplacian.txt\
  demo/mesh/mesh_brick_3d_5_forman_hodge_coeff.txt\
  demo/mesh/mesh_brick_3d_5_forman_hodge.txt\
  demo/mesh/mesh_brick_3d_5_forman_node_curvature.txt\
  demo/mesh/mesh_brick_3d_5_forman_metric_corrected.txt\
  demo/mesh/mesh_brick_3d_5_forman_inner_corrected.txt\
  demo/mesh/mesh_brick_3d_5_forman_cbd_star_corrected.txt\
  demo/mesh/mesh_brick_3d_5_forman_laplacian_corrected.txt\
  demo/mesh/mesh_brick_3d_5_forman_hodge_corrected.txt\

.PHONY: demo_mesh_brick_regular_3d_5
demo_mesh_brick_regular_3d_5: $(DEMO_MESH_BRICK_REGULAR_3D_5)

demo/mesh/mesh_brick_3d_5.txt:\
	  bin/mesh_brick_regular$(.EXE)
	$< 3 5 > $@

demo/mesh/mesh_brick_3d_5_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_3d_5.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_5_forman.txt:\
	  bin/forman_bd$(.EXE)\
	  demo/mesh/mesh_brick_3d_5.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_5_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_5_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_vol.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_5_forman_inner.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_5_forman_metric.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_5_forman_cbd_star.txt:\
	  bin/mesh_qc_cbd_star$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_inner.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_5_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_cbd_star.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_5_forman_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_5_forman_hodge.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_inner.txt\
	  demo/mesh/mesh_brick_3d_5_forman_hodge_coeff.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_5_forman_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_5_forman_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_5_forman_node_curvature.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_5_forman_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_5_forman_metric_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_5_forman_cbd_star_corrected.txt:\
	  bin/mesh_qc_cbd_star$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_inner_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_5_forman_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_cbd_star_corrected.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

demo/mesh/mesh_brick_3d_5_forman_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_inner_corrected.txt\
	  demo/mesh/mesh_brick_3d_5_forman_hodge_coeff.txt
	cat $(wordlist 2, $(words $^), $^) > tmp.txt
	$< < tmp.txt > $@
	rm tmp.txt

DEMO_MESH_BRICK_REGULAR_3 :=\
  $(DEMO_MESH_BRICK_REGULAR_3D_1)\
  $(DEMO_MESH_BRICK_REGULAR_3D_2)\
  $(DEMO_MESH_BRICK_REGULAR_3D_5)\

# d = 4
DEMO_MESH_BRICK_REGULAR_4D := demo_mesh_brick_regular_4d_2

.PHONY: demo_mesh_brick_regular_4d
demo_mesh_brick_regular_4d: $(DEMO_MESH_BRICK_REGULAR_4D)

# d = 4, n = 2
DEMO_MESH_BRICK_REGULAR_4D_2 := \
  demo/mesh/mesh_brick_4d_2.txt\
  # demo/mesh/mesh_brick_4d_2_forman.txt

.PHONY: demo_mesh_brick_regular_4d_2
demo_mesh_brick_regular_4d_2: $(DEMO_MESH_BRICK_REGULAR_4D_2)\
	# demo/mesh/mesh_brick_4d_2_forman_vol.txt\
	# demo/mesh/mesh_brick_4d_2_forman_metric.txt\
	# demo/mesh/mesh_brick_4d_2_forman_inner.txt\
	# demo/mesh/mesh_brick_4d_2_forman_cbd_star.txt\
	# demo/mesh/mesh_brick_4d_2_forman_laplacian.txt

demo/mesh/mesh_brick_4d_2.txt:
	bin/mesh_brick_regular$(.EXE) 4 2 > $@

# demo/mesh/mesh_brick_4d_2_forman.txt:\
# 	  bin/forman_bd$(.EXE)\
# 	  demo/mesh/mesh_brick_4d_2.txt
# 	$< < $(word 2, $^) > $@

# demo/mesh/mesh_brick_4d_2_forman_vol.txt:\
# 	  demo/mesh/mesh_brick_4d_2_forman.txt
# 	bin/mesh_qc_vol$(.EXE) < $< > $@
#
# demo/mesh/mesh_brick_4d_2_forman_metric.txt:\
# 	  demo/mesh/mesh_brick_4d_2_forman.txt\
# 	  demo/mesh/mesh_brick_4d_2_forman_vol.txt
# 	cat $^ > tmp.txt
# 	bin/mesh_qc_metric$(.EXE) < tmp.txt > $@
# 	rm tmp.txt
#
# demo/mesh/mesh_brick_4d_2_forman_inner.txt:\
# 	  demo/mesh/mesh_brick_4d_2_forman.txt\
# 	  demo/mesh/mesh_brick_4d_2_forman_vol.txt\
# 	  demo/mesh/mesh_brick_4d_2_forman_metric.txt
# 	cat $^ > tmp.txt
# 	bin/mesh_qc_inner$(.EXE) < tmp.txt > $@
# 	rm tmp.txt
#
# demo/mesh/mesh_brick_4d_2_forman_cbd_star.txt:\
# 	  demo/mesh/mesh_brick_4d_2_forman.txt\
# 	  demo/mesh/mesh_brick_4d_2_forman_inner.txt
# 	cat $^ > tmp.txt
# 	bin/mesh_qc_cbd_star$(.EXE) < tmp.txt > $@
# 	rm tmp.txt
#
# demo/mesh/mesh_brick_4d_2_forman_laplacian.txt:\
# 	  demo/mesh/mesh_brick_4d_2_forman.txt\
# 	  demo/mesh/mesh_brick_4d_2_forman_cbd_star.txt
# 	cat $^ > tmp.txt
# 	bin/mesh_qc_laplacian$(.EXE) < tmp.txt > $@
# 	rm tmp.txt

DEMO_MESH_BRICK_REGULAR_4 := $(DEMO_MESH_BRICK_REGULAR_4D_2)

DEMO_MESH_BRICK_REGULAR_ALL :=\
  $(DEMO_MESH_BRICK_REGULAR_2)\
  $(DEMO_MESH_BRICK_REGULAR_3)\
  $(DEMO_MESH_BRICK_REGULAR_4)\

.PHONY: demo_mesh_clean
demo_mesh_clean:
	-$(RM) $(DEMO_MESH_BRICK_REGULAR_ALL)