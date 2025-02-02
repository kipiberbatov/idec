.PHONY: txt_mesh
txt_mesh:\
  bin_mesh\
  txt_mesh_brick_regular\
  txt_mesh_circular\
  txt_mesh_square\
  txt_mesh_two_triangles\
  txt_mesh_triangle_and_square\
  txt_mesh_pentagon\
  txt_mesh_2d_10_grains\
  txt_mesh_square_pyramid\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh: | build/$(MODE)/txt
	mkdir -p $@

_txt_mesh_brick_regular :=\
  txt_mesh_brick_regular_2d\
  txt_mesh_brick_regular_3d\
  txt_mesh_brick_regular_4d\

.PHONY: txt_mesh_brick_regular
txt_mesh_brick_regular: $(_txt_mesh_brick_regular)\
  | build/$(MODE)/txt/mesh

# d = 2
_txt_mesh_brick_regular_2d :=\
  txt_mesh_brick_regular_2d_1\
  txt_mesh_brick_regular_2d_2\
  txt_mesh_brick_regular_2d_4\
  txt_mesh_brick_regular_2d_5\
  txt_mesh_brick_regular_2d_10\

.PHONY: txt_mesh_brick_regular_2d
txt_mesh_brick_regular_2d: $(_txt_mesh_brick_regular_2d)\
  | build/$(MODE)/txt/mesh
	
# d = 2, n = 1
_txt_mesh_brick_regular_2d_1 := \
  build/$(MODE)/txt/mesh/brick_2d_1.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_boundary.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_metric.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_laplacian_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_codifferential.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_codifferential_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_laplacian_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_displacement.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt\
  # build/$(MODE)/txt/mesh/brick_2d_1_forman_elastcity_laplacian_1_1_1.txt\

.PHONY: txt_mesh_brick_regular_2d_1
txt_mesh_brick_regular_2d_1: $(_txt_mesh_brick_regular_2d_1)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/brick_2d_1.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 2 1 > $@

build/$(MODE)/txt/mesh/brick_2d_1_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_boundary.txt:\
  build/$(MODE)/bin/mesh_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_laplacian_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_laplacian.txt\
  | build/$(MODE)/txt/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge.txt\
  | build/$(MODE)/txt/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_codifferential.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_codifferential$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_codifferential_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_codifferential.txt\
  | build/$(MODE)/txt/mesh
	$< --matrix-form-curly -list 2 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_laplacian.txt:\
  build/$(MODE)/bin/matrix_sparse_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_codifferential.txt\
  | build/$(MODE)/txt/mesh
	$< 2 --raw $(word 2, $^) --raw $(word 3, $^) --raw > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_laplacian_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_laplacian.txt\
  | build/$(MODE)/txt/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_displacement.txt:\
  build/$(MODE)/bin/mesh_displacement$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt:\
  build/$(MODE)/bin/mesh_qc_elasticity_coboundary_star_1$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< 1 1 $(wordlist 2, $(words $^), $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt:\
  build/$(MODE)/bin/mesh_qc_elasticity_coboundary_star_2$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< 1 $(wordlist 2, $(words $^), $^) > $@

# build/$(MODE)/txt/mesh/brick_2d_1_forman_elastcity_laplacian_1_1_1.txt:\
#   build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
#   build/$(MODE)/txt/mesh/brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt\
#   build/$(MODE)/txt/mesh/brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt\
  | build/$(MODE)/txt/mesh
# 	$^ > $@

# d = 2, n = 2
_txt_mesh_brick_regular_2d_2 := \
  build/$(MODE)/txt/mesh/brick_2d_2.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_boundary_hyperfaces.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_0_cells.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_dirichlet.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_normals.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_neighbors.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_vector_matrices.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_coefficients.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_boundary.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_metric.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_neumann_modified_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian_corrected_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_corrected_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_codifferential_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_codifferential_corrected_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_laplacian_corrected.txt\

.PHONY: txt_mesh_brick_regular_2d_2
txt_mesh_brick_regular_2d_2: $(_txt_mesh_brick_regular_2d_2)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/brick_2d_2.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 2 2 > $@

build/$(MODE)/txt/mesh/brick_2d_2_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_boundary_hyperfaces.txt:\
  build/$(MODE)/bin/mesh_boundary_hyperfaces$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_0_cells.txt:\
  build/$(MODE)/bin/mesh_boundary_lower_subfaces$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_dirichlet.txt:\
  build/$(MODE)/bin/mesh_boundary_nodes_from_constraint_dirichlet$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann.txt:\
  build/$(MODE)/bin/mesh_boundary_nodes_from_constraint_neumann$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_normals.txt:\
  build/$(MODE)/bin/mesh_boundary_node_normal$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_neighbors.txt:\
  build/$(MODE)/bin/mesh_neighboring_nodes$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_vector_matrices.txt:\
  build/$(MODE)/bin/mesh_boundary_node_vectors_matrix$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_coefficients.txt:\
  build/$(MODE)/bin/mesh_boundary_neumann_coefficients$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_boundary.txt:\
  build/$(MODE)/bin/mesh_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_neumann_modified_laplacian.txt:\
  build/$(MODE)/bin/diffusion_discrete_set_neumann_rows$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --raw $(word 3, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian_corrected_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_corrected_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_codifferential_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_codifferential$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_codifferential_corrected_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_codifferential_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< --matrix-form-curly -list 2 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_laplacian_corrected.txt:\
  build/$(MODE)/bin/matrix_sparse_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_codifferential_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< 2 --raw $(word 2, $^) --raw $(word 3, $^) --raw > $@

# d = 2, n = 4
_txt_mesh_brick_regular_2d_4 := \
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_bd.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_node_curvature.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_metric_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected_mathematica_sparse.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_hodge_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_hodge_corrected_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_hodge_corrected_mathematica_sparse.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_hodge_codifferential_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_hodge_codifferential_corrected_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_hodge_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected_symmetric.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected_symmetric2.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_bd_nodes.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected_symmetric_restricted.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_laplace_equation.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_laplace_equation_non_grid.txt\

.PHONY: txt_mesh_brick_regular_2d_4
txt_mesh_brick_regular_2d_4: $(_txt_mesh_brick_regular_2d_4)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/brick_2d_4.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 2 4 > $@

build/$(MODE)/txt/mesh/brick_2d_4_bd.txt:\
  build/$(MODE)/bin/mesh_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_4_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_4_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_4_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_4_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_4_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_4_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected_mathematica_sparse.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< --mathematica-sparse -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_4_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_4_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_4_hodge_corrected_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4_hodge_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_4_hodge_corrected_mathematica_sparse.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4_hodge_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< --mathematica-sparse -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_4_hodge_codifferential_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_codifferential$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_hodge_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_4_hodge_codifferential_corrected_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4_hodge_codifferential_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< --matrix-form-curly -list 2 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_4_hodge_laplacian_corrected.txt:\
  build/$(MODE)/bin/matrix_sparse_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_hodge_codifferential_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< 2 --raw $(word 2, $^) --raw $(word 3, $^) --raw > $@

build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected_symmetric.txt:\
  build/$(MODE)/bin/matrix_sparse_laplacian_symmetric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< 2 $(word 2, $^) --raw $(word 3, $^) --raw > $@ --raw

build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected_symmetric2.txt:\
  build/$(MODE)/bin/matrix_sparse_laplacian_symmetric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< 2 $(word 2, $^) --raw $(word 3, $^) --raw > $@ --matrix-form-curly

build/$(MODE)/txt/mesh/brick_2d_4_bd_nodes.txt:\
  build/$(MODE)/bin/mesh_boundary_nodes$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  | build/$(MODE)/txt/mesh
	$< $(word 2, $^) --raw > $@ --raw
	
build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected_symmetric_restricted.txt:\
  build/$(MODE)/bin/matrix_sparse_remove_symmetric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected_symmetric.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_bd_nodes.txt\
  | build/$(MODE)/txt/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw > $@ --matrix-form-curly

build/$(MODE)/txt/mesh/brick_2d_4_laplace_equation.txt:\
  build/$(MODE)/bin/mesh_qc_laplace_equation_solve$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw > $@ --raw

build/$(MODE)/txt/mesh/brick_2d_4_laplace_equation_non_grid.txt:\
  build/$(MODE)/bin/mesh_qc_laplace_equation_solve_non_grid$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected_symmetric.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^) --raw\
	> $@ --raw

build/$(MODE)/txt/mesh/brick_2d_4_heat_conduction_non_grid.txt:\
  build/$(MODE)/bin/mesh_qc_heat_conduction_solve_non_grid$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_laplacian_corrected_symmetric.txt\
  build/$(MODE)/txt/mesh/brick_2d_4_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^) --raw \
	0.1 10 --raw > $@

_txt_mesh_brick_regular_2d_5 := \
  build/$(MODE)/txt/mesh/brick_2d_5.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_metric.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_boundary_layer_0_1_nodes.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_hodge.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_hodge_corrected.txt\

.PHONY: txt_mesh_brick_regular_2d_5
txt_mesh_brick_regular_2d_5: $(_txt_mesh_brick_regular_2d_5)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/brick_2d_5.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 2 5 > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_5_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_boundary_layer_0_1_nodes.txt:\
  build/$(MODE)/bin/mesh_qc_boundary_layer$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_5_forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

_txt_mesh_brick_regular_2d_10 := \
  build/$(MODE)/txt/mesh/brick_2d_10.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_boundary.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_metric.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_hodge.txt\

.PHONY: txt_mesh_brick_regular_2d_10
txt_mesh_brick_regular_2d_10: $(_txt_mesh_brick_regular_2d_10)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/brick_2d_10.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 2 10 > $@

build/$(MODE)/txt/mesh/brick_2d_10_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_10_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/brick_2d_10_forman_boundary.txt:\
  build/$(MODE)/bin/mesh_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_10_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_10_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_10_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_10_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_10_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_10_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_2d_10_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_10_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

_txt_mesh_brick_regular_2:=\
  $(_txt_mesh_brick_regular_2d_1)\
  $(_txt_mesh_brick_regular_2d_2)\
  $(_txt_mesh_brick_regular_2d_4)\
  $(_txt_mesh_brick_regular_2d_5)\
  $(_txt_mesh_brick_regular_2d_10)\

_txt_mesh_two_triangles := \
  build/$(MODE)/txt/mesh/two_triangles_vol.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_vol.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_metric.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_inner.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_hodge.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_laplacian_corrected_matrix_form.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_laplacian_corrected_symmetric.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_laplacian_corrected_symmetric_matrix_form.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_hodge_corrected.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_laplace_equation_non_grid.txt\

.PHONY: txt_mesh_two_triangles
txt_mesh_two_triangles: $(_txt_mesh_two_triangles)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/two_triangles_vol.txt:\
  build/$(MODE)/bin/mesh_measure$(.EXE)\
  data/mesh/two_triangles.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/two_triangles_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  data/mesh/two_triangles.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/two_triangles_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/two_triangles_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/two_triangles_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/two_triangles_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/two_triangles_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/two_triangles_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/two_triangles_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_inner.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/two_triangles_forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/two_triangles_forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_vol.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/two_triangles_forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_vol.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/two_triangles_forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/two_triangles_forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/two_triangles_forman_laplacian_corrected_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman_laplacian_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/two_triangles_forman_laplacian_corrected_symmetric.txt:\
  build/$(MODE)/bin/matrix_sparse_laplacian_symmetric$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< 2 $(word 2, $^) --raw $(word 3, $^) --raw --raw > $@

build/$(MODE)/txt/mesh/two_triangles_forman_laplacian_corrected_symmetric_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman_laplacian_corrected_symmetric.txt\
  | build/$(MODE)/txt/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/two_triangles_forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/two_triangles_forman_laplace_equation_non_grid.txt:\
  build/$(MODE)/bin/mesh_qc_laplace_equation_solve_non_grid$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_laplacian_corrected_symmetric.txt\
  build/$(MODE)/txt/mesh/two_triangles_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^) --raw\
	> $@ --raw

_txt_mesh_triangle_and_square := \
  build/$(MODE)/txt/mesh/triangle_and_square_vol.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_vol.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_metric.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_inner.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge_corrected.txt\

.PHONY: txt_mesh_triangle_and_square
txt_mesh_triangle_and_square: $(_txt_mesh_triangle_and_square)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/triangle_and_square_vol.txt:\
  build/$(MODE)/bin/mesh_measure$(.EXE)\
  data/mesh/triangle_and_square.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  data/mesh/triangle_and_square.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_inner.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_vol.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_vol.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

_txt_mesh_pentagon := \
  build/$(MODE)/txt/mesh/pentagon_vol.txt\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_vol.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_metric.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_inner.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_hodge.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_hodge_corrected.txt\

.PHONY: txt_mesh_pentagon
txt_mesh_pentagon: $(_txt_mesh_pentagon)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/pentagon_vol.txt:\
  build/$(MODE)/bin/mesh_measure$(.EXE)\
  data/mesh/pentagon.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/pentagon_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  data/mesh/pentagon.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/pentagon_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/pentagon_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/pentagon_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/pentagon_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/pentagon_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/pentagon_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/pentagon_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_inner.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/pentagon_forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/pentagon_forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_vol.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/pentagon_forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_vol.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/pentagon_forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/pentagon_forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/pentagon_forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/pentagon_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

_txt_mesh_2d_10_grains :=\
  build/$(MODE)/txt/mesh/2d_10_grains.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_cbd.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_vol.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_inner.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_hodge.txt\

.PHONY: txt_mesh_2d_10_grains
txt_mesh_2d_10_grains: $(_txt_mesh_2d_10_grains)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/2d_10_grains.txt:\
  build/$(MODE)/bin/mesh_and_boundary_file_scan$(.EXE)\
  data/mesh/2d_10_grains.tess\
  | build/$(MODE)/txt/mesh
	$< --mesh-format=tess $(word 2, $^) > $@

build/$(MODE)/txt/mesh/2d_10_grains_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/2d_10_grains_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/2d_10_grains_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/2d_10_grains_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/2d_10_grains_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/2d_10_grains_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/2d_10_grains_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_inner.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

_txt_mesh_circular :=\
  build/$(MODE)/txt/mesh/circular_4_3.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_cbd.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_vol.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_inner.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_inner.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/circular_18_10.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_cbd.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_vol.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_inner.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_inner.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_cbd_star.txt\

.PHONY: txt_mesh_circular
txt_mesh_circular: $(_txt_mesh_circular) | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/circular_4_3.txt:\
  build/$(MODE)/bin/mesh_circular$(.EXE) | build/$(MODE)/txt/mesh
	$< 4 3 > $@

build/$(MODE)/txt/mesh/circular_4_3_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --circular --raw > $@

build/$(MODE)/txt/mesh/circular_4_3_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/circular_4_3_forman_vol.txt:\
  build/$(MODE)/bin/mesh_measures$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  | build/$(MODE)/txt/mesh
	$<\
  --mesh=$(word 2, $^)\
  --mesh-measures-function=circular-forman\
  > $@

build/$(MODE)/txt/mesh/circular_4_3_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/circular_4_3_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/circular_4_3_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/circular_4_3_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_inner.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/circular_18_10.txt:\
  build/$(MODE)/bin/mesh_circular$(.EXE) | build/$(MODE)/txt/mesh
	$< 18 10 > $@

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

.PHONY: txt_mesh_square
txt_mesh_square: $(_txt_mesh_square)\
  | build/$(MODE)/txt/mesh

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

# d = 3
_txt_mesh_brick_regular_3d :=\
  txt_mesh_brick_regular_3d_1\
  txt_mesh_brick_regular_3d_2\
  txt_mesh_brick_regular_3d_5\
#   txt_mesh_brick_regular_3d_10\
#   txt_mesh_brick_regular_3d_25\

.PHONY: txt_mesh_brick_regular_3d
txt_mesh_brick_regular_3d: $(_txt_mesh_brick_regular_3d)\
  | build/$(MODE)/txt/mesh

# d = 3, n = 1
_txt_mesh_brick_regular_3d_1 := \
  build/$(MODE)/txt/mesh/brick_3d_1.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_metric.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_hodge.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_hodge_corrected.txt\

.PHONY: txt_mesh_brick_regular_3d_1
txt_mesh_brick_regular_3d_1: $(_txt_mesh_brick_regular_3d_1)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/brick_3d_1.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 3 1 > $@

build/$(MODE)/txt/mesh/brick_3d_1_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_1_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/brick_3d_1_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_1_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_1_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_1_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_1_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_1_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_1_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_1_forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_1_forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_1_forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_1_forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_1_forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_1_forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_1_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

# d = 3, n = 2
_txt_mesh_brick_regular_3d_2 := \
  build/$(MODE)/txt/mesh/brick_3d_2.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_metric.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_hodge.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_hodge_corrected.txt\

.PHONY: txt_mesh_brick_regular_3d_2
txt_mesh_brick_regular_3d_2: $(_txt_mesh_brick_regular_3d_2)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/brick_3d_2.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 3 2 > $@

build/$(MODE)/txt/mesh/brick_3d_2_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_2_forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

# d = 3, n = 5
_txt_mesh_brick_regular_3d_5 := \
  build/$(MODE)/txt/mesh/brick_3d_5.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_metric.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_hodge.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_hodge_corrected.txt\

.PHONY: txt_mesh_brick_regular_3d_5
txt_mesh_brick_regular_3d_5: $(_txt_mesh_brick_regular_3d_5)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/brick_3d_5.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 3 5 > $@

build/$(MODE)/txt/mesh/brick_3d_5_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_5_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/brick_3d_5_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_5_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_5_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_5_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_5_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_5_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_5_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_5_forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_5_forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_5_forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_5_forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_5_forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_5_forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_5_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

# d = 3, n = 10
_txt_mesh_brick_regular_3d_10 := \
  build/$(MODE)/txt/mesh/brick_3d_10.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_metric.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_hodge.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_hodge_corrected.txt\

.PHONY: txt_mesh_brick_regular_3d_10
txt_mesh_brick_regular_3d_10: $(_txt_mesh_brick_regular_3d_10)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/brick_3d_10.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 3 10 > $@

build/$(MODE)/txt/mesh/brick_3d_10_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_10_forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_10_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

# d = 3, n = 25
_txt_mesh_brick_regular_3d_25 := \
  build/$(MODE)/txt/mesh/brick_3d_25.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_metric.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_hodge.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_hodge_corrected.txt\

.PHONY: txt_mesh_brick_regular_3d_25
txt_mesh_brick_regular_3d_25: $(_txt_mesh_brick_regular_3d_25)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/brick_3d_25.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 3 25 > $@

build/$(MODE)/txt/mesh/brick_3d_25_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  | build/$(MODE)/txt/mesh
	$< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  | build/$(MODE)/txt/mesh
	$< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

build/$(MODE)/txt/mesh/brick_3d_25_forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_25_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_3d_25_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$^ > $@

_txt_mesh_brick_regular_3 :=\
  $(_txt_mesh_brick_regular_3d_1)\
  $(_txt_mesh_brick_regular_3d_2)\
  $(_txt_mesh_brick_regular_3d_5)\
  $(_txt_mesh_brick_regular_3d_10)\
  $(_txt_mesh_brick_regular_3d_25)\

_txt_mesh_square_pyramid := \
  build/$(MODE)/txt/mesh/square_pyramid_forman.txt\

.PHONY: txt_mesh_square_pyramid
txt_mesh_square_pyramid: $(_txt_mesh_square_pyramid)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/square_pyramid_forman.txt:\
  build/$(MODE)/bin/forman$(.EXE)\
  data/mesh/square_pyramid.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

# d = 4
_txt_mesh_brick_regular_4d := txt_mesh_brick_regular_4d_2

.PHONY: txt_mesh_brick_regular_4d
txt_mesh_brick_regular_4d: $(_txt_mesh_brick_regular_4d)\
  | build/$(MODE)/txt/mesh

# d = 4, n = 2
_txt_mesh_brick_regular_4d_2 :=\
  build/$(MODE)/txt/mesh/brick_4d_2.txt\
  build/$(MODE)/txt/mesh/brick_4d_2_forman.txt

.PHONY: txt_mesh_brick_regular_4d_2
txt_mesh_brick_regular_4d_2: $(_txt_mesh_brick_regular_4d_2)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/brick_4d_2.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 4 2 > $@

build/$(MODE)/txt/mesh/brick_4d_2_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_4d_2.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

# dimensions 8, 9, 10
_txt_mesh_brick_regular_high_dimensions :=\
  build/$(MODE)/txt/mesh/brick_8d_1.txt\
  build/$(MODE)/txt/mesh/brick_8d_2.txt\
  build/$(MODE)/txt/mesh/brick_9d_1.txt\
  build/$(MODE)/txt/mesh/brick_9d_2.txt\
  build/$(MODE)/txt/mesh/brick_10d_1.txt\
  build/$(MODE)/txt/mesh/brick_8d_1_forman.txt\

.PHONY: txt_mesh_brick_regular_high_dimensions
txt_mesh_brick_regular_high_dimensions:\
  $(_txt_mesh_brick_regular_high_dimensions)\
  | build/$(MODE)/txt/mesh

build/$(MODE)/txt/mesh/brick_8d_1.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 8 1 > $@

build/$(MODE)/txt/mesh/brick_8d_2.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 8 2 > $@

build/$(MODE)/txt/mesh/brick_9d_1.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 9 1 > $@

build/$(MODE)/txt/mesh/brick_9d_2.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 9 2 > $@

build/$(MODE)/txt/mesh/brick_10d_1.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$< 10 1 > $@

build/$(MODE)/txt/mesh/brick_8d_1_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_8d_1.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) --standard --raw > $@

_txt_mesh_brick_regular_4 := $(_txt_mesh_brick_regular_4d_2)

_txt_mesh_all :=\
  $(_txt_mesh_brick_regular_2)\
  $(_txt_mesh_two_triangles)\
  $(_txt_mesh_triangle_and_square)\
  $(_txt_mesh_square)\
  $(_txt_mesh_pentagon)\
  $(_txt_mesh_2d_10_grains)\
  $(_txt_mesh_brick_regular_3)\
  $(_txt_mesh_square_pyramid)\
  $(_txt_mesh_brick_regular_4)\
  $(_txt_mesh_brick_regular_high_dimensions)\

.PHONY: txt_mesh_clean
txt_mesh_clean:
	-$(RM) $(_txt_mesh_all)
	-$(RM) -r build/$(MODE)/txt/mesh
