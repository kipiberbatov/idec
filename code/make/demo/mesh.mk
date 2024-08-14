.PHONY: demo_mesh
demo_mesh:\
  bin_mesh\
  demo_mesh_brick_regular\
  demo_mesh_square\
  demo_mesh_two_triangles\
  demo_mesh_triangle_and_square\
  demo_mesh_pentagon\
  demo_mesh_2d_10_grains\
  demo_mesh_square_pyramid\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh: | build/$(BUILD_MODE)/demo
	mkdir -p $@

_demo_mesh_brick_regular :=\
  demo_mesh_brick_regular_2d\
  demo_mesh_brick_regular_3d\
  demo_mesh_brick_regular_4d\

.PHONY: demo_mesh_brick_regular
demo_mesh_brick_regular: $(_demo_mesh_brick_regular)\
  | build/$(BUILD_MODE)/demo/mesh

# d = 2
_demo_mesh_brick_regular_2d :=\
  demo_mesh_brick_regular_2d_1\
  demo_mesh_brick_regular_2d_2\
  demo_mesh_brick_regular_2d_4\
  demo_mesh_brick_regular_2d_5\
  demo_mesh_brick_regular_2d_10\

.PHONY: demo_mesh_brick_regular_2d
demo_mesh_brick_regular_2d: $(_demo_mesh_brick_regular_2d)\
  | build/$(BUILD_MODE)/demo/mesh
	
# d = 2, n = 1
_demo_mesh_brick_regular_2d_1 := \
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_boundary.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_metric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_cbd_star.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_laplacian.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_laplacian_matrix_form.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_coeff.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_matrix_form.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_codifferential.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_codifferential_matrix_form.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_laplacian.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_laplacian_matrix_form.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_node_curvature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_metric_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_cbd_star_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_displacement.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt\
  # build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_elastcity_laplacian_1_1_1.txt\

.PHONY: demo_mesh_brick_regular_2d_1
demo_mesh_brick_regular_2d_1: $(_demo_mesh_brick_regular_2d_1)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 2 1 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_boundary.txt:\
  build/$(BUILD_MODE)/bin/mesh_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_cbd.txt:\
  build/$(BUILD_MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_metric.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_inner.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_cbd_star.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_inner.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_laplacian.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_cbd_star.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_laplacian_matrix_form.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_laplacian.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_coeff.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_matrix_form.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_codifferential.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_codifferential$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_codifferential_matrix_form.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_codifferential.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --matrix-form-curly -list 2 < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_laplacian.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_codifferential.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< 2 --raw $(word 2, $^) --raw $(word 3, $^) --raw > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_laplacian_matrix_form.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_laplacian.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_node_curvature.txt:\
  build/$(BUILD_MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_metric_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_node_curvature.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_metric_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_cbd_star_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_laplacian_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_cbd_star_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_displacement.txt:\
  build/$(BUILD_MODE)/bin/mesh_displacement$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_elasticity_coboundary_star_1$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< 1 1 $(wordlist 2, $(words $^), $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_elasticity_coboundary_star_2$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< 1 $(wordlist 2, $(words $^), $^) > $@

# build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_elastcity_laplacian_1_1_1.txt:\
#   build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
#   build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
#   build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt\
#   build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt\
  | build/$(BUILD_MODE)/demo/mesh
# 	$^ > $@

# d = 2, n = 2
_demo_mesh_brick_regular_2d_2 := \
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_boundary_hyperfaces.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_0_cells.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_nodes_dirichlet.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_nodes_neumann.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_normals.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_neighbors.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_vector_matrices.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_coefficients.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_boundary.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_metric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_laplacian.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_neumann_modified_laplacian.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_flux.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p1_temperature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p2_temperature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p4_temperature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_coeff.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_node_curvature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_metric_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_laplacian_corrected_matrix_form.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_corrected_matrix_form.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected_matrix_form.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_laplacian_corrected.txt\

.PHONY: demo_mesh_brick_regular_2d_2
demo_mesh_brick_regular_2d_2: $(_demo_mesh_brick_regular_2d_2)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 2 2 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_boundary_hyperfaces.txt:\
  build/$(BUILD_MODE)/bin/mesh_boundary_hyperfaces$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_0_cells.txt:\
  build/$(BUILD_MODE)/bin/mesh_boundary_lower_subfaces$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_nodes_dirichlet.txt:\
  build/$(BUILD_MODE)/bin/mesh_boundary_nodes_from_constraint_dirichlet$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_nodes_neumann.txt:\
  build/$(BUILD_MODE)/bin/mesh_boundary_nodes_from_constraint_neumann$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_normals.txt:\
  build/$(BUILD_MODE)/bin/mesh_boundary_node_normal$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_neighbors.txt:\
  build/$(BUILD_MODE)/bin/mesh_neighboring_nodes$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_vector_matrices.txt:\
  build/$(BUILD_MODE)/bin/mesh_boundary_node_vectors_matrix$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_coefficients.txt:\
  build/$(BUILD_MODE)/bin/mesh_boundary_neumann_coefficients$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_boundary.txt:\
  build/$(BUILD_MODE)/bin/mesh_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt:\
  build/$(BUILD_MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_metric.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_inner.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_inner.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_laplacian.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_neumann_modified_laplacian.txt:\
  build/$(BUILD_MODE)/bin/diffusion_discrete_set_neumann_rows$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_laplacian.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< --raw $(word 2, $^) --raw $(word 3, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_continuous$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_continuous_p0$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_continuous_p0 0.05 100 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_flux.txt:\
  build/$(BUILD_MODE)/bin/diffusion_discrete_calculate_flux$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.txt\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< $(word 2, $^) 100 $(word 3, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p1_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_continuous$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_continuous_p1$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_continuous_p1 0.05 20 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p2_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_continuous$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_continuous_p2$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_continuous_p2 0.001 100 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p4_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_continuous_to_steady_state$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_continuous_p4$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_continuous_p4 0.001 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_coeff.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_node_curvature.txt:\
  build/$(BUILD_MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_metric_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_node_curvature.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_inner_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_metric_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_laplacian_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_laplacian_corrected_matrix_form.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_laplacian_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_corrected_matrix_form.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_codifferential$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected_matrix_form.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --matrix-form-curly -list 2 < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_laplacian_corrected.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< 2 --raw $(word 2, $^) --raw $(word 3, $^) --raw > $@

# d = 2, n = 4
_demo_mesh_brick_regular_2d_4 := \
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_bd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_node_curvature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_metric_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_cbd_star_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected_matrix_form.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected_mathematica_sparse.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_coeff.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_corrected_matrix_form.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_corrected_mathematica_sparse.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected_matrix_form.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric2.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_bd_nodes.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric_restricted.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplace_equation.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplace_equation_non_grid.txt\

.PHONY: demo_mesh_brick_regular_2d_4
demo_mesh_brick_regular_2d_4: $(_demo_mesh_brick_regular_2d_4)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 2 4 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_bd.txt:\
  build/$(BUILD_MODE)/bin/mesh_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_cbd.txt:\
  build/$(BUILD_MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_node_curvature.txt:\
  build/$(BUILD_MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_metric_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_node_curvature.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_inner_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_metric_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_cbd_star_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_cbd_star_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected_matrix_form.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected_mathematica_sparse.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --mathematica-sparse -list 3 < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_coeff.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_corrected_matrix_form.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_corrected_mathematica_sparse.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --mathematica-sparse -list 3 < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_codifferential$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected_matrix_form.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --matrix-form-curly -list 2 < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_laplacian_corrected.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< 2 --raw $(word 2, $^) --raw $(word 3, $^) --raw > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_laplacian_symmetric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< 2 $(word 2, $^) --raw $(word 3, $^) --raw > $@ --raw

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric2.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_laplacian_symmetric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< 2 $(word 2, $^) --raw $(word 3, $^) --raw > $@ --matrix-form-curly

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_bd_nodes.txt:\
  build/$(BUILD_MODE)/bin/mesh_boundary_nodes$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< $(word 2, $^) --raw > $@ --raw
	
build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric_restricted.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_remove_symmetric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_bd_nodes.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw > $@ --matrix-form-curly

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplace_equation.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplace_equation_solve$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw > $@ --raw

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplace_equation_non_grid.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplace_equation_solve_non_grid$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^) --raw\
	> $@ --raw

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_heat_conduction_non_grid.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_heat_conduction_solve_non_grid$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_4_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^) --raw \
	0.1 10 --raw > $@

_demo_mesh_brick_regular_2d_5 := \
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_metric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_laplacian.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_diffusion_steady_state_continuous_p4_temperature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_boundary_layer_0_1_nodes.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_hodge_coeff.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_hodge.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_node_curvature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_metric_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_hodge_corrected.txt\

.PHONY: demo_mesh_brick_regular_2d_5
demo_mesh_brick_regular_2d_5: $(_demo_mesh_brick_regular_2d_5)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 2 5 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd.txt:\
  build/$(BUILD_MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_metric.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_inner.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_inner.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_laplacian.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_continuous$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_continuous_p2$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_continuous_p2 0.0001 10000 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_continuous$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_continuous_p4$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_continuous_p4 0.0001 10000 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_diffusion_steady_state_continuous_p4_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_steady_state_continuous$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_steady_state_continuous_p4$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_steady_state_continuous_p4 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_boundary_layer_0_1_nodes.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_boundary_layer$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_hodge_coeff.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_hodge.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_node_curvature.txt:\
  build/$(BUILD_MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_metric_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_node_curvature.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_inner_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_metric_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_laplacian_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_hodge_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_5_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

_demo_mesh_brick_regular_2d_10 := \
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_boundary.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_metric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_cbd_star.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_laplacian.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux.txt\

.PHONY: demo_mesh_brick_regular_2d_10
demo_mesh_brick_regular_2d_10: $(_demo_mesh_brick_regular_2d_10)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 2 10 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_boundary.txt:\
  build/$(BUILD_MODE)/bin/mesh_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_cbd.txt:\
  build/$(BUILD_MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_metric.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_inner.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_cbd_star.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_inner.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_laplacian.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_cbd_star.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_continuous$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_continuous_p4$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_continuous_p4 0.0001 4000 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux.txt:\
  build/$(BUILD_MODE)/bin/diffusion_discrete_calculate_flux$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.txt \
  | build/$(BUILD_MODE)/demo/mesh
	$< $(word 2, $^) 4000 $(word 3, $^) > $@

_demo_mesh_brick_regular_2:=\
  $(_demo_mesh_brick_regular_2d_1)\
  $(_demo_mesh_brick_regular_2d_2)\
  $(_demo_mesh_brick_regular_2d_4)\
  $(_demo_mesh_brick_regular_2d_5)\
  $(_demo_mesh_brick_regular_2d_10)\

_demo_mesh_two_triangles := \
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_metric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_cbd_star.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplacian.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_hodge_coeff.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_hodge.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_node_curvature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_metric_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_cbd_star_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplacian_corrected_matrix_form.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplacian_corrected_symmetric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplacian_corrected_symmetric_matrix_form.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_hodge_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplace_equation_non_grid.txt\

.PHONY: demo_mesh_two_triangles
demo_mesh_two_triangles: $(_demo_mesh_two_triangles)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_measure$(.EXE)\
  data/mesh/mesh_two_triangles.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  data/mesh/mesh_two_triangles.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_metric.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_inner.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_cbd_star.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_inner.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplacian.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_cbd_star.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_hodge_coeff.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_hodge.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_node_curvature.txt:\
  build/$(BUILD_MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_metric_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_node_curvature.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_inner_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_metric_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_cbd_star_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplacian_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_cbd_star_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplacian_corrected_matrix_form.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplacian_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplacian_corrected_symmetric.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_laplacian_symmetric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< 2 $(word 2, $^) --raw $(word 3, $^) --raw --raw > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplacian_corrected_symmetric_matrix_form.txt:\
  build/$(BUILD_MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplacian_corrected_symmetric.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_hodge_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplace_equation_non_grid.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplace_equation_solve_non_grid$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_laplacian_corrected_symmetric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_two_triangles_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^) --raw\
	> $@ --raw

_demo_mesh_triangle_and_square := \
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_metric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_cbd_star.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_laplacian.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_hodge_coeff.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_hodge.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_node_curvature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_metric_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_cbd_star_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_hodge_corrected.txt\

.PHONY: demo_mesh_triangle_and_square
demo_mesh_triangle_and_square: $(_demo_mesh_triangle_and_square)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_measure$(.EXE)\
  data/mesh/mesh_triangle_and_square.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  data/mesh/mesh_triangle_and_square.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_metric.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_inner.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_cbd_star.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_inner.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_laplacian.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_cbd_star.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_hodge_coeff.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_hodge.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_node_curvature.txt:\
  build/$(BUILD_MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_metric_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_node_curvature.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_inner_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_metric_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_cbd_star_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_laplacian_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_cbd_star_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_hodge_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_triangle_and_square_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

_demo_mesh_pentagon := \
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_metric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_cbd_star.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_laplacian.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_hodge_coeff.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_hodge.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_node_curvature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_metric_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_cbd_star_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_hodge_corrected.txt\

.PHONY: demo_mesh_pentagon
demo_mesh_pentagon: $(_demo_mesh_pentagon)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_measure$(.EXE)\
  data/mesh/mesh_pentagon.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  data/mesh/mesh_pentagon.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_metric.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_inner.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_cbd_star.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_inner.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_laplacian.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_cbd_star.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_hodge_coeff.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_hodge.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_node_curvature.txt:\
  build/$(BUILD_MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_metric_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_node_curvature.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_inner_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_metric_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_cbd_star_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_laplacian_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_cbd_star_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_hodge_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_pentagon_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

_demo_mesh_2d_10_grains :=\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd_star.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_diffusion_continuous_p7_temperature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_diffusion_continuous_p7_flux.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_temperature.txt\

.PHONY: demo_mesh_2d_10_grains
demo_mesh_2d_10_grains: $(_demo_mesh_2d_10_grains)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains.txt:\
  build/$(BUILD_MODE)/bin/mesh_and_boundary_file_scan$(.EXE)\
  data/mesh/mesh_2d_10_grains.tess\
  | build/$(BUILD_MODE)/demo/mesh
	$< --tess < $(word 2, $^) > $@

# build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman.txt:\
#   build/$(BUILD_MODE)/bin/forman$(.EXE)\
#   data/mesh/mesh_2d_10_grains.tess\
#   | build/$(BUILD_MODE)/demo/mesh
# 	$< --tess < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd.txt:\
  build/$(BUILD_MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_inner.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd_star.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_inner.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_diffusion_continuous_p7_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_continuous$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_continuous_p7$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_continuous_p7 0.0001 1000 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_diffusion_continuous_p7_flux.txt:\
  build/$(BUILD_MODE)/bin/diffusion_discrete_calculate_flux$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_diffusion_continuous_p7_temperature.txt \
  | build/$(BUILD_MODE)/demo/mesh
	$< $(word 2, $^) 1000 $(word 3, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_steady_state_continuous$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_steady_state_continuous_p7$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_steady_state_continuous_p7 > $@

_demo_mesh_square := \
  build/$(BUILD_MODE)/demo/mesh/mesh_square_2.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_4.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8_cbd_star.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8_diffusion_continuous_p5_temperature.txt\

.PHONY: demo_mesh_square
demo_mesh_square: $(_demo_mesh_square)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_square_2.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  data/mesh/mesh_square.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_square_4.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_2.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_square_8.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_4.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_square_8_cbd.txt:\
  build/$(BUILD_MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_square_8_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_square_8_inner.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_square_8_cbd_star.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8_inner.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_square_8_diffusion_continuous_p5_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_continuous$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_square_8_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_continuous_p5$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_continuous_p5 0.001 4000 > $@

# build/$(BUILD_MODE)/demo/mesh/mesh_square_8_diffusion_continuous_p5_temperature.txt:\
#   build/$(BUILD_MODE)/bin/diffusion_continuous_to_steady_state$(.EXE)\
#   build/$(BUILD_MODE)/demo/mesh/mesh_square_8.txt\
#   build/$(BUILD_MODE)/demo/mesh/mesh_square_8_cbd.txt\
#   build/$(BUILD_MODE)/demo/mesh/mesh_square_8_cbd_star.txt\
#   build/$(BUILD_MODE)/obj/diffusion_continuous_p5$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
# 	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
#   diffusion_continuous_p5 0.001 > $@

# d = 3
_demo_mesh_brick_regular_3d :=\
  demo_mesh_brick_regular_3d_1\
  demo_mesh_brick_regular_3d_2\
  demo_mesh_brick_regular_3d_5\
#   demo_mesh_brick_regular_3d_10\
#   demo_mesh_brick_regular_3d_25\

.PHONY: demo_mesh_brick_regular_3d
demo_mesh_brick_regular_3d: $(_demo_mesh_brick_regular_3d)\
  | build/$(BUILD_MODE)/demo/mesh

# d = 3, n = 1
_demo_mesh_brick_regular_3d_1 := \
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_metric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_cbd_star.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_laplacian.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_hodge_coeff.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_hodge.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_node_curvature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_metric_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_cbd_star_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_hodge_corrected.txt\

.PHONY: demo_mesh_brick_regular_3d_1
demo_mesh_brick_regular_3d_1: $(_demo_mesh_brick_regular_3d_1)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 3 1 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_metric.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_inner.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_cbd_star.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_inner.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_laplacian.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_cbd_star.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_hodge_coeff.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_hodge.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_node_curvature.txt:\
  build/$(BUILD_MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_metric_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_node_curvature.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_inner_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_metric_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_cbd_star_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_laplacian_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_cbd_star_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_hodge_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_1_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

# d = 3, n = 2
_demo_mesh_brick_regular_3d_2 := \
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_metric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd_star.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_diffusion_continuous_p6_temperature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_diffusion_steady_state_continuous_p6_temperature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_laplacian.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_hodge_coeff.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_hodge.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_node_curvature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_metric_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd_star_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_hodge_corrected.txt\

.PHONY: demo_mesh_brick_regular_3d_2
demo_mesh_brick_regular_3d_2: $(_demo_mesh_brick_regular_3d_2)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 3 2 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_metric.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_inner.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd_star.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_inner.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd.txt:\
  build/$(BUILD_MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_diffusion_continuous_p6_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_continuous$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_continuous_p6$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_continuous_p6 0.001 1000 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_diffusion_steady_state_continuous_p6_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_steady_state_continuous$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_steady_state_continuous_p6$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_steady_state_continuous_p6 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_laplacian.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd_star.txt\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_hodge_coeff.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_hodge.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_node_curvature.txt:\
  build/$(BUILD_MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_metric_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_node_curvature.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_inner_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_metric_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd_star_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_laplacian_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd_star_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_hodge_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_2_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

# d = 3, n = 5
_demo_mesh_brick_regular_3d_5 := \
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_metric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_cbd_star.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_laplacian.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_hodge_coeff.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_hodge.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_node_curvature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_metric_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_cbd_star_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_hodge_corrected.txt\

.PHONY: demo_mesh_brick_regular_3d_5
demo_mesh_brick_regular_3d_5: $(_demo_mesh_brick_regular_3d_5)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 3 5 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_metric.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_inner.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_cbd_star.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_inner.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_laplacian.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_cbd_star.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_hodge_coeff.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_hodge.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_node_curvature.txt:\
  build/$(BUILD_MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_metric_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_node_curvature.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_inner_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_metric_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_cbd_star_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_laplacian_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_cbd_star_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_hodge_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_5_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

# d = 3, n = 10
_demo_mesh_brick_regular_3d_10 := \
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_metric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_cbd_star.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_diffusion_steady_state_continuous_p6_temperature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_laplacian.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_hodge_coeff.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_hodge.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_node_curvature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_metric_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_cbd_star_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_hodge_corrected.txt\

.PHONY: demo_mesh_brick_regular_3d_10
demo_mesh_brick_regular_3d_10: $(_demo_mesh_brick_regular_3d_10)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 3 10 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_metric.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_inner.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_cbd_star.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_inner.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_cbd.txt:\
  build/$(BUILD_MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_diffusion_steady_state_continuous_p6_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_steady_state_continuous$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_steady_state_continuous_p6$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_steady_state_continuous_p6 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_laplacian.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_cbd_star.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_hodge_coeff.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_hodge.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_node_curvature.txt:\
  build/$(BUILD_MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_metric_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_node_curvature.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_inner_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_metric_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_cbd_star_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_laplacian_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_cbd_star_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_hodge_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_10_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

# d = 3, n = 25
_demo_mesh_brick_regular_3d_25 := \
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_metric.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_cbd_star.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_diffusion_steady_state_continuous_p6_temperature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_laplacian.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_hodge_coeff.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_hodge.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_node_curvature.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_metric_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_cbd_star_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_laplacian_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_hodge_corrected.txt\

.PHONY: demo_mesh_brick_regular_3d_25
demo_mesh_brick_regular_3d_25: $(_demo_mesh_brick_regular_3d_25)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 3 25 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_vol.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	 $< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_metric.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_inner.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_vol.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_cbd_star.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_inner.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_cbd.txt:\
  build/$(BUILD_MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_diffusion_steady_state_continuous_p6_temperature.txt:\
  build/$(BUILD_MODE)/bin/diffusion_steady_state_continuous$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_cbd.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_cbd_star.txt\
  build/$(BUILD_MODE)/obj/diffusion_steady_state_continuous_p6$(.OBJ)\
  | build/$(BUILD_MODE)/demo/mesh build/$(BUILD_MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_steady_state_continuous_p6 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_laplacian.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_cbd_star.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_hodge_coeff.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_hodge.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_inner.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_node_curvature.txt:\
  build/$(BUILD_MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_metric_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_node_curvature.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_inner_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_vol.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_metric_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_cbd_star_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_inner_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_laplacian_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_cbd_star_corrected.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_hodge_corrected.txt:\
  build/$(BUILD_MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_inner_corrected.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_3d_25_forman_hodge_coeff.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$^ > $@

_demo_mesh_brick_regular_3 :=\
  $(_demo_mesh_brick_regular_3d_1)\
  $(_demo_mesh_brick_regular_3d_2)\
  $(_demo_mesh_brick_regular_3d_5)\
  $(_demo_mesh_brick_regular_3d_10)\
  $(_demo_mesh_brick_regular_3d_25)\

_demo_mesh_square_pyramid := \
  build/$(BUILD_MODE)/demo/mesh/mesh_square_pyramid_forman.txt\

.PHONY: demo_mesh_square_pyramid
demo_mesh_square_pyramid: $(_demo_mesh_square_pyramid)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_square_pyramid_forman.txt:\
  build/$(BUILD_MODE)/bin/forman$(.EXE)\
  data/mesh/mesh_square_pyramid.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< --raw < $(word 2, $^) > $@

# d = 4
_demo_mesh_brick_regular_4d := demo_mesh_brick_regular_4d_2

.PHONY: demo_mesh_brick_regular_4d
demo_mesh_brick_regular_4d: $(_demo_mesh_brick_regular_4d)\
  | build/$(BUILD_MODE)/demo/mesh

# d = 4, n = 2
_demo_mesh_brick_regular_4d_2 :=\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_4d_2.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_4d_2_forman.txt

.PHONY: demo_mesh_brick_regular_4d_2
demo_mesh_brick_regular_4d_2: $(_demo_mesh_brick_regular_4d_2)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_brick_4d_2.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 4 2 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_4d_2_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_4d_2.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

# dimensions 8, 9, 10
_demo_mesh_brick_regular_high_dimensions :=\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_8d_1.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_8d_2.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_9d_1.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_9d_2.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_10d_1.txt\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_8d_1_forman.txt\

.PHONY: demo_mesh_brick_regular_high_dimensions
demo_mesh_brick_regular_high_dimensions:\
  $(_demo_mesh_brick_regular_high_dimensions)\
  | build/$(BUILD_MODE)/demo/mesh

build/$(BUILD_MODE)/demo/mesh/mesh_brick_8d_1.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 8 1 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_8d_2.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 8 2 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_9d_1.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 9 1 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_9d_2.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 9 2 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_10d_1.txt:\
  build/$(BUILD_MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(BUILD_MODE)/demo/mesh
	$< 10 1 > $@

build/$(BUILD_MODE)/demo/mesh/mesh_brick_8d_1_forman.txt:\
  build/$(BUILD_MODE)/bin/forman_boundary$(.EXE)\
  build/$(BUILD_MODE)/demo/mesh/mesh_brick_8d_1.txt\
  | build/$(BUILD_MODE)/demo/mesh
	$< < $(word 2, $^) > $@

_demo_mesh_brick_regular_4 := $(_demo_mesh_brick_regular_4d_2)

_demo_mesh_all :=\
  $(_demo_mesh_brick_regular_2)\
  $(_demo_mesh_two_triangles)\
  $(_demo_mesh_triangle_and_square)\
  $(_demo_mesh_square)\
  $(_demo_mesh_pentagon)\
  $(_demo_mesh_2d_10_grains)\
  $(_demo_mesh_brick_regular_3)\
  $(_demo_mesh_square_pyramid)\
  $(_demo_mesh_brick_regular_4)\
  $(_demo_mesh_brick_regular_high_dimensions)\

.PHONY: demo_mesh_clean
demo_mesh_clean:
	-$(RM) $(_demo_mesh_all)
	-$(RM) -r build/$(BUILD_MODE)/demo/mesh
