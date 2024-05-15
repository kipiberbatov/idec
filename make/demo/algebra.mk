DEMO_ALGEBRA := \
  demo/algebra/matrix_sparse_remove_res.txt\
  demo/algebra/matrix_sparse_remove_symmetric_res.txt\
  demo/algebra/matrix_sparse_4_4_copy.txt\
  demo/algebra/matrix_sparse_4_5_matrix_form_by_parts.txt\
  demo/algebra/matrix_sparse_4_5_twice.txt\
  demo/algebra/matrix_sparse_4_5_times_5_4.txt\
  demo/algebra/matrix_sparse_4_5_transpose.txt\
  demo/algebra/matrix_sparse_diagonal_3_linear_solve_double_3.txt\
  demo/algebra/matrix_sparse_4_4_linear_solve_double_4.txt\
  demo/algebra/matrix_sparse_4_4_vector_multiply_add_double_4.txt\
  demo/algebra/matrix_sparse_4_4_multiply_with_diagonal_matrix_double_4.txt\
  demo/algebra/matrix_determinant_example.txt\
  demo/algebra/matrix_times_transpose_example.txt\
  demo/algebra/matrix_inverse_example.txt\
  demo/algebra/matrix_times_vector_example.txt\
  demo/algebra/matrix_moore_penrose_inverse_example.txt\

.PHONY: demo_algebra
demo_algebra: bin_algebra $(DEMO_ALGEBRA) | demo/algebra

demo/algebra: | demo
	mkdir -p $@

demo/algebra/matrix_sparse_remove_res.txt:\
	  bin/matrix_sparse_remove$(.EXE)\
	  data/algebra/matrix_sparse_remove_ex.txt | demo/algebra
	$< < $(word 2, $^) > $@

demo/algebra/matrix_sparse_remove_symmetric_res.txt:\
	  bin/matrix_sparse_remove_symmetric$(.EXE)\
	  data/algebra/matrix_sparse_5_5.txt\
	  data/algebra/rows.txt | demo/algebra
	$< $(word 2, $^) --raw $(word 3, $^) --raw > $@ --raw

demo/algebra/matrix_sparse_4_4_copy.txt:\
	  bin/matrix_sparse_copy$(.EXE)\
	  data/algebra/matrix_sparse_4_4.txt | demo/algebra
	$< --raw $(word 2, $^) --matrix-form-curly > $@

demo/algebra/matrix_sparse_4_5_matrix_form_by_parts.txt:\
	  bin/matrix_sparse_part$(.EXE)\
	  data/algebra/matrix_sparse_4_5_1.txt | demo/algebra
	$< < $(word 2, $^) > $@

demo/algebra/matrix_sparse_4_5_twice.txt:\
	  bin/matrix_sparse_linear_combination$(.EXE)\
	  data/algebra/matrix_sparse_4_5_1.txt\
	  data/algebra/matrix_sparse_4_5_2.txt | demo/algebra
	$< $(word 2, $^) --raw $(word 3, $^) --raw 1 1 --matrix-form-curly > $@

demo/algebra/matrix_sparse_4_5_times_5_4.txt:\
	  bin/matrix_sparse_product$(.EXE)\
	  data/algebra/matrix_sparse_4_5_1.txt\
	  data/algebra/matrix_sparse_5_4_1.txt | demo/algebra
	$< $(word 2, $^) --raw $(word 3, $^) --raw --matrix-form-curly > $@

demo/algebra/matrix_sparse_4_5_transpose.txt:\
	  bin/matrix_sparse_transpose$(.EXE)\
	  data/algebra/matrix_sparse_4_5_1.txt | demo/algebra
	$< --raw $(word 2, $^) --matrix-form-curly > $@

demo/algebra/matrix_sparse_diagonal_3_linear_solve_double_3.txt:\
	  bin/matrix_sparse_linear_solve$(.EXE)\
	  data/algebra/matrix_sparse_diagonal_3.txt\
	  data/algebra/double_3.txt | demo/algebra
	$< $(word 2, $^) --raw $(word 3, $^) --cholesky > $@

demo/algebra/matrix_sparse_4_4_linear_solve_double_4.txt:\
	  bin/matrix_sparse_linear_solve$(.EXE)\
	  data/algebra/matrix_sparse_4_4.txt\
	  data/algebra/double_4.txt | demo/algebra
	$< $(word 2, $^) --raw $(word 3, $^) --lu > $@

demo/algebra/matrix_sparse_4_4_vector_multiply_add_double_4.txt:\
	  bin/matrix_sparse_vector_multiply_add$(.EXE)\
	  data/algebra/matrix_sparse_4_4.txt\
	  data/algebra/double_4.txt | demo/algebra
	$< $(word 2, $^) $(word 3, $^) > $@

demo/algebra/matrix_sparse_4_4_multiply_with_diagonal_matrix_double_4.txt:\
	  bin/matrix_sparse_multiply_with_diagonal_matrix$(.EXE)\
	  data/algebra/matrix_sparse_4_4.txt\
	  data/algebra/double_4.txt | demo/algebra
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw > $@

demo/algebra/matrix_determinant_example.txt: bin/matrix_determinant | demo/algebra
	$< > $@

demo/algebra/matrix_times_transpose_example.txt: bin/matrix_times_transpose | demo/algebra
	$< > $@

demo/algebra/matrix_inverse_example.txt: bin/matrix_inverse | demo/algebra
	$< > $@

demo/algebra/matrix_times_vector_example.txt: bin/matrix_times_vector | demo/algebra
	$< > $@

demo/algebra/matrix_moore_penrose_inverse_example.txt:\
	   bin/matrix_moore_penrose_inverse | demo/algebra
	$< > $@

.PHONY: demo_algebra_clean
demo_algebra_clean:
	-$(RM) $(DEMO_ALGEBRA)
	-$(RM) -r demo/algebra
