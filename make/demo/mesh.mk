.PHONY: demo_mesh
demo_mesh: bin_mesh demo_mesh_brick_regular demo_mesh_square | demo/mesh

demo/mesh: | demo
	mkdir -p $@

DEMO_MESH_BRICK_REGULAR :=\
  demo_mesh_brick_regular_2d\
  demo_mesh_two_triangles\
  demo_mesh_triangle_and_square\
  demo_mesh_brick_regular_3d\
  demo_mesh_brick_regular_4d\

.PHONY: demo_mesh_brick_regular
demo_mesh_brick_regular: $(DEMO_MESH_BRICK_REGULAR) | demo/mesh

# d = 2
DEMO_MESH_BRICK_REGULAR_2D :=\
  demo_mesh_brick_regular_2d_1\
  demo_mesh_brick_regular_2d_2\
  demo_mesh_brick_regular_2d_4\
  demo_mesh_brick_regular_2d_5\
  demo_mesh_brick_regular_2d_10\

.PHONY: demo_mesh_brick_regular_2d
demo_mesh_brick_regular_2d: $(DEMO_MESH_BRICK_REGULAR_2D) | demo/mesh
	
# d = 2, n = 1
DEMO_MESH_BRICK_REGULAR_2D_1 := \
  demo/mesh/mesh_brick_2d_1.txt\
  demo/mesh/mesh_brick_2d_1_vol.txt\
  demo/mesh/mesh_brick_2d_1_forman.txt\
  demo/mesh/mesh_brick_2d_1_forman_boundary.txt\
  demo/mesh/mesh_brick_2d_1_forman_cbd.txt\
  demo/mesh/mesh_brick_2d_1_forman_vol.txt\
  demo/mesh/mesh_brick_2d_1_forman_metric.txt\
  demo/mesh/mesh_brick_2d_1_forman_inner.txt\
  demo/mesh/mesh_brick_2d_1_forman_cbd_star.txt\
  demo/mesh/mesh_brick_2d_1_forman_laplacian.txt\
  demo/mesh/mesh_brick_2d_1_forman_laplacian_matrix_form.txt\
  demo/mesh/mesh_brick_2d_1_forman_hodge_coeff.txt\
  demo/mesh/mesh_brick_2d_1_forman_hodge.txt\
  demo/mesh/mesh_brick_2d_1_forman_hodge_matrix_form.txt\
  demo/mesh/mesh_brick_2d_1_forman_hodge_codifferential.txt\
  demo/mesh/mesh_brick_2d_1_forman_hodge_codifferential_matrix_form.txt\
  demo/mesh/mesh_brick_2d_1_forman_hodge_laplacian.txt\
  demo/mesh/mesh_brick_2d_1_forman_hodge_laplacian_matrix_form.txt\
  demo/mesh/mesh_brick_2d_1_forman_node_curvature.txt\
  demo/mesh/mesh_brick_2d_1_forman_metric_corrected.txt\
  demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt\
  demo/mesh/mesh_brick_2d_1_forman_cbd_star_corrected.txt\
  demo/mesh/mesh_brick_2d_1_forman_laplacian_corrected.txt\
  demo/mesh/mesh_brick_2d_1_forman_hodge_corrected.txt\
  demo/mesh/mesh_brick_2d_1_forman_displacement.txt\
  demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt\
  demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt\
  # demo/mesh/mesh_brick_2d_1_forman_elastcity_laplacian_1_1_1.txt\

.PHONY: demo_mesh_brick_regular_2d_1
demo_mesh_brick_regular_2d_1: $(DEMO_MESH_BRICK_REGULAR_2D_1) | demo/mesh

demo/mesh/mesh_brick_2d_1.txt:\
	  bin/mesh_brick_regular$(.EXE) | demo/mesh
	$< 2 1 > $@

demo/mesh/mesh_brick_2d_1_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_1.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman.txt:\
	  bin/forman_boundary$(.EXE)\
	  demo/mesh/mesh_brick_2d_1.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_boundary.txt:\
	  bin/mesh_boundary$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt | demo/mesh
	$< --raw < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_cbd.txt:\
	  bin/mesh_coboundary$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt | demo/mesh
	$< --raw < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_1_forman_inner.txt:\
	  bin/mesh_qc_inner_direct$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_1_forman_cbd_star.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_inner.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_1_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_cbd_star.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_1_forman_laplacian_matrix_form.txt:\
	  bin/matrix_sparse_file_print$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman_laplacian.txt | demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_hodge.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_inner.txt\
	  demo/mesh/mesh_brick_2d_1_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_1_forman_hodge_matrix_form.txt:\
	  bin/matrix_sparse_file_print$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman_hodge.txt | demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_hodge_codifferential.txt:\
	  bin/mesh_qc_hodge_codifferential$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_hodge.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_1_forman_hodge_codifferential_matrix_form.txt:\
	  bin/matrix_sparse_file_print$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman_hodge_codifferential.txt | demo/mesh
	$< --matrix-form-curly -list 2 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_hodge_laplacian.txt:\
	  bin/matrix_sparse_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman_cbd.txt\
	  demo/mesh/mesh_brick_2d_1_forman_hodge_codifferential.txt | demo/mesh
	$< 2 --raw $(word 2, $^) --raw $(word 3, $^) --raw > $@

demo/mesh/mesh_brick_2d_1_forman_hodge_laplacian_matrix_form.txt:\
	  bin/matrix_sparse_file_print$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman_hodge_laplacian.txt | demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_1_forman_node_curvature.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_1_forman_metric_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_1_forman_cbd_star_corrected.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_1_forman_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_cbd_star_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_1_forman_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt\
	  demo/mesh/mesh_brick_2d_1_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_1_forman_displacement.txt:\
	  bin/mesh_displacement$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt:\
	  bin/mesh_qc_elasticity_coboundary_star_1$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt | demo/mesh
	$< 1 1 $(wordlist 2, $(words $^), $^) > $@

demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt:\
	  bin/mesh_qc_elasticity_coboundary_star_2$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  demo/mesh/mesh_brick_2d_1_forman_inner_corrected.txt | demo/mesh
	$< 1 $(wordlist 2, $(words $^), $^) > $@

# demo/mesh/mesh_brick_2d_1_forman_elastcity_laplacian_1_1_1.txt:\
# 	  bin/mesh_qc_laplacian$(.EXE)\
# 	  demo/mesh/mesh_brick_2d_1_forman.txt\
# 	  demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt\
# 	  demo/mesh/mesh_brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt | demo/mesh
# 	$^ > $@

# d = 2, n = 2
DEMO_MESH_BRICK_REGULAR_2D_2 := \
  demo/mesh/mesh_brick_2d_2.txt\
  demo/mesh/mesh_brick_2d_2_vol.txt\
  demo/mesh/mesh_brick_2d_2_forman.txt\
  demo/mesh/mesh_brick_2d_2_forman_boundary_hyperfaces.txt\
  demo/mesh/mesh_brick_2d_2_forman_0_cells.txt\
  demo/mesh/mesh_brick_2d_2_forman_nodes_dirichlet.txt\
  demo/mesh/mesh_brick_2d_2_forman_nodes_neumann.txt\
  demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_normals.txt\
  demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_neighbors.txt\
  demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_vector_matrices.txt\
  demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_coefficients.txt\
  demo/mesh/mesh_brick_2d_2_forman_boundary.txt\
  demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  demo/mesh/mesh_brick_2d_2_forman_metric.txt\
  demo/mesh/mesh_brick_2d_2_forman_inner.txt\
  demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  demo/mesh/mesh_brick_2d_2_forman_laplacian.txt\
  demo/mesh/mesh_brick_2d_2_forman_neumann_modified_laplacian.txt\
  demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.txt\
  demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_flux.txt\
  demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p1_temperature.txt\
  demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p2_temperature.txt\
  demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p4_temperature.txt\
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
demo_mesh_brick_regular_2d_2: $(DEMO_MESH_BRICK_REGULAR_2D_2) | demo/mesh

demo/mesh/mesh_brick_2d_2.txt:\
	  bin/mesh_brick_regular$(.EXE) | demo/mesh
	$< 2 2 > $@

demo/mesh/mesh_brick_2d_2_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_2.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman.txt:\
	  bin/forman_boundary$(.EXE)\
	  demo/mesh/mesh_brick_2d_2.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_boundary_hyperfaces.txt:\
	  bin/mesh_boundary_hyperfaces$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_0_cells.txt:\
	  bin/mesh_boundary_lower_subfaces$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_nodes_dirichlet.txt:\
	  bin/mesh_boundary_nodes_from_constraint_dirichlet$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_nodes_neumann.txt:\
	  bin/mesh_boundary_nodes_from_constraint_neumann$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_normals.txt:\
	  bin/mesh_boundary_node_normal$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_neighbors.txt:\
	  bin/mesh_neighboring_nodes$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_vector_matrices.txt:\
	  bin/mesh_boundary_node_vectors_matrix$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_nodes_neumann_coefficients.txt:\
	  bin/mesh_boundary_neumann_coefficients$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_boundary.txt:\
	  bin/mesh_boundary$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt | demo/mesh
	$< --raw < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_cbd.txt:\
	  bin/mesh_coboundary$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt | demo/mesh
	$< --raw < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_2_forman_inner.txt:\
	  bin/mesh_qc_inner_direct$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_inner.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_2_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_2_forman_neumann_modified_laplacian.txt:\
	  bin/diffusion_discrete_set_neumann_rows$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_laplacian.txt | demo/mesh
	 $< --raw $(word 2, $^) --raw $(word 3, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.txt:\
	  bin/diffusion_continuous$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
	  demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
	  build/diffusion_continuous_p0.o | demo/mesh
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^)\
	  diffusion_continuous_p0 0.05 100 > $@

demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_flux.txt:\
	  bin/diffusion_discrete_calculate_flux$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.txt\
	  | demo/mesh
	$< $(word 2, $^) 100 $(word 3, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p1_temperature.txt:\
	  bin/diffusion_continuous$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
	  demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
	  build/diffusion_continuous_p1.o | demo/mesh
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^)\
	  diffusion_continuous_p1 0.05 20 > $@

demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p2_temperature.txt:\
	  bin/diffusion_continuous$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
	  demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
	  build/diffusion_continuous_p2.o | demo/mesh
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^)\
	  diffusion_continuous_p2 0.001 100 > $@

demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p4_temperature.txt:\
	  bin/diffusion_continuous_to_steady_state$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
	  demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
	  build/diffusion_continuous_p4.o | demo/mesh
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^)\
	  diffusion_continuous_p4 0.001 > $@

demo/mesh/mesh_brick_2d_2_forman_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_hodge.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_inner.txt\
	  demo/mesh/mesh_brick_2d_2_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_2_forman_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_2_forman_node_curvature.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_2_forman_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_2_forman_metric_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_2_forman_cbd_star_corrected.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_inner_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_2_forman_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_cbd_star_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_2_forman_laplacian_corrected_matrix_form.txt:\
	  bin/matrix_sparse_file_print$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman_laplacian_corrected.txt | demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_inner_corrected.txt\
	  demo/mesh/mesh_brick_2d_2_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_2_forman_hodge_corrected_matrix_form.txt:\
	  bin/matrix_sparse_file_print$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman_hodge_corrected.txt | demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected.txt:\
	  bin/mesh_qc_hodge_codifferential$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_hodge_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected_matrix_form.txt:\
	  bin/matrix_sparse_file_print$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected.txt | demo/mesh
	$< --matrix-form-curly -list 2 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_2_forman_hodge_laplacian_corrected.txt:\
	  bin/matrix_sparse_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
	  demo/mesh/mesh_brick_2d_2_forman_hodge_codifferential_corrected.txt\
	  | demo/mesh
	$< 2 --raw $(word 2, $^) --raw $(word 3, $^) --raw > $@

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
  demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric.txt\
  demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric2.txt\
  demo/mesh/mesh_brick_2d_4_bd_nodes.txt\
  demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric_restricted.txt\
  demo/mesh/mesh_brick_2d_4_laplace_equation.txt\
  demo/mesh/mesh_brick_2d_4_laplace_equation_non_grid.txt\

.PHONY: demo_mesh_brick_regular_2d_4
demo_mesh_brick_regular_2d_4: $(DEMO_MESH_BRICK_REGULAR_2D_4) | demo/mesh

demo/mesh/mesh_brick_2d_4.txt:\
	  bin/mesh_brick_regular$(.EXE) | demo/mesh
	$< 2 4 > $@

demo/mesh/mesh_brick_2d_4_bd.txt:\
	  bin/mesh_boundary$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt | demo/mesh
	$< --raw < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_cbd.txt:\
	  bin/mesh_coboundary$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt | demo/mesh
	$< --raw < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_vol.txt\
	  demo/mesh/mesh_brick_2d_4_node_curvature.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_4_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_vol.txt\
	  demo/mesh/mesh_brick_2d_4_metric_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_4_cbd_star_corrected.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_inner_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_cbd_star_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_4_laplacian_corrected_matrix_form.txt:\
	  bin/matrix_sparse_file_print$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt | demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_laplacian_corrected_mathematica_sparse.txt:\
	  bin/matrix_sparse_file_print$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt | demo/mesh
	$< --mathematica-sparse -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_inner_corrected.txt\
	  demo/mesh/mesh_brick_2d_4_hodge_coeff.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_4_hodge_corrected_matrix_form.txt:\
	  bin/matrix_sparse_file_print$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_hodge_corrected.txt | demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_hodge_corrected_mathematica_sparse.txt:\
	  bin/matrix_sparse_file_print$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_hodge_corrected.txt | demo/mesh
	$< --mathematica-sparse -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected.txt:\
	  bin/mesh_qc_hodge_codifferential$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_hodge_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected_matrix_form.txt:\
	  bin/matrix_sparse_file_print$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected.txt | demo/mesh
	$< --matrix-form-curly -list 2 < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_4_hodge_laplacian_corrected.txt:\
	  bin/matrix_sparse_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_cbd.txt\
	  demo/mesh/mesh_brick_2d_4_hodge_codifferential_corrected.txt\
	  | demo/mesh
	$< 2 --raw $(word 2, $^) --raw $(word 3, $^) --raw > $@

demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric.txt:\
	  bin/matrix_sparse_laplacian_symmetric$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt\
	  demo/mesh/mesh_brick_2d_4_inner_corrected.txt | demo/mesh
	$< 2 $(word 2, $^) --raw $(word 3, $^) --raw > $@ --raw

demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric2.txt:\
	  bin/matrix_sparse_laplacian_symmetric$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt\
	  demo/mesh/mesh_brick_2d_4_inner_corrected.txt | demo/mesh
	$< 2 $(word 2, $^) --raw $(word 3, $^) --raw > $@ --matrix-form-curly

demo/mesh/mesh_brick_2d_4_bd_nodes.txt:\
	  bin/mesh_boundary_nodes$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt | demo/mesh
	$< $(word 2, $^) --raw > $@ --raw
	
demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric_restricted.txt:\
	  bin/matrix_sparse_remove_symmetric$(.EXE)\
	  demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric.txt\
	  demo/mesh/mesh_brick_2d_4_bd_nodes.txt | demo/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw > $@ --matrix-form-curly

demo/mesh/mesh_brick_2d_4_laplace_equation.txt:\
	  bin/mesh_qc_laplace_equation_solve$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_laplacian_corrected.txt | demo/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw > $@ --raw

demo/mesh/mesh_brick_2d_4_laplace_equation_non_grid.txt:\
	  bin/mesh_qc_laplace_equation_solve_non_grid$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric.txt\
	  demo/mesh/mesh_brick_2d_4_inner_corrected.txt | demo/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^) --raw\
	> $@ --raw

demo/mesh/mesh_brick_2d_4_heat_conduction_non_grid.txt:\
	  bin/mesh_qc_heat_conduction_solve_non_grid$(.EXE)\
	  demo/mesh/mesh_brick_2d_4.txt\
	  demo/mesh/mesh_brick_2d_4_laplacian_corrected_symmetric.txt\
	  demo/mesh/mesh_brick_2d_4_inner_corrected.txt | demo/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^) --raw \
	0.1 10 --raw > $@

DEMO_MESH_BRICK_REGULAR_2D_5 := \
  demo/mesh/mesh_brick_2d_5.txt\
  demo/mesh/mesh_brick_2d_5_forman_cbd.txt\
  demo/mesh/mesh_brick_2d_5_vol.txt\
  demo/mesh/mesh_brick_2d_5_forman.txt\
  demo/mesh/mesh_brick_2d_5_forman_vol.txt\
  demo/mesh/mesh_brick_2d_5_forman_metric.txt\
  demo/mesh/mesh_brick_2d_5_forman_inner.txt\
  demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt\
  demo/mesh/mesh_brick_2d_5_forman_laplacian.txt\
  demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.txt\
  demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.txt\
  demo/mesh/mesh_brick_2d_5_forman_boundary_layer_0_1_nodes.txt\
  demo/mesh/mesh_brick_2d_5_forman_hodge_coeff.txt\
  demo/mesh/mesh_brick_2d_5_forman_hodge.txt\
  demo/mesh/mesh_brick_2d_5_forman_node_curvature.txt\
  demo/mesh/mesh_brick_2d_5_forman_metric_corrected.txt\
  demo/mesh/mesh_brick_2d_5_forman_inner_corrected.txt\
  demo/mesh/mesh_brick_2d_5_forman_cbd_star_corrected.txt\
  demo/mesh/mesh_brick_2d_5_forman_laplacian_corrected.txt\
  demo/mesh/mesh_brick_2d_5_forman_hodge_corrected.txt\

.PHONY: demo_mesh_brick_regular_2d_5
demo_mesh_brick_regular_2d_5: $(DEMO_MESH_BRICK_REGULAR_2D_5) | demo/mesh

demo/mesh/mesh_brick_2d_5.txt:\
	  bin/mesh_brick_regular$(.EXE) | demo/mesh
	$< 2 5 > $@

demo/mesh/mesh_brick_2d_5_forman_cbd.txt:\
	  bin/mesh_coboundary$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt | demo/mesh
	$< --raw < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_5_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_5.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_5_forman.txt:\
	  bin/forman_boundary$(.EXE)\
	  demo/mesh/mesh_brick_2d_5.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_5_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_5_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_5_forman_inner.txt:\
	  bin/mesh_qc_inner_direct$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_inner.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_5_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.txt:\
	  bin/diffusion_continuous$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_cbd.txt\
	  demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt\
	  build/diffusion_continuous_p2.o | demo/mesh
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^)\
	  diffusion_continuous_p2 0.0001 10000 > $@

demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.txt:\
	  bin/diffusion_continuous$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_cbd.txt\
	  demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt\
	  build/diffusion_continuous_p4.o | demo/mesh
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^)\
	  diffusion_continuous_p4 0.0001 10000 > $@

demo/mesh/mesh_brick_2d_5_forman_boundary_layer_0_1_nodes.txt:\
	  bin/mesh_qc_boundary_layer$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_5_forman_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_5_forman_hodge.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_inner.txt\
	  demo/mesh/mesh_brick_2d_5_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_5_forman_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_5_forman_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_5_forman_node_curvature.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_5_forman_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_vol.txt\
	  demo/mesh/mesh_brick_2d_5_forman_metric_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_5_forman_cbd_star_corrected.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_inner_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_5_forman_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_cbd_star_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_5_forman_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_inner_corrected.txt\
	  demo/mesh/mesh_brick_2d_5_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

DEMO_MESH_BRICK_REGULAR_2D_10 := \
  demo/mesh/mesh_brick_2d_10.txt\
  demo/mesh/mesh_brick_2d_10_vol.txt\
  demo/mesh/mesh_brick_2d_10_forman.txt\
  demo/mesh/mesh_brick_2d_10_forman_boundary.txt\
  demo/mesh/mesh_brick_2d_10_forman_cbd.txt\
  demo/mesh/mesh_brick_2d_10_forman_vol.txt\
  demo/mesh/mesh_brick_2d_10_forman_metric.txt\
  demo/mesh/mesh_brick_2d_10_forman_inner.txt\
  demo/mesh/mesh_brick_2d_10_forman_cbd_star.txt\
  demo/mesh/mesh_brick_2d_10_forman_laplacian.txt\
  demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.txt\
  demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux.txt\

.PHONY: demo_mesh_brick_regular_2d_10
demo_mesh_brick_regular_2d_10: $(DEMO_MESH_BRICK_REGULAR_2D_10) | demo/mesh

demo/mesh/mesh_brick_2d_10.txt:\
	  bin/mesh_brick_regular$(.EXE) | demo/mesh
	$< 2 10 > $@

demo/mesh/mesh_brick_2d_10_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_10.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_10_forman.txt:\
	  bin/forman_boundary$(.EXE)\
	  demo/mesh/mesh_brick_2d_10.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_10_forman_boundary.txt:\
	  bin/mesh_boundary$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt | demo/mesh
	$< --raw < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_10_forman_cbd.txt:\
	  bin/mesh_coboundary$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt | demo/mesh
	$< --raw < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_10_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_2d_10_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_10_forman_inner.txt:\
	  bin/mesh_qc_inner_direct$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_10_forman_cbd_star.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_inner.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_10_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_cbd_star.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.txt:\
	  bin/diffusion_continuous$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_cbd.txt\
	  demo/mesh/mesh_brick_2d_10_forman_cbd_star.txt\
	  build/diffusion_continuous_p4.o | demo/mesh
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^)\
	  diffusion_continuous_p4 0.0001 4000 > $@

demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux.txt:\
	  bin/diffusion_discrete_calculate_flux$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.txt \
	  | demo/mesh
	$< $(word 2, $^) 4000 $(word 3, $^) > $@

DEMO_MESH_BRICK_REGULAR_2 :=\
  $(DEMO_MESH_BRICK_REGULAR_2D_1)\
  $(DEMO_MESH_BRICK_REGULAR_2D_2)\
  $(DEMO_MESH_BRICK_REGULAR_2D_4)\
  $(DEMO_MESH_BRICK_REGULAR_2D_5)\
  $(DEMO_MESH_BRICK_REGULAR_2D_10)\

DEMO_MESH_TWO_TRIANGLES := \
  demo/mesh/mesh_two_triangles_vol.txt\
  demo/mesh/mesh_two_triangles_forman.txt\
  demo/mesh/mesh_two_triangles_forman_vol.txt\
  demo/mesh/mesh_two_triangles_forman_metric.txt\
  demo/mesh/mesh_two_triangles_forman_inner.txt\
  demo/mesh/mesh_two_triangles_forman_cbd_star.txt\
  demo/mesh/mesh_two_triangles_forman_laplacian.txt\
  demo/mesh/mesh_two_triangles_forman_hodge_coeff.txt\
  demo/mesh/mesh_two_triangles_forman_hodge.txt\
  demo/mesh/mesh_two_triangles_forman_node_curvature.txt\
  demo/mesh/mesh_two_triangles_forman_metric_corrected.txt\
  demo/mesh/mesh_two_triangles_forman_inner_corrected.txt\
  demo/mesh/mesh_two_triangles_forman_cbd_star_corrected.txt\
  demo/mesh/mesh_two_triangles_forman_laplacian_corrected.txt\
  demo/mesh/mesh_two_triangles_forman_laplacian_corrected_matrix_form.txt\
  demo/mesh/mesh_two_triangles_forman_laplacian_corrected_symmetric.txt\
  demo/mesh/mesh_two_triangles_forman_laplacian_corrected_symmetric_matrix_form.txt\
  demo/mesh/mesh_two_triangles_forman_hodge_corrected.txt\
  demo/mesh/mesh_two_triangles_forman_laplace_equation_non_grid.txt\

.PHONY: demo_mesh_two_triangles
demo_mesh_two_triangles: $(DEMO_MESH_TWO_TRIANGLES) | demo/mesh

demo/mesh/mesh_two_triangles_vol.txt:\
	  bin/mesh_measure$(.EXE)\
	  data/mesh/mesh_two_triangles.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_two_triangles_forman.txt:\
	  bin/forman_boundary$(.EXE)\
	  data/mesh/mesh_two_triangles.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_two_triangles_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_two_triangles_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman.txt\
	  demo/mesh/mesh_two_triangles_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_two_triangles_forman_inner.txt:\
	  bin/mesh_qc_inner_direct$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman.txt\
	  demo/mesh/mesh_two_triangles_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_two_triangles_forman_cbd_star.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman.txt\
	  demo/mesh/mesh_two_triangles_forman_inner.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_two_triangles_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman.txt\
	  demo/mesh/mesh_two_triangles_forman_cbd_star.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_two_triangles_forman_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_two_triangles_forman_hodge.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman.txt\
	  demo/mesh/mesh_two_triangles_forman_inner.txt\
	  demo/mesh/mesh_two_triangles_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_two_triangles_forman_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_two_triangles_forman_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman.txt\
	  demo/mesh/mesh_two_triangles_forman_vol.txt\
	  demo/mesh/mesh_two_triangles_forman_node_curvature.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_two_triangles_forman_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman.txt\
	  demo/mesh/mesh_two_triangles_forman_vol.txt\
	  demo/mesh/mesh_two_triangles_forman_metric_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_two_triangles_forman_cbd_star_corrected.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman.txt\
	  demo/mesh/mesh_two_triangles_forman_inner_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_two_triangles_forman_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman.txt\
	  demo/mesh/mesh_two_triangles_forman_cbd_star_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_two_triangles_forman_laplacian_corrected_matrix_form.txt:\
	  bin/matrix_sparse_file_print$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman_laplacian_corrected.txt | demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_two_triangles_forman_laplacian_corrected_symmetric.txt:\
	  bin/matrix_sparse_laplacian_symmetric$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman_laplacian_corrected.txt\
	  demo/mesh/mesh_two_triangles_forman_inner_corrected.txt | demo/mesh
	$< 2 $(word 2, $^) --raw $(word 3, $^) --raw --raw > $@

demo/mesh/mesh_two_triangles_forman_laplacian_corrected_symmetric_matrix_form.txt:\
	  bin/matrix_sparse_file_print$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman_laplacian_corrected_symmetric.txt  | demo/mesh
	$< --matrix-form-curly -list 3 < $(word 2, $^) > $@

demo/mesh/mesh_two_triangles_forman_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman.txt\
	  demo/mesh/mesh_two_triangles_forman_inner_corrected.txt\
	  demo/mesh/mesh_two_triangles_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_two_triangles_forman_laplace_equation_non_grid.txt:\
	  bin/mesh_qc_laplace_equation_solve_non_grid$(.EXE)\
	  demo/mesh/mesh_two_triangles_forman.txt\
	  demo/mesh/mesh_two_triangles_forman_laplacian_corrected_symmetric.txt\
	  demo/mesh/mesh_two_triangles_forman_inner_corrected.txt | demo/mesh
	$< $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^) --raw\
	> $@ --raw

DEMO_MESH_TRIANGLE_AND_SQUARE := \
  demo/mesh/mesh_triangle_and_square_vol.txt\
  demo/mesh/mesh_triangle_and_square_forman.txt\
  demo/mesh/mesh_triangle_and_square_forman_vol.txt\
  demo/mesh/mesh_triangle_and_square_forman_metric.txt\
  demo/mesh/mesh_triangle_and_square_forman_inner.txt\
  demo/mesh/mesh_triangle_and_square_forman_cbd_star.txt\
  demo/mesh/mesh_triangle_and_square_forman_laplacian.txt\
  demo/mesh/mesh_triangle_and_square_forman_hodge_coeff.txt\
  demo/mesh/mesh_triangle_and_square_forman_hodge.txt\
  demo/mesh/mesh_triangle_and_square_forman_node_curvature.txt\
  demo/mesh/mesh_triangle_and_square_forman_metric_corrected.txt\
  demo/mesh/mesh_triangle_and_square_forman_inner_corrected.txt\
  demo/mesh/mesh_triangle_and_square_forman_cbd_star_corrected.txt\
  demo/mesh/mesh_triangle_and_square_forman_laplacian_corrected.txt\
  demo/mesh/mesh_triangle_and_square_forman_hodge_corrected.txt\

.PHONY: demo_mesh_triangle_and_square
demo_mesh_triangle_and_square: $(DEMO_MESH_TRIANGLE_AND_SQUARE) | demo/mesh

demo/mesh/mesh_triangle_and_square_vol.txt:\
	  bin/mesh_measure$(.EXE)\
	  data/mesh/mesh_triangle_and_square.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_triangle_and_square_forman.txt:\
	  bin/forman_boundary$(.EXE)\
	  data/mesh/mesh_triangle_and_square.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_triangle_and_square_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_triangle_and_square_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_triangle_and_square_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_triangle_and_square_forman.txt\
	  demo/mesh/mesh_triangle_and_square_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_triangle_and_square_forman_inner.txt:\
	  bin/mesh_qc_inner_direct$(.EXE)\
	  demo/mesh/mesh_triangle_and_square_forman.txt\
	  demo/mesh/mesh_triangle_and_square_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_triangle_and_square_forman_cbd_star.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_triangle_and_square_forman.txt\
	  demo/mesh/mesh_triangle_and_square_forman_inner.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_triangle_and_square_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_triangle_and_square_forman.txt\
	  demo/mesh/mesh_triangle_and_square_forman_cbd_star.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_triangle_and_square_forman_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_triangle_and_square_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_triangle_and_square_forman_hodge.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_triangle_and_square_forman.txt\
	  demo/mesh/mesh_triangle_and_square_forman_inner.txt\
	  demo/mesh/mesh_triangle_and_square_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_triangle_and_square_forman_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_triangle_and_square_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_triangle_and_square_forman_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_triangle_and_square_forman.txt\
	  demo/mesh/mesh_triangle_and_square_forman_vol.txt\
	  demo/mesh/mesh_triangle_and_square_forman_node_curvature.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_triangle_and_square_forman_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_triangle_and_square_forman.txt\
	  demo/mesh/mesh_triangle_and_square_forman_vol.txt\
	  demo/mesh/mesh_triangle_and_square_forman_metric_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_triangle_and_square_forman_cbd_star_corrected.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_triangle_and_square_forman.txt\
	  demo/mesh/mesh_triangle_and_square_forman_inner_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_triangle_and_square_forman_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_triangle_and_square_forman.txt\
	  demo/mesh/mesh_triangle_and_square_forman_cbd_star_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_triangle_and_square_forman_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_triangle_and_square_forman.txt\
	  demo/mesh/mesh_triangle_and_square_forman_inner_corrected.txt\
	  demo/mesh/mesh_triangle_and_square_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

DEMO_MESH_SQUARE := \
  demo/mesh/mesh_square_2.txt\
  demo/mesh/mesh_square_4.txt\
  demo/mesh/mesh_square_8.txt\
  demo/mesh/mesh_square_8_cbd.txt\
  demo/mesh/mesh_square_8_vol.txt\
  demo/mesh/mesh_square_8_inner.txt\
  demo/mesh/mesh_square_8_cbd_star.txt\
  demo/mesh/mesh_square_8_diffusion_continuous_p5_temperature.txt\

.PHONY: demo_mesh_square
demo_mesh_square: $(DEMO_MESH_SQUARE) | demo/mesh

# demo/mesh/mesh_square_vol.txt:\
# 	  bin/mesh_qc_vol$(.EXE)\
# 	  demo/mesh/mesh_square.txt | demo/mesh
# 	 $< < $(word 2, $^) > $@

demo/mesh/mesh_square_2.txt:\
	  bin/forman_boundary$(.EXE)\
	  data/mesh/mesh_square.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_square_4.txt:\
	  bin/forman_boundary$(.EXE)\
	  demo/mesh/mesh_square_2.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_square_8.txt:\
	  bin/forman_boundary$(.EXE)\
	  demo/mesh/mesh_square_4.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_square_8_cbd.txt:\
	  bin/mesh_coboundary$(.EXE)\
	  demo/mesh/mesh_square_8.txt | demo/mesh
	$< --raw < $(word 2, $^) > $@

demo/mesh/mesh_square_8_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_square_8.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_square_8_inner.txt:\
	  bin/mesh_qc_inner_direct$(.EXE)\
	  demo/mesh/mesh_square_8.txt\
	  demo/mesh/mesh_square_8_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_square_8_cbd_star.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_square_8.txt\
	  demo/mesh/mesh_square_8_inner.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_square_8_diffusion_continuous_p5_temperature.txt:\
	  bin/diffusion_continuous$(.EXE)\
	  demo/mesh/mesh_square_8.txt\
	  demo/mesh/mesh_square_8_cbd.txt\
	  demo/mesh/mesh_square_8_cbd_star.txt\
	  build/diffusion_continuous_p5.o | demo/mesh
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^)\
	  diffusion_continuous_p5 0.001 4000 > $@

# demo/mesh/mesh_square_8_diffusion_continuous_p5_temperature.txt:\
# 	  bin/diffusion_continuous_to_steady_state$(.EXE)\
# 	  demo/mesh/mesh_square_8.txt\
# 	  demo/mesh/mesh_square_8_cbd.txt\
# 	  demo/mesh/mesh_square_8_cbd_star.txt\
# 	  build/diffusion_continuous_p5.o | demo/mesh
# 	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^)\
# 	  diffusion_continuous_p5 0.001 > $@

# d = 3
DEMO_MESH_BRICK_REGULAR_3D :=\
  demo_mesh_brick_regular_3d_1\
  demo_mesh_brick_regular_3d_2\
  demo_mesh_brick_regular_3d_5\

.PHONY: demo_mesh_brick_regular_3d
demo_mesh_brick_regular_3d: $(DEMO_MESH_BRICK_REGULAR_3D) | demo/mesh

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
demo_mesh_brick_regular_3d_1: $(DEMO_MESH_BRICK_REGULAR_3D_1) | demo/mesh

demo/mesh/mesh_brick_3d_1.txt:\
	  bin/mesh_brick_regular$(.EXE) | demo/mesh
	$< 3 1 > $@

demo/mesh/mesh_brick_3d_1_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_3d_1.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_1_forman.txt:\
	  bin/forman_boundary$(.EXE)\
	  demo/mesh/mesh_brick_3d_1.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_1_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_1_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_1_forman_inner.txt:\
	  bin/mesh_qc_inner_direct$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_1_forman_cbd_star.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_inner.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_1_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_cbd_star.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_1_forman_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_1_forman_hodge.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_inner.txt\
	  demo/mesh/mesh_brick_3d_1_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_1_forman_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_1_forman_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_1_forman_node_curvature.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_1_forman_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_1_forman_metric_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_1_forman_cbd_star_corrected.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_inner_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_1_forman_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_cbd_star_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_1_forman_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_3d_1_forman.txt\
	  demo/mesh/mesh_brick_3d_1_forman_inner_corrected.txt\
	  demo/mesh/mesh_brick_3d_1_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

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
demo_mesh_brick_regular_3d_2: $(DEMO_MESH_BRICK_REGULAR_3D_2) | demo/mesh

demo/mesh/mesh_brick_3d_2.txt:\
	  bin/mesh_brick_regular$(.EXE) | demo/mesh
	$< 3 2 > $@

demo/mesh/mesh_brick_3d_2_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_3d_2.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_2_forman.txt:\
	  bin/forman_boundary$(.EXE)\
	  demo/mesh/mesh_brick_3d_2.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_2_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt | demo/mesh
	 $< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_2_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_2_forman_inner.txt:\
	  bin/mesh_qc_inner_direct$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_2_forman_cbd_star.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_inner.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_2_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_cbd_star.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_2_forman_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_2_forman_hodge.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_inner.txt\
	  demo/mesh/mesh_brick_3d_2_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_2_forman_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_2_forman_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_2_forman_node_curvature.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_2_forman_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_2_forman_metric_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_2_forman_cbd_star_corrected.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_inner_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_2_forman_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_cbd_star_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_2_forman_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_3d_2_forman.txt\
	  demo/mesh/mesh_brick_3d_2_forman_inner_corrected.txt\
	  demo/mesh/mesh_brick_3d_2_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

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
demo_mesh_brick_regular_3d_5: $(DEMO_MESH_BRICK_REGULAR_3D_5) | demo/mesh

demo/mesh/mesh_brick_3d_5.txt:\
	  bin/mesh_brick_regular$(.EXE) | demo/mesh
	$< 3 5 > $@

demo/mesh/mesh_brick_3d_5_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_3d_5.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_5_forman.txt:\
	  bin/forman_boundary$(.EXE)\
	  demo/mesh/mesh_brick_3d_5.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_5_forman_vol.txt:\
	  bin/mesh_qc_vol$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_5_forman_metric.txt:\
	  bin/mesh_qc_metric$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_5_forman_inner.txt:\
	  bin/mesh_qc_inner_direct$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_vol.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_5_forman_cbd_star.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_inner.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_5_forman_laplacian.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_cbd_star.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_5_forman_hodge_coeff.txt:\
	  bin/mesh_qc_hodge_coeff$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_5_forman_hodge.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_inner.txt\
	  demo/mesh/mesh_brick_3d_5_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_5_forman_node_curvature.txt:\
	  bin/mesh_node_curvature$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt | demo/mesh
	$< < $(word 2, $^) > $@

demo/mesh/mesh_brick_3d_5_forman_metric_corrected.txt:\
	  bin/mesh_qc_metric_corrected$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_5_forman_node_curvature.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_5_forman_inner_corrected.txt:\
	  bin/mesh_qc_inner$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_vol.txt\
	  demo/mesh/mesh_brick_3d_5_forman_metric_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_5_forman_cbd_star_corrected.txt:\
	  bin/mesh_qc_coboundary_star$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_inner_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_5_forman_laplacian_corrected.txt:\
	  bin/mesh_qc_laplacian$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_cbd_star_corrected.txt | demo/mesh
	$^ > $@

demo/mesh/mesh_brick_3d_5_forman_hodge_corrected.txt:\
	  bin/mesh_qc_hodge$(.EXE)\
	  demo/mesh/mesh_brick_3d_5_forman.txt\
	  demo/mesh/mesh_brick_3d_5_forman_inner_corrected.txt\
	  demo/mesh/mesh_brick_3d_5_forman_hodge_coeff.txt | demo/mesh
	$^ > $@

DEMO_MESH_BRICK_REGULAR_3 :=\
  $(DEMO_MESH_BRICK_REGULAR_3D_1)\
  $(DEMO_MESH_BRICK_REGULAR_3D_2)\
  $(DEMO_MESH_BRICK_REGULAR_3D_5)\

# d = 4
DEMO_MESH_BRICK_REGULAR_4D := demo_mesh_brick_regular_4d_2

.PHONY: demo_mesh_brick_regular_4d
demo_mesh_brick_regular_4d: $(DEMO_MESH_BRICK_REGULAR_4D) | demo/mesh

# d = 4, n = 2
DEMO_MESH_BRICK_REGULAR_4D_2 := demo/mesh/mesh_brick_4d_2.txt

.PHONY: demo_mesh_brick_regular_4d_2
demo_mesh_brick_regular_4d_2: $(DEMO_MESH_BRICK_REGULAR_4D_2) | demo/mesh

demo/mesh/mesh_brick_4d_2.txt: bin/mesh_brick_regular$(.EXE) | demo/mesh
	$< 4 2 > $@

DEMO_MESH_BRICK_REGULAR_4 := $(DEMO_MESH_BRICK_REGULAR_4D_2)

DEMO_MESH_BRICK_REGULAR_ALL :=\
  $(DEMO_MESH_BRICK_REGULAR_2)\
  $(DEMO_MESH_TWO_TRIANGLES)\
  $(DEMO_MESH_TRIANGLE_AND_SQUARE)\
  $(DEMO_MESH_SQUARE)\
  $(DEMO_MESH_BRICK_REGULAR_3)\
  $(DEMO_MESH_BRICK_REGULAR_4)\

.PHONY: demo_mesh_clean
demo_mesh_clean:
	-$(RM) $(DEMO_MESH_BRICK_REGULAR_ALL) $(DEMO_MESH_TWO_TRIANGLES)
	-$(RM) -r demo/mesh 
