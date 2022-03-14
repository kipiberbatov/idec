DEMO_ALGEBRA := \
  demo/algebra/cs_remove_res.txt\
  demo/algebra/cs_remove_symmetric_res.txt\
  demo/algebra/cs_4_5_matrix_form_by_parts.txt\
  demo/algebra/matrix_sparse_4_5_twice.txt\
  demo/algebra/matrix_sparse_4_5_times_5_4.txt\
  demo/algebra/matrix_sparse_4_5_transpose.txt\
  demo/algebra/matrix_sparse_diagonal_3_linear_solve_double_3.txt\

.PHONY: demo_algebra
demo_algebra: bin $(DEMO_ALGEBRA)

demo/algebra/cs_remove_res.txt:\
	  bin/cs_remove$(.EXE)\
	  demo/algebra/cs_remove_ex.txt
	$< < $(word 2, $^) > $@
	
demo/algebra/cs_remove_symmetric_res.txt:\
	  bin/cs_remove_symmetric$(.EXE)\
	  demo/algebra/cs_remove_symmetric_ex.txt
	$< < $(word 2, $^) > $@

demo/algebra/cs_4_5_matrix_form_by_parts.txt:\
	  bin/cs_part$(.EXE)\
	  demo/algebra/cs_4_5.txt
	$< < $(word 2, $^) > $@

demo/algebra/matrix_sparse_4_5_twice.txt:\
	  bin/matrix_sparse_linear_combination$(.EXE)\
	  demo/algebra/matrix_sparse_4_5_1.txt\
	  demo/algebra/matrix_sparse_4_5_2.txt
	$< $(word 2, $^) --raw $(word 3, $^) --raw 1 1 --matrix-form-curly > $@

demo/algebra/matrix_sparse_4_5_times_5_4.txt:\
	  bin/matrix_sparse_product$(.EXE)\
	  demo/algebra/matrix_sparse_4_5_1.txt\
	  demo/algebra/matrix_sparse_5_4_1.txt
	$< $(word 2, $^) --raw $(word 3, $^) --raw --matrix-form-curly > $@

demo/algebra/matrix_sparse_4_5_transpose.txt:\
	  bin/matrix_sparse_transpose$(.EXE)\
	  demo/algebra/matrix_sparse_4_5_1.txt
	$< $(word 2, $^) --raw --matrix-form-curly > $@

demo/algebra/matrix_sparse_diagonal_3_linear_solve_double_3.txt:\
	  bin/matrix_sparse_linear_solve$(.EXE)\
	  demo/algebra/matrix_sparse_diagonal_3.txt\
	  demo/algebra/double_3.txt
	$< $(word 2, $^) --raw $(word 3, $^) --cholesky > $@

.PHONY: demo_algebra_clean
demo_algebra_clean:
	-$(RM) $(DEMO_ALGEBRA)
